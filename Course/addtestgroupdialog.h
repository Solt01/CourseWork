#ifndef ADDTESTGROUPDIALOG_H
#define ADDTESTGROUPDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlQuery>
namespace Ui {
class AddTestGroupDialog;
}

class AddTestGroupDialog : public QDialog
{
    Q_OBJECT

public:

    QMap <QString,QString> lecturers;
    explicit AddTestGroupDialog(QWidget *parent = nullptr);
    ~AddTestGroupDialog();

    void loadData(QString _nameDiscipline);

private slots:
    void on_addGroupButton_clicked();

private:
    Ui::AddTestGroupDialog *ui;
    QString disciplineName;
};

#endif // ADDTESTGROUPDIALOG_H
