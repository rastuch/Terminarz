#include "edittaskpopup.h"
#include "ui_edittaskpopup.h"
#include "TaskService.h"
#include <qdebug.h>
#include <QTime>
#include <QPlainTextEdit>

/*! @brief Główna funkcja edycji zadania
 *  @class QDialog jest podstawową klasą okien dialogowych. */

EditTaskPopUp::EditTaskPopUp(QWidget *parent,Task *task) :
    QDialog(parent),
    ui(new Ui::EditTaskPopUp)
{
    ui->setupUi(this);
    EditTaskPopUp::setMinimumSize(540,365);
    currentTask = *task;
    QTime time = QTime::fromString(currentTask.getTime(),"hh:mm");
    ui->editTitle->insertPlainText(currentTask.getTitle());
    ui->editTime->setTime(time);
    ui->editDescription->insertPlainText(currentTask.getDescription());
    ui->edidDate->setDate(currentTask.getQDate());
    if( currentTask.getType()=="MEETING")
        ui->meetingCheckBox->click();
    else
        ui->importantCheckBox->click();
}

EditTaskPopUp::~EditTaskPopUp()
{
    delete ui;
}
/*! @brief Funkcja która zatwierdza edycje zadań
* @class QSqlDatabase obsługuje połączenie z bazą danych
*/
void EditTaskPopUp::on_confirmEditButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();

    QString newTitle = ui->editTitle->toPlainText();    /** @brief utworzenie nowego tytułu w edycji jeżeli już wcześniej został zadeklarowany obiekt zadania */
    if(newTitle.length()!=0)
        currentTask.setTitle(newTitle);

    QString newDescription = ui->editDescription->toPlainText(); /** @brief edycja opisu */
    if(newDescription.length()!=0)
        currentTask.setDescription(newDescription);

    QString newTime = ui->editTime->time().toString("hh:mm"); /** @brief edycja godziny */
    currentTask.setTime(newTime);

    QString newDate = ui->edidDate->date().toString("yyyy-MM-dd"); /** @brief edycja daty */
    currentTask.setDate(newDate);

    TaskService::updateTask(db,currentTask);

    QDialog::reject();
}

/*! @brief Funkcja która edytuje zadania na "spotkanie" */
void EditTaskPopUp::on_meetingCheckBox_stateChanged(int arg1)
{
    if(ui->meetingCheckBox->isChecked()==true) /** @return Przypisanie zadania na "spotkanie" */
    {
        ui->importantCheckBox->setChecked(false);
        currentTask.setType("MEETING");
    }
    else
    {
        ui->importantCheckBox->setChecked(true);
    }
}
/** @brief Funkcja która edytuje zadania na "ważne zadanie" */
void EditTaskPopUp::on_importantCheckBox_stateChanged(int arg1)
{
    if(ui->importantCheckBox->isChecked()==true) /** @return Przypisanie zadania na "ważne zadanie" */
    {
        ui->meetingCheckBox->setChecked(false);
        currentTask.setType("IMPORTANT");
    }
    else
    {
        ui->meetingCheckBox->setChecked(true);
    }
}
/*! @brief Funkcja w której naciśniecie przycisku "anuluj " powoduje przerwanie edytowania */
void EditTaskPopUp::on_cancelEditButton_clicked()
{
    QDialog::reject();
}

/*! @brief Pole do edycji tytułu */
void EditTaskPopUp::on_editTitle_textChanged()
{
    if(ui->editTitle->toPlainText().length()>100)
        ui->editTitle->textCursor().deletePreviousChar();
}
/*! @brief Pole do edycji opisu */
void EditTaskPopUp::on_editDescription_textChanged()
{
    if(ui->editDescription->toPlainText().length()>200)
        ui->editDescription->textCursor().deletePreviousChar();
}
