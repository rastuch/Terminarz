#include "dashboardtask.h"
#include "ui_dashboardtask.h"
#include "deletetaskpopup.h"
#include "edittaskpopup.h"
#include <mainwindow.h>
#include "task.h"
#include <QDebug>
#include <TaskService.h>
using namespace std;

/*!
 * @brief Ustawienie styli dla typu zadania
 *
 * Funkcja ustawia styli dla zadania w zależności od jego typu. Jeżeli typem jest "MEETING",
 * to ustawiana jest ikona reprezentująca spotkanie. Jeżeli typem jest "IMPORTANT", to ustawiana
 * jest ikona reprezentująca ważne zadanie. W przeciwnym wypadku, typ zadania jest wyświetlany
 * jako tekst.
 *
 * @param type Typ zadania, który ma zostać ustawiony
 * @param ui Struktura interfejsu użytkownika DashboardTask
 */
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

/*!
 * @brief Tworzy obiekt DashboardTask i ustawia interfejs graficzny za pomocą obiektu Ui::DashboardTask.
 * @param parent Wskaźnik do rodzica obiektu.
 * @param task Wskaźnik do obiektu zadania, które ma zostać wyświetlone w panelu.
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

/*!
 * @brief Destruktor obiektu DashboardTask.
 *
 * Usuwa obiekt interfejsu graficznego Ui::DashboardTask.
 */

DashboardTask::~DashboardTask()
{
    delete ui;
}


/*!
 * @brief Slot obsługujący kliknięcie przycisku usuwania zadania z panelu.
 *
 * Tworzy obiekt deleteTaskPopUp i łączy sygnały i sloty między nim a obiektem DashboardTask oraz
 * głównym oknem aplikacji (MainWindow). Następnie ustawia modalność obiektu deleteTaskPopUp i wyświetla go.
 *
 * @sa deleteTaskPopUp
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

/*!
 * @brief Slot obsługujący usunięcie zadania z panelu.
 *
 * Slot wywoływany po wysłaniu sygnału emitDeleteTaskAndRefreshList. Wypisuje komunikat do konsoli za pomocą funkcji qDebug().
 *
 * @sa emitDeleteTaskAndRefreshList
 */
void DashboardTask::onTaskDeleted(){
    qDebug("nacisneto przycisk usuwania w popupie");
}

/*!
 * @brief Slot obsługujący kliknięcie przycisku edycji zadania z panelu.
 *
 * Tworzy obiekt EditTaskPopUp i łączy sygnały i sloty między nim a obiektem DashboardTask.
 * Następnie ustawia modalność obiektu EditTaskPopUp i wyświetla go.
 *
 * @sa EditTaskPopUp
 */
void DashboardTask::on_edit_dashboard_clicked()
{
    auto editTaskPopUp1 = new EditTaskPopUp(this,&currentTask);
    QObject::connect(editTaskPopUp1->findChild<QPushButton *>("confirmEditButton"), &QPushButton::clicked, this, &DashboardTask::emitEditTask);
    QObject::connect(this, &DashboardTask::emitEditTask, this, &DashboardTask::onTaskEdited);
    editTaskPopUp1->setModal(true);
    editTaskPopUp1->exec();
}
/*!
 * @brief Slot obsługujący edycję zadania z panelu.
 *
 * Slot wywoływany po wysłaniu sygnału emitEditTask. Wypisuje komunikat do konsoli za pomocą funkcji qDebug().
 *
 * @sa emitEditTask
 */
void DashboardTask::onTaskEdited()
{
    qDebug("nacisnieto przycisk edycji w popupie");
}



