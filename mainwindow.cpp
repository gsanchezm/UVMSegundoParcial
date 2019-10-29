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

    ui->lblNombreVacio->setStyleSheet("QLabel { color : red; }");
    ui->lblItemExist->setStyleSheet("QLabel { color : red; }");
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
    if(!ui->txtNombre->text().isEmpty()){
        int row = ui->tblAlumnnos->rowCount();

        QList<QTableWidgetItem *> ItemNombreList = ui->tblAlumnnos->findItems(nombre(), Qt::MatchExactly);
        QList<QTableWidgetItem *> ItemMateriaList = ui->tblAlumnnos->findItems(materia(), Qt::MatchExactly);
        QList<QTableWidgetItem *> ItemParcialList = ui->tblAlumnnos->findItems(parcial(), Qt::MatchExactly);

        if(ItemNombreList.count()>0 & ItemMateriaList.count() > 0 & ItemParcialList.count() > 0){
            ui->lblItemExist->setText("El nombre, la materia y el parcial ya fueron registrados!");
        }else{
            ui->lblItemExist->setText("");

            ui->tblAlumnnos->insertRow(row);
            cantidad ++;

            ui->tblAlumnnos->setItem(row,ID, new QTableWidgetItem(QString::number(cantidad)));
            ui->tblAlumnnos->setItem(row,NOMBRE, new QTableWidgetItem(nombre()));
            ui->tblAlumnnos->setItem(row,MATERIA, new QTableWidgetItem(materia()));
            ui->tblAlumnnos->setItem(row,PARCIAL, new QTableWidgetItem(parcial()));
            ui->tblAlumnnos->setItem(row,CALIFICACION, new QTableWidgetItem(QString::number(calificacion())));

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

            if(cantidad>=98){
                ui->btnAgregar->setEnabled(false);
                row=0;
                cantidad=0;
            }
        }

        ui->lblNombreVacio->setText("");
    }else{
        ui->lblNombreVacio->setText("El nombre no puede estar vacío!");
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

    promCircuitos = cantidadCircuitos>0&calCircuitos>0?calCircuitos/cantidadCircuitos:0;
    promProgramacion = calProgramacion>0&cantidadPracticas>0?calProgramacion/cantidadProgramacion:0;
    promPracticas = calPracticas>0&cantidadPracticas>0?calPracticas/cantidadPracticas:0;

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
