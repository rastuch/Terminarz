#ifndef DELETETASKPOPUP_H
#define DELETETASKPOPUP_H

#include <QDialog>
#include <dashboardtask.h>


/*!
 * @class Opis klasy usunięcia zadania
  */

namespace Ui {
class deleteTaskPopUp;
}

class deleteTaskPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit deleteTaskPopUp(QWidget *parent = nullptr,Task *task = new Task());
    ~deleteTaskPopUp();
    Task currentTask;

private slots:
    void on_noButton_clicked();

    void on_yesButton_clicked();



private:
    Ui::deleteTaskPopUp *ui;
};

#endif // DELETETASKPOPUP_H
