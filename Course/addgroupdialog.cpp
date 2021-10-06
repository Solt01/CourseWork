#include "addgroupdialog.h"
#include "ui_addgroupdialog.h"
#include <QDebug>
#include <QSqlError>
AddGroupDialog::AddGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGroupDialog)
{
    ui->setupUi(this);
    setWindowTitle("Группа");
}

AddGroupDialog::~AddGroupDialog()
{
    delete ui;
}

void AddGroupDialog::on_addGroupButton_clicked()
{
    if(ui->groupLine->text().isEmpty())
        QMessageBox::warning(this,"Ошибка","Вы забыли ввести название группы");
    else{
        nameGroup = ui->groupLine->text();
        QSqlQuery query;
        query.prepare("SELECT add_group(?)");
        query.addBindValue(nameGroup);

        if(query.exec())
        {
            while(query.next()){

                if(!query.value(0).toInt())
                {
                    QMessageBox::warning(this,"Ошибка","Запись уже существует");
                }else{
                    this->close();
                }
            }
        }else{
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }

    }
}

