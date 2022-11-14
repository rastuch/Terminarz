#include "calendartask.h"
#include "ui_calendartask.h"
#include "deletetaskpopup.h"

void setTaskTypeStyle(QString type, Ui::calendarTask ui){
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
    ui.type_task->setStyleSheet(style);
    }else{
        ui.type_task->setText(type);
    }

}

calendarTask::calendarTask(QWidget *parent, Task *task) :
    QWidget(parent),
    ui(new Ui::calendarTask)
{
    ui->setupUi(this);
    ui->title_task->setText(task->getTitle());
    ui->description_task->setText(task->getDescription());
    ui->date_task->setText(task->getTime() + " " + task->getQDate().toString("dd.MM.yyyy"));
    setTaskTypeStyle(task->getType(), *ui);
}

calendarTask::~calendarTask()
{
    delete ui;
}

void calendarTask::on_delete_task_clicked()
{
    deleteTaskPopUp deleteTaskPopUp;
    deleteTaskPopUp.setModal(true);
    deleteTaskPopUp.exec();
}


