#ifndef EDITSCORESTUDENTDIALOG_H
#define EDITSCORESTUDENTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>

namespace Ui {
class EditScoreStudentDialog;
}

class EditScoreStudentDialog : public QDialog
{
    Q_OBJECT

public:
    QString groupName,disciplineName, testScore, studentName,studentIdCard;
    explicit EditScoreStudentDialog(QWidget *paren, QString _groupName, QString _disciplineName,
                                    QString _testScore, QString _studentName,
                                    QString _studentIdCard, QSqlQueryModel *_modelStudents);
    ~EditScoreStudentDialog();

private slots:
    void on_editScoreButton_clicked();

private:
    Ui::EditScoreStudentDialog *ui;
    QSqlQueryModel * modelStudents;
};

#endif // EDITSCORESTUDENTDIALOG_H
