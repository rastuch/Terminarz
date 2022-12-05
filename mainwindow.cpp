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

void MainWindow::on_calendarWidget_selectionChanged()
{
    loadCalendarTaskList();
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->time_dashboard->setText(text);
}

void MainWindow::receiveRefreshSingal()
{
    ui->calendarTaskList->clear();
    loadCalendarTaskList();
    ui->dashboardTaskList->clear();
    loadDashboardTaskList();
}

void MainWindow::clearMarksForMonth(QDate date){
    for(int i = 1; i <= date.daysInMonth(); i++) {
       QDate currentDay = date;
       currentDay.setDate(date.year(),date.month(),i);
       bool isWeekend = currentDay.dayOfWeek() == 6 || currentDay.dayOfWeek() == 7;
       ui->calendarWidget->setDateTextFormat(currentDay , dayTaskTextFormat(false,isWeekend));
    }
};

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

void MainWindow::on_addButton_clicked()
{       auto emptyTaskWithSelectedDay = new Task();
        emptyTaskWithSelectedDay->setDate(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
        auto addNewTaskPopup = new EditTaskPopUp(this,emptyTaskWithSelectedDay,true);
        QObject::connect(addNewTaskPopup->findChild<QPushButton *>("confirmEditButton"), &QPushButton::clicked, this, &MainWindow::receiveRefreshSingal);
        addNewTaskPopup->setModal(true);
        addNewTaskPopup->exec();
}

