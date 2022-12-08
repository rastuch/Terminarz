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

/*! @class Klasa która dostarcza informacje o formatowaniu znaków
* @return  zwraca rodzaje elementów tekstowych
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
/*! @brief Funkcja listy inicjalizacyjnej
* @class QTimer zapewnia powtarzalne i pojedyncze liczniki czasu
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

MainWindow::~MainWindow()
{
    delete ui;
}

/*! @brief Główna funkcja zadań w kalendarzu ( dodawanie , edytowanie i usuwanie zadań )
* @class QList Przechowuje elementy na liście, która zapewnia szybki dostęp oparty na indeksie
 oraz wstawianie i usuwanie oparte na indeksie.
*/
void MainWindow::loadDashboardTaskList()
{
    QList<Task> taskList = TaskService::getThisWeekTaskList(db);
    foreach(Task currentTask, taskList){
      auto taskToList = new DashboardTask(this,&currentTask);
      QObject::connect(taskToList, &DashboardTask::emitDeleteTaskAndRefreshList, this,&MainWindow::receiveRefreshSingal);
      QObject::connect(taskToList, &DashboardTask::emitEditTask, this,&MainWindow::receiveRefreshSingal);
      auto item = new QListWidgetItem();
      item->setSizeHint(taskToList->sizeHint());
      ui->dashboardTaskList->addItem(item);
      ui->dashboardTaskList->setItemWidget(item,taskToList);
      markDaysWithTask(ui->calendarWidget->selectedDate());
    }
}

/*! @brief funkcja która pobiera liste zadań z bazy danych */
void MainWindow::loadCalendarTaskList()
{
    QList<Task> taskList = TaskService::getAllTasksByDate(db, ui->calendarWidget->selectedDate());
    ui->calendarTaskList->clear();
    foreach(Task currentTask, taskList){
            auto taskToList = new DashboardTask(this,&currentTask);
            QObject::connect(taskToList, &DashboardTask::emitDeleteTaskAndRefreshList, this,&MainWindow::receiveRefreshSingal);
            QObject::connect(taskToList, &DashboardTask::emitEditTask, this,&MainWindow::receiveRefreshSingal);
            auto item = new QListWidgetItem();
            item->setSizeHint(taskToList->sizeHint());
            ui->calendarTaskList->addItem(item);
            ui->calendarTaskList->setItemWidget(item,taskToList);
            markDaysWithTask(ui->calendarWidget->selectedDate());
    }
}
/*! @brief Funkcja która ładuje liste zadań */
void MainWindow::on_calendarWidget_selectionChanged()
{
    loadCalendarTaskList();
}

/*! @brief Funkcja która przedstawia czas w kalendarzu
 * @class QTime klasa podaje rzeczywisty czas
 * @class QString klasa pozwala na edycje czasu
*/
void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->time_dashboard->setText(text);
}
/*! @brief funkcja która ma za zdanie wyczyścić "zadania" w kalendarzu */
void MainWindow::receiveRefreshSingal()
{
    ui->calendarTaskList->clear();
    loadCalendarTaskList();
    ui->dashboardTaskList->clear();
    loadDashboardTaskList();
}
/*! @brief Funkcja która wyczyszcza date w kalendarzu */
void MainWindow::clearMarksForMonth(QDate date){
    for(int i = 1; i <= date.daysInMonth(); i++) {
       QDate currentDay = date;
       currentDay.setDate(date.year(),date.month(),i);
       bool isWeekend = currentDay.dayOfWeek() == 6 || currentDay.dayOfWeek() == 7;
       ui->calendarWidget->setDateTextFormat(currentDay , dayTaskTextFormat(false,isWeekend));
    }
};
/*! @brief Funkcja przedstawiająca date w kalendarzu */

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
