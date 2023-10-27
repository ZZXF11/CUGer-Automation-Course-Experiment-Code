/********************************************************************************
** Form generated from reading UI file 'sc_set.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SC_SET_H
#define UI_SC_SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sc_set
{
public:
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QPushButton *new_sc;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *del_sc;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *cha_sc;

    void setupUi(QWidget *sc_set)
    {
        if (sc_set->objectName().isEmpty())
            sc_set->setObjectName(QString::fromUtf8("sc_set"));
        sc_set->resize(502, 377);
        label = new QLabel(sc_set);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 30, 108, 24));
        tabWidget = new QTabWidget(sc_set);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 70, 461, 291));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(250, 50, 160, 113));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        verticalLayoutWidget_2 = new QWidget(tab);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(29, 49, 181, 111));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        new_sc = new QPushButton(tab);
        new_sc->setObjectName(QString::fromUtf8("new_sc"));
        new_sc->setGeometry(QRect(290, 190, 128, 32));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget_3 = new QWidget(tab_2);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(250, 50, 160, 113));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineEdit_4 = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout_3->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(verticalLayoutWidget_3);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        verticalLayout_3->addWidget(lineEdit_5);

        verticalLayoutWidget_4 = new QWidget(tab_2);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(50, 50, 181, 111));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        label_6 = new QLabel(verticalLayoutWidget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_4->addWidget(label_6);

        del_sc = new QPushButton(tab_2);
        del_sc->setObjectName(QString::fromUtf8("del_sc"));
        del_sc->setGeometry(QRect(280, 200, 128, 32));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayoutWidget_5 = new QWidget(tab_3);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(240, 40, 160, 113));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        lineEdit_6 = new QLineEdit(verticalLayoutWidget_5);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        verticalLayout_5->addWidget(lineEdit_6);

        lineEdit_7 = new QLineEdit(verticalLayoutWidget_5);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        verticalLayout_5->addWidget(lineEdit_7);

        lineEdit_8 = new QLineEdit(verticalLayoutWidget_5);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        verticalLayout_5->addWidget(lineEdit_8);

        verticalLayoutWidget_6 = new QWidget(tab_3);
        verticalLayoutWidget_6->setObjectName(QString::fromUtf8("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(40, 40, 181, 111));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(verticalLayoutWidget_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_6->addWidget(label_7);

        label_8 = new QLabel(verticalLayoutWidget_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_6->addWidget(label_8);

        label_9 = new QLabel(verticalLayoutWidget_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_6->addWidget(label_9);

        cha_sc = new QPushButton(tab_3);
        cha_sc->setObjectName(QString::fromUtf8("cha_sc"));
        cha_sc->setGeometry(QRect(290, 190, 128, 32));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(sc_set);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(sc_set);
    } // setupUi

    void retranslateUi(QWidget *sc_set)
    {
        sc_set->setWindowTitle(QCoreApplication::translate("sc_set", "Form", nullptr));
        label->setText(QCoreApplication::translate("sc_set", "\351\200\211\350\257\276\346\223\215\344\275\234", nullptr));
        label_3->setText(QCoreApplication::translate("sc_set", "\345\255\246\345\217\267\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("sc_set", "\350\257\276\347\250\213\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("sc_set", "\346\210\220\347\273\251\357\274\232", nullptr));
        new_sc->setText(QCoreApplication::translate("sc_set", "\346\226\260\345\242\236", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("sc_set", "\346\226\260\345\242\236", nullptr));
        label_5->setText(QCoreApplication::translate("sc_set", "\345\255\246\345\217\267\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("sc_set", "\350\257\276\347\250\213\345\217\267\357\274\232", nullptr));
        del_sc->setText(QCoreApplication::translate("sc_set", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("sc_set", "\345\210\240\351\231\244", nullptr));
        label_7->setText(QCoreApplication::translate("sc_set", "\345\255\246\345\217\267\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("sc_set", "\350\257\276\347\250\213\345\217\267\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("sc_set", "\346\210\220\347\273\251\357\274\232", nullptr));
        cha_sc->setText(QCoreApplication::translate("sc_set", "\344\277\256\346\224\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("sc_set", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sc_set: public Ui_sc_set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SC_SET_H
