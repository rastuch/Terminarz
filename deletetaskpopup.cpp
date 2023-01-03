#include "deletetaskpopup.h"
#include "ui_deletetaskpopup.h"
#include <dashboardtask.h>
#include "task.h"
#include <TaskService.h>

/*!
 * @brief Konstruktor klasy deleteTaskPopUp
 * @param parent Obiekt rodzica
 * @param task Wskaźnik do obiektu typu Task
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

/*!
 * @brief Destruktor klasy deleteTaskPopUp
 */

deleteTaskPopUp::~deleteTaskPopUp()
{
    delete ui;
}
/*!
 * @brief Slot obsługi kliknięcia przycisku "NIE"
 *
 * Po kliknięciu przycisku "NIE" okno dialogowe jest zamykane.
 */
void deleteTaskPopUp::on_noButton_clicked()
{
    QDialog::reject();
}
/*!
 * @brief Slot obsługi kliknięcia przycisku "TAK"
 *
 * Po kliknięciu przycisku "TAK" do bazy danych jest wysyłane polecenie usunięcia
 * zadania o podanym identyfikatorze, a następnie okno dialogowe jest zamykane.
 */
void deleteTaskPopUp::on_yesButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    TaskService::deleteTaskById(db,currentTask.getId());
    QDialog::reject();
}

