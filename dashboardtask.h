#ifndef DASHBOARDTASK_H
#define DASHBOARDTASK_H

#include <QWidget>
#include <task.h>
#include <mainwindow.h>

namespace Ui {
class DashboardTask;
}

class DashboardTask : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardTask(QWidget *parent = nullptr, Task *task = new Task());
    ~DashboardTask();

public slots:
    void yesClicked();

    void on_delete_dashboard_clicked();

    void onTaskDeleted();

signals:
    void emitClicked();
    void emitDeleteTaskAndRefreshList();

private:
    Ui::DashboardTask *ui;

};


#endif // DASHBOARDTASK_H
