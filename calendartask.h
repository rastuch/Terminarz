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

public slots:
    void yesClicked();

private slots:


    void on_delete_task_clicked();

    void on_edit_task_clicked();

    void on_calendarTask_destroyed();

private:
    Ui::calendarTask *ui;
};

#endif // CALENDARTASK_H
