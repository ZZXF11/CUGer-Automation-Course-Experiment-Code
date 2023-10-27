/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *zhengfu;
    QPushButton *num7;
    QPushButton *daoshu;
    QPushButton *num8;
    QPushButton *plus;
    QPushButton *num3;
    QPushButton *num9;
    QPushButton *num5;
    QPushButton *qiuyu;
    QPushButton *point;
    QPushButton *num4;
    QPushButton *back;
    QPushButton *cle;
    QPushButton *em;
    QPushButton *kaifang;
    QPushButton *num2;
    QPushButton *min;
    QPushButton *pinfang;
    QPushButton *num6;
    QPushButton *div;
    QPushButton *num0;
    QPushButton *mul;
    QPushButton *num1;
    QPushButton *ce;
    QPushButton *equ;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QPushButton *qln;
    QPushButton *sin;
    QPushButton *asin;
    QPushButton *acos;
    QPushButton *tan;
    QPushButton *pi;
    QPushButton *cos;
    QPushButton *atan;
    QPushButton *gantan;
    QPushButton *rkuo;
    QPushButton *lkuo;
    QPushButton *qlog;
    QTextBrowser *textBrowser;
    QTextBrowser *his_show;
    QPushButton *clc;
    QPushButton *out;
    QPushButton *time;
    QTextBrowser *textabc;
    QRadioButton *red;
    QRadioButton *blue;
    QRadioButton *black;
    QPushButton *qe;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(739, 609);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 160, 441, 441));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Forte")});
        font.setPointSize(18);
        font.setBold(false);
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 421, 341));
        sizePolicy.setHeightForWidth(gridLayoutWidget->sizePolicy().hasHeightForWidth());
        gridLayoutWidget->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Bahnschrift SemiLight Condensed")});
        font1.setPointSize(16);
        font1.setBold(false);
        gridLayoutWidget->setFont(font1);
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        zhengfu = new QPushButton(gridLayoutWidget);
        zhengfu->setObjectName(QString::fromUtf8("zhengfu"));
        sizePolicy.setHeightForWidth(zhengfu->sizePolicy().hasHeightForWidth());
        zhengfu->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Bodoni MT")});
        font2.setPointSize(22);
        font2.setBold(false);
        zhengfu->setFont(font2);

        gridLayout->addWidget(zhengfu, 8, 0, 1, 1);

        num7 = new QPushButton(gridLayoutWidget);
        num7->setObjectName(QString::fromUtf8("num7"));
        sizePolicy.setHeightForWidth(num7->sizePolicy().hasHeightForWidth());
        num7->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Bodoni MT")});
        font3.setPointSize(16);
        font3.setBold(false);
        num7->setFont(font3);

        gridLayout->addWidget(num7, 4, 0, 1, 1);

        daoshu = new QPushButton(gridLayoutWidget);
        daoshu->setObjectName(QString::fromUtf8("daoshu"));
        sizePolicy.setHeightForWidth(daoshu->sizePolicy().hasHeightForWidth());
        daoshu->setSizePolicy(sizePolicy);
        daoshu->setFont(font3);

        gridLayout->addWidget(daoshu, 2, 0, 1, 1);

        num8 = new QPushButton(gridLayoutWidget);
        num8->setObjectName(QString::fromUtf8("num8"));
        sizePolicy.setHeightForWidth(num8->sizePolicy().hasHeightForWidth());
        num8->setSizePolicy(sizePolicy);
        num8->setFont(font3);

        gridLayout->addWidget(num8, 4, 1, 1, 1);

        plus = new QPushButton(gridLayoutWidget);
        plus->setObjectName(QString::fromUtf8("plus"));
        sizePolicy.setHeightForWidth(plus->sizePolicy().hasHeightForWidth());
        plus->setSizePolicy(sizePolicy);
        plus->setFont(font2);

        gridLayout->addWidget(plus, 7, 3, 1, 1);

        num3 = new QPushButton(gridLayoutWidget);
        num3->setObjectName(QString::fromUtf8("num3"));
        sizePolicy.setHeightForWidth(num3->sizePolicy().hasHeightForWidth());
        num3->setSizePolicy(sizePolicy);
        num3->setFont(font3);

        gridLayout->addWidget(num3, 7, 2, 1, 1);

        num9 = new QPushButton(gridLayoutWidget);
        num9->setObjectName(QString::fromUtf8("num9"));
        sizePolicy.setHeightForWidth(num9->sizePolicy().hasHeightForWidth());
        num9->setSizePolicy(sizePolicy);
        num9->setFont(font3);

        gridLayout->addWidget(num9, 4, 2, 1, 1);

        num5 = new QPushButton(gridLayoutWidget);
        num5->setObjectName(QString::fromUtf8("num5"));
        sizePolicy.setHeightForWidth(num5->sizePolicy().hasHeightForWidth());
        num5->setSizePolicy(sizePolicy);
        num5->setFont(font3);

        gridLayout->addWidget(num5, 5, 1, 1, 1);

        qiuyu = new QPushButton(gridLayoutWidget);
        qiuyu->setObjectName(QString::fromUtf8("qiuyu"));
        sizePolicy.setHeightForWidth(qiuyu->sizePolicy().hasHeightForWidth());
        qiuyu->setSizePolicy(sizePolicy);
        qiuyu->setFont(font3);

        gridLayout->addWidget(qiuyu, 0, 0, 1, 1);

        point = new QPushButton(gridLayoutWidget);
        point->setObjectName(QString::fromUtf8("point"));
        sizePolicy.setHeightForWidth(point->sizePolicy().hasHeightForWidth());
        point->setSizePolicy(sizePolicy);
        point->setFont(font2);

        gridLayout->addWidget(point, 8, 2, 1, 1);

        num4 = new QPushButton(gridLayoutWidget);
        num4->setObjectName(QString::fromUtf8("num4"));
        sizePolicy.setHeightForWidth(num4->sizePolicy().hasHeightForWidth());
        num4->setSizePolicy(sizePolicy);
        num4->setFont(font3);

        gridLayout->addWidget(num4, 5, 0, 1, 1);

        back = new QPushButton(gridLayoutWidget);
        back->setObjectName(QString::fromUtf8("back"));
        sizePolicy.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy);
        back->setFont(font3);

        gridLayout->addWidget(back, 0, 3, 1, 1);

        cle = new QPushButton(gridLayoutWidget);
        cle->setObjectName(QString::fromUtf8("cle"));
        sizePolicy.setHeightForWidth(cle->sizePolicy().hasHeightForWidth());
        cle->setSizePolicy(sizePolicy);
        cle->setFont(font3);

        gridLayout->addWidget(cle, 0, 2, 1, 1);

        em = new QPushButton(gridLayoutWidget);
        em->setObjectName(QString::fromUtf8("em"));
        sizePolicy.setHeightForWidth(em->sizePolicy().hasHeightForWidth());
        em->setSizePolicy(sizePolicy);

        gridLayout->addWidget(em, 8, 3, 1, 1);

        kaifang = new QPushButton(gridLayoutWidget);
        kaifang->setObjectName(QString::fromUtf8("kaifang"));
        sizePolicy.setHeightForWidth(kaifang->sizePolicy().hasHeightForWidth());
        kaifang->setSizePolicy(sizePolicy);
        kaifang->setFont(font3);

        gridLayout->addWidget(kaifang, 2, 1, 1, 1);

        num2 = new QPushButton(gridLayoutWidget);
        num2->setObjectName(QString::fromUtf8("num2"));
        sizePolicy.setHeightForWidth(num2->sizePolicy().hasHeightForWidth());
        num2->setSizePolicy(sizePolicy);
        num2->setFont(font3);

        gridLayout->addWidget(num2, 7, 1, 1, 1);

        min = new QPushButton(gridLayoutWidget);
        min->setObjectName(QString::fromUtf8("min"));
        sizePolicy.setHeightForWidth(min->sizePolicy().hasHeightForWidth());
        min->setSizePolicy(sizePolicy);
        min->setFont(font2);

        gridLayout->addWidget(min, 5, 3, 1, 1);

        pinfang = new QPushButton(gridLayoutWidget);
        pinfang->setObjectName(QString::fromUtf8("pinfang"));
        sizePolicy.setHeightForWidth(pinfang->sizePolicy().hasHeightForWidth());
        pinfang->setSizePolicy(sizePolicy);
        pinfang->setFont(font3);

        gridLayout->addWidget(pinfang, 2, 2, 1, 1);

        num6 = new QPushButton(gridLayoutWidget);
        num6->setObjectName(QString::fromUtf8("num6"));
        sizePolicy.setHeightForWidth(num6->sizePolicy().hasHeightForWidth());
        num6->setSizePolicy(sizePolicy);
        num6->setFont(font3);

        gridLayout->addWidget(num6, 5, 2, 1, 1);

        div = new QPushButton(gridLayoutWidget);
        div->setObjectName(QString::fromUtf8("div"));
        sizePolicy.setHeightForWidth(div->sizePolicy().hasHeightForWidth());
        div->setSizePolicy(sizePolicy);
        div->setFont(font2);

        gridLayout->addWidget(div, 2, 3, 1, 1);

        num0 = new QPushButton(gridLayoutWidget);
        num0->setObjectName(QString::fromUtf8("num0"));
        sizePolicy.setHeightForWidth(num0->sizePolicy().hasHeightForWidth());
        num0->setSizePolicy(sizePolicy);
        num0->setFont(font3);

        gridLayout->addWidget(num0, 8, 1, 1, 1);

        mul = new QPushButton(gridLayoutWidget);
        mul->setObjectName(QString::fromUtf8("mul"));
        sizePolicy.setHeightForWidth(mul->sizePolicy().hasHeightForWidth());
        mul->setSizePolicy(sizePolicy);
        mul->setFont(font2);

        gridLayout->addWidget(mul, 4, 3, 1, 1);

        num1 = new QPushButton(gridLayoutWidget);
        num1->setObjectName(QString::fromUtf8("num1"));
        sizePolicy.setHeightForWidth(num1->sizePolicy().hasHeightForWidth());
        num1->setSizePolicy(sizePolicy);
        num1->setFont(font3);

        gridLayout->addWidget(num1, 7, 0, 1, 1);

        ce = new QPushButton(gridLayoutWidget);
        ce->setObjectName(QString::fromUtf8("ce"));
        sizePolicy.setHeightForWidth(ce->sizePolicy().hasHeightForWidth());
        ce->setSizePolicy(sizePolicy);
        ce->setFont(font3);

        gridLayout->addWidget(ce, 0, 1, 1, 1);

        equ = new QPushButton(tab);
        equ->setObjectName(QString::fromUtf8("equ"));
        equ->setGeometry(QRect(10, 360, 421, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(equ->sizePolicy().hasHeightForWidth());
        equ->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Bodoni MT")});
        font4.setPointSize(24);
        font4.setBold(false);
        equ->setFont(font4);
        equ->setStyleSheet(QString::fromUtf8("background-color: rgb(7, 156, 255);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget = new QWidget(tab_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 428, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qln = new QPushButton(verticalLayoutWidget);
        qln->setObjectName(QString::fromUtf8("qln"));
        sizePolicy.setHeightForWidth(qln->sizePolicy().hasHeightForWidth());
        qln->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Bodoni MT")});
        font5.setPointSize(18);
        font5.setBold(false);
        font5.setItalic(true);
        qln->setFont(font5);

        gridLayout_2->addWidget(qln, 1, 4, 1, 1);

        sin = new QPushButton(verticalLayoutWidget);
        sin->setObjectName(QString::fromUtf8("sin"));
        sizePolicy.setHeightForWidth(sin->sizePolicy().hasHeightForWidth());
        sin->setSizePolicy(sizePolicy);
        sin->setFont(font5);

        gridLayout_2->addWidget(sin, 3, 1, 1, 1);

        asin = new QPushButton(verticalLayoutWidget);
        asin->setObjectName(QString::fromUtf8("asin"));
        sizePolicy.setHeightForWidth(asin->sizePolicy().hasHeightForWidth());
        asin->setSizePolicy(sizePolicy);
        asin->setFont(font5);

        gridLayout_2->addWidget(asin, 4, 1, 1, 1);

        acos = new QPushButton(verticalLayoutWidget);
        acos->setObjectName(QString::fromUtf8("acos"));
        sizePolicy.setHeightForWidth(acos->sizePolicy().hasHeightForWidth());
        acos->setSizePolicy(sizePolicy);
        acos->setFont(font5);

        gridLayout_2->addWidget(acos, 4, 3, 1, 1);

        tan = new QPushButton(verticalLayoutWidget);
        tan->setObjectName(QString::fromUtf8("tan"));
        sizePolicy.setHeightForWidth(tan->sizePolicy().hasHeightForWidth());
        tan->setSizePolicy(sizePolicy);
        tan->setFont(font5);

        gridLayout_2->addWidget(tan, 3, 4, 1, 1);

        pi = new QPushButton(verticalLayoutWidget);
        pi->setObjectName(QString::fromUtf8("pi"));
        sizePolicy.setHeightForWidth(pi->sizePolicy().hasHeightForWidth());
        pi->setSizePolicy(sizePolicy);
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Bodoni MT")});
        font6.setPointSize(14);
        font6.setBold(false);
        font6.setItalic(true);
        pi->setFont(font6);
        pi->setStyleSheet(QString::fromUtf8("background-color: rgb(3, 200, 239);"));

        gridLayout_2->addWidget(pi, 1, 1, 1, 1);

        cos = new QPushButton(verticalLayoutWidget);
        cos->setObjectName(QString::fromUtf8("cos"));
        sizePolicy.setHeightForWidth(cos->sizePolicy().hasHeightForWidth());
        cos->setSizePolicy(sizePolicy);
        cos->setFont(font5);

        gridLayout_2->addWidget(cos, 3, 3, 1, 1);

        atan = new QPushButton(verticalLayoutWidget);
        atan->setObjectName(QString::fromUtf8("atan"));
        sizePolicy.setHeightForWidth(atan->sizePolicy().hasHeightForWidth());
        atan->setSizePolicy(sizePolicy);
        atan->setFont(font5);

        gridLayout_2->addWidget(atan, 4, 4, 1, 1);

        gantan = new QPushButton(verticalLayoutWidget);
        gantan->setObjectName(QString::fromUtf8("gantan"));
        sizePolicy.setHeightForWidth(gantan->sizePolicy().hasHeightForWidth());
        gantan->setSizePolicy(sizePolicy);
        gantan->setFont(font5);

        gridLayout_2->addWidget(gantan, 5, 3, 1, 1);

        rkuo = new QPushButton(verticalLayoutWidget);
        rkuo->setObjectName(QString::fromUtf8("rkuo"));
        sizePolicy.setHeightForWidth(rkuo->sizePolicy().hasHeightForWidth());
        rkuo->setSizePolicy(sizePolicy);
        rkuo->setFont(font5);

        gridLayout_2->addWidget(rkuo, 5, 4, 1, 1);

        lkuo = new QPushButton(verticalLayoutWidget);
        lkuo->setObjectName(QString::fromUtf8("lkuo"));
        sizePolicy.setHeightForWidth(lkuo->sizePolicy().hasHeightForWidth());
        lkuo->setSizePolicy(sizePolicy);
        lkuo->setFont(font5);

        gridLayout_2->addWidget(lkuo, 5, 1, 1, 1);

        qlog = new QPushButton(verticalLayoutWidget);
        qlog->setObjectName(QString::fromUtf8("qlog"));
        sizePolicy.setHeightForWidth(qlog->sizePolicy().hasHeightForWidth());
        qlog->setSizePolicy(sizePolicy);
        qlog->setSizeIncrement(QSize(5, 0));
        qlog->setFont(font5);
        qlog->setStyleSheet(QString::fromUtf8("alternate-background-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255, 255, 255, 255), stop:0.373979 rgba(255, 255, 255, 255), stop:0.373991 rgba(33, 30, 255, 255), stop:0.624018 rgba(33, 30, 255, 255), stop:0.624043 rgba(255, 0, 0, 255), stop:1 rgba(255, 0, 0, 255));"));

        gridLayout_2->addWidget(qlog, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        tabWidget->addTab(tab_2, QString());
        textBrowser = new QTextBrowser(Dialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 10, 441, 121));
        textBrowser->setStyleSheet(QString::fromUtf8(""));
        his_show = new QTextBrowser(Dialog);
        his_show->setObjectName(QString::fromUtf8("his_show"));
        his_show->setGeometry(QRect(470, 10, 261, 531));
        clc = new QPushButton(Dialog);
        clc->setObjectName(QString::fromUtf8("clc"));
        clc->setGeometry(QRect(560, 580, 80, 20));
        out = new QPushButton(Dialog);
        out->setObjectName(QString::fromUtf8("out"));
        out->setGeometry(QRect(650, 580, 80, 20));
        time = new QPushButton(Dialog);
        time->setObjectName(QString::fromUtf8("time"));
        time->setGeometry(QRect(470, 580, 80, 20));
        textabc = new QTextBrowser(Dialog);
        textabc->setObjectName(QString::fromUtf8("textabc"));
        textabc->setGeometry(QRect(200, 140, 261, 21));
        red = new QRadioButton(Dialog);
        red->setObjectName(QString::fromUtf8("red"));
        red->setGeometry(QRect(20, 140, 41, 18));
        blue = new QRadioButton(Dialog);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setGeometry(QRect(70, 140, 51, 18));
        black = new QRadioButton(Dialog);
        black->setObjectName(QString::fromUtf8("black"));
        black->setGeometry(QRect(130, 140, 61, 18));
        qe = new QPushButton(Dialog);
        qe->setObjectName(QString::fromUtf8("qe"));
        qe->setGeometry(QRect(470, 550, 80, 20));

        retranslateUi(Dialog);
        QObject::connect(out, &QPushButton::clicked, Dialog, qOverload<>(&QDialog::close));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        zhengfu->setText(QCoreApplication::translate("Dialog", "+/-", nullptr));
        num7->setText(QCoreApplication::translate("Dialog", "7", nullptr));
        daoshu->setText(QCoreApplication::translate("Dialog", "1/X", nullptr));
        num8->setText(QCoreApplication::translate("Dialog", "8", nullptr));
        plus->setText(QCoreApplication::translate("Dialog", "+", nullptr));
        num3->setText(QCoreApplication::translate("Dialog", "3", nullptr));
        num9->setText(QCoreApplication::translate("Dialog", "9", nullptr));
        num5->setText(QCoreApplication::translate("Dialog", "5", nullptr));
        qiuyu->setText(QCoreApplication::translate("Dialog", "%", nullptr));
        point->setText(QCoreApplication::translate("Dialog", ".", nullptr));
        num4->setText(QCoreApplication::translate("Dialog", "4", nullptr));
        back->setText(QCoreApplication::translate("Dialog", "\342\227\200\342\227\200\342\227\200", nullptr));
        cle->setText(QCoreApplication::translate("Dialog", "C", nullptr));
        em->setText(QCoreApplication::translate("Dialog", "e^", nullptr));
        kaifang->setText(QCoreApplication::translate("Dialog", "\342\210\232X", nullptr));
        num2->setText(QCoreApplication::translate("Dialog", "2", nullptr));
        min->setText(QCoreApplication::translate("Dialog", "-", nullptr));
        pinfang->setText(QCoreApplication::translate("Dialog", "^", nullptr));
        num6->setText(QCoreApplication::translate("Dialog", "6", nullptr));
        div->setText(QCoreApplication::translate("Dialog", "\303\267", nullptr));
        num0->setText(QCoreApplication::translate("Dialog", "0", nullptr));
        mul->setText(QCoreApplication::translate("Dialog", "\303\227", nullptr));
        num1->setText(QCoreApplication::translate("Dialog", "1", nullptr));
        ce->setText(QCoreApplication::translate("Dialog", "CE", nullptr));
        equ->setText(QCoreApplication::translate("Dialog", "=", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Dialog", "\346\240\207\345\207\206", nullptr));
        qln->setText(QCoreApplication::translate("Dialog", "ln", nullptr));
        sin->setText(QCoreApplication::translate("Dialog", "sin", nullptr));
        asin->setText(QCoreApplication::translate("Dialog", "asin", nullptr));
        acos->setText(QCoreApplication::translate("Dialog", "acos", nullptr));
        tan->setText(QCoreApplication::translate("Dialog", "tan", nullptr));
        pi->setText(QCoreApplication::translate("Dialog", "\317\200", nullptr));
        cos->setText(QCoreApplication::translate("Dialog", "cos", nullptr));
        atan->setText(QCoreApplication::translate("Dialog", "atan", nullptr));
        gantan->setText(QCoreApplication::translate("Dialog", "!", nullptr));
        rkuo->setText(QCoreApplication::translate("Dialog", ")", nullptr));
        lkuo->setText(QCoreApplication::translate("Dialog", "(", nullptr));
        qlog->setText(QCoreApplication::translate("Dialog", "log", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Dialog", "\347\247\221\345\255\246", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt; font-weight:600; vertical-align:sub;\">\347\214\252\347\214\252\345\260\217\350\202\245\347\232\204\350\256\241\347\256\227\345\231\250</span></p></body></html>", nullptr));
        his_show->setHtml(QCoreApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">\345\216\206\345\217\262\350\256\260\345\275\225</span></p></body></html>", nullptr));
        clc->setText(QCoreApplication::translate("Dialog", "\346\270\205\347\251\272\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        out->setText(QCoreApplication::translate("Dialog", "\351\200\200\345\207\272", nullptr));
        time->setText(QCoreApplication::translate("Dialog", "\345\275\223\345\211\215\346\227\266\351\227\264", nullptr));
        red->setText(QCoreApplication::translate("Dialog", "red", nullptr));
        blue->setText(QCoreApplication::translate("Dialog", "blue", nullptr));
        black->setText(QCoreApplication::translate("Dialog", "black", nullptr));
        qe->setText(QCoreApplication::translate("Dialog", " e", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
