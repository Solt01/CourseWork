#include "connectdbdialog.h"
#include "ui_connectdbdialog.h"

ConnectDBDialog::ConnectDBDialog(QWidget *parent, QSqlDatabase& db) :
    QDialog(parent),
    ui(new Ui::ConnectDBDialog)
{
    ui->setupUi(this);
    setWindowTitle("Подключение к БД");
    ui->serverLine->setText("localhost");
    ui->databaseLine->setText("course");
    ui->portLine->setText("5432");
    ui->usernameBox->addItem("root");
    ui->usernameBox->addItem("users");
    //ui->usernameBox->addItem("postgres");
    ui->passwordLine->setText("1");

    this->db = &db;
}

ConnectDBDialog::~ConnectDBDialog()
{
    delete ui;
}

void ConnectDBDialog::on_connectButton_clicked()
{
    *db = QSqlDatabase::addDatabase("QPSQL");

    db->setHostName(ui->serverLine->text());

    db->setDatabaseName(ui->databaseLine->text());

    db->setPort(ui->portLine->text().toInt());

    db->setUserName(ui->usernameBox->currentText());

    db->setPassword(ui->passwordLine->text());

    db->open();

    this->close();
}

