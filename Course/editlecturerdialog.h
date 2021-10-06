#ifndef EDITLECTURERDIALOG_H
#define EDITLECTURERDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class EditLecturerDialog;
}

class EditLecturerDialog : public QDialog
{
    Q_OBJECT

public:
    QString firstName,lastName,patronymic,lecturerIdCard;
    explicit EditLecturerDialog(QWidget *parent = nullptr);
    ~EditLecturerDialog();
    void loadDate(QString _lastName,QString _firstName,
                  QString _patronymic,
                  QString _lecturerIdCard);
private slots:
    void on_editLecturerButton_clicked();

private:
    Ui::EditLecturerDialog *ui;
};

#endif // EDITLECTURERDIALOG_H
