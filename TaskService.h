#ifndef TASKSERVICE_H
#define TASKSERVICE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <task.h>

#endif // TASKSERVICE_H
namespace TaskService {
QList<Task> getAllTasks(QSqlDatabase db);
QList<Task> getAllTasksByDate(QSqlDatabase db, QDate date);
void addTask(QSqlDatabase db,Task newTask);
void deleteTaskById(QSqlDatabase db,int taskId);
void updateTask(QSqlDatabase db,Task updatedTask);
}


