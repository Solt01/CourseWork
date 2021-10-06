#include "editscorestudentdialog.h"
#include "ui_editscorestudentdialog.h"

EditScoreStudentDialog::EditScoreStudentDialog(QWidget *parent, QString _groupName,QString _disciplineName,
                                               QString _testScore, QString _studentName,
                                               QString _studentIdCard, QSqlQueryModel *_modelStudents) :
    QDialog(parent),
    ui(new Ui::EditScoreStudentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
    groupName = _groupName;
    disciplineName = _disciplineName;
    testScore = _testScore;
    studentIdCard = _studentIdCard;
    studentName = _studentName;
    modelStudents = _modelStudents;
    ui->studentNameLine->setText(_studentName);
    ui->scoreLine->setText(_testScore);
}

EditScoreStudentDialog::~EditScoreStudentDialog()
{
    delete ui;
}

void EditScoreStudentDialog::on_editScoreButton_clicked()
{
    if(ui->scoreLine->text().isEmpty()){
        QMessageBox::warning(this,"Ошибка","Вы не поставили оценку");
    }else{
        if(ui->scoreLine->text() != testScore){
            QString queryDiscipline = "'" + disciplineName + "'" + ")";
            QString queryGroup = "'" + groupName + "'" + ")";

            QSqlQuery query;
            query.prepare("SELECT edit_tests_score(?,?,?)");
            query.addBindValue(disciplineName);
            query.addBindValue(ui->scoreLine->text());
            query.addBindValue(studentIdCard);

            if(query.exec()){
                while(query.next()){
                    if(query.value(0).toInt() == 1)
                    {

                        modelStudents->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic, "
                            "students_table.studentIdCard, Score.test_flag "
                            "FROM students_table LEFT JOIN (SELECT student_id,test_flag "
                            "FROM tests_table LEFT JOIN tests_disciplines_table ON tests_table.discipline_id = tests_disciplines_table.id "
                            "WHERE tests_table.discipline_id = "
                            "(SELECT id FROM tests_disciplines_table WHERE discipline_id = "
                            "(SELECT id FROM disciplines_table WHERE discipline_name = " + queryDiscipline + ")) Score ON students_table.id = Score.student_id "
                            "WHERE students_table.group_id = "
                            "(SELECT id FROM groups_table WHERE group_name = " + queryGroup);;
                        this->close();
                    }
                }
            }else{
                QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
            }
        }
    }
}

