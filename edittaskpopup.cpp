#include "edittaskpopup.h"
#include "ui_edittaskpopup.h"
#include "TaskService.h"
#include <qdebug.h>
#include <QTime>
#include <QPlainTextEdit>

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

EditTaskPopUp::~EditTaskPopUp()
{
    delete ui;
}

void EditTaskPopUp::on_confirmEditButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();

    QString newTitle = ui->editTitle->toPlainText();
    if(newTitle.length()!=0)
        currentTask.setTitle(newTitle);

    QString newDescription = ui->editDescription->toPlainText();
    if(newDescription.length()!=0)
        currentTask.setDescription(newDescription);

    QString newTime = ui->editTime->time().toString("hh:mm");
    currentTask.setTime(newTime);

    QString newDate = ui->edidDate->date().toString("yyyy-MM-dd");
    currentTask.setDate(newDate);

    if(addNewTaskOption == true){
        TaskService::addTask(db,currentTask);
    }else{
        TaskService::updateTask(db,currentTask);
    }

    QDialog::reject();
}


void EditTaskPopUp::on_meetingCheckBox_stateChanged(int arg1)
{
    if(ui->meetingCheckBox->isChecked()==true)
    {
        ui->importantCheckBox->setChecked(false);
        currentTask.setType("MEETING");
    }
    else
    {
        ui->importantCheckBox->setChecked(true);
    }
}

void EditTaskPopUp::on_importantCheckBox_stateChanged(int arg1)
{
    if(ui->importantCheckBox->isChecked()==true)
    {
        ui->meetingCheckBox->setChecked(false);
        currentTask.setType("IMPORTANT");
    }
    else
    {
        ui->meetingCheckBox->setChecked(true);
    }
}

void EditTaskPopUp::on_cancelEditButton_clicked()
{
    QDialog::reject();
}


void EditTaskPopUp::on_editTitle_textChanged()
{
    if(ui->editTitle->toPlainText().length()>100)
        ui->editTitle->textCursor().deletePreviousChar();
}

void EditTaskPopUp::on_editDescription_textChanged()
{
    if(ui->editDescription->toPlainText().length()>200)
        ui->editDescription->textCursor().deletePreviousChar();
}
