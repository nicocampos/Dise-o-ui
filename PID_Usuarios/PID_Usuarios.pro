QT       += core gui xml
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    camera.cpp \
    check_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mylineedit.cpp \
    photoedit.cpp \
    usercard.cpp \
    userwindow.cpp \
    usuarioconfig.cpp \
    usuarios.cpp \
    xmlhandler.cpp

HEADERS += \
    adminwindow.h \
    camera.h \
    check_dialog.h \
    mainwindow.h \
    mylineedit.h \
    photoedit.h \
    usercard.h \
    userwindow.h \
    usuarioconfig.h \
    usuarios.h \
    xmlhandler.h

FORMS += \
    adminwindow.ui \
    camera.ui \
    check_dialog.ui \
    mainwindow.ui \
    photoedit.ui \
    usercard.ui \
    userwindow.ui \
    usuarioconfig.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
