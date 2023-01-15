#include "task.h"
#include <QString>
#include <QList>
/*!
 * @class Klasa reprezentująca pojedyncze zadanie.
 *
 * Klasa zawiera pola dotyczące identyfikatora, tytułu, opisu, daty, godziny oraz typu zadania.
 * Posiada także metody służące do ustawienia tych pól oraz konstruktory.
 */
Task::Task(){}
Task::Task(int id, QString title, QString description, QString date, QString time, QString type)
{
    setTask(id,title,description,date,time,type);
}
void Task::setTask(int id, QString title, QString description, QString date, QString time, QString type){
    id = id;
    title = title;
    description = description;
    date = date;
    time = time;
    type = type;
}

