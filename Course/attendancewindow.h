#ifndef ATTENDANCEWINDOW_H
#define ATTENDANCEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>
#include <QSqlQueryModel>
#include "addattendancesdialog.h"
namespace Ui {
class AttendanceWindow;
}

class AttendanceWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString studentIdCard;
    int countAttendance = 0;
    QMap <QString,QString> lecturers;

    explicit AttendanceWindow(QWidget *parent,QString _studentIdCard);
    ~AttendanceWindow();

    void updateAttendaceTable();


    void increaseCountAttendace();


private slots:
    void on_attendanceTable_pressed(const QModelIndex &index);

    void on_addAttendanceButton_clicked();

    void on_removeAttendanceButton_clicked();

    void attendanceSlotCustomMenuRequested(QPoint pos);
private:
    Ui::AttendanceWindow *ui;

    QSqlQueryModel *modelAttendance;

    void initializingUi();

    int rowAttendance = -1;

    void editAttendance();
};

#endif // ATTENDANCEWINDOW_H
