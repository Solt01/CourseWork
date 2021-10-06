#include "editprogressdialog.h"
#include "ui_editprogressdialog.h"

EditProgressDialog::EditProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProgressDialog)
{
    ui->setupUi(this);
    setWindowTitle("Редактирование");
    resize(280,85);
}

EditProgressDialog::~EditProgressDialog()
{
    delete ui;
}

void EditProgressDialog::loadDate(QString _score, QString _dateScore, int _numberScore, QString _studentIdCard)
{
    score = _score;
    dateScore = _dateScore;
    numberScore =_numberScore;
    studentIdCard = _studentIdCard;

    ui->scoreLine->setText(score);
    ui->dateScoreLine->setText(dateScore);
}


void EditProgressDialog::on_editProgressButton_clicked()
{
    if(ui->scoreLine->text() != score or
            ui->dateScoreLine->text() != dateScore)
    {
        QSqlQuery query;
        query.prepare("SELECT edit_progress(?,?,?,?)");
        query.addBindValue(numberScore);
        query.addBindValue(ui->dateScoreLine->text());
        query.addBindValue(ui->scoreLine->text().toInt());
        query.addBindValue(studentIdCard);

        if(query.exec()){
            while(query.next()){
                if(query.value(0).toInt() == 1 or query.value(0).toInt() == 2
                        or query.value(0).toInt() == 3)
                {
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

