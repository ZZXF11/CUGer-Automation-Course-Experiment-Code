/********************************************************************************
** Form generated from reading UI file 'logindlg.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDLG_H
#define UI_LOGINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logindlg
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *Logindlg)
    {
        if (Logindlg->objectName().isEmpty())
            Logindlg->setObjectName(QString::fromUtf8("Logindlg"));
        Logindlg->resize(349, 223);
        verticalLayoutWidget = new QWidget(Logindlg);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 80, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(Logindlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 158, 36));

        retranslateUi(Logindlg);

        QMetaObject::connectSlotsByName(Logindlg);
    } // setupUi

    void retranslateUi(QDialog *Logindlg)
    {
        Logindlg->setWindowTitle(QCoreApplication::translate("Logindlg", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Logindlg", "\345\257\206\347\240\201\351\224\231\350\257\257", nullptr));
        label_2->setText(QCoreApplication::translate("Logindlg", "\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245", nullptr));
        label_3->setText(QCoreApplication::translate("Logindlg", "\346\217\220\347\244\272\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Logindlg: public Ui_Logindlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDLG_H
