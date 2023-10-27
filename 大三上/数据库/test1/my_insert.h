#ifndef MY_INSERT_H
#define MY_INSERT_H

#include <QWidget>

namespace Ui {
class my_insert;
}

class my_insert : public QWidget
{
    Q_OBJECT

public:
    explicit my_insert(QWidget *parent = nullptr);
    ~my_insert();

private:
    Ui::my_insert *ui;
};

#endif // MY_INSERT_H
