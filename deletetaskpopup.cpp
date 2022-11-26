#include "deletetaskpopup.h"
#include "ui_deletetaskpopup.h"
#include <dashboardtask.h>
#include "task.h"
#include <TaskService.h>

deleteTaskPopUp::deleteTaskPopUp(QWidget *parent,Task *task) :
    QDialog(parent),
    ui(new Ui::deleteTaskPopUp)
{
    ui->setupUi(this);
    currentTask = *task;
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
    qDebug("delete");
    QSqlDatabase db = QSqlDatabase::database();
    auto deleteDashboardTask = new deleteTaskPopUp(this,&currentTask);
    TaskService::deleteTaskById(db,currentTask.getId());
    QDialog::reject();
}

