#include "my_load.h"
#include "ui_my_load.h"
int tell;
int a=0;
QVector<QString>teacher_login={"10002000","10003000"};
QVector<QString>teacher_password={"123456","234567"};
my_load::my_load(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::my_load)
{
    ui->setupUi(this);
    ui->server->setPlaceholderText(QString::fromUtf8("请输入用户名"));
    ui->password->setPlaceholderText(QString::fromUtf8("请输入密码"));

}

my_load::~my_load()
{
    delete ui;
}

void my_load::on_loadsure_clicked()
{
    if(tell==1)
    {
        //QVector<QString>::iterator it;
        int judge=0;
        int a=0;
        int length=teacher_login.size();
        int length1=teacher_password.size();
        for(int i=0;i<length;++i)
        {
            if(teacher_login[i]==ui->server->text())
            {
               a=i;
               judge=1;
               break;
            }
        }
        if(teacher_password[a]==ui->password->text())
        {
          //  ui1=new MainWindow(this);
            //ui1->setModal(false);
           // ui1->show();
        }

        else
        {
            ui->password->clear();
            ui->password->setPlaceholderText(QString::fromUtf8("密码错误"));
        }

    }


}


void my_load::on_checkBox_stateChanged(int arg1)
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

