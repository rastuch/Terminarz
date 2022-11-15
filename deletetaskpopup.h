#ifndef DELETETASKPOPUP_H
#define DELETETASKPOPUP_H

#include <QDialog>
#include <calendartask.h>
namespace Ui {
class deleteTaskPopUp;
}

class deleteTaskPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit deleteTaskPopUp(QWidget *parent = nullptr);
    ~deleteTaskPopUp();

private slots:
    void on_noButton_clicked();

    void on_yesButton_clicked();

private:
    Ui::deleteTaskPopUp *ui;
};

#endif // DELETETASKPOPUP_H
