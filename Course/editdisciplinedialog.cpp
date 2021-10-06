#include "editdisciplinedialog.h"
#include "ui_editdisciplinedialog.h"

EditDisciplineDialog::EditDisciplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDisciplineDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
}

EditDisciplineDialog::~EditDisciplineDialog()
{
    delete ui;
}

void EditDisciplineDialog::loadName(QString _name)
{
    name = _name;
    ui->disciplineLine->setText(name);
}

void EditDisciplineDialog::on_editButton_clicked()
{
    if(ui->disciplineLine->text() != name)
    {
        QSqlQuery query;
        query.prepare("SELECT edit_discipline(?,?)");
        query.addBindValue(name);
        query.addBindValue(ui->disciplineLine->text());
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

