#ifndef ADDTESTSFORM_H
#define ADDTESTSFORM_H

#include <QWidget>

namespace Ui {
class AddTestsForm ;
}

class AddTestsForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddTestsForm(QWidget *parent = nullptr);
    ~AddTestsForm();

private:
    Ui::AddTestsForm *ui;
};

#endif // ADDTESTSFORM_H
