#ifndef FIND_SC_H
#define FIND_SC_H

#include <QWidget>

namespace Ui {
class Find_sc;
}

class Find_sc : public QWidget
{
    Q_OBJECT

public:
    explicit Find_sc(QWidget *parent = nullptr);
    ~Find_sc();
signals:
    void send_sno(QString);
    void send_sname(QString);
private slots:
    void on_find_sure_3_clicked();

    void on_find_sure_4_clicked();

private:
    Ui::Find_sc *ui;
};

#endif // FIND_SC_H
