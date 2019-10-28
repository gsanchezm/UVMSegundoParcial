#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addstudentdialog.h"
#include "searchstudentdialog.h"
#include <QDebug>
#include <QRegExp>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Universidad del Valle de México");
    ui->cmbMaterias->addItems({"Programación","Circuitos","Prácticas Profesionales"});
    for(int i = 1; i<=3;i++){
        ui->cmbParciales->addItem("Parcial " + QString::number(i));
    }

    ui->tblAlumnnos->setColumnCount(5);
    QStringList titulos;
    titulos << "ID" << "Nombre" << "Materia" << "Parcial" << "Calificación";
    ui->tblAlumnnos->setHorizontalHeaderLabels(titulos);
    if(ui->tblAlumnnos->rowCount()==0){
        ui->btnBuscarAlumno->setEnabled(false);
        ui->txtBuscar->setEnabled(false);
        ui->btnCalcular->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSalir_clicked()
{
    this->close();
}

struct alumno {
    int id;
    std::string nombre;
    std::string materia;
    std::string parcial;
    double calificacion;
}student[100];

void MainWindow::on_btnBuscarAlumno_clicked()
{
    int rows = ui->tblAlumnnos->rowCount();

    QString filter = ui->txtBuscar->text();
    for( int i = 0; i < rows; ++i )
    {
        bool match = false;
        for( int j = 0; j < ui->tblAlumnnos->columnCount(); ++j )
        {
            QTableWidgetItem *item = ui->tblAlumnnos->item( i, j );
            if( item->text().contains(filter) )
            {
                match = true;
                break;
            }
        }
        ui->tblAlumnnos->setRowHidden( i, !match );
    }
}

void MainWindow::on_btnAgregar_clicked()
{
    int row = ui->tblAlumnnos->rowCount();
    ui->tblAlumnnos->insertRow(row);
    //alumno *student = new alumno[100];
    cantidad ++;

    ui->tblAlumnnos->setItem(row,ID, new QTableWidgetItem(QString::number(cantidad)));
    ui->tblAlumnnos->setItem(row,NOMBRE, new QTableWidgetItem(nombre()));
    ui->tblAlumnnos->setItem(row,MATERIA, new QTableWidgetItem(materia()));
    ui->tblAlumnnos->setItem(row,PARCIAL, new QTableWidgetItem(parcial()));
    ui->tblAlumnnos->setItem(row,CALIFICACION, new QTableWidgetItem(QString::number(calificacion())));

    ui->tblAlumnnos->viewport()->update();
    ui->btnBuscarAlumno->setEnabled(true);
    ui->txtBuscar->setEnabled(true);
    ui->btnCalcular->setEnabled(true);

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
        ui->btnAgregar->setEnabled(false);
    }
}

void MainWindow::on_btnCalcular_clicked()
{
    double sumatoria = 0.0;
    double highNum = 0.0;
    double lowNum=10.0;
    double calProgramacion = 0.0;
    double calCircuitos = 0.0;
    double calPracticas = 0.0;
    double promedio = 0.0, promCircuitos = 0.0, promProgramacion = 0.0, promPracticas = 0.0;
    int cantidadCircuitos = 0, cantidadProgramacion = 0, cantidadPracticas = 0;

    for (int i=1;i<=cantidad;i++) {

        sumatoria += student[i].calificacion;

        if(student[i].calificacion>highNum){
            highNum = student[i].calificacion;
        }

        if(student[i].calificacion<lowNum){
            lowNum = student[i].calificacion;
        }

        if(student[i].materia == "Programación"){
            calProgramacion += student[i].calificacion;
            cantidadProgramacion++;
        }else if(student[i].materia == "Circuitos"){
            calCircuitos += student[i].calificacion;
            cantidadCircuitos ++;
        }else{
            calPracticas += student[i].calificacion;
            cantidadPracticas++;
        }
    }

    promedio = sumatoria/cantidad;
    promCircuitos = calCircuitos/cantidadCircuitos;
    promProgramacion = calProgramacion/cantidadProgramacion;
    promPracticas = calPracticas/cantidadPracticas;

    ui->lblPromGeneral->setText(QString::number(promedio,'f',2));
    ui->lblMejorCal->setText(QString::number(highNum));
    ui->lblMenorCal->setText(QString::number(lowNum));
    ui->lblCircuitos->setText(QString::number(promCircuitos,'f',2));
    ui->lblProgramacion->setText(QString::number(promProgramacion,'f',2));
    ui->lblPracticas->setText(QString::number(promPracticas,'f',2));
}

QString MainWindow::nombre() const{
   return ui->txtNombre->text();
}

//int AddStudentDialog::id() const{}
QString MainWindow::materia() const{
    return ui->cmbMaterias->currentText();
}

QString MainWindow::parcial() const{
    return ui->cmbParciales->currentText();
}

double MainWindow::calificacion() const{
    return ui->dsbCalificacion->value();
}
