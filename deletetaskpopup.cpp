#include "deletetaskpopup.h"
#include "ui_deletetaskpopup.h"
#include <dashboardtask.h>

deleteTaskPopUp::deleteTaskPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteTaskPopUp)
{
    ui->setupUi(this);
//    DashboardTask *dashboardtask = new DashboardTask;
//    connect(ui->yesButton,&QPushButton::clicked,dashboardtask,&DashboardTask::yesClicked);
    /*Polaczenie przycisku TAK w popUpie po kliknieciu i wyslanie go do funkcji w DashboardTask*/
}

deleteTaskPopUp::~deleteTaskPopUp()
{
    delete ui;
}

void deleteTaskPopUp::on_noButton_clicked()
{
    QDialog::reject();
}
void deleteTaskPopUp::on_yesButton_clicked()
{

}

