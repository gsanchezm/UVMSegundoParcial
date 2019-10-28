#ifndef SEARCHSTUDENTDIALOG_H
#define SEARCHSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class searchStudentDialog;
}

class searchStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchStudentDialog(QWidget *parent = nullptr);
    ~searchStudentDialog();

private:
    Ui::searchStudentDialog *ui;
};

#endif // SEARCHSTUDENTDIALOG_H
