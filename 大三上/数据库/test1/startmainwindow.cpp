#include "startmainwindow.h"
#include "ui_startmainwindow.h"
int tell;
int a;
QVector<QString> teacher_login;
QVector<QString> teacher_password;
QVector<QString> student_login;
QVector<QString> student_password;
startMainWindow::startMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startMainWindow)
{
    ui->setupUi(this);


   // QFile file("student_password");
     //老师
     QFile file("./teacher_login");
     if(!file.open(QIODevice::ReadOnly))
        {

             return;
        }
        QTextStream in(&file);
        while(!in.atEnd()){
            //ui->textBrowser->setText(in.readLine());
           teacher_login.push_back(in.readLine());
           // ui->textBrowser->setText(teacher_login[0]);
        }
        file.close();

       QFile file2("./teacher_password");
       if(!file2.open(QIODevice::ReadOnly))
            {
                 return;
            }
            QTextStream in2(&file2);
            while(!in2.atEnd()){
               teacher_password.push_back(in2.readLine());
               // ui->textBrowser->setText(teacher_login[1]);
            }
            file2.close();

            //学生

            QFile file3("./student_login");
            if(!file3.open(QIODevice::ReadOnly))
               {

                    return;
               }
               QTextStream in3(&file3);
               while(!in3.atEnd()){
                   //ui->textBrowser->setText(in.readLine());
                  student_login.push_back(in3.readLine());
                  // ui->textBrowser->setText(teacher_login[0]);
               }
               file3.close();

              QFile file4("./student_password");
              if(!file4.open(QIODevice::ReadOnly))
                   {
                        return;
                   }
                   QTextStream in4(&file4);
                   while(!in4.atEnd()){
                      student_password.push_back(in4.readLine());
                      // ui->textBrowser->setText(teacher_login[1]);
                   }
                   file4.close();


        ui->lineEdit->setPlaceholderText(QString::fromUtf8("请输入用户名"));
        ui->lineEdit_2->setPlaceholderText(QString::fromUtf8("请输入密码"));

}

startMainWindow::~startMainWindow()
{
    delete ui;
}

void startMainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2)
        {
            tell=1;
        }
        else if(arg1 == 0)
        {
            tell=0;
        }
}


void startMainWindow::on_pushButton_clicked()
{
    if(tell==1)
    {
        //QVector<QString>::iterator it;
        int judge=0;
        a=0;
        int length=teacher_login.size();
        int length1=teacher_password.size();
        for(int i=0;i<length;++i)
        {
            if(teacher_login[i]==ui->lineEdit->text())
            {
               a=i;
               //judge=1;

            }
        }
        if(teacher_password[a]==ui->lineEdit_2->text())
        {
          start=new MainWindow(this);
          start->show();
        }

        else
        {
            ui->lineEdit_2->clear();
            ui->lineEdit_2->setPlaceholderText(QString::fromUtf8("密码错误"));
        }

    }
    if(tell==0)
    {
        int judge=0;
        a=0;
        int length=student_login.size();
        int length1=student_password.size();
        for(int i=0;i<length;++i)
        {
            if(student_login[i]==ui->lineEdit->text())
            {
               a=i;
               //judge=1;

            }
        }
        if(student_password[a]==ui->lineEdit_2->text())
        {
          stustart=new stuMainWindow(this);
          stustart->show();
           //stu=new Dialog2(this);
           //stu->show();
        }

        else
        {
            ui->lineEdit_2->clear();
            ui->lineEdit_2->setPlaceholderText(QString::fromUtf8("密码错误"));
        }

    }
}

