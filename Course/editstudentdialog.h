#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class EditStudentDialog;
}

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:
    QString groupName,firstName,lastName,patronymic,studentIdCard;

    explicit EditStudentDialog(QWidget *parent = nullptr);
    ~EditStudentDialog();

    void loadDate(QString _groupName,QString _lastName,QString _firstName,
                  QString _patronymic,
                  QString _studentIdCard);

private slots:
    void on_editStudentButton_clicked();

private:
    Ui::EditStudentDialog *ui;
    void addGroupBox();
};

#endif // EDITSTUDENTDIALOG_H
