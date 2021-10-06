#include "testgroupwindow.h"
#include "ui_testgroupwindow.h"

TestGroupWindow::TestGroupWindow(QWidget *parent, QString _disciplineName) :
    QMainWindow(parent),
    ui(new Ui::TestGroupWindow)
{
    ui->setupUi(this);
    setWindowTitle("Группы");
    disciplineName = _disciplineName;
    initializingUi();
}

TestGroupWindow::~TestGroupWindow()
{
    delete ui;
}

void TestGroupWindow::updateTestGroup()
{
    QString query = "'" + disciplineName + "'" + ")";
    modelGroup->setQuery("SELECT groups_table.group_name, lecturers_table.last_name || ' ' || lecturers_table.first_name || ' ' || lecturers_table.patronymic, "
                        "lecturers_table.lecturer_id_card, tests_groups_table.date_test, tests_groups_table.discipline_id "
                        "FROM tests_groups_table JOIN groups_table ON groups_table.Id = tests_groups_table.group_id "
                        "JOIN lecturers_table ON lecturers_table.Id = tests_groups_table.lecturer_id "
                        "JOIN tests_disciplines_table ON tests_disciplines_table.Id = tests_groups_table.discipline_id WHERE "
                        "tests_disciplines_table.discipline_id = (SELECT id FROM disciplines_table WHERE discipline_name = " + query);
    ui->groupTable->resizeColumnsToContents();
}


void TestGroupWindow::groupSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);
    QAction * appointDevice = new QAction("Список студентов", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editGroupTest())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeGroupButton_clicked())); // Обработчик удаления записи
    connect(appointDevice, SIGNAL(triggered()), this, SLOT(studentTest()));

    /* Устанавливаем действия в меню */
    menu->addAction(appointDevice);
    menu->addAction(editDevice);
    menu->addSeparator();
    menu->addAction(deleteDevice);
    /* Вызываем контекстное меню */
    menu->popup(ui->groupTable->viewport()->mapToGlobal(pos));
}

void TestGroupWindow::studentTest()
{

    StudentTestWindow * student = new StudentTestWindow(this,modelGroup->index(rowGroup,0).data().toString(), disciplineName,
                                                        modelGroup->index(rowGroup,2).data().toString(),
                                                        modelGroup->index(rowGroup,3).data().toString());
    student->show();
}

void TestGroupWindow::editGroupTest()
{
    EditTestGroupDialog  * edit = new EditTestGroupDialog(this,modelGroup->index(rowGroup,0).data().toString(),disciplineName,
                                                          modelGroup->index(rowGroup,2).data().toString(),modelGroup->index(rowGroup,3).data().toString(),modelGroup);
    edit->show();
}

void TestGroupWindow::initializingUi()
{
    QString query = "'" + disciplineName + "'" + ")";
    /*Creating model*/
    modelGroup = new QSqlQueryModel(this);
    modelGroup->setQuery("SELECT groups_table.group_name, lecturers_table.last_name || ' ' || lecturers_table.first_name || ' ' || lecturers_table.patronymic, "
                        "lecturers_table.lecturer_id_card, tests_groups_table.date_test, tests_groups_table.discipline_id "
                        "FROM tests_groups_table JOIN groups_table ON groups_table.Id = tests_groups_table.group_id "
                        "JOIN lecturers_table ON lecturers_table.Id = tests_groups_table.lecturer_id "
                        "JOIN tests_disciplines_table ON tests_disciplines_table.Id = tests_groups_table.discipline_id WHERE "
                        "tests_disciplines_table.discipline_id = (SELECT id FROM disciplines_table WHERE discipline_name = " + query);
    modelGroup->setHeaderData(0, Qt::Horizontal, tr("Группа"));
    modelGroup->setHeaderData(1, Qt::Horizontal, tr("Преподаватель"));
    modelGroup->setHeaderData(2, Qt::Horizontal, tr("№ удостоверения"));
    modelGroup->setHeaderData(3, Qt::Horizontal, tr("Дата экзамена"));

    /*Installing model*/
    ui->groupTable->setModel(modelGroup);
    ui->groupTable->hideColumn(4);
    ui->groupTable->resizeColumnsToContents();

    /*Instaling contex menu*/
    ui->groupTable->setContextMenuPolicy(Qt::CustomContextMenu);


    /*Include SLOT call contex menu*/
    connect(ui->groupTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(groupSlotCustomMenuRequested(QPoint)));

}

void TestGroupWindow::on_groupTable_pressed(const QModelIndex &index)
{
    rowGroup = index.row();
}


void TestGroupWindow::on_addGroupButton_clicked()
{
    AddTestGroupDialog group;
    group.loadData(disciplineName);
    group.setModal(true);
    group.exec();
    updateTestGroup();

}


void TestGroupWindow::on_removeGroupButton_clicked()
{
    if(rowGroup != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить эту группу?");
        ms.setInformativeText("Удалятся и все зачетные данные группы!");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare(QString("SELECT %1(?)").arg("drop_data_tests_groups_table"));
            query.addBindValue(modelGroup->index(rowGroup,0).data().toString());
            if(query.exec())
            {
                updateTestGroup();
                rowGroup = -1;

                QSqlQuery q;
                q.prepare("SELECT drop_all_data_tests_table()");
                q.exec();
            }else{
                QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
            }

        }else if(ms.clickedButton() == noButton){
            ms.close();
        }
    }else if(rowGroup == -1){
        QMessageBox::warning(this,"Ошибка","Для удаления выделите запись");
    }
}

