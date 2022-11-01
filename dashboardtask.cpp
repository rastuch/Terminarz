#include "dashboardtask.h"
#include "ui_dashboardtask.h"

DashboardTask::DashboardTask(QWidget *parent,Task *task) :
    QWidget(parent),
    ui(new Ui::DashboardTask)
{
    ui->setupUi(this);
    ui->titleLabel->setText(task->getTitle());
    ui->descriptionLabel->setText(task->getDescription());
    ui->typeLabel->setText(task->getType());
    ui->dateTimeLabel->setText(task->getTime() + " " + task->getQDate().toString("dd.MM.yyyy"));

}

DashboardTask::~DashboardTask()
{
    delete ui;
}
