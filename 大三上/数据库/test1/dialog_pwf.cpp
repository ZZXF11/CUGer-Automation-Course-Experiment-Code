#include "dialog_pwf.h"
#include "ui_dialog_pwf.h"



Dialog_pwf::Dialog_pwf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_pwf)
{
    ui->setupUi(this);
}

Dialog_pwf::~Dialog_pwf()
{
    delete ui;
}

void Dialog_pwf::on_pushButton_clicked()
{
    in1="";
    //in2="";
    //in3="";
    //in4="";
    in="";
    in=ui->lineEdit->text();
    in1=ui->lineEdit_2->text();
    //in2=ui_1->lineEdit_3->text();
    //in3=ui_1->lineEdit_4->text();
    //in4=ui_1->lineEdit_7->text();
    //ui_1->lineEdit->clear();
   // ui_1->lineEdit_2->clear();
   // ui_1->lineEdit_3->clear();
   // ui_1->lineEdit_4->clear();
   // ui_1->lineEdit_7->clear();


    if(in!=""&&in1!="")
    {
        QStringList strList;
        QString strAll;
        if(in1==in)
        {
          // teacher_password[a]=in;

           QFile readFile("./teacher_password");		//PATH是自定义读取文件的地址
                if(readFile.open((QIODevice::ReadOnly|QIODevice::Text)))
                {
                    //把文件所有信息读出来
                    QTextStream stream(&readFile);
                    strAll=stream.readAll();
                }
                readFile.close();

           QFile writeFile("./teacher_password");	//PATH是自定义写文件的地址
           if(writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
           {
                QTextStream stream(&writeFile);
                strList=strAll.split("\n");           //以换行符为基准分割文本
                for(int i=0;i<strList.count();i++)    //遍历每一行
                    {
                        if(strList.at(i).contains(teacher_password[a]))    //"123456789"是要修改的内容
                        {
                            QString tempStr=strList.at(i);
                            tempStr.replace(0,tempStr.length(),in);   //"Hello!"是要替换的内容
                            stream<<tempStr<<'\n';

                            ui->textBrowser->setText("密码修改成功");
                        }
                        else
                         {
                             if(i==strList.count()-1)
                             {
                                  stream<<strList.at(i);
                             }
                            else
                            {
                                stream<<strList.at(i)<<'\n';
                             }
                            }


             //writeFile.close();
             }


                }

          writeFile.close();
     }
        else
        {
            ui->lineEdit_2->clear();
             ui->lineEdit_2->setPlaceholderText(QString::fromUtf8("与第一次密码不符合"));
        }
       }
    QFile file2("./teacher_password");
    if(!file2.open(QIODevice::ReadOnly))
         {
              return;
         }
         QTextStream in2(&file2);
         teacher_password.clear();
         while(!in2.atEnd()){
            teacher_password.push_back(in2.readLine());
            // ui->textBrowser->setText(teacher_login[1]);
         }
         file2.close();

}


void Dialog_pwf::on_pushButton_2_clicked()
{
   close();
}

