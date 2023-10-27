#ifndef STUMAINWINDOW_H
#define STUMAINWINDOW_H

#include <QMainWindow>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlTableModel>
#include<QtSql/QSqlQueryModel>
#include<Qtsql/QSqlQuery>
#include<Qtsql/QSqlRelationalTableModel>
#include<Qtsql>
namespace Ui {
class stuMainWindow;
}

class stuMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlTableModel*studentserModel;
    QSqlQueryModel*studentserqrModel;
    bool myconnect();
public:
    explicit stuMainWindow(QWidget *parent = nullptr);
    ~stuMainWindow();

private slots:


     void on_pushButton_clicked();

private:
    Ui::stuMainWindow *ui;
};

#endif // STUMAINWINDOW_H
