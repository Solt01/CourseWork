#include "editlecturerdialog.h"
#include "ui_editlecturerdialog.h"

EditLecturerDialog::EditLecturerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLecturerDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
}

EditLecturerDialog::~EditLecturerDialog()
{
    delete ui;
}

void EditLecturerDialog::loadDate(QString _lastName, QString _firstName, QString _patronymic, QString _lecturerIdCard)
{
    lastName = _lastName;
    firstName = _firstName;
    patronymic = _patronymic;
    lecturerIdCard = _lecturerIdCard;

    ui->lastNameLine->setText(lastName);
    ui->firstNameLine->setText(firstName);
    ui->patronymicLine->setText(patronymic);
    ui->lecturerIdCard->setText(lecturerIdCard);
}

void EditLecturerDialog::on_editLecturerButton_clicked()
{
    if(ui->lastNameLine->text() != lastName or
            ui->firstNameLine->text() != firstName or
            ui->patronymicLine->text() != patronymic or
            ui->lecturerIdCard->text() != lecturerIdCard)
    {
        QSqlQuery query;
        query.prepare("SELECT edit_lecturer(?,?,?,?,?)");
        query.addBindValue(lecturerIdCard);
        query.addBindValue(ui->lastNameLine->text());
        query.addBindValue(ui->firstNameLine->text());
        query.addBindValue(ui->patronymicLine->text());
        query.addBindValue(ui->lecturerIdCard->text());

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
    else{
        this->close();
    }
}


