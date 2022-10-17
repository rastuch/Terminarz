#include <TaskService.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <task.h>

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
        //TODO: oblusga bledu bazy danych
    }
    q.clear(); // wyczszczenie zapytania
    db.close(); // kazde polaczenie z baza powinno byc na koniec zamkniete!
    // nie wiem dokladnie jak to dziala w SQLite ale np. w MYSQL kazde otwarte polaczenie zajmuje pamiec RAM, i w MYSQL np 1GB ramu pozwala na maksymalnie 64 polaczenia do bazy
    // dlatego tak wazne jest zamykanie polaczen (zwalnianie puli polaczen) aby nasz apka byla wydajna i nie zeby nie okazalo sie ze brakuje polaczen bo nie uzyskay danych z bazy
    return taskList;
}
}
