#ifndef EDITTASKPOPUP_H
#define EDITTASKPOPUP_H

#include <QDialog>
#include <dashboardtask.h>

/*!
 * @class EditTaskPopUp
 * @brief Klasa odpowiadająca za okno dialogowe edytowania zadania.
 *
 * W tej klasie zaimplementowano okno dialogowe, które pojawia się, gdy użytkownik chce edytować zadanie.
 * Zawiera ono pola tekstowe do edycji nazwy i opisu zadania, checkboxy do oznaczenia zadania jako ważnego lub
 * spotkanie oraz przyciski do potwierdzenia lub anulowania edycji.
 */

namespace Ui {
class EditTaskPopUp;
}

class EditTaskPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit EditTaskPopUp(QWidget *parent = nullptr,Task *task = new Task(),bool isNewTask = false);
    ~EditTaskPopUp();
    Task currentTask;
    bool addNewTaskOption;

private slots:
    void on_confirmEditButton_clicked();

    void on_meetingCheckBox_stateChanged(int arg1);

    void on_importantCheckBox_stateChanged(int arg1);

    void on_cancelEditButton_clicked();

    void on_editTitle_textChanged();

    void on_editDescription_textChanged();

private:
    Ui::EditTaskPopUp *ui;
};

#endif // EDITTASKPOPUP_H
