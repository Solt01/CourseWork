#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class EditGroupDialog;
}

class EditGroupDialog : public QDialog
{
    Q_OBJECT

public:
    QString name;
    explicit EditGroupDialog(QWidget *parent = nullptr);

    ~EditGroupDialog();

    void loadName(QString _name);

private slots:
    void on_editGroupButton_clicked();

private:
    Ui::EditGroupDialog *ui;
};

#endif // EDITGROUPDIALOG_H
