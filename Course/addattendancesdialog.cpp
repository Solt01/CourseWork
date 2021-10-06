#include "addattendancesdialog.h"
#include "ui_addattendancesdialog.h"

AddAttendancesDialog::AddAttendancesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAttendancesDialog)
{
    ui->setupUi(this);
    setWindowTitle("Посещение");
    resize(280,85);
    disciplineBox();
    lecturerBox();
    attendancesBox();
}

AddAttendancesDialog::~AddAttendancesDialog()
{
    delete ui;
}

void AddAttendancesDialog::addDate(QString _studentId, int _countAttendance)
{
    studentId = _studentId;
    countAttendance = _countAttendance;
}

void AddAttendancesDialog::on_addAttendanceButton_clicked()
{
    if(ui->dateAttendanceLine->text().isEmpty() or
            ui->disciplinesBox->currentIndex() == -1 or
            ui->lecturersBox->currentIndex() == -1 or
            ui->attendaceBox->currentIndex() == -1)
        QMessageBox::warning(this,"Ошибка","Не все поля заполнены");
    else{
        ++countAttendance;
        QSqlQuery query;
        query.prepare("SELECT add_attendances(?,?,?,?,?,?)");
        query.addBindValue(countAttendance);
        query.addBindValue(ui->dateAttendanceLine->text());
        query.addBindValue(ui->attendaceBox->currentText());
        query.addBindValue(ui->disciplinesBox->currentText());
        query.addBindValue(studentId);
        query.addBindValue(lecturers.key(ui->lecturersBox->currentText()));
        if(query.exec())
        {
            while(query.next()){
                if(query.value(0).toInt() == 1)
                {
                    this->close();
                }
            }
        }else{
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }

    }
}

void AddAttendancesDialog::attendancesBox()
{
    //ui->attendaceBox->addItem("Б");
    ui->attendaceBox->addItem("Н");
}

void AddAttendancesDialog::disciplineBox()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM disciplines_table");

    if(query.exec())
        while (query.next())
    {
        ui->disciplinesBox->addItem(query.value(1).toString());
    }
}

void AddAttendancesDialog::lecturerBox()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM lecturers_table");
    if(query.exec())
        while (query.next())
    {
        lecturers.insert(query.value(4).toString(),query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
        ui->lecturersBox->addItem(query.value(1).toString() + ' ' + query.value(2).toString() + ' ' + query.value(3).toString() + " № " + query.value(4).toString());
        }
}

