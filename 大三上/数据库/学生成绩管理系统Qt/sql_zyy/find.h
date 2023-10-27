#ifndef FIND_H
#define FIND_H

#include <QWidget>

namespace Ui {
class Find;
}

class Find : public QWidget
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = nullptr);
    ~Find();

signals:
    //void sendDataa(int);
    void send_sno(QString);
    void send_sname(QString);


private slots:


    void on_find_sure_clicked();

    void on_find_sure_2_clicked();

private:
    Ui::Find *ui;
};

#endif // FIND_H
