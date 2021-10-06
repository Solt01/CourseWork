#ifndef ADDDISCIPLINEDIALOG_H
#define ADDDISCIPLINEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
namespace Ui {
class AddDisciplineDialog;
}

class AddDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    QString nameDiscipline;
    explicit AddDisciplineDialog(QWidget *parent = nullptr);
    ~AddDisciplineDialog();

private slots:
    void on_addDisciplineButton_clicked();

private:
    Ui::AddDisciplineDialog *ui;
};

#endif // ADDDISCIPLINEDIALOG_H
