#ifndef DASHBOARDTASK_H
#define DASHBOARDTASK_H

#include <QWidget>
#include <task.h>
#include <mainwindow.h>


/*!
 * @class DashboardTask
 * @brief Klasa odpowiadająca za widget z informacjami o zadaniu na panelu użytkownika.
 *
 * W tej klasie zaimplementowano widget, który wyświetla informacje o zadaniu na panelu użytkownika, takie jak nazwa, opis, priorytet i datę.
 * Zawiera on również przyciski do usuwania i edytowania zadania.
 */


namespace Ui {
class DashboardTask;
}

class DashboardTask : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardTask(QWidget *parent = nullptr, Task *task = new Task());
    ~DashboardTask();
    Task currentTask;

public slots:
    void on_delete_dashboard_clicked();

    void on_edit_dashboard_clicked();

    void onTaskDeleted();

    void onTaskEdited();

signals:
    void emitDeleteTaskAndRefreshList();

    void emitEditTask();

private slots:

private:
    Ui::DashboardTask *ui;

};


#endif // DASHBOARDTASK_H
