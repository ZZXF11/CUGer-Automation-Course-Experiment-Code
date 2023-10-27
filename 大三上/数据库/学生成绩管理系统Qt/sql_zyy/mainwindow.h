#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include<QtSql/QSqlDatabase>
#include<QPushButton>
#include<Qtsql/QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include<Qtsql/QSqlRelationalTableModel>
#include<Qtsql>
#include "find.h"
#include "find_sc.h"
#include "stu_set.h"
#include "course_set.h"
#include "sc_set.h"
#include "grade_sel.h"
#include "load.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    bool sql_connect();
private:
    QSqlTableModel* homeModel;//单表模型
    QSqlRelationalTableModel* studentModel;//关联模型
    QSqlQueryModel* studentqrModel;//只读模型
    Find *find =new Find;
    Find_sc *find_sc =new Find_sc;
    stu_set *stuset =new stu_set;
    course_set *coset =new course_set;
    sc_set *scset =new sc_set;
    grade_sel *gsel =new grade_sel;
    load *ld =new load;
private slots:
    void rec_sno(QString);
    void rec_sname(QString);
    void rec_sno_sc(QString);
    void rec_sname_sc(QString);
    void rec_new_stu(QString,QString,QString,QString,QString);
    void rec_del_stu(QString);
    void rec_rename_stu(QString,QString);
    void rec_reage_stu(QString,QString);
    void rec_resex_stu(QString,QString);
    void rec_redept_stu(QString,QString);
    void rec_new_course(QString,QString,QString,QString);
    void rec_del_course(QString);
    void rec_recname_course(QString,QString);
    void rec_recpno_course(QString,QString);
    void rec_recredit_course(QString,QString);
    void rec_new_sc(QString,QString,QString);
    void rec_del_sc(QString,QString);
    void rec_cha_sc(QString,QString,QString);
    void rec_stu_sel(QString);
    void rec_course_sel(QString);
    void rec_man_mode(QString);

private slots:
    //void processDataa(int);

    //void on_one_clicked();

    //void on_two_clicked();

    //void on_three_clicked();

    void on_find_stu_clicked();

    void on_find_stu_all_clicked();

    void on_find_stu_all_2_clicked();

    void on_find_sc_clicked();

    void on_find_sc_2_clicked();

    void on_find_sc_3_clicked();

    void on_find_sc_4_clicked();

    void on_grade_sel_clicked();

    void on_loadsys_clicked();

    void on_ex_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
