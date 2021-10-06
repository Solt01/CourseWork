#ifndef EDITPROGRESSDIALOG_H
#define EDITPROGRESSDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class EditProgressDialog;
}

class EditProgressDialog : public QDialog
{
    Q_OBJECT

public:
    QString score,dateScore, studentIdCard;
    int numberScore;
    explicit EditProgressDialog(QWidget *parent = nullptr);
    ~EditProgressDialog();

    void loadDate(QString _score, QString _dateScore,int _numberScore, QString _studentIdCard);

private slots:
    void on_editProgressButton_clicked();

private:
    Ui::EditProgressDialog *ui;
};

#endif // EDITPROGRESSDIALOG_H
