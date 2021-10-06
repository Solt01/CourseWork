#ifndef EDITDISCIPLINEDIALOG_H
#define EDITDISCIPLINEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class EditDisciplineDialog;
}

class EditDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    QString name;
    explicit EditDisciplineDialog(QWidget *parent = nullptr);
    ~EditDisciplineDialog();

    void loadName(QString _name);

private slots:
    void on_editButton_clicked();

private:
    Ui::EditDisciplineDialog *ui;
};

#endif // EDITDISCIPLINEDIALOG_H
