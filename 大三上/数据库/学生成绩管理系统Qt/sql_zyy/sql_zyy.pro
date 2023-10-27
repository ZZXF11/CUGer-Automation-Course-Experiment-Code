QT       += core gui
QT +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    course_set.cpp \
    find.cpp \
    find_sc.cpp \
    grade_sel.cpp \
    load.cpp \
    logindlg.cpp \
    main.cpp \
    mainwindow.cpp \
    sc_set.cpp \
    stu_set.cpp

HEADERS += \
    course_set.h \
    find.h \
    find_sc.h \
    grade_sel.h \
    load.h \
    logindlg.h \
    mainwindow.h \
    sc_set.h \
    stu_set.h

FORMS += \
    course_set.ui \
    find.ui \
    find_sc.ui \
    grade_sel.ui \
    load.ui \
    logindlg.ui \
    mainwindow.ui \
    sc_set.ui \
    stu_set.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
