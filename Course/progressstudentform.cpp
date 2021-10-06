#include "progressstudentform.h"
#include "ui_progressstudentform.h"

ProgressStudentForm::ProgressStudentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressStudentForm)
{
    ui->setupUi(this);
}

ProgressStudentForm::~ProgressStudentForm()
{
    delete ui;
}
