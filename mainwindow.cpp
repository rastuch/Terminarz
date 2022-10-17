#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "task.h"
#include <QList>
#include <QListWidget>
#include <TaskService.h>
#include <QDate>

// Funkcja ustawiajaca liste dni w miesiacu dla kalendarza,
// domyslna wartoscia jest akutalna data dlatego mozemy uzyc jej juz podczas uruchomienia aplikacji
void showCurrentDays(Ui::MainWindow ui, QDate date = QDate::currentDate()){
      QList<int> days; // deklaracja listy z liczba dni
      QDate now = date; // zdefiniowanie aktualnej daty
      int daysCount = now.daysInMonth(); // definicja liczby dni w miesiacu
      if(ui.listWidget->count() > 0){
          ui.listWidget->clear(); // Jesli liczba elementow listy jest wieksza niz 0 to lista zostaje wyczyszczona
      }
      for(int i = 1; i < daysCount+1; i++){
          days.append(i); // dodanie dnia do lisy dni do wyswietlenia
       }
      foreach (int currentDay, days) {
          QString day = "";
          day.append(QString::number(currentDay));
           ui.listWidget->addItem(day); //Dodanie wigetu z dniem do wigetu listy
           //TODO: ladny widget z numerem dnia i lista zadan w danym dniu
      }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE"); //Deklaracja jakiej bazy bedziemy uzywac w aplikacji
    db.setDatabaseName("calendar.sqlite"); //Ustawienie nazwy pliku z baza danych (baza danych powinna byc folderze budowania aplikacji a nie w plikach zrodlowych!)
    showCurrentDays(*ui); // Ustawienie listy dni na starcie programu

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
    ui->textEdit->setText(response); // wyswietlenie response na elemencie textEdit
}



void MainWindow::on_textEdit_textChanged()
{

}




void MainWindow::on_tabWidget_tabBarClicked(int index) //analogicznie do funkcji ponizej, wywolanie po kliknieciu w zakladke
{


}


void MainWindow::on_dateEdit_dateChanged(const QDate &date) // Funkcja wowluje sie przy kazdej zmiane daty
{
    showCurrentDays(*ui,date); //ustawienie liczby dni w kalendarzu po zmianie daty
}

