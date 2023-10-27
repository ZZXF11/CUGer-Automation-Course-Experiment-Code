#ifndef STU_SET_H
#define STU_SET_H

#include <QWidget>

namespace Ui {
class stu_set;
}

class stu_set : public QWidget
{
    Q_OBJECT

public:
    explicit stu_set(QWidget *parent = nullptr);
    ~stu_set();

private slots:
    void on_new_stu_clicked();
    void on_pushButton_clicked();

    void on_rename_clicked();

    void on_reage_clicked();

    void on_resex_clicked();

    void on_redept_clicked();

signals:
    void new_student(QString,QString,QString,QString,QString);
    void del_student(QString);
    void rename_stu(QString,QString);
    void reage_stu(QString,QString);
    void resex_stu(QString,QString);
    void redept_stu(QString,QString);
private:
    Ui::stu_set *ui;
};

#endif // STU_SET_H
