#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog();
    QString nombre() const;
    int id() const;
    QString materia() const;
    QString parcial() const;
    double calificacion() const;
    int cantidad = 0;

private slots:
    void on_btnSalir_clicked();

    void on_btnAgegar_clicked();

private:
    Ui::AddStudentDialog *ui;

    enum Columna{
      ID, NOMBRE, MATERIA, PARCIAL, CALIFICACION
    };
};

#endif // ADDSTUDENTDIALOG_H
