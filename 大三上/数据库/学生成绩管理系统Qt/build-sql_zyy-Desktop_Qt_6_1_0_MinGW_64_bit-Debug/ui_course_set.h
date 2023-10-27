/********************************************************************************
** Form generated from reading UI file 'course_set.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSE_SET_H
#define UI_COURSE_SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_course_set
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
    QLineEdit *lineEdit_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *newsc;
    QWidget *tab_2;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QPushButton *delsc;
    QWidget *tab_3;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *recname;
    QPushButton *recpno;
    QPushButton *recredit;

    void setupUi(QWidget *course_set)
    {
        if (course_set->objectName().isEmpty())
            course_set->setObjectName(QString::fromUtf8("course_set"));
        course_set->resize(541, 398);
        label = new QLabel(course_set);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 10, 108, 24));
        tabWidget = new QTabWidget(course_set);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 491, 321));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(230, 50, 160, 152));
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

        lineEdit_4 = new QLineEdit(verticalLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout->addWidget(lineEdit_4);

        verticalLayoutWidget_2 = new QWidget(tab);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(50, 50, 161, 151));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        newsc = new QPushButton(tab);
        newsc->setObjectName(QString::fromUtf8("newsc"));
        newsc->setGeometry(QRect(330, 230, 128, 32));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        lineEdit_5 = new QLineEdit(tab_2);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(220, 70, 158, 33));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 70, 159, 33));
        delsc = new QPushButton(tab_2);
        delsc->setObjectName(QString::fromUtf8("delsc"));
        delsc->setGeometry(QRect(330, 210, 128, 32));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 50, 159, 33));
        lineEdit_6 = new QLineEdit(tab_3);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(190, 50, 158, 33));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(60, 100, 181, 31));
        lineEdit_7 = new QLineEdit(tab_3);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(190, 150, 158, 33));
        horizontalLayoutWidget = new QWidget(tab_3);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 210, 481, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        recname = new QPushButton(horizontalLayoutWidget);
        recname->setObjectName(QString::fromUtf8("recname"));

        horizontalLayout->addWidget(recname);

        recpno = new QPushButton(horizontalLayoutWidget);
        recpno->setObjectName(QString::fromUtf8("recpno"));

        horizontalLayout->addWidget(recpno);

        recredit = new QPushButton(horizontalLayoutWidget);
        recredit->setObjectName(QString::fromUtf8("recredit"));

        horizontalLayout->addWidget(recredit);

        tabWidget->addTab(tab_3, QString());

        retranslateUi(course_set);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(course_set);
    } // setupUi

    void retranslateUi(QWidget *course_set)
    {
        course_set->setWindowTitle(QCoreApplication::translate("course_set", "Form", nullptr));
        label->setText(QCoreApplication::translate("course_set", "\350\257\276\347\250\213\346\223\215\344\275\234", nullptr));
        label_2->setText(QCoreApplication::translate("course_set", "\350\257\276\347\250\213\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("course_set", "\350\257\276\347\250\213\345\220\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("course_set", "\345\205\210\350\241\214\350\257\276\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("course_set", "\345\255\246\345\210\206\357\274\232", nullptr));
        newsc->setText(QCoreApplication::translate("course_set", "\346\226\260\345\242\236", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("course_set", "\345\242\236\345\212\240", nullptr));
        label_6->setText(QCoreApplication::translate("course_set", "\350\257\276\347\250\213\345\217\267\357\274\232", nullptr));
        delsc->setText(QCoreApplication::translate("course_set", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("course_set", "\345\210\240\351\231\244", nullptr));
        label_7->setText(QCoreApplication::translate("course_set", "\350\257\276\347\250\213\345\217\267\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("course_set", "\351\234\200\350\246\201\344\277\256\346\224\271\347\232\204\345\206\205\345\256\271", nullptr));
        recname->setText(QCoreApplication::translate("course_set", "\344\277\256\346\224\271\350\257\276\347\250\213\345\220\215", nullptr));
        recpno->setText(QCoreApplication::translate("course_set", "\344\277\256\346\224\271\345\205\210\350\241\214\350\257\276", nullptr));
        recredit->setText(QCoreApplication::translate("course_set", "\344\277\256\346\224\271\345\255\246\345\210\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("course_set", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class course_set: public Ui_course_set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSE_SET_H
