#include "deletetaskpopup.h"
#include "ui_deletetaskpopup.h"
#include <calendartask.h>

deleteTaskPopUp::deleteTaskPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteTaskPopUp)
{
    ui->setupUi(this);
}

deleteTaskPopUp::~deleteTaskPopUp()
{
    delete ui;
}

void deleteTaskPopUp::on_noButton_clicked()
{
    QDialog::reject();
}
