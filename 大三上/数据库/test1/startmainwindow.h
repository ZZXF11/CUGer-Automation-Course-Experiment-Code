#ifndef STARTMAINWINDOW_H
#define STARTMAINWINDOW_H

#include <QMainWindow>
#include"mainwindow.h"
#include"dialog2.h"
#include <string>
extern int tell;
extern int a;
extern QVector<QString> teacher_login;
extern QVector<QString> teacher_password;
extern QVector<QString> student_login;
extern QVector<QString> student_password;
namespace Ui {
class startMainWindow;
}

class startMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit startMainWindow(QWidget *parent = nullptr);
    ~startMainWindow();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::startMainWindow *ui;
    MainWindow * start;
    stuMainWindow*stustart;
    QDialog * stu;
};

#endif // STARTMAINWINDOW_H
