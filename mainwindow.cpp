#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "task.h"
#include <QList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE"); //Deklaracja jakiej bazy bedziemy uzywac w aplikacji
    db.setDatabaseName("calendar.sqlite"); //Ustawienie nazwy pliku z baza danych

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // Event okreslajacy co ma sie stac gdy nacisniemy na element pushButton
{
    db.open(); // Otworzenie polaczenia z baza danych
    QSqlQuery q; // Deklaracja zmiennej typu zapytanie do DB

    q.exec("SELECT * FROM TASK"); //Uzupelniamy tresc zapytania do bazy (zwykly SQL ale bez ";" na koncu)
    if(db.isOpen()){
        //informacja ze polaczono z baza, wszystkie zapytania do bazy powinny byc tutaj
    }else{
        //Blad polaczenia cos tam sie nie udalo
    }

    QList<Task> taskList; //Deklaracja listy do ktorej bedziemy dolaczac utworzone taski

    while(q.next()){ // Petla dziala dopoki nasze zapytanie zwraca wyniki (otworzy sie tylko tyle razy ile REKORDOW zwroci zapytanie)
        Task newTask; // Zmienna typu Task, zapisujemy w nim konkretny rekord z bazy (klasa task.h task.cpp)
        newTask.setId(q.value(0).toInt()); // uzywamy setterow ktore uzupelnia nasza zmienna o wartosci z zapytania, q.value(n) gdzie n to numer kolumny w tabeli
        newTask.setTitle(q.value(1).toString());
        newTask.setDescription(q.value(2).toString());
        newTask.setDate(q.value(3).toString());
        newTask.setTime(q.value(4).toString());
        newTask.setType(q.value(5).toString());
        taskList.append(newTask); //Dopisanie do konca listy nowego elementu
    }
    QString response = ""; //obiekt textEdit przymuje tylko jeden QString wiec sobie go deklarujemy

    foreach(Task currentTask, taskList){ //iteracja po liscie, taka petla
        response += "Nazwa: " + currentTask.getTitle() +"\nOpis: "+ currentTask.getDescription() + "\nData: " + currentTask.getTime() + " " + currentTask.getDate() +"\n\n";
        //element ktory teraz jest przetwazany to currentTask, dopisujemy do response kazdy z naszych elementow juz ladnie opisany
    }
    ui->textEdit->setText(response); // wyswietlenie response na elemencie textEdit
    q.clear(); // wyczszczenie zapytania
    db.close(); // kazde polaczenie z baza powinno byc na koniec zamkniete!
}





void MainWindow::on_textEdit_textChanged()
{

}



