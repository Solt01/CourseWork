#include "addprogressdialog.h"
#include "ui_addprogressdialog.h"

AddProgressDialog::AddProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProgressDialog)
{
    ui->setupUi(this);
    setWindowTitle("Оценка");

    disciplineBox();
    lecturerBox();
}

AddProgressDialog::~AddProgressDialog()
{
    delete ui;
}

void AddProgressDialog::addDate(QString _studentId, int _countScore)
{
        studentId = _studentId;
        countScore = _countScore;
}

void AddProgressDialog::on_addProgressButton_clicked()
{
    QString q = "'" + studentId + "'";
    QSqlQuery query1;
    query1.prepare("SELECT max(number_attendance) FROM attendances_table WHERE student_id = "
                                "(SELECT id FROM students_table WHERE studentIdCard = " + q + ')');
    query1.exec();
    int countAttendance = query1.value(0).toInt();
    ++countAttendance;
    if(ui->scoreLine->text().isEmpty() or ui->dateLine->text().isEmpty() or
            ui->disciplineBox->currentIndex() == -1 or ui->lecturerBox->currentIndex() == -1)
        QMessageBox::warning(this,"Ошибка","Не все поля заполнены");
    else{
        ++countScore;
        QSqlQuery query;
        query.prepare("SELECT add_progress(?,?,?,?,?,?)");
        query.addBindValue(countScore);
        query.addBindValue(ui->dateLine->text());
        query.addBindValue(ui->scoreLine->text().toInt());
        query.addBindValue(ui->disciplineBox->currentText());
        query.addBindValue(studentId);
        query.addBindValue(lecturers.key(ui->lecturerBox->currentText()));
        if(query.exec())
        {
            while(query.next()){
                if(query.value(0).toInt() == 1)
                {
                    /*
                    QSqlQuery query;
                    query.prepare("SELECT add_attendances(?,?,?,?,?,?)");
                    query.addBindValue(countAttendance);
                    query.addBindValue(ui->dateLine->text());
                    query.addBindValue("Б");
                    query.addBindValue(ui->disciplineBox->currentText());
                    query.addBindValue(studentId);
                    query.addBindValue(lecturers.key(ui->lecturerBox->currentText()));
                    query.exec();
                    */
                    this->close();
                }
            }
        }else{
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }

    }
}

void AddProgressDialog::disciplineBox()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM disciplines_table");

    if(query.exec())
        while (query.next())
    {
        ui->disciplineBox->addItem(query.value(1).toString());
    }
}

void AddProgressDialog::lecturerBox()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM lecturers_table");
    if(query.exec())
        while (query.next())
    {
        lecturers.insert(query.value(4).toString(),query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
        ui->lecturerBox->addItem(query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
    }
}

