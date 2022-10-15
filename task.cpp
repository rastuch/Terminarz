#include "task.h"
#include <QString>
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
