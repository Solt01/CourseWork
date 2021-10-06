#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
namespace Ui {
class AddGroupDialog;
}

class AddGroupDialog : public QDialog
{
    Q_OBJECT

public:
    QString nameGroup;
    explicit AddGroupDialog(QWidget *parent = nullptr);
    ~AddGroupDialog();

private slots:
    void on_addGroupButton_clicked();

private:
    Ui::AddGroupDialog *ui;
};

#endif // ADDGROUPDIALOG_H
