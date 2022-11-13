#ifndef CALENDARTASK_H
#define CALENDARTASK_H

#include <QWidget>
#include <task.h>

namespace Ui {
class calendarTask;
}

class calendarTask : public QWidget
{
    Q_OBJECT

public:
    explicit calendarTask(QWidget *parent = nullptr, Task *task = new Task());
    ~calendarTask();

private slots:
    void on_delete_task_clicked();

private:
    Ui::calendarTask *ui;
};

#endif // CALENDARTASK_H
