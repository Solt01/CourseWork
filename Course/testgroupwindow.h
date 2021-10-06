#ifndef TESTGROUPWINDOW_H
#define TESTGROUPWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include "addtestgroupdialog.h"
#include "studenttestwindow.h"
#include "edittestgroupdialog.h"
namespace Ui {
class TestGroupWindow;
}

class TestGroupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestGroupWindow(QWidget *parent,QString _disciplineName);
    ~TestGroupWindow();

    void updateTestGroup();

private slots:
    void on_groupTable_pressed(const QModelIndex &index);

    void on_addGroupButton_clicked();

    void on_removeGroupButton_clicked();

    void groupSlotCustomMenuRequested(QPoint pos);

    void studentTest();

    void editGroupTest();
private:
    Ui::TestGroupWindow *ui;

    void initializingUi();

    QSqlQueryModel * modelGroup;

    QString disciplineName;



    int rowGroup = -1;
};

#endif // TESTGROUPWINDOW_H
