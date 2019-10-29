#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString nombre() const;
    int id() const;
    QString materia() const;
    QString parcial() const;
    double calificacion() const;
    int cantidad = 0;

private slots:
    void on_btnSalir_clicked();

    //void on_btnAgregarAlumno_clicked();

    void on_btnBuscarAlumno_clicked();

    void on_btnAgregar_clicked();

    //void on_txtBuscar_textChanged(const QString &arg1);

    void on_btnCalcular_clicked();

private:
    Ui::MainWindow *ui;

    enum Columna{
      ID, NOMBRE, MATERIA, PARCIAL, CALIFICACION
    };
};
#endif // MAINWINDOW_H
