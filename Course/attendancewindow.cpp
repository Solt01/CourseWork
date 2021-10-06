#include "attendancewindow.h"
#include "ui_attendancewindow.h"

AttendanceWindow::AttendanceWindow(QWidget *parent, QString _studentIdCard) :
    QMainWindow(parent),
    ui(new Ui::AttendanceWindow)
{
    ui->setupUi(this);
    setWindowTitle("Посещаемость");
    resize(720,450);
    studentIdCard = _studentIdCard;
    initializingUi();
    countAttendance = modelAttendance->rowCount();
}

AttendanceWindow::~AttendanceWindow()
{
    delete ui;
}

void AttendanceWindow::updateAttendaceTable()
{
    QString q = "'" + studentIdCard + "'";
    modelAttendance->setQuery("SELECT A.number_attendance, D.discipline_name,A.attendance_flag, L.last_name || ' ' || L.first_name || ' ' || L.patronymic AS LFP, L.lecturer_id_card, A.date_attendance "
                            "FROM attendances_table AS A, disciplines_table AS D, lecturers_table AS L "
                            "WHERE A.discipline_id = D.Id AND A.lecturer_id = L.Id AND A.student_id = "
                            "(SELECT id FROM students_table WHERE studentIdCard = " + q + ')');
    ui->attendanceTable->resizeColumnsToContents();
}



void AttendanceWindow::increaseCountAttendace()
{
    ++countAttendance;
}

void AttendanceWindow::initializingUi()
{
    QString q = "'" + studentIdCard + "'";
    /*Creating model*/
    modelAttendance = new QSqlQueryModel(this);
    modelAttendance->setQuery("SELECT A.number_attendance, D.discipline_name,A.attendance_flag, L.last_name || ' ' || L.first_name || ' ' || L.patronymic AS LFP, L.lecturer_id_card, A.date_attendance "
                            "FROM attendances_table AS A, disciplines_table AS D, lecturers_table AS L "
                            "WHERE A.discipline_id = D.Id AND A.lecturer_id = L.Id AND A.student_id = "
                            "(SELECT id FROM students_table WHERE studentIdCard = " + q + ')');
    modelAttendance->setHeaderData(0, Qt::Horizontal, tr("№ посещения"));
    modelAttendance->setHeaderData(1, Qt::Horizontal, tr("Дисциплина"));
    modelAttendance->setHeaderData(2, Qt::Horizontal, tr("Присутствие"));
    modelAttendance->setHeaderData(3, Qt::Horizontal, tr("Преподаватель"));
    modelAttendance->setHeaderData(4, Qt::Horizontal, tr("№ удостоверения"));
    modelAttendance->setHeaderData(5, Qt::Horizontal, tr("Дата"));

    /*Installing model*/
    ui->attendanceTable->setModel(modelAttendance);
    ui->attendanceTable->hideColumn(0);
    ui->attendanceTable->resizeColumnsToContents();

    /*Instaling contex menu*/
    ui->attendanceTable->setContextMenuPolicy(Qt::CustomContextMenu);


    /*Include SLOT call contex menu*/
    connect(ui->attendanceTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(attendanceSlotCustomMenuRequested(QPoint)));
}

void AttendanceWindow::attendanceSlotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu(this);

    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(editAttendance())); // Обработчик редактирования записи
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_removeAttendanceButton_clicked())); // Обработчик удаления записи

    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);

    /* Вызываем контекстное меню */
    menu->popup(ui->attendanceTable->viewport()->mapToGlobal(pos));
}

void AttendanceWindow::editAttendance()
{

}

void AttendanceWindow::on_attendanceTable_pressed(const QModelIndex &index)
{
    rowAttendance = index.row();
}


void AttendanceWindow::on_addAttendanceButton_clicked()
{
    AddAttendancesDialog attendance;
    attendance.addDate(studentIdCard,countAttendance);
    attendance.setModal(true);
    attendance.exec();
    updateAttendaceTable();
    countAttendance = modelAttendance->rowCount();
}


void AttendanceWindow::on_removeAttendanceButton_clicked()
{
    if(rowAttendance != -1)
    {
        QMessageBox ms;
        ms.setWindowTitle("Удаление записи");
        ms.setIcon(QMessageBox::Warning);

        QAbstractButton *yesButton = ms.addButton("Удалить",QMessageBox::YesRole);
        QAbstractButton *noButton = ms.addButton("Отмена",QMessageBox::NoRole);

        ms.setText("Вы уверены, что хотите удалить посещение?");
        ms.exec();
        if(ms.clickedButton() == yesButton)
        {
            QSqlQuery query;

            query.prepare("SELECT drop_data_attendances_table(?,?)");

            query.addBindValue(modelAttendance->index(rowAttendance,0).data().toInt());
            query.addBindValue(studentIdCard);
            query.exec();
            updateAttendaceTable();
            rowAttendance = -1;
            countAttendance = modelAttendance->rowCount();
        }else if(ms.clickedButton() == noButton){
            ms.close();
        }
    }else{
        QMessageBox::warning(this,"Ошибка","Для удаления выделите запись");
    }
}

