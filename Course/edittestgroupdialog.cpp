#include "edittestgroupdialog.h"
#include "ui_edittestgroupdialog.h"

EditTestGroupDialog::EditTestGroupDialog(QWidget *parent,QString _group_name,QString _disciplineName, QString _lecturerId, QString _dateTest,QSqlQueryModel *_modelGroup) :
    QDialog(parent),
    ui(new Ui::EditTestGroupDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
    disciplineName = _disciplineName;
    dateTest = _dateTest;
    lecturer = _lecturerId;
    modelGroup = _modelGroup;

    ui->groupLine->setText(_group_name);
    ui->dateTestLine->setText(_dateTest);
    QSqlQuery query;
    query.prepare("SELECT * FROM lecturers_table");
    if(query.exec())
        while (query.next())
    {
        lecturers.insert(query.value(4).toString(),query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
        ui->lecturerBox->addItem(query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
    }
    ui->lecturerBox->setCurrentText(lecturers.value(_lecturerId));
}

EditTestGroupDialog::~EditTestGroupDialog()
{
    delete ui;
}

void EditTestGroupDialog::on_editGroupButton_clicked()
{
    if(ui->lecturerBox->currentIndex() == -1 or ui->dateTestLine->text().isEmpty() or ui->dateTestLine->text().isEmpty()){
        QMessageBox::warning(this,"Ошибка","Вы не заполнили все поля");
    }else{
        if(dateTest != ui->dateTestLine->text() or lecturer != lecturers.key(ui->lecturerBox->currentText())){
            QString queryDiscipline = "'" + disciplineName + "'" + ")";

            QSqlQuery query;
            query.prepare("SELECT edit_tests_group(?,?,?,?)");
            query.addBindValue(ui->groupLine->text());
            query.addBindValue(disciplineName);
            query.addBindValue(lecturers.key(ui->lecturerBox->currentText()));
            query.addBindValue(ui->dateTestLine->text());
            if(query.exec()){
                while(query.next()){
                    if(query.value(0).toInt() == 1)
                    {

                        modelGroup->setQuery("SELECT groups_table.group_name, lecturers_table.last_name || ' ' || lecturers_table.first_name || ' ' || lecturers_table.patronymic, "
                        "lecturers_table.lecturer_id_card, tests_groups_table.date_test, tests_groups_table.discipline_id "
                        "FROM tests_groups_table JOIN groups_table ON groups_table.Id = tests_groups_table.group_id "
                        "JOIN lecturers_table ON lecturers_table.Id = tests_groups_table.lecturer_id "
                        "JOIN tests_disciplines_table ON tests_disciplines_table.Id = tests_groups_table.discipline_id WHERE "
                        "tests_disciplines_table.discipline_id = (SELECT id FROM disciplines_table WHERE discipline_name = " + queryDiscipline);
                        this->close();
                    }
                }
            }else{
                QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
            }
        }
    }
}

