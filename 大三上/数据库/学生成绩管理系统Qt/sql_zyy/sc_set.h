#ifndef SC_SET_H
#define SC_SET_H

#include <QWidget>

namespace Ui {
class sc_set;
}

class sc_set : public QWidget
{
    Q_OBJECT

public:
    explicit sc_set(QWidget *parent = nullptr);
    ~sc_set();

private slots:
    void on_new_sc_clicked();
    void on_del_sc_clicked();

    void on_cha_sc_clicked();

signals:
    void new_sc(QString,QString,QString);
    void del_sc(QString,QString);
    void cha_sc(QString,QString,QString);
private:
    Ui::sc_set *ui;
};

#endif // SC_SET_H
