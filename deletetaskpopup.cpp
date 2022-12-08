#include "deletetaskpopup.h"
#include "ui_deletetaskpopup.h"
#include <dashboardtask.h>
#include "task.h"
#include <TaskService.h>

/*! @brief Główna funkcja definitywnego usunięcia zadania
* @class QDialog(parent)-> Relacja nadrzędna okna dialogowego
*/
deleteTaskPopUp::deleteTaskPopUp(QWidget *parent,Task *task) :
    QDialog(parent),
    ui(new Ui::deleteTaskPopUp)
{
    ui->setupUi(this);
    deleteTaskPopUp::setMinimumSize(364,152);
    currentTask = *task;
//    DashboardTask *dashboardtask = new DashboardTask;
//    connect(ui->yesButton,&QPushButton::clicked,dashboardtask,&DashboardTask::yesClicked);
    /*Polaczenie przycisku TAK w popUpie po kliknieciu i wyslanie go do funkcji w DashboardTask*/
}

deleteTaskPopUp::~deleteTaskPopUp()
{
    delete ui;
}
/*! @brief Naciśnięcie przycisku "nie" powoduje przerwanie usuwania zadania i wrócenie do dashbordu
* @class QDialog::reject() --> okno dialogowe zostało odrzucone przez funkcje odrzucenia
*/
void deleteTaskPopUp::on_noButton_clicked()
{
    QDialog::reject();
}
/*! @brief Naciśnięcie przycisku "tak" powoduje usunięcie "zadania" z listy i bazy */
void deleteTaskPopUp::on_yesButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    TaskService::deleteTaskById(db,currentTask.getId());
    QDialog::reject();
}

