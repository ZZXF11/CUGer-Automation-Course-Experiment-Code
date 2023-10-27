#ifndef MY_LOAD_H
#define MY_LOAD_H

#include <QMainWindow>
#include "mainwindow.h"
#include<QString>
extern int tell;
extern int a;
extern QVector<QString>teacher_login;
extern QVector<QString>teacher_password;
namespace Ui {
class my_load;
}

class my_load : public QMainWindow
{
    Q_OBJECT

public:
    explicit my_load(QWidget *parent = nullptr);
    ~my_load();

private slots:
    void on_loadsure_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::my_load *ui;
    //MainWindow * page;

};

#endif // MY_LOAD_H
