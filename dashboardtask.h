#ifndef DASHBOARDTASK_H
#define DASHBOARDTASK_H

#include <QWidget>
#include <task.h>

namespace Ui {
class DashboardTask;
}

class DashboardTask : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardTask(QWidget *parent = nullptr, Task *task = new Task());
    ~DashboardTask();

private:
    Ui::DashboardTask *ui;
};

#endif // DASHBOARDTASK_H
