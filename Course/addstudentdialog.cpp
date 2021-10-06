#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"

AddStudentDialog::AddStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Студент");
    addGroupBox();

}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}

void AddStudentDialog::on_addStudentButton_clicked()
{
    if(ui->groupBox->currentIndex() == -1 or ui->firstNameLine->text().isEmpty() or
            ui->lastNameLine->text().isEmpty() or
            ui->patronymicLine->text().isEmpty() or
            ui->studentIdCardLine->text().isEmpty())
    {
        QMessageBox::warning(this,"Ошибка","Не все поля заполнены");
    }else{
        groupName = ui->groupBox->currentText();
        firstName = ui->firstNameLine->text();
        lastName = ui->lastNameLine->text();
        patronymic = ui->patronymicLine->text();
        studentIdCard = ui->studentIdCardLine->text();

        QSqlQuery query;
        query.prepare("SELECT add_student(?,?,?,?,?)");
        query.addBindValue(groupName);
        query.addBindValue(lastName);
        query.addBindValue(firstName);
        query.addBindValue(patronymic);
        query.addBindValue(studentIdCard);

        if(query.exec()){
            while(query.next()){
                if(query.value(0).toInt() == 0)
                {
                    QMessageBox::warning(this,"Ошибка","Такой студент уже существует!");
                }else if(query.value(0).toInt() == 1)
                {
                    QMessageBox::warning(this,"Ошибка","Студент с таким номером студенческого билета уже существует!");
                }else if(query.value(0).toInt() == 2){
                    this->close();
                }
            }
        }else{
            qDebug() << query.lastError();
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }
    }
}

void AddStudentDialog::addGroupBox()
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

