#ifndef MULTILIST_H
#define MULTILIST_H

#include <QWidget>

namespace Ui {
class MultiList;
}

class MultiList : public QWidget
{
    Q_OBJECT

public:
    explicit MultiList(QWidget *parent = nullptr);
    ~MultiList();

private:
    Ui::MultiList *ui;
};

#endif // MULTILIST_H
