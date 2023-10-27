#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(flag_log=="0"){
        ui->find_stu_all->setEnabled(false);
        ui->find_stu->setEnabled(false);
        ui->find_stu_all_2->setEnabled(false);
        ui->find_sc->setEnabled(false);
        ui->find_sc_2->setEnabled(false);
        ui->find_sc_3->setEnabled(false);
        ui->find_sc_4->setEnabled(false);
        ui->grade_sel->setEnabled(false);
    }
    sql_connect();
    //find->show();
    //connect(find,SIGNAL(sendDataa(int)),this,SLOT(processDataa(int)));
    connect(find,&Find::send_sno,this,&MainWindow::rec_sno);
    connect(find,&Find::send_sname,this,&MainWindow::rec_sname);
    connect(find_sc,&Find_sc::send_sno,this,&MainWindow::rec_sno_sc);
    connect(find_sc,&Find_sc::send_sname,this,&MainWindow::rec_sname_sc);
    connect(stuset,&stu_set::new_student,this,&MainWindow::rec_new_stu);
    connect(stuset,&stu_set::del_student,this,&MainWindow::rec_del_stu);
    connect(stuset,&stu_set::rename_stu,this,&MainWindow::rec_rename_stu);
    connect(stuset,&stu_set::reage_stu,this,&MainWindow::rec_reage_stu);
    connect(stuset,&stu_set::resex_stu,this,&MainWindow::rec_resex_stu);
    connect(stuset,&stu_set::redept_stu,this,&MainWindow::rec_redept_stu);
    connect(coset,&course_set::new_course,this,&MainWindow::rec_new_course);
    connect(coset,&course_set::del_course,this,&MainWindow::rec_del_course);
    connect(coset,&course_set::rcname_course,this,&MainWindow::rec_recname_course);
    connect(coset,&course_set::rcpno_course,this,&MainWindow::rec_recpno_course);
    connect(coset,&course_set::rcredit_course,this,&MainWindow::rec_recredit_course);
    connect(scset,&sc_set::new_sc,this,&MainWindow::rec_new_sc);
    connect(scset,&sc_set::del_sc,this,&MainWindow::rec_del_sc);
    connect(scset,&sc_set::cha_sc,this,&MainWindow::rec_cha_sc);
    connect(gsel,&grade_sel::stu_sel,this,&MainWindow::rec_stu_sel);
    connect(gsel,&grade_sel::course_sel,this,&MainWindow::rec_course_sel);
    connect(ld,&load::man_mode,this,&MainWindow::rec_man_mode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::sql_connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("student_zyy.db");
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

void MainWindow::rec_sno(QString m_sno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("select * from student");
    qr.prepare("select * from student where sno = ?");
    qr.addBindValue(m_sno);//有点类似格式化字符串的作用
    qr.exec();
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_sname(QString m_sname)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("select * from student");
    qr.prepare("select * from student where sname = ?");
    qr.addBindValue(m_sname);//有点类似格式化字符串的作用
    qr.exec();
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_sno_sc(QString sno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("select * from student");
    qr.prepare("select sc.sno,sname,cname,grade from sc,student,course where sc.sno=student.sno AND sc.sno=? AND course.cno=sc.cno");
    qr.addBindValue(sno);//有点类似格式化字符串的作用
    qr.exec();
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_sname_sc(QString sname)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("select * from student");
    qr.prepare("select sc.sno,sname,cname,grade from sc,student,course where sc.sno=student.sno AND sname=? AND course.cno=sc.cno");
    qr.addBindValue(sname);//有点类似格式化字符串的作用
    qr.exec();
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_new_stu(QString sno, QString sname, QString ssex, QString sage, QString sdept)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("insert into student(Sno,Sname,Ssex,Sage,Sdept) values('20191000663','张宇一','男',22,'AC')");
    qr.prepare("insert into student(Sno,Sname,Ssex,Sage,Sdept) values(:a,:b,:c,:d,:e)");
    qr.bindValue(":a",sno);//有点类似格式化字符串的作用
    qr.bindValue(":b",sname);
    qr.bindValue(":c",ssex);
    qr.bindValue(":d",sage);
    qr.bindValue(":e",sdept);
    qr.exec();
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_del_stu(QString sno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("insert into student(Sno,Sname,Ssex,Sage,Sdept) values('20191000663','张宇一','男',22,'AC')");
    qr.prepare("delete from student where sno = ?");
    qr.addBindValue(sno);//有点类似格式化字符串的作用
    qr.exec();
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);

}

void MainWindow::rec_rename_stu(QString sno, QString sname)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("insert into student(Sno,Sname,Ssex,Sage,Sdept) values('20191000663','张宇一','男',22,'AC')");
    qr.prepare("update student set Sname = :b where Sno = :a");
    qr.bindValue(":a",sno);//有点类似格式化字符串的作用
    qr.bindValue(":b",sname);
    qr.exec();
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_reage_stu(QString sno, QString sage)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update student set Sage = :b where Sno = :a");
    qr.bindValue(":a",sno);//有点类似格式化字符串的作用
    qr.bindValue(":b",sage);
    qr.exec();
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_resex_stu(QString sno, QString sex)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update student set Ssex = :b where Sno = :a");
    qr.bindValue(":a",sno);//有点类似格式化字符串的作用
    qr.bindValue(":b",sex);
    qr.exec();
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_redept_stu(QString sno, QString sdept)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update student set Sdept = :b where Sno = :a");
    qr.bindValue(":a",sno);//有点类似格式化字符串的作用
    qr.bindValue(":b",sdept);
    qr.exec();
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_new_course(QString cno, QString cname, QString cpno, QString credit)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("select * from course");
    qr.prepare("insert into course(Cno,Cname,Cpno,Ccredit) values(:a,:b,:c,:d)");
    qr.bindValue(":a",cno);//有点类似格式化字符串的作用
    qr.bindValue(":b",cname);
    qr.bindValue(":c",cpno);
    qr.bindValue(":d",credit);
    qr.exec();
    qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_del_course(QString cno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("delete from course where Cno = ?");
    qr.addBindValue(cno);//有点类似格式化字符串的作用
    qr.exec();
    qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_recname_course(QString cno, QString cname)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update course set Cname = :b where Cno = :a");
    qr.bindValue(":a",cno);//有点类似格式化字符串的作用
    qr.bindValue(":b",cname);
    qr.exec();
    qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_recpno_course(QString cno, QString cpno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update course set Cpno = :b where Cno = :a");
    qr.bindValue(":a",cno);//有点类似格式化字符串的作用
    qr.bindValue(":b",cpno);
    qr.exec();
    qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_recredit_course(QString cno, QString credit)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update course set Ccredit = :b where Cno = :a");
    qr.bindValue(":a",cno);//有点类似格式化字符串的作用
    qr.bindValue(":b",credit);
    qr.exec();
    qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_new_sc(QString sno, QString cno, QString grade)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    //qr.exec("select * from course");
    qr.prepare("insert into sc(Sno,Cno,grade) values(:a,:b,:c)");
    qr.bindValue(":a",sno);//有点类似格式化字符串的作用
    qr.bindValue(":b",cno);
    qr.bindValue(":c",grade);
    qr.exec();
    qr.exec("select Sname,sc.Sno,sc.Cno,Cname,grade from student,sc,course where sc.Sno=student.Sno AND sc.Cno=course.Cno");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_del_sc(QString sno, QString cno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("delete from sc where Cno = :a AND Sno = :b");
    qr.bindValue(":a",cno);//有点类似格式化字符串的作用
    qr.bindValue(":b",sno);
    qr.exec();
    qr.exec("select Sname,sc.Sno,sc.Cno,Cname,grade from student,sc,course where sc.Sno=student.Sno AND sc.Cno=course.Cno");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_cha_sc(QString sno, QString cno, QString grade)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("update sc set grade = :b where Cno = :a AND Sno = :c");
    qr.bindValue(":a",cno);//有点类似格式化字符串的作用
    qr.bindValue(":b",grade);
    qr.bindValue(":c",sno);
    qr.exec();
    qr.exec("select Sname,sc.Sno,sc.Cno,Cname,grade from student,sc,course where sc.Sno=student.Sno AND sc.Cno=course.Cno");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_stu_sel(QString sno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("select student.Sno,Sname,AVG(grade) 平均成绩,MAX(grade) 最高分,MIN(grade) 最低分 from sc,student,course where sc.Sno=student.Sno AND sc.Cno=course.Cno AND sc.Sno = ? group by sc.Sno");
    qr.addBindValue(sno);//有点类似格式化字符串的作用
    qr.exec();
    //qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_course_sel(QString cno)
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.prepare("select sc.Cno,Cname,AVG(grade) 平均成绩,MAX(grade) 最高分,MIN(grade) 最低分 from sc,student,course where sc.Sno=student.Sno AND sc.Cno=course.Cno AND sc.Cno = ? group by sc.Cno");
    qr.addBindValue(cno);//有点类似格式化字符串的作用
    qr.exec();
    //qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}

void MainWindow::rec_man_mode(QString)
{
    if(flag_log=="0"){
        ui->find_stu_all->setEnabled(false);
        ui->find_stu->setEnabled(false);
        ui->find_stu_all_2->setEnabled(false);
        ui->find_sc->setEnabled(false);
        ui->find_sc_2->setEnabled(false);
        ui->find_sc_3->setEnabled(false);
        ui->find_sc_4->setEnabled(false);
        ui->grade_sel->setEnabled(false);
    }
    else if(flag_log=="1"){
        ui->find_stu_all->setEnabled(true);
        ui->find_stu->setEnabled(true);
        ui->find_stu_all_2->setEnabled(true);
        ui->find_sc->setEnabled(true);
        ui->find_sc_2->setEnabled(true);
        ui->find_sc_3->setEnabled(true);
        ui->find_sc_4->setEnabled(true);
        ui->grade_sel->setEnabled(true);
        ld->close();
    }
    else if(flag_log=="2"){
        ui->find_stu_all->setEnabled(false);
        ui->find_stu->setEnabled(true);
        ui->find_stu_all_2->setEnabled(false);
        ui->find_sc->setEnabled(true);
        ui->find_sc_2->setEnabled(true);
        ui->find_sc_3->setEnabled(false);
        ui->find_sc_4->setEnabled(false);
        ui->grade_sel->setEnabled(true);
        ld->close();

    }
}



/*
void MainWindow::on_one_clicked()
{
    ui->one->setEnabled(false);
    ui->two->setEnabled(true);
    ui->three->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_two_clicked()
{
    ui->one->setEnabled(true);
    ui->two->setEnabled(false);
    ui->three->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_three_clicked()
{
    ui->one->setEnabled(true);
    ui->two->setEnabled(true);
    ui->three->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(2);
}*/


void MainWindow::on_find_stu_clicked()
{
    find->show();
}


void MainWindow::on_find_stu_all_clicked()
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.exec("select * from student");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}


void MainWindow::on_find_stu_all_2_clicked()
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.exec("select sname,cname,sc.cno,grade from sc,student,course where student.sno=sc.sno AND course.cno=sc.cno");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
}


void MainWindow::on_find_sc_clicked()
{
    find_sc->show();
}


void MainWindow::on_find_sc_2_clicked()
{
    stuset->show();
}


void MainWindow::on_find_sc_3_clicked()
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.exec("select * from course");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
    coset->show();
}


void MainWindow::on_find_sc_4_clicked()
{
    studentqrModel=new QSqlQueryModel(this);
    sql_connect();
    QSqlQuery qr;
    qr.exec("select Sname,sc.Sno,sc.Cno,Cname,grade from student,sc,course where sc.Sno=student.Sno AND sc.Cno=course.Cno");
    studentqrModel->setQuery(qr);
    ui->tableView_manage->setModel(studentqrModel);
    scset->show();
}


void MainWindow::on_grade_sel_clicked()
{
    gsel->show();
}


void MainWindow::on_loadsys_clicked()
{
    ld->show();
}


void MainWindow::on_ex_clicked()
{

        ui->find_stu_all->setEnabled(false);
        ui->find_stu->setEnabled(false);
        ui->find_stu_all_2->setEnabled(false);
        ui->find_sc->setEnabled(false);
        ui->find_sc_2->setEnabled(false);
        ui->find_sc_3->setEnabled(false);
        ui->find_sc_4->setEnabled(false);
        ui->grade_sel->setEnabled(false);
        flag_log="0";
        ld->show();
}

