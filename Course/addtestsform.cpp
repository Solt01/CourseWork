#include "addtestsform.h"
#include "ui_addtestsform.h"

AddTestsForm::AddTestsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTestsForm)
{
    ui->setupUi(this);
}

AddTestsForm::~AddTestsForm()
{
    delete ui;
}
