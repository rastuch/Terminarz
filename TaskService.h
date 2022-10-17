#ifndef TASKSERVICE_H
#define TASKSERVICE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <task.h>

#endif // TASKSERVICE_H
namespace TaskService {
QList<Task> getAllTasks(QSqlDatabase db);
}
