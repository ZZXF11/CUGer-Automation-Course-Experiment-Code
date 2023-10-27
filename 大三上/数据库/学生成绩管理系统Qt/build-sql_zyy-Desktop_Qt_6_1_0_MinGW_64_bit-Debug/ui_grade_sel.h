/********************************************************************************
** Form generated from reading UI file 'grade_sel.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADE_SEL_H
#define UI_GRADE_SEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_grade_sel
{
public:
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *stu_sel;
    QWidget *tab_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QPushButton *coure_sel;

    void setupUi(QWidget *grade_sel)
    {
        if (grade_sel->objectName().isEmpty())
            grade_sel->setObjectName(QString::fromUtf8("grade_sel"));
        grade_sel->resize(563, 395);
        label = new QLabel(grade_sel);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 10, 108, 24));
        tabWidget = new QTabWidget(grade_sel);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 521, 331));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(17, 63, 171, 31));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 60, 161, 31));
        stu_sel = new QPushButton(tab);
        stu_sel->setObjectName(QString::fromUtf8("stu_sel"));
        stu_sel->setGeometry(QRect(320, 210, 128, 32));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        lineEdit_2 = new QLineEdit(tab_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(270, 80, 161, 31));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 80, 171, 31));
        coure_sel = new QPushButton(tab_2);
        coure_sel->setObjectName(QString::fromUtf8("coure_sel"));
        coure_sel->setGeometry(QRect(330, 230, 128, 32));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(grade_sel);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(grade_sel);
    } // setupUi

    void retranslateUi(QWidget *grade_sel)
    {
        grade_sel->setWindowTitle(QCoreApplication::translate("grade_sel", "Form", nullptr));
        label->setText(QCoreApplication::translate("grade_sel", "\346\210\220\347\273\251\347\273\237\350\256\241", nullptr));
        label_2->setText(QCoreApplication::translate("grade_sel", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\345\255\246\345\217\267", nullptr));
        stu_sel->setText(QCoreApplication::translate("grade_sel", "\347\273\237\350\256\241", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("grade_sel", "\345\255\246\347\224\237\344\270\252\344\272\272\346\210\220\347\273\251\347\273\237\350\256\241", nullptr));
        label_3->setText(QCoreApplication::translate("grade_sel", "\350\257\267\350\276\223\345\205\245\350\257\276\347\250\213\345\217\267", nullptr));
        coure_sel->setText(QCoreApplication::translate("grade_sel", "\347\273\237\350\256\241", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("grade_sel", "\350\257\276\347\250\213\346\210\220\347\273\251\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class grade_sel: public Ui_grade_sel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADE_SEL_H
