#include "dialog.h"
#include "ui_dialog.h"
#include<QTime>
#include<QKeyEvent>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ended=0;
    m_opr.push(make_unique<Hash>());
}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog::on_num1_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="1";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);

}

void Dialog::on_num2_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="2";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num3_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="3";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num4_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="4";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num5_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="5";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num6_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="6";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num7_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="7";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num8_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="8";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num9_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="9";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_num0_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="0";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_point_clicked()
{
    QString btm=".";
    if(readdot(m_epx)){
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
    }
}


void Dialog::on_plus_clicked()
{
    QString btm="+";
    if(readdot(m_epx)){
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
    }
}


void Dialog::on_pi_clicked()
{
    if(ended==1){
        m_epx.clear();
        m_show.clear();
        m_num.clear();
    }
    QString btm="(pi)";
    QString sbtm="π";
    m_show+=sbtm;
    m_epx+=btm;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_sin_clicked()
{
    QString btm="sin";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
    }
    else{
        m_show+=btm;
        m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_cos_clicked()
{
    QString btm="cos";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
    }
    else{
        m_show+=btm;
        m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_tan_clicked()
{
    QString btm="tan";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
    }
    else{
        m_show+=btm;
        m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_asin_clicked()
{
    QString btm="asin";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
    }
    else{
        m_show+=btm;
        m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_acos_clicked()
{
    QString btm="acos";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
    }
    else{
        m_show+=btm;
        m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_atan_clicked()
{
    QString btm="atan";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
    }
    else{
        m_show+=btm;
        m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_lkuo_clicked()
{
    QString btm="(";
    if(ended==1){
        m_show.clear();
        m_epx.clear();
        m_num.clear();
    }
    m_epx+=btm;
    m_show+=btm;
    ui->textBrowser->setText(m_show);
    ended=0;
}


void Dialog::on_rkuo_clicked()
{
    QString btm=")";
    if(ended==1){
        m_show.clear();
        m_epx.clear();
        m_num.clear();
    }
    m_epx+=btm;
    m_show+=btm;
    ui->textBrowser->setText(m_show);
    ended=0;
}


void Dialog::on_gantan_clicked()
{
    QString btm="!";
    m_show+=btm;
    m_epx+=btm;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_min_clicked()
{
    if(readdot(m_epx)){
    QString btm="-";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
    }
}


void Dialog::on_mul_clicked()
{
    if(readdot(m_epx)){
    QString btm="*";
    QString sbtm="×";
    m_show+=sbtm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
    }
}


void Dialog::on_div_clicked()
{
    QString btm="/";
    QString sbtm="÷";
    if(readdot(m_epx)){
    m_show+=sbtm;
    ended=0;
    m_epx+=btm;
    ui->textBrowser->setText(m_show);
    }
}


void Dialog::on_qiuyu_clicked()
{
    if(readdot(m_epx)){
    QString btm="%";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
     }
}




void Dialog::on_pinfang_clicked()
{
     if(readdot(m_epx)){
    QString btm="^";
    m_show+=btm;
    m_epx+=btm;
    ended=0;
    ui->textBrowser->setText(m_show);
     }
}


void Dialog::on_kaifang_clicked()
{
    QString btm="sqrt";
    QString sbtm="√";
    if(ended==1){
        m_show.push_front(sbtm);
        m_epx.push_front(btm);
        }
    else{
    m_show+=sbtm;
    m_epx+=btm;
    }
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_back_clicked()
{
    if(m_show.right(1)=="π"){
        m_show.chop(1);
        m_epx.chop(4);
    }
    else if(m_show.right(4)=="asin"||m_show.right(4)=="acos"||m_show.right(4)=="atan"){
        m_show.chop(4);
        m_epx.chop(4);
    }
    else if(m_show.right(3)=="sin"||m_show.right(3)=="cos"||m_show.right(3)=="tan"||m_show.right(3)=="log"){
        m_show.chop(3);
        m_epx.chop(3);
    }
    else if(m_show.right(3)=="sin"){
        m_show.chop(3);
        m_epx.chop(2);
    }
    else if(m_show.right(2)=="ln"||m_show.right(2)=="e^"){
        m_show.chop(2);
        m_epx.chop(2);
    }
    else{
        m_show.chop(1);
        m_epx.chop(1);
    }
    ui->textBrowser->setText(m_show);
    //ui->textabc->setText(m_epx);
}


void Dialog::on_cle_clicked()
{
    m_epx.clear();
    m_show.clear();
    m_num.clear();
    //m_opr.clear();
    ui->textBrowser->setText("0");
}

double Dialog::doIt(QString &epx) {
    unique_ptr<Operator> oo;
    ui->his_show->append(m_show);
    string exp;
    exp= epx.toStdString();
    for (auto it = exp.begin(); it != exp.end();) {
        // 如果是操作数, 压栈之
        if (isNum(it))
            m_num.push(readNum(it));
        else {// 如果是运算符, 压栈或计算
              // 将readOpr得到的string转化为Operator
            if(issin(it))
                oo=Factory::create(readsin(it));
            else
            {
                string s;
                s+=*it++;
                oo=Factory::create(s);
            }
            // 如果栈顶优先级高, 则计算
            if(oo->symbol()!="(")
            {
                while (oo->precedence() <= m_opr.top()->precedence()) {
                if (m_opr.top()->symbol() == "#")
                    break;
                calculate();
                }
            }
            // "="从不入栈
            if (oo->symbol() != "=")
                m_opr.push(std::move(oo));
        }
    }
    double result = m_num.top();
    double a=m_num.top();
    ui->textBrowser->append(QString::number(a));
    ui->his_show->append(QString::number(a));
    epx.clear();
    m_show.clear();
    m_epx+=QString::number(a);
    m_show+=QString::number(a);
    return result;
}

double Dialog::readNum(string::iterator& it){
    string t;
    while (isNum(it))
        t += *it++;
    if (t == "pi")
    {
        return acos(-1);
    }
    return stod(t);
}
double Dialog::readnum(string::iterator& it){
    string t;
    while (isNum(it))
        t += *it--;
    if (t == "ip")
    {
        return acos(-1);
    }
    return stod(t);
}

bool Dialog::readdot(QString s){
    QString t;
    string z;
    QString a;
    t=s;
    z=t.toStdString();
    a=m_epx.right(1);
    if(a=="."||a=="+"||a=="-"||a=="*"||a=="/"||a=="^"){
        return 0;
    }
    else if(m_show.length()==0){
        return 0;
    }
    else{
        return 1;
    }
}

bool Dialog::isopr(QString s){
    QString t;
    string z;
    string a;
    t=s;
    z=t.toStdString();
    a=*(z.end()-1);
    if(a=="√"||a=="+"||a=="-"||a=="*"||a=="/"||a=="^"){
        return 0;
    }
    else{
        return 1;
    }
}

string Dialog::readsin(string::iterator& it){
    string t;
    while (issin(it)&&t!="em"&&t!="sin"&&t!="cos"&&t!="sqrt"&&t!="log"&&t!="ln"&&t!="reciprocal"&&t!="asin"&&t!="acos"&&t!="atan"&&t!="tan")
        t += *it++;
    return t;
}
void Dialog::calculate() {
    // 操作数出栈并传入Operator进行计算, 在此只考虑单目和双目运算符
    double a[2] = { 0 };
    for (auto i = 0; i < m_opr.top()->numOprand(); ++i) {
        a[i] = m_num.top();
        m_num.pop();
    }
    m_num.push(m_opr.top()->get(a[1], a[0]));
    m_opr.pop();
}

void Dialog::on_equ_clicked()
{
    QString btm="=";
    m_epx+=btm;
    m_show+=btm;
    ui->textBrowser->setText(m_show);
    doIt(m_epx);
    ended=1;
}


void Dialog::on_clc_clicked()
{
    QString t="clear";
    ui->his_show->setText(t);
}


void Dialog::on_ce_clicked()
{
    string exp;
    exp= m_epx.toStdString();
    if(exp.length()!=0){
    for(auto it=(exp.end()-1);;){
        if((exp.end()-1)==exp.begin()){
            m_epx.clear();
            m_show.clear();
            m_num.clear();
            break;
        }
        if(isNum(it)){
            --it;
            m_show.chop(1);
            m_epx.chop(1);
           if(it==exp.begin()){
                m_epx.clear();
                m_show.clear();
                m_num.clear();
                break;
            }
        }
        else{
            break;
        }
    }
    ui->textBrowser->setText(m_show);
    }
}


void Dialog::on_zhengfu_clicked()
{
    m_show.push_front("(-(");
    m_epx.push_front("0-(");
    m_show.push_back(")");
    m_epx.push_back(")");
    ended=0;
    ui->textBrowser->setText(m_show);
    ui->textabc->setText(m_epx);
}


void Dialog::on_qlog_clicked()
{
    QString btm="log";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
        }
    else{
        m_epx+=btm;
        m_show+=btm;
        }
    ended=0;
     ui->textBrowser->setText(m_show);
}


void Dialog::on_qln_clicked()
{
    QString btm="ln";
    if(ended==1){
        m_show.push_front(btm);
        m_epx.push_front(btm);
        }
    else{
        m_epx+=btm;
        m_show+=btm;
        }
    ended=0;
     ui->textBrowser->setText(m_show);
}


void Dialog::on_daoshu_clicked()
{
    QString btm="ds";
    m_epx+=btm;
    m_show+="^-1";
    ended=0;
    ui->textBrowser->setText(m_show);
}


void Dialog::on_em_clicked()
{
    QString btm="em";
    if(ended==1){
        ended=0;
        m_show.push_front("e^");
        m_epx.push_front(btm);
        }
    else{
        m_epx+=btm;
        m_show+="e^";
        }
    ended=0;
     ui->textBrowser->setText(m_show);
}


void Dialog::on_time_clicked()
{
    QDateTime current_time = QDateTime::currentDateTime();
    //显示时间，格式为：年-月-日 时：分：秒 周几
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    //时间显示格式可自由设定，如hh:mm ddd 显示 时：分 周几
    //具体格式见函数QString QDateTime::​toString(const QString & format) const
    ui->textabc->setText(StrCurrentTime);
}

void Dialog::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_0){
        Dialog::on_num0_clicked();
    }
    else if(e->key()==Qt::Key_1){
        Dialog::on_num1_clicked();
    }
    else if(e->key()==Qt::Key_2){
        Dialog::on_num2_clicked();
    }
    else if(e->key()==Qt::Key_3){
        Dialog::on_num3_clicked();
    }
    else if(e->key()==Qt::Key_4){
        Dialog::on_num4_clicked();
    }
    else if(e->key()==Qt::Key_5){
        Dialog::on_num5_clicked();
    }
    else if(e->key()==Qt::Key_6){
        Dialog::on_num6_clicked();
    }
    else if(e->key()==Qt::Key_7){
        Dialog::on_num7_clicked();
    }
    else if(e->key()==Qt::Key_8){
        Dialog::on_num8_clicked();
    }
    else if(e->key()==Qt::Key_9){
        Dialog::on_num9_clicked();
    }
    else if(e->key()==Qt::Key_A){
        Dialog::on_plus_clicked();
    }
    else if(e->key()==Qt::Key_Minus){
        Dialog::on_min_clicked();
    }
    else if(e->key()==Qt::Key_M){
        Dialog::on_mul_clicked();
    }
    else if(e->key()==Qt::Key_Slash){
        Dialog::on_div_clicked();
    }
    else if(e->key()==Qt::Key_Period){
        Dialog::on_point_clicked();
    }
    else if(e->key()==Qt::Key_Backspace){
        Dialog::on_back_clicked();
    }
    else if(e->key()==Qt::Key_Equal){
        Dialog::on_equ_clicked();
    }
    else if(e->key()==Qt::Key_T){
        Dialog::on_time_clicked();
    }
    else if(e->key()==Qt::Key_Y){
        Dialog::on_qiuyu_clicked();
    }
    else if(e->key()==Qt::Key_AsciiCircum){
        Dialog::on_pinfang_clicked();
    }
    else if(e->key()==Qt::Key_G){
        Dialog::on_gantan_clicked();
    }
    else if(e->key()==Qt::Key_R){
        Dialog::on_rkuo_clicked();
    }
    else if(e->key()==Qt::Key_L){
        Dialog::on_lkuo_clicked();
    }
    else if(e->key()==Qt::Key_C){
        Dialog::on_cle_clicked();
    }

}



void Dialog::on_red_clicked()
{
    QPalette plet=ui->textBrowser->palette();
    plet.setColor(QPalette::Text,Qt::red);
    ui->textBrowser->setPalette(plet);
    ui->his_show->setPalette(plet);
    ui->textabc->setPalette(plet);
}


void Dialog::on_blue_clicked()
{
    QPalette plet=ui->textBrowser->palette();
    plet.setColor(QPalette::Text,Qt::blue);
    ui->textBrowser->setPalette(plet);
    ui->his_show->setPalette(plet);
    ui->textabc->setPalette(plet);
}


void Dialog::on_black_clicked()
{
    QPalette plet=ui->textBrowser->palette();
    plet.setColor(QPalette::Text,Qt::black);
    ui->textBrowser->setPalette(plet);
    ui->his_show->setPalette(plet);
    ui->textabc->setPalette(plet);
}


void Dialog::on_qe_clicked()
{
    QString sbtm="e";
    QString btm="2.718";
    m_show+=sbtm;
    m_epx+=btm;
    ui->textBrowser->setText(m_show);
    //ui->textabc->setText(m_epx);
}

