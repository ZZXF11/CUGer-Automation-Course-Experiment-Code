#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QString>
#include"my_insert.h"

bool MainWindow::myconnect()
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    studentqrModel=new QSqlQueryModel(this);
    courseqrModel=new QSqlQueryModel(this);
    scqrModel=new QSqlQueryModel(this);
    myconnect();
   // ui->setupUi(this);
    //studentqrModel=new QSqlQueryModel(this);
    //myconnect();

   // QString id="0";
   // QSqlQuery qr;
   // qr.prepare("select * from home where id = ? ，？ ，？");
   // qr.addBindValue(2，id);
    // qr.exec();
    //studentqrModel->setQuery(qr);
    //ui->tableView->setModel(studentqrModel);

    //homeModel=new QSqlTableModel(this);
    //homeModel->setTable("home");
    //homeModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //homeModel->setFilter("id=1");
   // homeModel->select();
    //ui->tableView_2->setModel(homeModel);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked()
{
    studentModel= new QSqlTableModel(this);
    studentModel->setTable("student");
    studentModel->select();
    ui->tableView_1->setModel(studentModel);
    ui->stackedWidget->setCurrentIndex(0);




    //QSqlQuery qr;
   // qr.exec("select * from student");
    //studentqrModel->setQuery(qr);
   // ui->tableView_1->setModel(studentqrModel);
    //ui->stackedWidget->setCurrentIndex(0);



}


void MainWindow::on_pushButton_4_clicked()
{
    courseModel= new QSqlTableModel(this);
    courseModel->setTable("course");
    courseModel->select();
    ui->tableView_1->setModel(courseModel);
    ui->stackedWidget->setCurrentIndex(0);


}


void MainWindow::on_pushButton_6_clicked()
{
    scModel= new QSqlTableModel(this);
    scModel->setTable("sc");
    scModel->select();
    ui->tableView_1->setModel(scModel);
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_clicked()
{



    myinsert=new Dialog(this);
    myinsert->setModal(false);
    myinsert->show();







}


void MainWindow::on_pushButton_2_clicked()
{

    mydelete=new Dialog1(this);
    mydelete->setModal(false);
    mydelete->show();

}


void MainWindow::on_pushButton_3_clicked()
{
    studentModel->database().transaction();
    if (studentModel->submitAll()) {
        studentModel->database().commit();
    } else {
        studentModel->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),
                             tr("The database reported an error: %1")
                             .arg(studentModel->lastError().text()));
    }
/*
    courseModel->database().transaction();
        if (courseModel->submitAll()) {
            courseModel->database().commit();
        } else {
            courseModel->database().rollback();
            QMessageBox::warning(this, tr("Cached Table"),
                                 tr("The database reported an error: %1")
                                 .arg(studentModel->lastError().text()));
        }*/

   /* scModel->database().transaction();
    if (scModel->submitAll()) {
        scModel->database().commit();
    } else {
        scModel->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),
                             tr("The database reported an error: %1")
                             .arg(courseModel->lastError().text()));
    }*/


}


void MainWindow::on_pwf_clicked()
{
    pwf=new Dialog_pwf(this);
    pwf->setModal(false);
    pwf->show();
}





void MainWindow::on_pushButton_7_clicked()
{
    search=new Dialog2(this);
    search->setModal(false);
    search->show();

}

