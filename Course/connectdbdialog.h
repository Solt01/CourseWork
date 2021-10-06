#ifndef CONNECTDBDIALOG_H
#define CONNECTDBDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
namespace Ui {
class ConnectDBDialog;
}

class ConnectDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDBDialog(QWidget *parent,QSqlDatabase& db);
    ~ConnectDBDialog();

private slots:
    void on_connectButton_clicked();


private:
    Ui::ConnectDBDialog *ui;
    QSqlDatabase* db;
};

#endif // CONNECTDBDIALOG_H
