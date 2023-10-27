/********************************************************************************
** Form generated from reading UI file 'find.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_H
#define UI_FIND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Find
{
public:
    QPushButton *find_sure;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *input_sno;
    QLineEdit *input_sname;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *find_sure_2;

    void setupUi(QWidget *Find)
    {
        if (Find->objectName().isEmpty())
            Find->setObjectName(QString::fromUtf8("Find"));
        Find->resize(460, 343);
        find_sure = new QPushButton(Find);
        find_sure->setObjectName(QString::fromUtf8("find_sure"));
        find_sure->setGeometry(QRect(60, 240, 151, 31));
        verticalLayoutWidget = new QWidget(Find);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(180, 110, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        input_sno = new QLineEdit(verticalLayoutWidget);
        input_sno->setObjectName(QString::fromUtf8("input_sno"));

        verticalLayout->addWidget(input_sno);

        input_sname = new QLineEdit(verticalLayoutWidget);
        input_sname->setObjectName(QString::fromUtf8("input_sname"));

        verticalLayout->addWidget(input_sname);

        label = new QLabel(Find);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 120, 108, 24));
        label_2 = new QLabel(Find);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 160, 108, 24));
        label_3 = new QLabel(Find);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 40, 201, 31));
        find_sure_2 = new QPushButton(Find);
        find_sure_2->setObjectName(QString::fromUtf8("find_sure_2"));
        find_sure_2->setGeometry(QRect(247, 241, 151, 31));

        retranslateUi(Find);

        QMetaObject::connectSlotsByName(Find);
    } // setupUi

    void retranslateUi(QWidget *Find)
    {
        Find->setWindowTitle(QCoreApplication::translate("Find", "Form", nullptr));
        find_sure->setText(QCoreApplication::translate("Find", "\351\200\232\350\277\207\345\255\246\345\217\267\346\237\245\350\257\242", nullptr));
        label->setText(QCoreApplication::translate("Find", "\345\255\246\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Find", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Find", "\350\257\267\350\276\223\345\205\245\345\255\246\345\217\267\346\210\226\345\247\223\345\220\215", nullptr));
        find_sure_2->setText(QCoreApplication::translate("Find", "\351\200\232\350\277\207\345\247\223\345\220\215\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Find: public Ui_Find {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_H
