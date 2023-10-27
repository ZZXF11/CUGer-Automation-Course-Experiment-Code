#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<OperatorFactory.h>
#include"ui_dialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int precedence(const QString& s) const;//获取优先级,没有用到
    string readsin(string::iterator& it);
    bool issin(string::iterator& c) const {
        return *c >= 'a' && *c <= 'z';
    }
    bool isopr(QString s);
    void calculate();
    void keyPressEvent(QKeyEvent *e);

private slots:

    void on_num1_clicked();

    void on_num2_clicked();

    void on_num3_clicked();

    void on_num4_clicked();

    void on_num5_clicked();

    void on_num6_clicked();

    void on_num7_clicked();

    void on_num8_clicked();

    void on_num9_clicked();

    void on_num0_clicked();

    void on_point_clicked();

    void on_plus_clicked();

    void on_pi_clicked();

    void on_sin_clicked();

    void on_cos_clicked();

    void on_tan_clicked();

    void on_asin_clicked();

    void on_acos_clicked();

    void on_atan_clicked();

    void on_lkuo_clicked();

    void on_rkuo_clicked();

    void on_gantan_clicked();

    void on_min_clicked();

    void on_mul_clicked();

    void on_div_clicked();

    void on_qiuyu_clicked();

    void on_pinfang_clicked();

    void on_kaifang_clicked();

    void on_back_clicked();

    void on_cle_clicked();

    void on_equ_clicked();

    void on_clc_clicked();

    void on_ce_clicked();

    void on_zhengfu_clicked();


    void on_qlog_clicked();

    void on_qln_clicked();

    void on_daoshu_clicked();

    void on_em_clicked();

    void on_time_clicked();



    void on_red_clicked();

    void on_blue_clicked();

    void on_black_clicked();

    void on_qe_clicked();

private:
    Stack<double> m_num; // 数字栈
    Stack<unique_ptr<Operator>> m_opr; // 运算符栈
    Ui::Dialog *ui;
    QString m_epx;
    QString m_show;
    int ended;
    double readNum(string::iterator &it); 	// 读取操作数
    double readnum(string::iterator& it);
    bool readdot(QString s);
    bool isNum(string::iterator &c) { // 判断字符是否为数字
        return (*c >= '0'&&*c <= '9' )|| *c == '.'||*c=='p'||*c=='i';
    }
    double doIt(QString &question);
};



#endif // DIALOG_H
