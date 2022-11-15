#include "dashboardtask.h"
#include "ui_dashboardtask.h"
#include "deletetaskpopup.h"

void setTaskTypeStyle(QString type, Ui::DashboardTask ui){
    QString style = "border: 0;background-position:left center;min-width: 30px;min-height:30px;background-repeat:no-repeat";
    bool shouldSetTextType = false;

    if(type == "MEETING"){
        style = "background-image: url(:/icon/account-group.png);" + style;
    }else if(type == "IMPORTANT"){
        style = "background-image: url(:/icon/alert-box-outline.png);" + style;
    }else{
        shouldSetTextType = true;
    };

    if(shouldSetTextType == false){
    ui.type_dashboard->setStyleSheet(style);
    }else{
        ui.type_dashboard->setText(type);
    }

}


DashboardTask::DashboardTask(QWidget *parent,Task *task) :
    QWidget(parent),
    ui(new Ui::DashboardTask)
{
    ui->setupUi(this);
    ui->title_dashboard->setText(task->getTitle());
    ui->description_dashboard->setText(task->getDescription());
    ui->date_dashboard->setText(task->getTime() + " " + task->getQDate().toString("dd.MM.yyyy"));
    setTaskTypeStyle(task->getType(), *ui);

}

DashboardTask::~DashboardTask()
{
    delete ui;
}



void DashboardTask::on_delete_dashboard_clicked()
{
    deleteTaskPopUp deleteTaskPopUp;
    deleteTaskPopUp.setModal(true);
    deleteTaskPopUp.exec();
}

