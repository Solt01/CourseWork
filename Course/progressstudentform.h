#ifndef PROGRESSSTUDENTFORM_H
#define PROGRESSSTUDENTFORM_H

#include <QWidget>

namespace Ui {
class ProgressStudentForm;
}

class ProgressStudentForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressStudentForm(QWidget *parent = nullptr);
    ~ProgressStudentForm();

private:
    Ui::ProgressStudentForm *ui;
};

#endif // PROGRESSSTUDENTFORM_H
