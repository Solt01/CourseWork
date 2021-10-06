#ifndef PROGRESSMAINWINDOW_H
#define PROGRESSMAINWINDOW_H

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

#include "addprogressdialog.h"
#include "editprogressdialog.h"
#include "attendancewindow.h"

namespace Ui {
class ProgressMainWindow;
}

class ProgressMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString studentIdCard;
    int countScore = 0;
    explicit ProgressMainWindow(QWidget *parent, QString _studentIdCard);
    ~ProgressMainWindow();

    void updateProgressTable();

    void CheckTable(AttendanceWindow *_attendance);

private slots:
    void on_progressTable_pressed(const QModelIndex &index);

    void on_removeProgressButton_clicked();

    void on_addProgressButton_clicked();

    /*обработка нажатия правой кнопки мыши в таблице*/
    void progressSlotCustomMenuRequested(QPoint pos);

    void editProgress();

private:
    Ui::ProgressMainWindow *ui;

    QSqlQueryModel *modelProgress;

    void initializingUi();

    int rowProgress = -1;

    AttendanceWindow *attendance;

};

#endif // PROGRESSMAINWINDOW_H
