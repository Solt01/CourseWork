#ifndef STUDENTTESTWINDOW_H
#define STUDENTTESTWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPushButton>
#include "addscorestudentdialog.h"
#include "editscorestudentdialog.h"
namespace Ui {
class StudentTestWindow;
}

class StudentTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    AddScoreStudentDialog  score;
    QString queryGroup,queryDiscipline;
    QString groupName,disciplineName,lecturerId,dateTest;
    explicit StudentTestWindow(QWidget *parent, QString _groupName, QString _disciplineName, QString _lecturer_id, QString _date_test);
    ~StudentTestWindow();



private slots:
    void on_studentTable_pressed(const QModelIndex &index);

    void putScoreStudent();

    void editScoreStudent();

    void updateStudentGroup();

    void studentSlotCustomMenuRequested(QPoint pos);



private:
    Ui::StudentTestWindow *ui;

    void initializingUi();

    QSqlQueryModel * modelStudent;

    int rowStudent = -1;
};

#endif // STUDENTTESTWINDOW_H
