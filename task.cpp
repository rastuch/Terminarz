#include "task.h"
#include <QString>
#include <QList>
Task::Task(){}

/*! @brief Deklaracja wartości zadania */
Task::Task(int id, QString title, QString description, QString date, QString time, QString type)
{
    setTask(id,title,description,date,time,type);
}

/*! @brief Funkcja, która przypisuje wartości */

void Task::setTask(int id, QString title, QString description, QString date, QString time, QString type){
    id = id;
    title = title;
    description = description;
    date = date;
    time = time;
    type = type;
}

