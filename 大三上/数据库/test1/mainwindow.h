#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlTableModel>
#include<QtSql/QSqlQueryModel>
#include<Qtsql/QSqlQuery>
#include<Qtsql/QSqlRelationalTableModel>
#include<Qtsql>
#include"dialog.h"
#include"dialog1.h"
#include"dialog_pwf.h"
#include"dialog2.h"
#include"stumainwindow.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
      bool myconnect();

private:
    QSqlTableModel*homeModel;
    QSqlTableModel*studentModel;
    QSqlTableModel*scModel;
    QSqlTableModel*courseModel;
    QSqlQueryModel*studentqrModel;
    QSqlQueryModel*scqrModel;
    QSqlQueryModel*courseqrModel;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pwf_clicked();



    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QDialog * myinsert;
    QDialog * mydelete;
    QDialog * pwf;
    QDialog * search;
   // QDialog * my_insert;
};
#endif // MAINWINDOW_H
