QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datawindow.cpp \
    details.cpp \
    main.cpp \
    mainwindow.cpp \
    pininputdialog.cpp

HEADERS += \
    datawindow.h \
    details.h \
    mainwindow.h \
    pininputdialog.h

FORMS += \
    datawindow.ui \
    details.ui \
    mainwindow.ui \
    pininputdialog.ui


LIBS += -L/opt/homebrew/lib -lssl -lcrypto
INCLUDEPATH += /Users/ampidexter/openssl/openssl-3.3.0-alpha1/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
