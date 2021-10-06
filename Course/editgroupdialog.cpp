#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"

EditGroupDialog::EditGroupDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
}

EditGroupDialog::~EditGroupDialog()
{
    delete ui;
}

void EditGroupDialog::loadName(QString _name)
{
    name = _name;
    ui->nameLine->setText(name);
}

void EditGroupDialog::on_editGroupButton_clicked()
{
    if(ui->nameLine->text() != name)
    {
        QSqlQuery query;
        query.prepare("SELECT edit_group(?,?)");
        query.addBindValue(name);
        query.addBindValue(ui->nameLine->text());
        if(query.exec()){
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
    else{
        this->close();
    }

}

