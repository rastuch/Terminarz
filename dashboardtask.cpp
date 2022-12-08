#include "dashboardtask.h"
#include "ui_dashboardtask.h"
#include "deletetaskpopup.h"
#include "edittaskpopup.h"
#include <mainwindow.h>
#include "task.h"
#include <QDebug>
#include <TaskService.h>
using namespace std;

/*! @brief Funkcja przypisania zadania */
void setTaskTypeStyle(QString type, Ui::DashboardTask ui){
    QString style = "border: 0;background-position:left center;min-width: 30px;min-height:30px;background-repeat:no-repeat";
    bool shouldSetTextType = false;
     if(type == "MEETING"){ /** @return Przypisanie zadania jako "spotkanie" */
        style = "background-image: url(:/icon/account-group.png);" + style;
    }else if(type == "IMPORTANT"){ /** @return Przypisanie zadania jako "ważne zadanie" */
        style = "background-image: url(:/icon/alert-box-outline.png);" + style;
    }else{
        shouldSetTextType = true;
    };

    if(shouldSetTextType == false){ /** @return przerwanie przypisywania zadania */
    ui.type_dashboard->setStyleSheet(style);
    }else{
        ui.type_dashboard->setText(type);
    }

}

/*! @brief Główna funkcja panelu zadania
 *  @class QWidget jest klasą bazową wszystkich obiektów interfejsu
 */
DashboardTask::DashboardTask(QWidget *parent,Task *task) :
    QWidget(parent),
    ui(new Ui::DashboardTask)
{
    ui->setupUi(this);
    ui->title_dashboard->setWordWrap(true);
    ui->description_dashboard->setWordWrap(true);
    currentTask = *task;
    ui->title_dashboard->setText(task->getTitle());
    ui->description_dashboard->setText(task->getDescription());
    ui->date_dashboard->setText(task->getTime() + " " + task->getQDate().toString("dd.MM.yyyy"));
    setTaskTypeStyle(task->getType(), *ui);

}

DashboardTask::~DashboardTask()
{
    delete ui;
}


/*! @brief Funkcja usuwania "zadania" po kliknięciu w dashbordzie
 *  @class QObject jest klasą bazową wszystkich obiektów , connect łączy sygnał do gniazda
 */

void DashboardTask::on_delete_dashboard_clicked()
{
    auto deleteTaskPopUp1 = new deleteTaskPopUp(this,&currentTask);
    // Na etapie tworzenia obiektu deleteTaskPopUp dodajemy connect pomiedzy SYGNALEM ktorym bedziemy nadawac wyżej do rodzica oraz do samego siebie(MAINWINDOW i DashboardTask)
    //czyli &DashboardTask::emitDeleteTaskAndRefreshList

    // i sygnalem emitowanym przez tworzony obiekt czyli nasz popup deleteTaskPopUp.findChild<QPushButton *>("yesButton"), &QPushButton::clicked
    // zauważ że na tym etapie nie mozemy sie jeszcze odwolac bezposrednio do yesButton dlatego uzywam funkcji findChild
    // znajdzie ona przycisk po jego nazwie i umożliwi odwolanie sie do niego
    QObject::connect(deleteTaskPopUp1->findChild<QPushButton *>("yesButton"), &QPushButton::clicked, this, &DashboardTask::emitDeleteTaskAndRefreshList);


    // Nastepnie tworzymy kolejne polaczenie, tym razem miedzy syganelem ktory bedziemy tez emitowac do MAINWINDOW
    // czyli wybieramy sygnal  &DashboardTask::emitDeleteTaskAndRefreshList i łączymy go ze slotem &DashboardTask::onTaskDeleted
    QObject::connect(this, &DashboardTask::emitDeleteTaskAndRefreshList, this, &DashboardTask::onTaskDeleted);
    deleteTaskPopUp1->setModal(true);
    deleteTaskPopUp1->exec();

}

/*! @brief Funkcja usuwania zadania w popupie
 *  @class qDebug udostępnia strumień wyjściowy dla informacji debugowania
*/
void DashboardTask::onTaskDeleted(){
    qDebug("nacisneto przycisk usuwania w popupie");
}

/*! @brief Funkcja edycji "zadania" po kliknięciu w panelu która przenosi nas do edycji okna zadania
*/
void DashboardTask::on_edit_dashboard_clicked()
{
    auto editTaskPopUp1 = new EditTaskPopUp(this,&currentTask);
    QObject::connect(editTaskPopUp1->findChild<QPushButton *>("confirmEditButton"), &QPushButton::clicked, this, &DashboardTask::emitEditTask);
    QObject::connect(this, &DashboardTask::emitEditTask, this, &DashboardTask::onTaskEdited);
    editTaskPopUp1->setModal(true);
    editTaskPopUp1->exec();
}
/*! @brief Funkcja edycji zadania w popupie */
void DashboardTask::onTaskEdited()
{
    qDebug("nacisnieto przycisk edycji w popupie");
}



