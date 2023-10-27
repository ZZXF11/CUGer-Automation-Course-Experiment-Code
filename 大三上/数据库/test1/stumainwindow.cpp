#include "stumainwindow.h"
#include "ui_stumainwindow.h"
#include<QMessageBox>
bool stuMainWindow::myconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("student.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    return true;
}

stuMainWindow::stuMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stuMainWindow)
{
    ui->setupUi(this);
    myconnect();


}

stuMainWindow::~stuMainWindow()
{
    delete ui;
}




void stuMainWindow::on_pushButton_clicked()
{
    studentserqrModel=new QSqlQueryModel(this);
    QString sqlCreate = QString(
                "SELECT student.sno,sname,ssex,sdept,sage,course.cno,cname,cpno,ccredit,grade "
                "FROM student,sc,course "
                "WHERE student.sno=sc.sno AND sc.cno=course.cno;"
                   );

       QSqlQuery st;
       st.exec(sqlCreate);
       studentserqrModel->setQuery(st);
       ui->tableView->setModel(studentserqrModel);
}

