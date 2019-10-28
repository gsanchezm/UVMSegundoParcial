#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"
#include <iostream>
#include <string>
#include<QDebug>

AddStudentDialog::AddStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);

    ui->cmbMaterias->addItems({"Programación","Circuitos","Prácticas Profesionales"});
    for(int i = 1; i<=3;i++){
        ui->cmbParciales->addItem("Parcial " + QString::number(i));
    }

    ui->tblAlumnnos->setColumnCount(5);
    QStringList titulos;
    titulos << "ID" << "Nombre" << "Materia" << "Parcial" << "Calificación";
    ui->tblAlumnnos->setHorizontalHeaderLabels(titulos);
}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}

void AddStudentDialog::on_btnSalir_clicked()
{
    this->close();
}

struct alumno {
    int id;
    std::string nombre;
    std::string materia;
    std::string parcial;
    double calificacion;
};

void AddStudentDialog::on_btnAgegar_clicked()
{
    int row = ui->tblAlumnnos->rowCount();
    ui->tblAlumnnos->insertRow(row);
    alumno *student = new alumno[100];
    cantidad ++;

    ui->tblAlumnnos->setItem(row,ID, new QTableWidgetItem(QString::number(cantidad)));
    ui->tblAlumnnos->setItem(row,NOMBRE, new QTableWidgetItem(nombre()));
    ui->tblAlumnnos->setItem(row,MATERIA, new QTableWidgetItem(materia()));
    ui->tblAlumnnos->setItem(row,PARCIAL, new QTableWidgetItem(parcial()));
    ui->tblAlumnnos->setItem(row,CALIFICACION, new QTableWidgetItem(QString::number(calificacion())));

    ui->tblAlumnnos->viewport()->update();

    student[cantidad].id = cantidad;
    student[cantidad].nombre = ui->txtNombre->text().toStdString();
    student[cantidad].materia = ui->cmbMaterias->currentText().toStdString();
    student[cantidad].parcial = ui->cmbParciales->currentText().toStdString();
    student[cantidad].calificacion = ui->dsbCalificacion->value();

    ui->txtNombre->clear();
    ui->cmbMaterias->clear();
    ui->cmbMaterias->addItems({"Programación","Circuitos","Prácticas Profesionales"});
    ui->cmbParciales->clear();
    for(int i = 1; i<=3;i++){
        ui->cmbParciales->addItem("Parcial " + QString::number(i));
    }
    ui->dsbCalificacion->clear();
    ui->dsbCalificacion->setValue(0.0);

    if(cantidad>100){
        ui->btnAgegar->setEnabled(false);
    }

    qInfo() << "El id es " << QString::number(student[cantidad].id);
    qInfo() << "El nombre es " << QString::fromStdString(student[cantidad].nombre);
    qInfo() << "La materia es " << QString::fromStdString(student[cantidad].materia);
    qInfo() << "El parcial es " << QString::fromStdString(student[cantidad].parcial);
    qInfo() << "Su calificación es " << QString::number(student[cantidad].calificacion);
    qInfo() << "################################################################### ";
}

QString AddStudentDialog::nombre() const{
   return  ui->txtNombre->text();
}

//int AddStudentDialog::id() const{}
QString AddStudentDialog::materia() const{
    return ui->cmbMaterias->currentText();
}

QString AddStudentDialog::parcial() const{
    return ui->cmbParciales->currentText();
}

double AddStudentDialog::calificacion() const{
    return  ui->dsbCalificacion->value();
}
