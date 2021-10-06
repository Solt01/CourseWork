#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>
#include <QFileDialog>
#include <QSqlQueryModel>

#include "connectdbdialog.h"
#include "addgroupdialog.h"
#include "addstudentdialog.h"
#include "adddisciplinedialog.h"
#include "addlecturerdialog.h"
#include "editgroupdialog.h"
#include "editstudentdialog.h"
#include "editdisciplinedialog.h"
#include "editlecturerdialog.h"
#include "progressmainwindow.h"
#include "attendancewindow.h"
#include "addtestsdialog.h"
#include "testgroupwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateGroupTable();

    void updateStudentTable();

    void updateDisciplineTable();

    void updateTestsTable();

    //void updateExamsTable();

    void updateLecturerTable();

private slots:
    /*обработка кнопок в разделе ФАЙЛ*/
    void on_newFileButton_clicked();

    void on_openFileButton_clicked();

    void on_saveFileButton_clicked();

    void on_quitFileButton_clicked();//выход через файл

    /*обработка кнопок добавления и удаления записей в таблицах*/
    void on_addGroupButton_clicked();
    void on_removeGroupButton_clicked();

    void on_addStudentButton_clicked();
    void on_removeStudentButton_clicked();

    void on_addDisciplineButton_clicked();
    void on_removeDisciplineButton_clicked();

    void on_addLecturerButton_clicked();
    void on_removeLecturerButton_clicked();


    /*редактирование записей в таблицах*/
    void editGroup();

    void editStudent();

    void editDiscipline();

    void editLecturer();

    void progressStudent();

    void attendanceStudent();

    void testGroup();

    /*обработка нажатия правой кнопки мыши в таблице*/
    void groupSlotCustomMenuRequested(QPoint pos);

    void studentSlotCustomMenuRequested(QPoint pos);

    void disciplineSlotCustomMenuRequested(QPoint pos);

    void lecturerSlotCustomMenuRequested(QPoint pos);

    void testsSlotCustomMenuRequested(QPoint pos);

    void querySlotCustomMenuRequested(QPoint pos);

    /*обработка выделенной строки*/
    void on_groupsTable_pressed(const QModelIndex &index);

    void on_studentsTable_pressed(const QModelIndex &index);

    void on_disciplinesTable_pressed(const QModelIndex &index);

    void on_lecturersTable_pressed(const QModelIndex &index);

    void on_addTestButton_clicked();

    void on_removeTestButton_clicked();

    void on_testsTable_pressed(const QModelIndex &index);


    /*Запросы из пункта 2*/
    void queryA();

    void queryBPrint();

    void queryBAdd();

    void queryBUpdate();

    void queryBDelete();

    void queryCSelect();

    void queryCFrom();

    void queryCWhere();

    void queryD();

    void queryE();

private:
    Ui::MainWindow *ui;
    AttendanceWindow * attendace;

    QSqlTableModel *modelGroups;

    QSqlQueryModel *modelStudents;

    QSqlTableModel *modelDisciplines;

    QSqlTableModel *modelProgress;

    QSqlTableModel *modelAttendance;

    QSqlQueryModel *modelTests;

    QSqlTableModel *modelLecturer;

    QSqlQueryModel *modelQueryA;

    QSqlQueryModel *modelQueryB;

    QSqlQueryModel *modelQueryC;

    QSqlQueryModel *modelQueryD;

    QSqlQueryModel *modelQueryE;

    QSqlDatabase db;

    QString saveFileName;

    QString openFileName;

    void createMenuFile();

    void initializingUi();

    void LoadDB(); // подключение к БД

    void closeEvent(QCloseEvent *event); //выход через крестик

    int rowGroup = -1;
    int rowStudent = -1;
    int rowDiscipline = -1;
    int rowLecturer = -1;
    int rowTests = -1;
};
#endif // MAINWINDOW_H
