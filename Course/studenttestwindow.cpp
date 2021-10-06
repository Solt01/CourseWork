#include "studenttestwindow.h"
#include "ui_studenttestwindow.h"

StudentTestWindow::StudentTestWindow(QWidget *parent, QString _groupName, QString _disciplineName
                                     , QString _lecturer_id,QString _date_test) :
    QMainWindow(parent),
    ui(new Ui::StudentTestWindow)
{
    ui->setupUi(this);
    setWindowTitle("Студенты");
    groupName = _groupName;
    disciplineName = _disciplineName;
    lecturerId = _lecturer_id;
    dateTest = _date_test;
    queryGroup = "'" + groupName + "'" + ")";
    queryDiscipline = "'" + disciplineName + "'" + ")";

    initializingUi();


}

StudentTestWindow::~StudentTestWindow()
{
    delete ui;
}

void StudentTestWindow::studentSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * putScore = new QAction("Поставить оценку", this);
    QAction * editDevice = new QAction("Изменить оценку", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(putScore, SIGNAL(triggered()), this, SLOT(putScoreStudent())); // Обработчик оценивия
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editScoreStudent())); // Обработчик редактирования оценки


    /* Устанавливаем действия в меню */
    menu->addAction(putScore);
    menu->addAction(editDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->studentTable->viewport()->mapToGlobal(pos));
}

void StudentTestWindow::on_studentTable_pressed(const QModelIndex &index)
{
    rowStudent = index.row();

}

void StudentTestWindow::putScoreStudent()
{
    if(rowStudent != -1)
    {
        if(modelStudent->index(rowStudent,2).data().toString().isEmpty()){
            score.loadData(groupName, lecturerId, dateTest,
                           disciplineName,modelStudent->index(rowStudent,1).data().toString(),
                           modelStudent->index(rowStudent,0).data().toString(),modelStudent);
            score.show();
            updateStudentGroup();
        }else{
            QMessageBox::warning(this,"Ошибка","Для данного студента оценка уже стоит!");
        }
    }else{
        QMessageBox::warning(this,"Ошибка","Для оценивания выделите студента");
    }
}

void StudentTestWindow::editScoreStudent()
{
    if(rowStudent != -1)
    {
        EditScoreStudentDialog  * edit = new EditScoreStudentDialog(this,groupName,disciplineName,
                                                                    modelStudent->index(rowStudent,2).data().toString(),
                                                                    modelStudent->index(rowStudent,0).data().toString(),
                                                                    modelStudent->index(rowStudent,1).data().toString(),
                                                                    modelStudent);
        edit->show();
    }else{
        QMessageBox::warning(this,"Ошибка","Для изменения выделите студента");
    }
}



void StudentTestWindow::updateStudentGroup()
{

    modelStudent->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic, "
                            "students_table.studentIdCard, Score.test_flag "
                            "FROM students_table LEFT JOIN (SELECT student_id,test_flag "
                            "FROM tests_table LEFT JOIN tests_disciplines_table ON tests_table.discipline_id = tests_disciplines_table.id "
                            "WHERE tests_table.discipline_id = "
                            "(SELECT id FROM tests_disciplines_table WHERE discipline_id = "
                            "(SELECT id FROM disciplines_table WHERE discipline_name = " + queryDiscipline + ")) Score ON students_table.id = Score.student_id "
                            "WHERE students_table.group_id = "
                            "(SELECT id FROM groups_table WHERE group_name = " + queryGroup);
    ui->studentTable->resizeColumnsToContents();
}

void StudentTestWindow::initializingUi()
{
    /*Creating model*/
    modelStudent = new QSqlQueryModel(this);
    modelStudent->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic, "
                            "students_table.studentIdCard, Score.test_flag "
                            "FROM students_table LEFT JOIN (SELECT student_id,test_flag "
                            "FROM tests_table LEFT JOIN tests_disciplines_table ON tests_table.discipline_id = tests_disciplines_table.id "
                            "WHERE tests_table.discipline_id = "
                            "(SELECT id FROM tests_disciplines_table WHERE discipline_id = "
                            "(SELECT id FROM disciplines_table WHERE discipline_name = " + queryDiscipline + ")) Score ON students_table.id = Score.student_id "
                            "WHERE students_table.group_id = "
                            "(SELECT id FROM groups_table WHERE group_name = " + queryGroup);

    modelStudent->setHeaderData(0, Qt::Horizontal, tr("Студент"));
    modelStudent->setHeaderData(1, Qt::Horizontal, tr("№ зачётной книжки"));
    modelStudent->setHeaderData(2, Qt::Horizontal, tr("Оценка"));

    /*Installing model*/
    ui->studentTable->setModel(modelStudent);
    ui->studentTable->hideColumn(3);
    ui->studentTable->resizeColumnsToContents();

    /*Instaling contex menu*/
    ui->studentTable->setContextMenuPolicy(Qt::CustomContextMenu);


    /*Include SLOT call contex menu*/
    connect(ui->studentTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(studentSlotCustomMenuRequested(QPoint)));
}

