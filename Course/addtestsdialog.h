#ifndef ADDTESTSDIALOG_H
#define ADDTESTSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlQuery>
namespace Ui {
class AddTestsDialog;
}

class AddTestsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTestsDialog(QWidget *parent = nullptr);
    ~AddTestsDialog();

    void loadDate();

private slots:
    void on_addTestButton_clicked();

private:
    Ui::AddTestsDialog *ui;
};

#endif // ADDTESTSDIALOG_H
