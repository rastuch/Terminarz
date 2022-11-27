#include <TaskService.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <task.h>
#include <QDebug>
#include <QSqlError>
#include <QRandomGenerator>

// Serwisy beda odpowiedzialne za dostarczanie danych z bazy, to tutaj mapujemy dane (tzn. przypisujemy wartosci z bazy do obiektu danej klasy)
// Przestrzen nazw jest tu uzywana zamiast klasy poniewaz sa tu tylko metody statyczne wiec nie mamy potrzeby tworzenia nowej instancji obiektu
// Tutaj bedziemy wrzucac wszystkie funkcje ktore maja dostarczac informacje oraz/z bazy
namespace TaskService {

QList<Task> getAllTasks(QSqlDatabase db){ //Funkcja ktora wyciaga wszystkie zadania z bazy i zwraca liste obiektow typu Task, argumentem jest zadeklarowana baza danych
    db.open(); // Otworzenie polaczenia z bazy danych
    QSqlQuery q; // Deklaracja zmiennej typu zapytanie do DB
    QList<Task> taskList; //Deklaracja listy do ktorej bedziemy dolaczac utworzone taski
    q.exec("SELECT * FROM TASK"); //Uzupelniamy tresc zapytania do bazy (zwykly SQL ale bez ";" na koncu)
    if(db.isOpen()){
        //informacja ze polaczono z baza, wszystkie zapytania do bazy powinny byc tutaj
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
    }else{
        //Blad polaczenia cos tam sie nie udalo
        qDebug( "getAllTasks can not get DB connection" );
        qWarning() << db.lastError();
    }
    if (q.lastError().isValid()){
         qWarning() << q.lastError();
    }else{
        qDebug() << q.lastQuery();
        qDebug("getAllTasks sucessfull");
    }
    q.clear(); // wyczszczenie zapytania
    db.close(); // kazde polaczenie z baza powinno byc na koniec zamkniete!
    // nie wiem dokladnie jak to dziala w SQLite ale np. w MYSQL kazde otwarte polaczenie zajmuje pamiec RAM, i w MYSQL np 1GB ramu pozwala na maksymalnie 64 polaczenia do bazy
    // dlatego tak wazne jest zamykanie polaczen (zwalnianie puli polaczen) aby nasz apka byla wydajna i nie zeby nie okazalo sie ze brakuje polaczen bo nie uzyskay danych z bazy
    return taskList;
}
QList<Task> getAllTasksByDate(QSqlDatabase db,QDate date){
    db.open();
    QSqlQuery q;
    QList<Task> taskList;
    QString query = "SELECT * FROM TASK WHERE date like '" +date.toString("yyyy-MM-dd")+"'";
    q.exec(query);
      if(db.isOpen()){
          while(q.next()){
              Task newTask;
              newTask.setId(q.value(0).toInt());
              newTask.setTitle(q.value(1).toString());
              newTask.setDescription(q.value(2).toString());
              newTask.setDate(q.value(3).toString());
              newTask.setTime(q.value(4).toString());
              newTask.setType(q.value(5).toString());
              taskList.append(newTask);
          }
      }else{
              qDebug( "getAllTasksByDate can not get DB connection" );
              qWarning() << db.lastError();
          }
      if (q.lastError().isValid()){
           qDebug() << query;
           qWarning() << q.lastError();
      }else{
          qDebug() << q.lastQuery();
          qDebug("getAllTasksByDate sucessfull");
      }
      q.clear();
      db.close();
      return taskList;
}

void addTask(QSqlDatabase db,Task newTask){
    db.open();
    QSqlQuery q;
    QString query = QString("INSERT INTO TASK (title, description, date, time, type) VALUES ('%1','%2','%3','%4','%5')").arg(
                newTask.getTitle(),newTask.getDescription(),newTask.getDate(),newTask.getTime(),newTask.getType());
    q.exec(query);
    if (q.lastError().isValid()){
         qDebug() << query;
         qWarning() << q.lastError();
    }else{
        qDebug() << q.lastQuery();
        qDebug("addTask sucessfull");
    }
    q.clear();
    db.close();
}

void deleteTaskById(QSqlDatabase db,int taskId){
    db.open();
    QSqlQuery q;
    QString query = QString("DELETE FROM TASK WHERE id = %1").arg(taskId);
    q.exec(query);
    if (q.lastError().isValid()){
         qDebug() << query;
         qWarning() << q.lastError();
    }else{
        qDebug() << q.lastQuery();
        qDebug("deleteTaskById sucessfull");
    }
    q.clear();
    db.close();
}

void updateTask(QSqlDatabase db,Task updatedTask){
    db.open();
    QSqlQuery q;
    QString query = QString("UPDATE TASK SET title = '%1', description = '%2', date = '%3', time = '%4', type = '%5' WHERE id=%6").arg(
                updatedTask.getTitle(),
                updatedTask.getDescription(),
                updatedTask.getDate(),
                updatedTask.getTime(),
                updatedTask.getType(),
                QString::number(updatedTask.getId())
                );

    q.exec(query);
    if (q.lastError().isValid()){
         qDebug() << query;
         qWarning() << q.lastError();
    }else{
        qDebug() << q.lastQuery();
        qDebug("updateTask sucessfull");
    }
    q.clear();
    db.close();
}

QList<Task> getThisWeekTaskList(QSqlDatabase db){
     QList<Task> weekTaskList;
     QDate date = QDate::currentDate();
        for(int i = 0; i <= 6; i++ ){
           date = date.addDays(i);
           QList<Task> dayTaskList = getAllTasksByDate(db, date);
           foreach (Task currentTask, dayTaskList) {
               weekTaskList.append(currentTask);
           }
        }
        return weekTaskList;
}

void addTasksForNextMounth(QSqlDatabase db){
    QString loremIpsumText ="Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, "
                            "eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. "
                            "Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. "
                            "Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. "
                            "Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? "
                            "Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";

    QDate date = QDate::currentDate();
    for(int i = 0; i < 30; i++ ){
        date = date.addDays(1);
        Task task;
        task.setTitle(loremIpsumText.mid(0,QRandomGenerator::global()->bounded(1,20)));
        task.setDescription(loremIpsumText.mid(215,QRandomGenerator::global()->bounded(216,415)));
        task.setDate(date.toString("yyyy-MM-dd"));
        QString randomTime = QString::number(QRandomGenerator::global()->bounded(10,23)) + ":" + QString::number(QRandomGenerator::global()->bounded(10,59));
        task.setTime(randomTime);
        QString type;
        if(i % 2 == 0){
            task.setType("MEETING");
        }else{
            task.setType("IMPORTANT");
        }
        TaskService::addTask(db,task);
    }
}
}

