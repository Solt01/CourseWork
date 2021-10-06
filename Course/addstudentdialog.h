#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog
{
    Q_OBJECT

public:
    QString groupName,firstName,lastName,patronymic,studentIdCard;

    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog();



private slots:
    void on_addStudentButton_clicked();

private:
    Ui::AddStudentDialog *ui;

    void addGroupBox();
};

#endif // ADDSTUDENTDIALOG_H
