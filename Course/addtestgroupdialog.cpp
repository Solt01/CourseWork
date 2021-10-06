#include "addtestgroupdialog.h"
#include "ui_addtestgroupdialog.h"
#include "QSqlError"
AddTestGroupDialog::AddTestGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTestGroupDialog)
{
    ui->setupUi(this);
    setWindowTitle("Группа");

}

AddTestGroupDialog::~AddTestGroupDialog()
{
    delete ui;
}

void AddTestGroupDialog::loadData(QString _nameDiscipline)
{
    disciplineName = _nameDiscipline;

    QSqlQueryModel * modelGroup = new QSqlQueryModel(this);
    modelGroup->setQuery("SELECT group_name FROM groups_table");
    ui->groupBox->setModel(modelGroup);

    QSqlQuery query;
    query.prepare("SELECT * FROM lecturers_table");
    if(query.exec())
        while (query.next())
    {
        lecturers.insert(query.value(4).toString(),query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
        ui->lecturerBox->addItem(query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
    }
}

void AddTestGroupDialog::on_addGroupButton_clicked()
{
    if(ui->dateLine->text().isEmpty() or ui->groupBox->currentIndex() == -1 or ui->lecturerBox->currentIndex() == -1)
        QMessageBox::warning(this,"Ошибка","Не все поля заполнены");
    else{
        QSqlQuery query;
        query.prepare("SELECT add_tests_groups(?,?,?,?)");
        query.addBindValue(ui->groupBox->currentText());
        query.addBindValue(disciplineName);
        query.addBindValue(lecturers.key(ui->lecturerBox->currentText()));
        query.addBindValue(ui->dateLine->text());
        if(query.exec())
        {
            while(query.next()){
                if(query.value(0).toInt() == 0)
                {
                    QMessageBox::warning(this,"Ошибка","Данная группа уже добавлена");
                }else if(query.value(0).toInt() == 1){
                    this->close();
                }else if(query.value(0).toInt() == 2){
                    QMessageBox::warning(this,"Ошибка","В данной группе нет студентов");
                }
            }
        }else{

            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }

    }
}

