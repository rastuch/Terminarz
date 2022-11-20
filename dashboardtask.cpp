#include "dashboardtask.h"
#include "ui_dashboardtask.h"
#include "deletetaskpopup.h"
#include <mainwindow.h>
#include "task.h"
#include <QDebug>

using namespace std;
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
    MainWindow *mainwindow = new MainWindow;
    connect(this,&DashboardTask::emitClicked,mainwindow,&MainWindow::receiveSignal);
    /*Polaczenie emitowanego sygnalu emitClicked z funkcji yesClicked i wyslanie go do funkcji receiveSignal w MainWindow*/
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

void DashboardTask::yesClicked()
{
    emit emitClicked();

}



