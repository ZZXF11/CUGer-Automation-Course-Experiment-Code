QT       += core gui
QT +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    dialog1.cpp \
    dialog2.cpp \
    dialog_pwf.cpp \
    main.cpp \
    mainwindow.cpp \
    startmainwindow.cpp \
    stumainwindow.cpp

HEADERS += \
    dialog.h \
    dialog1.h \
    dialog2.h \
    dialog_pwf.h \
    mainwindow.h \
    startmainwindow.h \
    stumainwindow.h

FORMS += \
    dialog.ui \
    dialog1.ui \
    dialog2.ui \
    dialog_pwf.ui \
    mainwindow.ui \
    startmainwindow.ui \
    stumainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
