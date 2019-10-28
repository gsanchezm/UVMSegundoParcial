#include "searchstudentdialog.h"
#include "ui_searchstudentdialog.h"

searchStudentDialog::searchStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchStudentDialog)
{
    ui->setupUi(this);
}

searchStudentDialog::~searchStudentDialog()
{
    delete ui;
}
