#include "multilist.h"
#include "ui_multilist.h"

MultiList::MultiList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiList)
{
    ui->setupUi(this);
}

MultiList::~MultiList()
{
    delete ui;
}
