#ifndef ADDATTENDANCESDIALOG_H
#define ADDATTENDANCESDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class AddAttendancesDialog;
}

class AddAttendancesDialog : public QDialog
{
    Q_OBJECT

public:
    QString studentId;
    QMap <QString,QString> lecturers;
    int countAttendance;
    explicit AddAttendancesDialog(QWidget *parent = nullptr);
    ~AddAttendancesDialog();


    void addDate(QString _studentId,int _countAttendance);

private slots:
    void on_addAttendanceButton_clicked();

private:
    Ui::AddAttendancesDialog *ui;

    void attendancesBox();

    void disciplineBox();

    void lecturerBox();
};

#endif // ADDATTENDANCESDIALOG_H
