/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *find_stu_all;
    QPushButton *find_stu;
    QPushButton *find_stu_all_2;
    QPushButton *find_sc;
    QPushButton *find_sc_2;
    QPushButton *find_sc_3;
    QPushButton *find_sc_4;
    QPushButton *grade_sel;
    QSpacerItem *verticalSpacer_2;
    QTableView *tableView_manage;
    QWidget *page_2;
    QRadioButton *radioButton;
    QWidget *page_3;
    QToolButton *toolButton;
    QLabel *label;
    QPushButton *loadsys;
    QPushButton *ex;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 50, 751, 491));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayoutWidget_2 = new QWidget(page);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(610, 30, 131, 431));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        find_stu_all = new QPushButton(verticalLayoutWidget_2);
        find_stu_all->setObjectName(QString::fromUtf8("find_stu_all"));
        QFont font;
        font.setPointSize(11);
        find_stu_all->setFont(font);

        verticalLayout_2->addWidget(find_stu_all);

        find_stu = new QPushButton(verticalLayoutWidget_2);
        find_stu->setObjectName(QString::fromUtf8("find_stu"));
        QFont font1;
        font1.setPointSize(12);
        find_stu->setFont(font1);

        verticalLayout_2->addWidget(find_stu);

        find_stu_all_2 = new QPushButton(verticalLayoutWidget_2);
        find_stu_all_2->setObjectName(QString::fromUtf8("find_stu_all_2"));
        find_stu_all_2->setFont(font);

        verticalLayout_2->addWidget(find_stu_all_2);

        find_sc = new QPushButton(verticalLayoutWidget_2);
        find_sc->setObjectName(QString::fromUtf8("find_sc"));
        find_sc->setFont(font1);

        verticalLayout_2->addWidget(find_sc);

        find_sc_2 = new QPushButton(verticalLayoutWidget_2);
        find_sc_2->setObjectName(QString::fromUtf8("find_sc_2"));
        find_sc_2->setFont(font1);

        verticalLayout_2->addWidget(find_sc_2);

        find_sc_3 = new QPushButton(verticalLayoutWidget_2);
        find_sc_3->setObjectName(QString::fromUtf8("find_sc_3"));
        find_sc_3->setFont(font1);

        verticalLayout_2->addWidget(find_sc_3);

        find_sc_4 = new QPushButton(verticalLayoutWidget_2);
        find_sc_4->setObjectName(QString::fromUtf8("find_sc_4"));
        find_sc_4->setFont(font1);

        verticalLayout_2->addWidget(find_sc_4);

        grade_sel = new QPushButton(verticalLayoutWidget_2);
        grade_sel->setObjectName(QString::fromUtf8("grade_sel"));
        grade_sel->setFont(font1);

        verticalLayout_2->addWidget(grade_sel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tableView_manage = new QTableView(page);
        tableView_manage->setObjectName(QString::fromUtf8("tableView_manage"));
        tableView_manage->setGeometry(QRect(20, 30, 581, 451));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        radioButton = new QRadioButton(page_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(150, 120, 157, 30));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        toolButton = new QToolButton(page_3);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(190, 170, 68, 31));
        stackedWidget->addWidget(page_3);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 10, 191, 31));
        loadsys = new QPushButton(centralwidget);
        loadsys->setObjectName(QString::fromUtf8("loadsys"));
        loadsys->setGeometry(QRect(30, 10, 128, 32));
        ex = new QPushButton(centralwidget);
        ex->setObjectName(QString::fromUtf8("ex"));
        ex->setGeometry(QRect(500, 10, 128, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        find_stu_all->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\211\200\346\234\211\345\255\246\347\224\237\344\277\241\346\201\257", nullptr));
        find_stu->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\345\255\246\347\224\237\344\277\241\346\201\257", nullptr));
        find_stu_all_2->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\211\200\346\234\211\351\200\211\350\257\276\344\277\241\346\201\257", nullptr));
        find_sc->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\351\200\211\350\257\276\344\277\241\346\201\257", nullptr));
        find_sc_2->setText(QCoreApplication::translate("MainWindow", "\345\255\246\347\224\237\346\223\215\344\275\234", nullptr));
        find_sc_3->setText(QCoreApplication::translate("MainWindow", "\350\257\276\347\250\213\346\223\215\344\275\234", nullptr));
        find_sc_4->setText(QCoreApplication::translate("MainWindow", "\351\200\211\350\257\276\346\223\215\344\275\234", nullptr));
        grade_sel->setText(QCoreApplication::translate("MainWindow", "\346\210\220\347\273\251\347\273\237\350\256\241", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "RadioButton", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\255\246\347\224\237\344\277\241\346\201\257\346\237\245\350\257\242\347\263\273\347\273\237", nullptr));
        loadsys->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        ex->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
