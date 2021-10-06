#ifndef ADDSCORESTUDENTDIALOG_H
#define ADDSCORESTUDENTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QShowEvent>
#include <QSqlQueryModel>
namespace Ui {
class AddScoreStudentDialog;
}

class AddScoreStudentDialog : public QDialog
{
    Q_OBJECT

public:
    QString group_name,lecturer_id_card,date_test,
    discipline_name, student_id, test_flag;
    explicit AddScoreStudentDialog(QWidget *parent = nullptr);
    ~AddScoreStudentDialog();

    void loadData(QString _group_name, QString _lecturer_id_card, QString _date_test,
                  QString _discipline_name, QString _student_id,
                  QString _studentName,QSqlQueryModel * _modelStudent);
    virtual void  showEvent(QShowEvent *event);
private slots:
    void on_addScoreButton_clicked();

private:
    Ui::AddScoreStudentDialog *ui;
    QSqlQueryModel * modelStudent;
};

#endif // ADDSCORESTUDENTDIALOG_H
