#ifndef TASKSERVICE_H
#define TASKSERVICE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <task.h>

#endif // TASKSERVICE_H

/*!
 * @namespace TaskService
 * @brief Przestrzeń nazw zawierająca funkcje do obsługi zadań w bazie danych.
 *
 * W tej przestrzeni nazw zaimplementowano funkcje do pobierania wszystkich zadań, pobierania zadań na dany dzień,
 *  dodawania nowych zadań, usuwania zadań, aktualizowania zadań oraz pobierania zadań na ten tydzień.
 */
namespace TaskService {
QList<Task> getAllTasks(QSqlDatabase db);
QList<Task> getAllTasksByDate(QSqlDatabase db, QDate date);
void addTask(QSqlDatabase db,Task newTask);
void deleteTaskById(QSqlDatabase db,int taskId);
void updateTask(QSqlDatabase db,Task updatedTask);
QList<Task> getThisWeekTaskList(QSqlDatabase db);
void addTasksForNextMounth(QSqlDatabase db);
}


