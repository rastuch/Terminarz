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
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE"); //Deklaracja jakiej bazy bedziemy uzywac w aplikacji
    db.setDatabaseName("calendar.sqlite"); //Ustawienie nazwy pliku z baza danych (baza danych powinna byc folderze budowania aplikacji a nie w plikach zrodlowych!)

    QList<Task> taskList = TaskService::getThisWeekTaskList(db);
         qDebug("odswierzanie");
    foreach(Task currentTask, taskList){
      auto taskToList = new DashboardTask(this,&currentTask);
      QObject::connect(taskToList, &DashboardTask::emitDeleteTaskAndRefreshList, this,&MainWindow::receiveRefreshSingal);
      auto item = new QListWidgetItem();
      item->setSizeHint(taskToList->sizeHint());
      ui->dashboardTaskList->addItem(item);
      ui->dashboardTaskList->setItemWidget(item,taskToList);

    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
     timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_selectionChanged() //Wywolanie funkcji po kliknieciu w dany dzien kalendarza
{
    QList<Task> taskList = TaskService::getAllTasks(db); // Zaciagniecie z bazy listy taskow
    QString selectedDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    ui->calendarTaskList->clear();
    foreach(Task currentTask, taskList){
        if(currentTask.getDate()==selectedDate){ //Sprawdzenie czy dla zaznaczonej daty jest jakis task
            auto taskToList = new DashboardTask(this,&currentTask);

            // Na etapie tworzenia obiektu DashboardTask dodajemy connect pomiedzy slotem &MainWindow::receiveRefreshSingal
            //i emitowanym sygnalem z taskToList (czyli tworzony obiekt DashboardTask), syganl ten to &DashboardTask::emitDeleteTaskAndRefreshList

            QObject::connect(taskToList, &DashboardTask::emitDeleteTaskAndRefreshList, this,&MainWindow::receiveRefreshSingal);
            auto item = new QListWidgetItem();
            item->setSizeHint(taskToList->sizeHint());
            ui->calendarTaskList->addItem(item);
            ui->calendarTaskList->setItemWidget(item,taskToList);
        }
    }
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->time_dashboard->setText(text);
}

void MainWindow::receiveSignal()
{
    qDebug("asdas");
}

void MainWindow::receiveRefreshSingal(){
    // po odebraniu informaji proponuje odswierzyc liste taskow na dashboardzie oraz pod kalendarzem
    qDebug("MAINWINDOW dostaje informacje o potrzebie odswierzenia listy");
}
