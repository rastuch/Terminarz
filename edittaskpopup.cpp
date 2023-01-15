#include "edittaskpopup.h"
#include "ui_edittaskpopup.h"
#include "TaskService.h"
#include <qdebug.h>
#include <QTime>
#include <QPlainTextEdit>

/*!
 * @brief Konstruuje obiekt EditTaskPopUp
 * @param parent Wskaźnik do widgetu nadrzędnego
 * @param task Wskaźnik do obiektu zadania, które ma zostać edytowane lub dodane
 * @param isNewTask Wartość boolowska określająca, czy zadanie jest nowe czy jest edytowane
 */
EditTaskPopUp::EditTaskPopUp(QWidget *parent,Task *task,bool isNewTask) :
    QDialog(parent),
    ui(new Ui::EditTaskPopUp)
{
    ui->setupUi(this);
    EditTaskPopUp::setMinimumSize(540,365);
    addNewTaskOption = isNewTask;
    currentTask = *task;

    if(addNewTaskOption){
        this->setWindowTitle("Dodaj nowe zadanie");
        ui->zmienTytulText->setMarkdown("<span style=\" font-size:10pt;\">Tytuł</span>");
        ui->zmienOpisText->setMarkdown("<span style=\" font-size:10pt;\">Opis</span>");
        ui->zmienTypText->setMarkdown("<span style=\" font-size:10pt; font-weight:700;\">Typ</span>");
        ui->textDateText->setMarkdown("<span style=\" font-size:10pt; font-weight:700;\">Data</span>");
        ui->confirmEditButton->setText("ZAPISZ");
        ui->cancelEditButton->setText("ANULUJ");
        QTime time =QTime::currentTime();
        ui->editTime->setTime(time);
        ui->edidDate->setDate(currentTask.getQDate());
        ui->importantCheckBox->click();
    }else{
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
}

/*!
 * @brief Destruktor obiektu EditTaskPopUp
 */
EditTaskPopUp::~EditTaskPopUp()
{
    delete ui;
}
/*!
 * @brief Slot obsługi sygnału kliknięcia przycisku potwierdzenia edycji
 */
void EditTaskPopUp::on_confirmEditButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();

    QString newTitle = ui->editTitle->toPlainText();    /*! @brief utworzenie nowego tytułu w edycji jeżeli już wcześniej został zadeklarowany obiekt zadania */
    if(newTitle.length()!=0)
        currentTask.setTitle(newTitle);

    QString newDescription = ui->editDescription->toPlainText(); /*! @brief edycja opisu */
    if(newDescription.length()!=0)
        currentTask.setDescription(newDescription);

    QString newTime = ui->editTime->time().toString("hh:mm"); /*! @brief edycja godziny */
    currentTask.setTime(newTime);

    QString newDate = ui->edidDate->date().toString("yyyy-MM-dd"); /*! @brief edycja daty */
    currentTask.setDate(newDate);

    if(addNewTaskOption == true){
        TaskService::addTask(db,currentTask);
    }else{
        TaskService::updateTask(db,currentTask);
    }

    QDialog::reject();
}

/*!
 * @brief Slot obsługi zmiany stanu pola wyboru "spotkanie"
 * @param arg1 Stan pola wyboru
 */
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
/*!
 * @brief Slot obsługi zmiany stanu pola wyboru "ważne zadanie"
 * @param arg1 Stan pola wyboru
 */
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
/*!
 * @brief Slot obsługi sygnału kliknięcia przycisku anulowania edycji
 */
void EditTaskPopUp::on_cancelEditButton_clicked()
{
    QDialog::reject();
}

/*!
 * @brief Slot obsługi zmiany tekstu w polu edycji tytułu
 */
void EditTaskPopUp::on_editTitle_textChanged()
{
    if(ui->editTitle->toPlainText().length()>100)
        ui->editTitle->textCursor().deletePreviousChar();
}
/*!
 * @brief Slot obsługi zmiany tekstu w polu edycji opisu
 */
void EditTaskPopUp::on_editDescription_textChanged()
{
    if(ui->editDescription->toPlainText().length()>200)
        ui->editDescription->textCursor().deletePreviousChar();
}
