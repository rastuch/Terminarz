#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "task.h"
#include <QList>
#include <QListWidget>
#include <QCalendarWidget>
#include <TaskService.h>
#include <QDate>
#include <iostream>
#include <dashboardtask.h>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE"); //Deklaracja jakiej bazy bedziemy uzywac w aplikacji
    db.setDatabaseName("calendar.sqlite"); //Ustawienie nazwy pliku z baza danych (baza danych powinna byc folderze budowania aplikacji a nie w plikach zrodlowych!)
    QList<Task> taskList = TaskService::getAllTasks(db);
    foreach(Task currentTask, taskList){
      auto taskToList = new DashboardTask(this,&currentTask);
      auto item = new QListWidgetItem();
      item->setSizeHint(taskToList->sizeHint());
      ui->dashboardTaskList->addItem(item);
      ui->dashboardTaskList->setItemWidget(item,taskToList);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked() // Event okreslajacy co ma sie stac gdy nacisniemy na element pushButton
{
   QList<Task> taskList = TaskService::getAllTasks(db); // Zaciagniecie z bazy listy taskow

    QString response = ""; //obiekt textEdit przymuje tylko jeden QString wiec sobie go deklarujemy

    foreach(Task currentTask, taskList){ //iteracja po liscie, taka petla
        response += "Nazwa: " + currentTask.getTitle() +"\nOpis: "+ currentTask.getDescription() + "\nData: " + currentTask.getTime() + " " + currentTask.getDate() +"\n\n";
        //element ktory teraz jest przetwazany to currentTask, dopisujemy do response kazdy z naszych elementow juz ladnie opisany
    }
    ui->textEdit_2->setText(response); // wyswietlenie response na elemencie textEdit
}



void MainWindow::on_tabWidget_tabBarClicked(int index) //analogicznie do funkcji ponizej, wywolanie po kliknieciu w zakladke
{

}



void MainWindow::on_calendarWidget_selectionChanged() //Wywolanie funkcji po kliknieciu w dany dzien kalendarza
{
    QList<Task> taskList = TaskService::getAllTasks(db); // Zaciagniecie z bazy listy taskow
    QString response = ""; //obiekt textEdit przymuje tylko jeden QString wiec sobie go deklarujemy
    QString selectedDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    foreach(Task currentTask, taskList){ //iteracja po liscie, taka petla
        if(currentTask.getDate()==selectedDate){ //Sprawdzenie czy dla zaznaczonej daty jest jakis task
            response += "Nazwa: " + currentTask.getTitle() +"\nOpis: "+ currentTask.getDescription() + "\nData: " + currentTask.getTime() + " " + currentTask.getDate() +"\n\n";
            //element ktory teraz jest przetwazany to currentTask, dopisujemy do response kazdy z naszych elementow juz ladnie opisany
        }
    }
    ui->textEdit_2->setText(response); // wyswietlenie response na elemencie textEdit
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date){

};


void MainWindow::on_textEdit_textChanged(){

};

void MainWindow::on_calendarWidget_clicked(const QDate &date){

};


