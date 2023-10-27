#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlTableModel>
#include<QtSql/QSqlQueryModel>
#include<Qtsql/QSqlQuery>
#include<Qtsql/QSqlRelationalTableModel>
#include<Qtsql>
extern QString in;
extern QString in1;
extern QString in2;
extern QString in3;
extern QString in4;


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_save_clicked();

    void on_save_3_clicked();

    void on_save_10_clicked();

public:
    Ui::Dialog *ui_1;
};

#endif // DIALOG_H
