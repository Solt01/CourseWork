#include "addscorestudentdialog.h"
#include "ui_addscorestudentdialog.h"
AddScoreStudentDialog::AddScoreStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddScoreStudentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Оценка");

    ui->scoreBox->addItem("5");
    ui->scoreBox->addItem("4");
    ui->scoreBox->addItem("3");
    ui->scoreBox->addItem("2");
    ui->scoreBox->addItem("Неявка");

}

AddScoreStudentDialog::~AddScoreStudentDialog()
{
    delete ui;
}

void AddScoreStudentDialog::loadData(QString _group_name, QString _lecturer_id_card, QString _date_test, QString _discipline_name, QString _student_id, QString _studentName, QSqlQueryModel *_modelStudent)
{
    group_name = _group_name;
    lecturer_id_card = _lecturer_id_card;
    date_test = _date_test;
    discipline_name = _discipline_name;
    student_id = _student_id;

    ui->studentNameLine->setText(_studentName);
    modelStudent = _modelStudent;
}

void AddScoreStudentDialog::showEvent(QShowEvent *event)
{

}

void AddScoreStudentDialog::on_addScoreButton_clicked()
{
    if(ui->scoreBox->currentIndex() == -1)
    {
        QMessageBox::warning(this,"Ошибка","Вы забыли поставить оценку");
    }else{
        QString queryGroup = "'" + group_name + "'" + ")";
        QString queryDiscipline = "'" + discipline_name + "'" + ")";
        QSqlQuery query;
        query.prepare("SELECT add_score_tests(?,?,?,?,?,?)");
        query.addBindValue(group_name);
        query.addBindValue(lecturer_id_card);
        query.addBindValue(date_test);
        query.addBindValue(discipline_name);
        query.addBindValue(student_id);
        query.addBindValue(ui->scoreBox->currentText());
        if(query.exec()){
            while(query.next()){
                if(query.value(0).toInt() == 1)
                {
                    this->close();
                    modelStudent->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic, "
                                            "students_table.studentIdCard, Score.test_flag "
                                            "FROM students_table LEFT JOIN (SELECT student_id,test_flag "
                                            "FROM tests_table LEFT JOIN tests_disciplines_table ON tests_table.discipline_id = tests_disciplines_table.id "
                                            "WHERE tests_table.discipline_id = "
                                            "(SELECT id FROM tests_disciplines_table WHERE discipline_id = "
                                            "(SELECT id FROM disciplines_table WHERE discipline_name = " + queryDiscipline + ")) Score ON students_table.id = Score.student_id "
                                            "WHERE students_table.group_id = "
                                            "(SELECT id FROM groups_table WHERE group_name = " + queryGroup);
                }
            }
        }else{
            qDebug() << query.lastError();
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }
    }
}

