#include "addtestsdialog.h"
#include "ui_addtestsdialog.h"
#include <QSqlError>
AddTestsDialog::AddTestsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTestsDialog)
{
    ui->setupUi(this);
    setWindowTitle("Экзамен");
    loadDate();

}

AddTestsDialog::~AddTestsDialog()
{
    delete ui;
}

void AddTestsDialog::loadDate()
{
    QSqlQueryModel * modelDiscipline = new QSqlQueryModel(this);
    modelDiscipline->setQuery("SELECT discipline_name FROM disciplines_table");
    ui->disciplinesBox->setModel(modelDiscipline);

}

void AddTestsDialog::on_addTestButton_clicked()
{

    if(ui->disciplinesBox->currentIndex() == -1)
        QMessageBox::warning(this,"Ошибка","Не все поля заполнены");
    else{
        QSqlQuery query;
        query.prepare("SELECT add_tests_discipline(?)");
        query.addBindValue(ui->disciplinesBox->currentText());

        if(query.exec())
        {
            while(query.next()){

                if(query.value(0).toInt() == 1)
                {
                    this->close();
                }else if(query.value(0).toInt() == 0){
                QMessageBox::warning(this,"Ошибка","Предмет уже существует");
              }
           }
        }else{
            QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
        }

    }
}

