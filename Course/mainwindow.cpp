#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Курсовая");

    createMenuFile();// создание меню файл

    LoadDB(); // подключение к бд

    initializingUi();// инициализация UI

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_newFileButton_clicked()
{
    if(modelGroups->rowCount() != 0)
    {
        if(saveFileName.isEmpty())
        {
            QMessageBox ms;
            ms.setWindowTitle("Новый файл");
            ms.setIcon(QMessageBox::Warning);

            QPushButton *saveProject = ms.addButton("Сохранить",QMessageBox::YesRole);
            QPushButton *noSaveProject = ms.addButton("Нет",QMessageBox::NoRole);
            QPushButton *cancelProject = ms.addButton("Отмена",QMessageBox::RejectRole);

            ms.setText("Сохранить текущий файл?");
            ms.exec();
            if(ms.clickedButton() == saveProject)
            {
                on_saveFileButton_clicked();
                if(!saveFileName.isEmpty())
                {
                    QSqlQuery query;
                    query.prepare("SELECT drop_all_data_table_groups()");
                    query.exec();
                    updateGroupTable();
                }
            }else if(ms.clickedButton() == noSaveProject){
                QSqlQuery query;
                query.prepare("SELECT drop_all_data_table_groups()");
                query.exec();
                updateGroupTable();
            }
            else if(ms.clickedButton() == cancelProject){
                ms.close();
            }
        }else{
            QSqlQuery query;
            query.prepare("SELECT drop_all_data_table_groups()");
            query.exec();
            updateGroupTable();
        }
    }
}

void MainWindow::on_openFileButton_clicked()
{

}

void MainWindow::on_saveFileButton_clicked()
{
    saveFileName = QFileDialog::getSaveFileName(this,
                                               tr("Save Xml"), ".",
                                               tr("Xml files (*.xml)"));
    // Открываем файл для Записи
    QFile file(saveFileName);
    file.open(QIODevice::WriteOnly);
}

void MainWindow::on_quitFileButton_clicked()
{
    /*
    if(modelGroups->rowCount() != 0)
    {
        if(saveFileName.isEmpty())
        {
            QMessageBox ms;
            ms.setWindowTitle("Выход");
            ms.setIcon(QMessageBox::Warning);

            QPushButton *saveProject = ms.addButton("Сохранить",QMessageBox::YesRole);
            QPushButton *noSaveProject = ms.addButton("Нет",QMessageBox::NoRole);
            QPushButton *cancelProject = ms.addButton("Отмена",QMessageBox::RejectRole);

            //connect(noSaveProject, &QPushButton::clicked, qApp, &QApplication::quit);

            ms.setText("Сохранить файл перед выходом?");
            ms.exec();
            if(ms.clickedButton() == saveProject)
            {
                on_saveFileButton_clicked();
                if(!saveFileName.isEmpty())
                {
                    exit(EXIT_FAILURE);
                }

            }else if(ms.clickedButton() == cancelProject){
                ms.close();
            }else if(ms.clickedButton() == noSaveProject)
            {
                QSqlQuery query;
                query.prepare("SELECT drop_all_data_table_groups()");
                query.exec();
                updateGroupTable();
                exit(EXIT_FAILURE);
            }
        }else{
            exit(EXIT_FAILURE);
        }
    }else{
        exit(EXIT_FAILURE);
    }
    */
}

void MainWindow::on_addGroupButton_clicked()
{
    AddGroupDialog group;
    group.setModal(true);
    group.exec();
    updateGroupTable();

}
void MainWindow::on_removeGroupButton_clicked()
{
    if(rowGroup != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить эту группу?");
        ms.setInformativeText("Удалятся и все студенты группы!");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare(QString("SELECT %1(?)").arg("drop_data_table_groups"));
            query.addBindValue(modelGroups->index(rowGroup,1).data().toString());
            if(query.exec())
            {
                updateGroupTable();
                updateStudentTable();
                rowGroup = -1;
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

void MainWindow::on_addStudentButton_clicked()
{
    AddStudentDialog student;
    student.setModal(true);
    student.exec();
    updateStudentTable();
}
void MainWindow::on_removeStudentButton_clicked()
{
    if(rowStudent != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить студента?");
        ms.setInformativeText("Удалятся все данные студента!");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare(QString("SELECT %1(?)").arg("drop_data_table_students"));
            query.addBindValue(modelStudents->index(rowStudent,3).data().toString());
            if(query.exec())
            {
                updateStudentTable();
                rowStudent = -1;
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

void MainWindow::on_addDisciplineButton_clicked()
{
    AddDisciplineDialog discipline;
    discipline.setModal(true);
    discipline.exec();
    updateDisciplineTable();

}
void MainWindow::on_removeDisciplineButton_clicked()
{
    if(rowDiscipline != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить эту дисциплину?");
        ms.setInformativeText("Удалятся и все зависящие от него данные!");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare(QString("SELECT %1(?)").arg("drop_data_disciplines_table"));
            query.addBindValue(modelDisciplines->index(rowDiscipline,1).data().toString());
            if(query.exec())
            {
                updateDisciplineTable();
                updateTestsTable();
                rowDiscipline = -1;
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

void MainWindow::on_addLecturerButton_clicked()
{
    AddLecturerDialog lecturer;
    lecturer.setModal(true);
    lecturer.exec();

    if(!lecturer.firstName.isEmpty() and
            !lecturer.lastName.isEmpty() and
            !lecturer.patronymic.isEmpty() and
            !lecturer.lecturerIdCard.isEmpty())
    {
        updateLecturerTable();
    }
}
void MainWindow::on_removeLecturerButton_clicked()
{
    if(rowLecturer != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить преподавателя?");
        ms.setInformativeText("Удалятся все данные преподавателя!");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;
            query.prepare(QString("SELECT %1(?)").arg("drop_data_lecturers_table"));
            query.addBindValue(modelLecturer->index(rowLecturer,4).data().toString());
            if(query.exec()){
                updateLecturerTable();
                rowLecturer = -1;
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

void MainWindow::editGroup()
{
    if(rowGroup != -1)
    {
        EditGroupDialog edit;
        edit.loadName(modelGroups->index(rowGroup,1).data().toString());
        edit.setModal(true);
        edit.exec();
        updateGroupTable();
        updateStudentTable();
        rowGroup = -1;

    }else{
        QMessageBox::warning(this,"Ошибка","Для изменения выделите запись");
    }
}

void MainWindow::editStudent()
{

    if(rowStudent != -1)
    {
        EditStudentDialog edit;
        edit.loadDate(modelStudents->index(rowStudent,4).data().toString(),
                      modelStudents->index(rowStudent,0).data().toString(),
                      modelStudents->index(rowStudent,1).data().toString(),
                      modelStudents->index(rowStudent,2).data().toString(),
                      modelStudents->index(rowStudent,3).data().toString());
        edit.setModal(true);
        edit.exec();
        updateStudentTable();
        rowStudent = -1;

    }else{
        QMessageBox::warning(this,"Ошибка","Для изменения выделите запись");
    }

}

void MainWindow::editDiscipline()
{
    if(rowDiscipline != -1)
    {
        EditDisciplineDialog edit;
        edit.loadName(modelDisciplines->index(rowDiscipline,1).data().toString());
        edit.setModal(true);
        edit.exec();
        updateDisciplineTable();
        updateTestsTable();
        rowDiscipline = -1;
    }else{
        QMessageBox::warning(this,"Ошибка","Для изменения выделите запись");
    }
}

void MainWindow::editLecturer()
{
    if(rowLecturer != -1)
    {
        EditLecturerDialog edit;
        edit.loadDate(modelLecturer->index(rowLecturer,1).data().toString(),
                      modelLecturer->index(rowLecturer,2).data().toString(),
                      modelLecturer->index(rowLecturer,3).data().toString(),
                      modelLecturer->index(rowLecturer,4).data().toString());
        edit.setModal(true);
        edit.exec();
        updateLecturerTable();
        rowLecturer = -1;
    }else{
        QMessageBox::warning(this,"Ошибка","Для изменения выделите запись");
    }
}

void MainWindow::progressStudent()
{

    ProgressMainWindow * progress = new ProgressMainWindow(this, modelStudents->index(rowStudent,3).data().toString());
    progress->show();    


}

void MainWindow::attendanceStudent()
{
    attendace = new AttendanceWindow(this,modelStudents->index(rowStudent,3).data().toString());
    attendace->show();
}

void MainWindow::testGroup()
{
    TestGroupWindow * testWin = new TestGroupWindow(this,modelTests->index(rowTests,0).data().toString());
    testWin->show();
}

void MainWindow::groupSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editGroup())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeGroupButton_clicked())); // Обработчик удаления записи

    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->groupsTable->viewport()->mapToGlobal(pos));
}

void MainWindow::studentSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);
    QAction * progressDevice = new QAction("Успеваемость", this);
    QAction * attendanceDevice = new QAction("Посещаемость", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editStudent())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeStudentButton_clicked())); // Обработчик удаления записи
    connect(progressDevice, SIGNAL(triggered()), this, SLOT(progressStudent()));
    connect(attendanceDevice, SIGNAL(triggered()), this, SLOT(attendanceStudent()));

    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);
    menu->addSeparator();
    menu->addAction(progressDevice);
    menu->addAction(attendanceDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->studentsTable->viewport()->mapToGlobal(pos));
}

void MainWindow::disciplineSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editDiscipline())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeDisciplineButton_clicked())); // Обработчик удаления записи

    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->disciplinesTable->viewport()->mapToGlobal(pos));
}

void MainWindow::lecturerSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editLecturer())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeLecturerButton_clicked())); // Обработчик удаления записи

    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->lecturersTable->viewport()->mapToGlobal(pos));
}

void MainWindow::testsSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * deleteDevice = new QAction("Удалить", this);
    QAction * appointDevice = new QAction("Список групп", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeTestButton_clicked())); // Обработчик удаления записи
    connect(appointDevice, SIGNAL(triggered()), this, SLOT(testGroup()));

    /* Устанавливаем действия в меню */
    menu->addAction(appointDevice);
    menu->addSeparator();
    menu->addAction(deleteDevice);
    /* Вызываем контекстное меню */
    menu->popup(ui->testsTable->viewport()->mapToGlobal(pos));
}

void MainWindow::querySlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);
    QMenu * submenuB = menu->addMenu("b)Представление студентов");
    QMenu * submenuC = menu->addMenu("c)Коррелированные подзапросы");

    /* Создаём действия для контекстного меню */
    QAction * query_A = new QAction("a)Все оценки за Физику", this);
    QAction * query_B_print = submenuB->addAction("Вывести представление");
    submenuB->addSeparator();
    QAction * query_B_add = submenuB->addAction("Добавить");
    QAction * query_B_update = submenuB->addAction("Обновить");
    QAction * query_B_delete = submenuB->addAction("Удалить");

    QAction * query_C_Select = submenuC->addAction("Select");
    QAction * query_C_From = submenuC->addAction("From");
    QAction * query_C_Where = submenuC->addAction("Where");

    QAction * query_D = new QAction("d)Количество 2", this);
    QAction * query_E = new QAction("e)Вывести студентов с ростом > 190", this);



    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(query_A, SIGNAL(triggered()), this, SLOT(queryA()));

    connect(query_B_print, SIGNAL(triggered()), this, SLOT(queryBPrint()));
    connect(query_B_add, SIGNAL(triggered()), this, SLOT(queryBAdd()));
    connect(query_B_update, SIGNAL(triggered()), this, SLOT(queryBUpdate()));
    connect(query_B_delete, SIGNAL(triggered()), this, SLOT(queryBDelete()));

    connect(query_C_Select, SIGNAL(triggered()), this, SLOT(queryCSelect()));
    connect(query_C_From, SIGNAL(triggered()), this, SLOT(queryCFrom()));
    connect(query_C_Where, SIGNAL(triggered()), this, SLOT(queryCWhere()));

    connect(query_D, SIGNAL(triggered()), this, SLOT(queryD()));
    connect(query_E, SIGNAL(triggered()), this, SLOT(queryE()));


    /* Устанавливаем действия в меню */
    menu->addAction(query_A);
    menu->addMenu(submenuB);
    menu->addMenu(submenuC);
    menu->addAction(query_D);
    menu->addAction(query_E);


    /* Вызываем контекстное меню */
    menu->popup(ui->lecturersTable->viewport()->mapToGlobal(pos));




}

void MainWindow::on_groupsTable_pressed(const QModelIndex &index)
{
    rowGroup = index.row();
}

void MainWindow::on_studentsTable_pressed(const QModelIndex &index)
{
    rowStudent = index.row();
}

void MainWindow::on_disciplinesTable_pressed(const QModelIndex &index)
{
    rowDiscipline = index.row();
}

void MainWindow::on_lecturersTable_pressed(const QModelIndex &index)
{
    rowLecturer = index.row();
}



void MainWindow::updateGroupTable()
{
    modelGroups->select();
    ui->groupsTable->resizeColumnsToContents();

}

void MainWindow::updateStudentTable()
{
    modelStudents->setQuery("SELECT students_table.last_name, students_table.first_name, students_table.patronymic, students_table.studentIdCard, groups_table.group_name,students_table.height "
                            "FROM students_table JOIN groups_table ON groups_table.Id = students_table.group_id",db);
    ui->studentsTable->resizeColumnsToContents();
}

void MainWindow::updateDisciplineTable()
{    
    modelDisciplines->select();
    ui->disciplinesTable->resizeColumnsToContents();
}

void MainWindow::updateTestsTable()
{
    modelTests->setQuery("SELECT disciplines_table.discipline_name "
                            "FROM tests_disciplines_table JOIN disciplines_table ON disciplines_table.Id = tests_disciplines_table.discipline_id",db);
    ui->testsTable->resizeColumnsToContents();
}

void MainWindow::updateLecturerTable()
{
    modelLecturer->select();
    ui->lecturersTable->resizeColumnsToContents();

}

void MainWindow::LoadDB()
{
    ConnectDBDialog cdd(this, db);
    cdd.setModal(true);
    cdd.exec();
    if (!db.open())
    {
        qDebug() <<db.lastError();
        QMessageBox::critical(this, "Ошибка", "Не удается подключиться к базе данных!", QMessageBox::Ok);

    }else{
        QMessageBox::information(this, "Уведомление", "Вы подключились к базе данных!", QMessageBox::Ok);
    }

}

void MainWindow::createMenuFile()
{
    QAction *newFile = new QAction("Новый файл",this);
    QAction *open = new QAction("Открыть", this);
    QAction *save = new QAction("Сохранить", this);
    QAction *quit = new QAction("Выйти", this);

    //горячие клавиши
    newFile->setShortcut(tr("CTRL+N"));
    save->setShortcut(tr("CTRL+S"));
    open->setShortcut(tr("CTRL+O"));
    quit->setShortcut(tr("CTRL+Q"));

    QMenu *file;

    // добавляем действия
    file = menuBar()->addMenu("Файл");
    file->addAction(newFile);
    file->addAction(save);
    file->addAction(open);
    file->addSeparator();
    file->addAction(quit);

    connect(newFile, SIGNAL(triggered()), this, SLOT(on_newFileButton_clicked()));
    connect(save, SIGNAL(triggered()), this, SLOT(on_saveFileButton_clicked()));
    connect(open, SIGNAL(triggered()), this, SLOT(on_openFileButton_clicked()));
    connect(quit, SIGNAL(triggered()), this, SLOT(on_quitFileButton_clicked()));
}

void MainWindow::initializingUi()
{
    /*Creating model*/
    modelGroups = new QSqlTableModel(this,db);
    modelGroups->setTable("groups_table");
    modelGroups->select();
    modelGroups->setHeaderData(1, Qt::Horizontal, tr("Название группы"));

    modelStudents = new QSqlQueryModel(this);
    modelStudents->setQuery("SELECT students_table.last_name, students_table.first_name, students_table.patronymic, students_table.studentIdCard, groups_table.group_name,students_table.height "
                            "FROM students_table JOIN groups_table ON groups_table.Id = students_table.group_id",db);
    modelStudents->setHeaderData(0, Qt::Horizontal, tr("Фамилия"));
    modelStudents->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    modelStudents->setHeaderData(2, Qt::Horizontal, tr("Отчество"));
    modelStudents->setHeaderData(3, Qt::Horizontal, tr("Номер студенческого билета"));
    modelStudents->setHeaderData(4, Qt::Horizontal, tr("Группа"));
    modelStudents->setHeaderData(5, Qt::Horizontal, tr("Рост"));


    modelDisciplines = new QSqlTableModel(this,db);
    modelDisciplines->setTable("disciplines_table");
    modelDisciplines->select();
    modelDisciplines->setHeaderData(1, Qt::Horizontal, tr("Название дисциплины"));

    modelLecturer = new QSqlTableModel(this,db);
    modelLecturer->setTable("lecturers_table");
    modelLecturer->select();
    modelLecturer->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    modelLecturer->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    modelLecturer->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    modelLecturer->setHeaderData(4, Qt::Horizontal, tr("Номер удостоверения"));

    modelTests = new QSqlTableModel(this);
    modelTests->setQuery("SELECT disciplines_table.discipline_name "
                            "FROM tests_disciplines_table JOIN disciplines_table ON disciplines_table.Id = tests_disciplines_table.discipline_id",db);
    modelTests->setHeaderData(0, Qt::Horizontal, tr("Экзаменационные дисциплины"));



    /*Installing model*/
    ui->groupsTable->setModel(modelGroups);
    ui->groupsTable->hideColumn(0); // hide ID
    ui->groupsTable->resizeColumnsToContents();

    ui->studentsTable->setModel(modelStudents);
    ui->studentsTable->resizeColumnsToContents();

    ui->disciplinesTable->setModel(modelDisciplines);
    ui->disciplinesTable->hideColumn(0); // hide ID
    ui->disciplinesTable->resizeColumnsToContents();

    ui->lecturersTable->setModel(modelLecturer);
    ui->lecturersTable->hideColumn(0); // hide ID
    ui->lecturersTable->resizeColumnsToContents();

    ui->testsTable->setModel(modelTests);
    ui->testsTable->resizeColumnsToContents();

    /*Instaling contex menu*/
    ui->groupsTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->studentsTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->disciplinesTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->lecturersTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->testsTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->queryTable->setContextMenuPolicy(Qt::CustomContextMenu);

    /*Include SLOT call contex menu*/
    connect(ui->groupsTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(groupSlotCustomMenuRequested(QPoint)));
    connect(ui->studentsTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(studentSlotCustomMenuRequested(QPoint)));
    connect(ui->disciplinesTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(disciplineSlotCustomMenuRequested(QPoint)));
    connect(ui->lecturersTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(lecturerSlotCustomMenuRequested(QPoint)));
    connect(ui->testsTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(testsSlotCustomMenuRequested(QPoint)));
    connect(ui->queryTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(querySlotCustomMenuRequested(QPoint)));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*
    if(modelGroups->rowCount() != 0)
    {
        if(saveFileName.isEmpty())
        {
            QMessageBox ms;
            ms.setWindowTitle("Выход");
            ms.setIcon(QMessageBox::Warning);

            QAbstractButton *saveProject = ms.addButton("Сохранить",QMessageBox::YesRole);
            QAbstractButton *noSaveProject = ms.addButton("Нет",QMessageBox::NoRole);
            QAbstractButton *cancelProject = ms.addButton("Отмена",QMessageBox::RejectRole);
            ms.setText("Сохранить файл перед выходом?");
            ms.exec();
            if(ms.clickedButton() == saveProject)
            {
                on_saveFileButton_clicked();
                if(saveFileName.isEmpty())
                    event->ignore();
                else{
                    event->accept();
                }
            }else if(ms.clickedButton() == cancelProject){
                event->ignore();
            }else if(ms.clickedButton() == noSaveProject)
            {
                QSqlQuery query;
                query.prepare("SELECT drop_all_data_table_groups()");
                query.exec();
                updateGroupTable();
                exit(EXIT_FAILURE);
            }
        }else{
            exit(EXIT_FAILURE);
        }
    }else{
        exit(EXIT_FAILURE);
    }
    */
}

void MainWindow::on_addTestButton_clicked()
{
   AddTestsDialog tests;
   tests.setModal(true);
   tests.exec();
   updateTestsTable();
}


void MainWindow::on_removeTestButton_clicked()
{
    if(rowTests != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить экзамен по данной дисциплине?");
        ms.setInformativeText("Удалятся и все данные экзамена!");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare(QString("SELECT %1(?)").arg("drop_data_tests_disciplines_table"));
            query.addBindValue(modelTests->index(rowTests,0).data().toString());
            if(query.exec())
            {
                updateTestsTable();
                rowTests = -1;
                QSqlQuery q;
                q.prepare("SELECT drop_all_data_tests_table()");
                q.exec();
            }else{
                QMessageBox::warning(this,"Ошибка","У вас недостаточно прав");
            }

        }else if(ms.clickedButton() == noButton){
            ms.close();
        }
    }else if(rowTests == -1){
        QMessageBox::warning(this,"Ошибка","Для удаления выделите запись");
    }
}


void MainWindow::on_testsTable_pressed(const QModelIndex &index)
{
    rowTests = index.row();
}

void MainWindow::queryA()
{
    ui->queryTable->reset();
   QString discipline = "'Физика'";
   modelQueryA = new QSqlQueryModel(this);
   modelQueryA->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic, "
                "students_table.studentIdCard, Score.test_flag, "
                "CASE WHEN Score.test_flag = '5' THEN 'Отлично' "
                "WHEN Score.test_flag = '4' THEN 'Хорошо'"
                "WHEN Score.test_flag = '3' THEN 'Удовлетворительно'"
                "WHEN Score.test_flag = '2' THEN 'Не сдал'"
                "WHEN Score.test_flag = 'Неявка' THEN 'Неявка'"
                "ELSE 'Нет оценки'"
                "END"
                " FROM students_table LEFT JOIN (SELECT student_id,test_flag "
                "FROM tests_table LEFT JOIN tests_disciplines_table ON tests_table.discipline_id = tests_disciplines_table.id "
                "WHERE tests_table.discipline_id = "
                "(SELECT id FROM tests_disciplines_table WHERE discipline_id = "
                "(SELECT id FROM disciplines_table WHERE discipline_name = " + discipline + "))) Score ON students_table.id = Score.student_id");

   modelQueryA->setHeaderData(0, Qt::Horizontal, tr("Студент"));
   modelQueryA->setHeaderData(1, Qt::Horizontal, tr("№ студенческого билета"));
   modelQueryA->setHeaderData(2, Qt::Horizontal, tr("Оценка за экзамен"));
   modelQueryA->setHeaderData(3, Qt::Horizontal, tr("Итоговая оценка"));
   ui->queryTable->setModel(modelQueryA);
   ui->queryTable->resizeColumnsToContents();
}

void MainWindow::queryBPrint()
{

    QString groupName = "DESC";
    modelQueryB = new QSqlQueryModel(this);
    modelQueryB->setQuery("SELECT * FROM student_group_view ORDER BY group_name " + groupName);

    modelQueryB->setHeaderData(1, Qt::Horizontal, tr("Группа"));
    modelQueryB->setHeaderData(3, Qt::Horizontal, tr("Фамилия"));
    modelQueryB->setHeaderData(4, Qt::Horizontal, tr("Имя"));
    modelQueryB->setHeaderData(5, Qt::Horizontal, tr("Отчество"));
    modelQueryB->setHeaderData(6, Qt::Horizontal, tr("№ студенческого билета"));
    modelQueryB->setHeaderData(7, Qt::Horizontal, tr("Рост"));
    ui->queryTable->setModel(modelQueryB);
    ui->queryTable->hideColumn(0);
    ui->queryTable->hideColumn(2);
    ui->queryTable->hideColumn(8);
    ui->queryTable->resizeColumnsToContents();

}

void MainWindow::queryBAdd()
{
    QSqlQuery query;

    query.prepare("INSERT INTO student_group_view VALUES(5,'БИСО-05-19',52,'Сидоров', 'Иван', 'Иванович','19В1589','192')");
    if(query.exec()){
        QString groupName = "DESC";
        modelQueryB = new QSqlQueryModel(this);
        modelQueryB->setQuery("SELECT * FROM student_group_view ORDER BY group_name " + groupName);

        modelQueryB->setHeaderData(1, Qt::Horizontal, tr("Группа"));
        modelQueryB->setHeaderData(3, Qt::Horizontal, tr("Фамилия"));
        modelQueryB->setHeaderData(4, Qt::Horizontal, tr("Имя"));
        modelQueryB->setHeaderData(5, Qt::Horizontal, tr("Отчество"));
        modelQueryB->setHeaderData(6, Qt::Horizontal, tr("№ студенческого билета"));
        modelQueryB->setHeaderData(7, Qt::Horizontal, tr("Рост"));
        ui->queryTable->setModel(modelQueryB);
        ui->queryTable->hideColumn(0);
        ui->queryTable->hideColumn(2);
        ui->queryTable->hideColumn(8);
        ui->queryTable->resizeColumnsToContents();
    }
}

void MainWindow::queryBUpdate()
{

    QSqlQuery query;

    query.prepare("UPDATE student_group_view SET last_name = 'Козлов'  WHERE group_id = 5 and student_id = 52");
    if(query.exec()){
        QString groupName = "DESC";
        modelQueryB = new QSqlQueryModel(this);
        modelQueryB->setQuery("SELECT * FROM student_group_view ORDER BY group_name " + groupName);

        modelQueryB->setHeaderData(1, Qt::Horizontal, tr("Группа"));
        modelQueryB->setHeaderData(3, Qt::Horizontal, tr("Фамилия"));
        modelQueryB->setHeaderData(4, Qt::Horizontal, tr("Имя"));
        modelQueryB->setHeaderData(5, Qt::Horizontal, tr("Отчество"));
        modelQueryB->setHeaderData(6, Qt::Horizontal, tr("№ студенческого билета"));
        modelQueryB->setHeaderData(7, Qt::Horizontal, tr("Рост"));
        ui->queryTable->setModel(modelQueryB);
        ui->queryTable->hideColumn(0);
        ui->queryTable->hideColumn(2);
        ui->queryTable->hideColumn(8);
        ui->queryTable->resizeColumnsToContents();
    }
}

void MainWindow::queryBDelete()
{

    QSqlQuery query;

    query.prepare("DELETE FROM student_group_view WHERE group_id = 5 and student_id = 52;");
    if(query.exec()){
        QString groupName = "DESC";
        modelQueryB = new QSqlQueryModel(this);
        modelQueryB->setQuery("SELECT * FROM student_group_view ORDER BY group_name " + groupName);

        modelQueryB->setHeaderData(1, Qt::Horizontal, tr("Группа"));
        modelQueryB->setHeaderData(3, Qt::Horizontal, tr("Фамилия"));
        modelQueryB->setHeaderData(4, Qt::Horizontal, tr("Имя"));
        modelQueryB->setHeaderData(5, Qt::Horizontal, tr("Отчество"));
        modelQueryB->setHeaderData(6, Qt::Horizontal, tr("№ студенческого билета"));
        modelQueryB->setHeaderData(7, Qt::Horizontal, tr("Рост"));
        ui->queryTable->setModel(modelQueryB);
        ui->queryTable->hideColumn(0);
        ui->queryTable->hideColumn(2);
        ui->queryTable->hideColumn(8);
        ui->queryTable->resizeColumnsToContents();
    }
}

void MainWindow::queryCSelect()
{

    modelQueryC = new QSqlQueryModel(this);
    modelQueryC->setQuery("SELECT lecturers_table.last_name ||' '|| lecturers_table.first_name ||' '|| lecturers_table.patronymic AS fio, Lecturer.date_test "
                "FROM lecturers_table LEFT JOIN (SELECT (SELECT id FROM tests_disciplines_table "
                "WHERE tests_disciplines_table.id = lecturer_discipline_test.discipline_id) "
                "AS discipline_id,lecturer_id, date_test "
                "FROM tests_groups_table AS lecturer_discipline_test) "
                "AS Lecturer ON lecturers_table.id = Lecturer.lecturer_id");

    modelQueryC->setHeaderData(0, Qt::Horizontal, tr("Преподаватель"));
    modelQueryC->setHeaderData(1, Qt::Horizontal, tr("Дата экзамена"));

    ui->queryTable->setModel(modelQueryC);
    ui->queryTable->resizeColumnsToContents();
}

void MainWindow::queryCFrom()
{
    modelQueryC = new QSqlQueryModel(this);
    modelQueryC->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic AS FIO, "
                            "subquery1.score, subquery1.date_score "
                            "FROM students_table,"
                            "(SELECT progress_table.student_id, progress_table.score, progress_table.date_score "
                            "FROM progress_table) subquery1 "
                            "WHERE students_table.id = subquery1.student_id;");

    modelQueryC->setHeaderData(0, Qt::Horizontal, tr("Студент"));
    modelQueryC->setHeaderData(1, Qt::Horizontal, tr("Оценка"));
    modelQueryC->setHeaderData(2, Qt::Horizontal, tr("Дата оценки"));
    ui->queryTable->setModel(modelQueryC);
    ui->queryTable->resizeColumnsToContents();
}

void MainWindow::queryCWhere()
{  
    modelQueryC = new QSqlQueryModel(this);
    modelQueryC->setQuery("SELECT s.last_name || ' ' || s.first_name || ' ' || s.patronymic "
                            "FROM students_table s "
                            "WHERE s.id = (SELECT student_id "
                            "FROM attendances_table WHERE "
                            "number_attendance = (SELECT MAX(number_attendance) FROM attendances_table))");

    modelQueryC->setHeaderData(0, Qt::Horizontal, tr("Студент"));

    ui->queryTable->setModel(modelQueryC);
    ui->queryTable->resizeColumnsToContents();

}

void MainWindow::queryD()
{

    QString count_score = "'2'";
    modelQueryD = new QSqlQueryModel(this);
    modelQueryD->setQuery("SELECT students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic AS FIO, COUNT(*) AS Count_Two "
                            "FROM students_table LEFT "
                            "JOIN tests_table ON students_table.id= tests_table.student_id "
                            "GROUP BY students_table.last_name || ' ' || students_table.first_name || ' ' || students_table.patronymic,test_flag "
                            "HAVING (test_flag = " + count_score +")");
    modelQueryD->setHeaderData(0, Qt::Horizontal, tr("Студент"));
    modelQueryD->setHeaderData(1, Qt::Horizontal, tr("Количество 2 по экзаменам"));
    ui->queryTable->setModel(modelQueryD);
    ui->queryTable->resizeColumnsToContents();

}

void MainWindow::queryE()
{

    QString height = "190";
    modelQueryE = new QSqlQueryModel(this);
    modelQueryE->setQuery("SELECT last_name || ' ' || first_name || ' ' || patronymic, height "
                        "FROM students_table WHERE height = "
                        "ANY (SELECT height FROM students_table WHERE height > " + height + ")");

    modelQueryE->setHeaderData(0, Qt::Horizontal, tr("Студент"));
    modelQueryE->setHeaderData(1, Qt::Horizontal, tr("Рост"));

    ui->queryTable->setModel(modelQueryE);
    ui->queryTable->resizeColumnsToContents();
}

