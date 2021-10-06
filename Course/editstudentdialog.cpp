#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

EditStudentDialog::EditStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
    addGroupBox();
}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::loadDate(QString _groupName, QString _lastName, QString _firstName, QString _patronymic, QString _studentIdCard)
{
    groupName = _groupName;
    lastName = _lastName;
    firstName = _firstName;
    patronymic = _patronymic;
    studentIdCard = _studentIdCard;

    ui->groupBox->setCurrentText(groupName);
    ui->lastNameLine->setText(lastName);
    ui->firstNameLine->setText(firstName);
    ui->patronymicLine->setText(patronymic);
    ui->studentIdCardLine->setText(studentIdCard);
}

void EditStudentDialog::on_editStudentButton_clicked()
{
    if(ui->groupBox->currentText() != groupName or
            ui->lastNameLine->text() != lastName or
            ui->firstNameLine->text() != firstName or
            ui->patronymicLine->text() != patronymic or
            ui->studentIdCardLine->text() != studentIdCard)
    {
        QSqlQuery query;
        query.prepare("SELECT edit_student(?,?,?,?,?,?)");
        query.addBindValue(studentIdCard);

        query.addBindValue(ui->groupBox->currentText());
        query.addBindValue(ui->lastNameLine->text());
        query.addBindValue(ui->firstNameLine->text());
        query.addBindValue(ui->patronymicLine->text());
        query.addBindValue(ui->studentIdCardLine->text());

        if(query.exec()){
            while(query.next()){
                if(query.value(0).toInt() == 0)
                {
                    QMessageBox::warning(this,"Ошибка","Такой студент уже существует!");
                }else if(query.value(0).toInt() == 1)
                {
                    QMessageBox::warning(this,"Ошибка","Студент с таким номером студенческого билета уже существует!");
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

void EditStudentDialog::addGroupBox()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM groups_table");
    query.exec();

    QSqlRecord rec = query.record();
    int nameCol = rec.indexOf("group_name"); // index of the field "group_name"

    if(query.exec())
        while (query.next())
            ui->groupBox->addItem(query.value(nameCol).toString()); // output all group_name
}

