#ifndef ADDLECTURERDIALOG_H
#define ADDLECTURERDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class AddLecturerDialog;
}

class AddLecturerDialog : public QDialog
{
    Q_OBJECT

public:
    QString disciplineName,firstName,lastName,patronymic,lecturerIdCard;
    explicit AddLecturerDialog(QWidget *parent = nullptr);
    ~AddLecturerDialog();

private slots:
    void on_addDisciplineButton_clicked();

private:
    Ui::AddLecturerDialog *ui;
};

#endif // ADDLECTURERDIALOG_H
