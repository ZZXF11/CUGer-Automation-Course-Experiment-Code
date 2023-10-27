#ifndef COURSE_SET_H
#define COURSE_SET_H

#include <QWidget>

namespace Ui {
class course_set;
}

class course_set : public QWidget
{
    Q_OBJECT

public:
    explicit course_set(QWidget *parent = nullptr);
    ~course_set();

private slots:
    void on_newsc_clicked();
    void on_delsc_clicked();

    void on_recname_clicked();

    void on_recpno_clicked();

    void on_recredit_clicked();

signals:
    void new_course(QString,QString,QString,QString);
    void del_course(QString);
    void rcname_course(QString,QString);
    void rcpno_course(QString,QString);
    void rcredit_course(QString,QString);
private:
    Ui::course_set *ui;
};

#endif // COURSE_SET_H
