#ifndef ADDPROGRESSDIALOG_H
#define ADDPROGRESSDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
#include "attendancewindow.h"
namespace Ui {
class AddProgressDialog;
}

class AddProgressDialog : public QDialog
{
    Q_OBJECT

public:
    QString studentId;
    QMap <QString,QString> lecturers;
    int countScore;
    explicit AddProgressDialog(QWidget *parent = nullptr);
    ~AddProgressDialog();

    void addDate(QString _studentId,int _countScore);

private slots:
    void on_addProgressButton_clicked();

private:
    Ui::AddProgressDialog *ui;

    void disciplineBox();

    void lecturerBox();


};

#endif // ADDPROGRESSDIALOG_H
