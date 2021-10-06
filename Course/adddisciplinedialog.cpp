#include "adddisciplinedialog.h"
#include "ui_adddisciplinedialog.h"

AddDisciplineDialog::AddDisciplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDisciplineDialog)
{
    ui->setupUi(this);
    setWindowTitle("Дисциплина");

}

AddDisciplineDialog::~AddDisciplineDialog()
{
    delete ui;
}

void AddDisciplineDialog::on_addDisciplineButton_clicked()
{
    if(ui->disciplineLine->text().isEmpty())
        QMessageBox::warning(this,"Ошибка","Вы забили заполнить дисциплину");
    else{
        QSqlQuery query;
        query.prepare("SELECT add_discipline(?)");
        query.addBindValue(ui->disciplineLine->text());

        if(query.exec()){
            while(query.next()){
                if(query.value(0).toInt() == 0)
                {
                    QMessageBox::warning(this,"Ошибка","Запись уже существует!");
                }else{
                    this->close();
                }
            }
          }else{
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }

    }

}


