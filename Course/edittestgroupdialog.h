#ifndef EDITTESTGROUPDIALOG_H
#define EDITTESTGROUPDIALOG_H

#include <QDialog>
#include <QMap>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
namespace Ui {
class EditTestGroupDialog;
}

class EditTestGroupDialog : public QDialog
{
    Q_OBJECT

public:
    QMap <QString,QString> lecturers;
    QString disciplineName,lecturer,dateTest;
    explicit EditTestGroupDialog(QWidget *parent, QString _group_name, QString _disciplineName, QString _lecturerId, QString _dateTest, QSqlQueryModel *_modelGroup);
    ~EditTestGroupDialog();

private slots:
    void on_editGroupButton_clicked();

private:
    Ui::EditTestGroupDialog *ui;

    QSqlQueryModel * modelGroup;
};

#endif // EDITTESTGROUPDIALOG_H
