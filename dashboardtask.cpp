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
//    MainWindow *mainwindow = new MainWindow;
//    connect(this,&DashboardTask::emitClicked,mainwindow,&MainWindow::receiveSignal);
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
    // Na etapie tworzenia obiektu deleteTaskPopUp dodajemy connect pomiedzy SYGNALEM ktorym bedziemy nadawac wyżej do rodzica oraz do samego siebie(MAINWINDOW i DashboardTask)
    //czyli &DashboardTask::emitDeleteTaskAndRefreshList

    // i sygnalem emitowanym przez tworzony obiekt czyli nasz popup deleteTaskPopUp.findChild<QPushButton *>("yesButton"), &QPushButton::clicked
    // zauważ że na tym etapie nie mozemy sie jeszcze odwolac bezposrednio do yesButton dlatego uzywam funkcji findChild
    // znajdzie ona przycisk po jego nazwie i umożliwi odwolanie sie do niego
    QObject::connect(deleteTaskPopUp.findChild<QPushButton *>("yesButton"), &QPushButton::clicked, this, &DashboardTask::emitDeleteTaskAndRefreshList);


    // Nastepnie tworzymy kolejne polaczenie, tym razem miedzy syganelem ktory bedziemy tez emitowac do MAINWINDOW
    // czyli wybieramy sygnal  &DashboardTask::emitDeleteTaskAndRefreshList i łączymy go ze slotem &DashboardTask::onTaskDeleted
    QObject::connect(this, &DashboardTask::emitDeleteTaskAndRefreshList, this, &DashboardTask::onTaskDeleted);
    deleteTaskPopUp.setModal(true);
    deleteTaskPopUp.exec();

}

void DashboardTask::yesClicked()
{
    emit emitClicked();

}

void DashboardTask::onTaskDeleted(){
    // z uwagi na to ze posiadamy juz na tym etapie id tasku (zobacz na konstruktor w 30 linijce tego pliku) sugeruje tutaj usunac nasz task z bazy
    //ale spradz ktory sygnal dociera pierwszy bo moze lepiej to bedzie zrobic na popupie ze wzgledu na to ze nie wiem ktory sygnal dociera pierwszy
    // jesli pierwszy dotrze do mainwindow to trzeba bedzie przekazac id tasku w konstruktorze popup i tam usunac

    qDebug("nacisneto przycisk usuwania w popupie");
}



