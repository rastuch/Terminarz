#include "dashboardtask.h"
#include "ui_dashboardtask.h"

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
    ui.typeLabel->setStyleSheet(style);
    }else{
        ui.typeLabel->setText(type);
    }

}


DashboardTask::DashboardTask(QWidget *parent,Task *task) :
    QWidget(parent),
    ui(new Ui::DashboardTask)
{
    ui->setupUi(this);
    ui->titleLabel->setText(task->getTitle());
    ui->descriptionLabel->setText(task->getDescription());
    ui->dateTimeLabel->setText(task->getTime() + " " + task->getQDate().toString("dd.MM.yyyy"));
    setTaskTypeStyle(task->getType(), *ui);

}

DashboardTask::~DashboardTask()
{
    delete ui;
}


