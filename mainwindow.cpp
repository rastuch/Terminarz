#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "task.h"
#include <QList>
#include <QListWidget>
#include <QCalendarWidget>
#include <TaskService.h>
#include <QDate>
#include <QTimer>
#include <dashboardtask.h>
#include <deletetaskpopup.h>
#include <edittaskpopup.h>
#include <QDebug>
#include <QTableWidget>
#include <QListWidgetItem>
#include <QTextCharFormat>

/*!
 * @brief Tworzy format tekstu dla elementu kalendarza.
 * @param haveTask Określa, czy dany dzień ma zadania.
 * @param isWeekend Określa, czy dany dzień jest dniem weekendu.
 * @return Zwraca obiekt QTextCharFormat z odpowiednio ustawionym podkreśleniem, kolorem i innymi atrybutami.
 */

QTextCharFormat dayTaskTextFormat(bool haveTask,bool isWeekend){
    QTextCharFormat format;
    if(haveTask){
        format.setUnderlineStyle(QTextCharFormat::SingleUnderline);
        format.setForeground(QColor("orange"));
    }else{
        format.setUnderlineStyle(QTextCharFormat::NoUnderline);
        if(isWeekend){
            format.setForeground(QColor("red"));
        }else{
            format.setForeground(QColor("white"));
        }
    }
    return format;
}
/*!
 * @class MainWindow
 * @brief Klasa MainWindow to główne okno aplikacji.
 * Klasa MainWindow dziedziczy po QMainWindow i posiada interfejs użytkownika (UI) utworzony przez Qt Designer.
 * Posiada publiczny konstruktor, który przyjmuje wskaźnik na nadrzędny widżet, oraz publiczny destruktor.
 * W konstruktorze tworzony jest obiekt interfejs użytkownika, ładowane są listy zadań z bazy danych oraz
 * uruchamiany jest zegar, który co sekundę wyświetla aktualny czas.
 * @brief Publiczny konstruktor klasy MainWindow.
 * @param parent Wskaźnik na nadrzędny widżet.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("calendar.sqlite");
    loadDashboardTaskList();
    loadCalendarTaskList();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
     timer->start(1000);
}

/*!
 * @brief Publiczny destruktor klasy MainWindow.
 */

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * @brief Wczytuje listę zadań na głównym panelu aplikacji.
 *
 * Funkcja pobiera listę zadań z bazy danych za pomocą metody `TaskService::getThisWeekTaskList`,
 * a następnie iteruje przez elementy tej listy i tworzy dla nich obiekty DashboardTask.
 * Są one podłączane do sygnałów emitowanych przez klasę DashboardTask i dodawane do listy widgetu QListWidget.
 * Funkcja także wywołuje metodę `markDaysWithTask`, która oznacza w kalendarzu dni, w których znajdują się zadania.
 */
void MainWindow::loadDashboardTaskList()
{
    QList<Task> taskList = TaskService::getThisWeekTaskList(db);
    foreach(Task currentTask, taskList){
      auto taskToList = new DashboardTask(this,&currentTask);
      QObject::connect(taskToList, &DashboardTask::emitDeleteTaskAndRefreshList, this,&MainWindow::receiveRefreshSingal);
      QObject::connect(taskToList, &DashboardTask::emitEditTask, this,&MainWindow::receiveRefreshSingal);
      auto item = new QListWidgetItem();
      item->setSizeHint(ui->dashboardTaskList->sizeHint());
      ui->dashboardTaskList->addItem(item);
      ui->dashboardTaskList->setItemWidget(item,taskToList);
      markDaysWithTask(ui->calendarWidget->selectedDate());
    }
}

/*!
 * @brief Wczytuje listę zadań dla danego dnia w kalendarzu z bazy danych.
 *
 * Funkcja pobiera listę zadań dla danego dnia za pomocą metody `TaskService::getAllTasksByDate`,
 * a następnie iteruje przez elementy tej listy i tworzy dla nich obiekty DashboardTask.
 * Są one podłączane do sygnałów emitowanych przez klasę DashboardTask i dodawane do listy widgetu QListWidget.
 * Funkcja także wywołuje metodę `markDaysWithTask`, która oznacza w kalendarzu dni, w których znajdują się zadania.
 */
void MainWindow::loadCalendarTaskList()
{
    QList<Task> taskList = TaskService::getAllTasksByDate(db, ui->calendarWidget->selectedDate());
    ui->calendarTaskList->clear();
    foreach(Task currentTask, taskList){
            auto taskToList = new DashboardTask(this,&currentTask);
            QObject::connect(taskToList, &DashboardTask::emitDeleteTaskAndRefreshList, this,&MainWindow::receiveRefreshSingal);
            QObject::connect(taskToList, &DashboardTask::emitEditTask, this,&MainWindow::receiveRefreshSingal);
            auto item = new QListWidgetItem();
            item->setSizeHint(ui->calendarTaskList->sizeHint());
            ui->calendarTaskList->addItem(item);
            ui->calendarTaskList->setItemWidget(item,taskToList);
            markDaysWithTask(ui->calendarWidget->selectedDate());
    }
}
/*!
 * @brief Slot, który jest wywoływany po zmianie wyboru w kalendarzu.
 *
 * Slot wywołuje metodę `loadCalendarTaskList`, która odświeża listę zadań dla nowo wybranego dnia w kalendarzu.
 */
void MainWindow::on_calendarWidget_selectionChanged()
{
    loadCalendarTaskList();
}

/*!
 * @brief Wyświetla aktualny czas na głównym panelu aplikacji.
 *
 * Funkcja pobiera aktualny czas za pomocą metody `QTime::currentTime`,
 * a następnie konwertuje go do formatu "hh:mm" i ustawia jako tekst widgetu `time_dashboard`.
 * Co drugą sekundę, kropka między godziną a minutą jest usuwana, co daje efekt "migającego" czasu.
 */
void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->time_dashboard->setText(text);
}
/*!
 * @brief Slot, który jest wywoływany po edycji lub usunięciu zadania.
 *
 * Slot czyści listy zadań z głównego panelu oraz z kalendarza,
 * a następnie odświeża je przez wywołanie metod `loadCalendarTaskList` oraz `loadDashboardTaskList`.
 */
void MainWindow::receiveRefreshSingal()
{
    ui->calendarTaskList->clear();
    loadCalendarTaskList();
    ui->dashboardTaskList->clear();
    loadDashboardTaskList();
}
/*!
 * @brief Usuwa oznaczenia dni z kalendarza dla danego miesiąca.
 *
 * Funkcja iteruje przez dni danego miesiąca, a dla każdego z nich ustawia format tekstu na domyślny
 * (bez podkreślenia, kolor biały lub czerwony dla weekendu).
 *
 * @param date Data, dla której należy usunąć oznaczenia dni.
 */
void MainWindow::clearMarksForMonth(QDate date){
    for(int i = 1; i <= date.daysInMonth(); i++) {
       QDate currentDay = date;
       currentDay.setDate(date.year(),date.month(),i);
       bool isWeekend = currentDay.dayOfWeek() == 6 || currentDay.dayOfWeek() == 7;
       ui->calendarWidget->setDateTextFormat(currentDay , dayTaskTextFormat(false,isWeekend));
    }
};
/*!
 * @brief Oznacza dni z zadaniami w kalendarzu.
 *
 * Funkcja usuwa oznaczenia dni dla bieżącego, poprzedniego i następnego miesiąca przez wywołanie metody `clearMarksForMonth`.
 * Następnie pobiera listę wszystkich zadań z bazy danych i iteruje przez nie,
 * ustawiając dla każdego z nich oznaczenie dnia za pomocą metody `setDateTextFormat`.
 *
 * @param currentDate Data, dla której należy oznaczać dni.
 */

void MainWindow::markDaysWithTask(QDate currentDate){
     auto currentMonth = currentDate;
     auto prevMonth = currentDate.addMonths(-1);
     auto nextMonth = currentDate.addMonths(1);
     clearMarksForMonth(currentMonth);
     clearMarksForMonth(prevMonth);
     clearMarksForMonth(nextMonth);

     auto allTasks = TaskService::getAllTasks(db);
     foreach(Task currentTask, allTasks){
         if(currentTask.getQDate().isValid()){ 
                ui->calendarWidget->setDateTextFormat(currentTask.getQDate() , dayTaskTextFormat(true,false));
         }
     }
}

/*!
 * @brief Slot, który jest wywoływany po kliknięciu przycisku dodawania zadania.
 *
 * Slot tworzy puste zadanie z datą aktualnie wybraną w kalendarzu oraz wyświetla okno edycji zadania.
 * Po potwierdzeniu edycji zadania przez użytkownika, zostaje wyemitowany sygnał `clicked` dla przycisku `confirmEditButton`,
 * który jest połączony z slotem `receiveRefreshSingal`.
 * Okno edycji jest modalne i blokuje interakcję z głównym oknem aplikacji.
 */
void MainWindow::on_addButton_clicked()
{       auto emptyTaskWithSelectedDay = new Task();
        emptyTaskWithSelectedDay->setDate(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
        auto addNewTaskPopup = new EditTaskPopUp(this,emptyTaskWithSelectedDay,true);
        QObject::connect(addNewTaskPopup->findChild<QPushButton *>("confirmEditButton"), &QPushButton::clicked, this, &MainWindow::receiveRefreshSingal);
        addNewTaskPopup->setModal(true);
        addNewTaskPopup->exec();
}

