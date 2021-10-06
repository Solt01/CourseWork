#include "progressmainwindow.h"
#include "ui_progressmainwindow.h"

ProgressMainWindow::ProgressMainWindow(QWidget *parent, QString _studentIdCard) :
    QMainWindow(parent),
    ui(new Ui::ProgressMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Успеваемость");
    studentIdCard = _studentIdCard;
    initializingUi();
    countScore = modelProgress->rowCount();

}

ProgressMainWindow::~ProgressMainWindow()
{
    delete ui;
}

void ProgressMainWindow::updateProgressTable()
{
    QString q = "'" + studentIdCard + "'";
    modelProgress->setQuery("SELECT P.number_score, D.discipline_name,P.score, L.last_name || ' ' || L.first_name || ' ' || L.patronymic AS LFP, L.lecturer_id_card, P.date_score "
                            "FROM progress_table AS P, disciplines_table AS D, lecturers_table AS L "
                            "WHERE P.discipline_id = D.Id AND P.lecturer_id = L.Id AND P.student_id = "
                            "(SELECT id FROM students_table WHERE studentIdCard = " + q + ')');

    ui->progressTable->resizeColumnsToContents();

}




void ProgressMainWindow::on_progressTable_pressed(const QModelIndex &index)
{
    rowProgress = index.row();
}

void ProgressMainWindow::initializingUi()
{
    QString q = "'" + studentIdCard + "'";
    /*Creating model*/
    modelProgress = new QSqlQueryModel(this);
    modelProgress->setQuery("SELECT P.number_score, D.discipline_name,P.score, L.last_name || ' ' || L.first_name || ' ' || L.patronymic AS LFP, L.lecturer_id_card, P.date_score "
                            "FROM progress_table AS P, disciplines_table AS D, lecturers_table AS L "
                            "WHERE P.discipline_id = D.Id AND P.lecturer_id = L.Id AND P.student_id = "
                            "(SELECT id FROM students_table WHERE studentIdCard = " + q + ')');
    modelProgress->setHeaderData(0, Qt::Horizontal, tr("№ оценки"));
    modelProgress->setHeaderData(1, Qt::Horizontal, tr("Дисциплина"));
    modelProgress->setHeaderData(2, Qt::Horizontal, tr("Оценка"));
    modelProgress->setHeaderData(3, Qt::Horizontal, tr("Преподаватель"));
    modelProgress->setHeaderData(4, Qt::Horizontal, tr("№ удостоверения"));
    modelProgress->setHeaderData(5, Qt::Horizontal, tr("Дата"));

    /*Installing model*/
    ui->progressTable->setModel(modelProgress);
    ui->progressTable->hideColumn(0);
    ui->progressTable->resizeColumnsToContents();

    /*Instaling contex menu*/
    ui->progressTable->setContextMenuPolicy(Qt::CustomContextMenu);


    /*Include SLOT call contex menu*/
    connect(ui->progressTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(progressSlotCustomMenuRequested(QPoint)));

}

void ProgressMainWindow::progressSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editProgress())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeProgressButton_clicked())); // Обработчик удаления записи

    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->progressTable->viewport()->mapToGlobal(pos));
}

void ProgressMainWindow::editProgress()
{
    if(rowProgress != -1)
    {
        EditProgressDialog edit;
        edit.loadDate(modelProgress->index(rowProgress,2).data().toString(),
                      modelProgress->index(rowProgress,5).data().toString(),
                      modelProgress->index(rowProgress,0).data().toInt(),
                      studentIdCard);
        edit.setModal(true);
        edit.exec();
        updateProgressTable();
        rowProgress = -1;
    }else{
        QMessageBox::warning(this,"Ошибка","Для изменения выделите запись");
    }
}


void ProgressMainWindow::on_removeProgressButton_clicked()
{
    if(rowProgress != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить оценку?");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare("SELECT drop_data_progress_table(?,?)");

            query.addBindValue(modelProgress->index(rowProgress,0).data().toInt());
            query.addBindValue(studentIdCard);
            if(query.exec()){
                updateProgressTable();
                rowProgress = -1;
                countScore = modelProgress->rowCount();
            }else{
                QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
            }


        }else if(ms.clickedButton() == noButton){
            ms.close();
        }
    }else{
        QMessageBox::warning(this,"Ошибка","Для удаления выделите запись");
    }
}


void ProgressMainWindow::on_addProgressButton_clicked()
{
    AddProgressDialog progress;
    progress.addDate(studentIdCard,countScore);
    progress.setModal(true);
    progress.exec();
    updateProgressTable();
    countScore = modelProgress->rowCount();


}

