/********************************************************************************
** Form generated from reading UI file 'find_sc.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_SC_H
#define UI_FIND_SC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Find_sc
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *input_sno_1;
    QLineEdit *input_sname_1;
    QPushButton *find_sure_3;
    QLabel *label_2;
    QPushButton *find_sure_4;
    QLabel *label_3;
    QLabel *label;

    void setupUi(QWidget *Find_sc)
    {
        if (Find_sc->objectName().isEmpty())
            Find_sc->setObjectName(QString::fromUtf8("Find_sc"));
        Find_sc->resize(400, 300);
        verticalLayoutWidget = new QWidget(Find_sc);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(170, 110, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        input_sno_1 = new QLineEdit(verticalLayoutWidget);
        input_sno_1->setObjectName(QString::fromUtf8("input_sno_1"));

        verticalLayout->addWidget(input_sno_1);

        input_sname_1 = new QLineEdit(verticalLayoutWidget);
        input_sname_1->setObjectName(QString::fromUtf8("input_sname_1"));

        verticalLayout->addWidget(input_sname_1);

        find_sure_3 = new QPushButton(Find_sc);
        find_sure_3->setObjectName(QString::fromUtf8("find_sure_3"));
        find_sure_3->setGeometry(QRect(50, 240, 151, 31));
        label_2 = new QLabel(Find_sc);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 160, 108, 24));
        find_sure_4 = new QPushButton(Find_sc);
        find_sure_4->setObjectName(QString::fromUtf8("find_sure_4"));
        find_sure_4->setGeometry(QRect(237, 241, 151, 31));
        label_3 = new QLabel(Find_sc);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 40, 201, 31));
        label = new QLabel(Find_sc);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 120, 108, 24));

        retranslateUi(Find_sc);

        QMetaObject::connectSlotsByName(Find_sc);
    } // setupUi

    void retranslateUi(QWidget *Find_sc)
    {
        Find_sc->setWindowTitle(QCoreApplication::translate("Find_sc", "Form", nullptr));
        find_sure_3->setText(QCoreApplication::translate("Find_sc", "\351\200\232\350\277\207\345\255\246\345\217\267\346\237\245\350\257\242", nullptr));
        label_2->setText(QCoreApplication::translate("Find_sc", "\345\247\223\345\220\215\357\274\232", nullptr));
        find_sure_4->setText(QCoreApplication::translate("Find_sc", "\351\200\232\350\277\207\345\247\223\345\220\215\346\237\245\350\257\242", nullptr));
        label_3->setText(QCoreApplication::translate("Find_sc", "\350\257\267\350\276\223\345\205\245\345\255\246\345\217\267\346\210\226\345\247\223\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("Find_sc", "\345\255\246\345\217\267\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Find_sc: public Ui_Find_sc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_SC_H
