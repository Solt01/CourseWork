#include "addlecturerdialog.h"
#include "ui_addlecturerdialog.h"

AddLecturerDialog::AddLecturerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLecturerDialog)
{
    ui->setupUi(this);
    setWindowTitle("Преподаватель");
    resize(280,85);
}

AddLecturerDialog::~AddLecturerDialog()
{
    delete ui;
}

void AddLecturerDialog::on_addDisciplineButton_clicked()
{
    if(ui->firstNameLine->text().isEmpty() or
            ui->lastNameLine->text().isEmpty() or
            ui->patronymicLine->text().isEmpty() or
            ui->lecturerIdCard->text().isEmpty())
    {
        QMessageBox::warning(this,"Ошибка","Не все поля заполнены");
    }else{
        firstName = ui->firstNameLine->text();
        lastName = ui->lastNameLine->text();
        patronymic = ui->patronymicLine->text();
        lecturerIdCard = ui->lecturerIdCard->text();

        QSqlQuery query;
        query.prepare("SELECT add_lecturer(?,?,?,?)");
        query.addBindValue(lastName);
        query.addBindValue(firstName);
        query.addBindValue(patronymic);
        query.addBindValue(lecturerIdCard);

        if(query.exec()){
            while(query.next()){
                if(query.value(0).toInt() == 0)
                {
                    QMessageBox::warning(this,"Ошибка","Такой преподаватель уже существует!");
                }else if(query.value(0).toInt() == 1)
                {
                    QMessageBox::warning(this,"Ошибка","Преподаватель с таким номером удостоверения уже существует!");
                }else{
                    this->close();
                }
            }
        }else{
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }
    }
}
