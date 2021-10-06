#ifndef CHECKTESTLIST_H
#define CHECKTESTLIST_H

#include <QComboBox>
#include <QWidget>
#include <QComboBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QEvent>
#include <QStyledItemDelegate>
#include <QListView>

class CheckTestList : public QComboBox
{
    Q_OBJECT

    public:
    explicit CheckTestList(QWidget *parent = 0);
    ~CheckTestList();

    private:
    Ui::CheckTestList *ui;
    QStandardItemModel *model;

    private slots:

    void buttonclicked();
};

#endif // CHECKTESTLIST_H
