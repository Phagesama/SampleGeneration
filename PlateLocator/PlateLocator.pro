#-------------------------------------------------
#
# Project created by QtCreator 2019-06-24T10:05:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlateLocator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        charsegment_v3.cpp \
        main.cpp \
        matswitch.cpp \
        platecategory_svm.cpp \
        platechar_svm.cpp \
        platelocator.cpp \
        platelocator_v3.cpp \
        savechar.cpp \
        savecharthread.cpp \
        saveimgthread.cpp \
        saveimgwidget.cpp \
        showcharthread.cpp \
        showplatethread.cpp

HEADERS += \
        charsegment_v3.h \
        matswitch.h \
        platecategory.h \
        platecategory_svm.h \
        platechar_svm.h \
        platelocator.h \
        platelocator_v3.h \
        savechar.h \
        savecharthread.h \
        saveimgthread.h \
        saveimgwidget.h \
        showcharthread.h \
        showplatethread.h

FORMS += \
        platelocator.ui \
        savechar.ui \
        saveimgwidget.ui

INCLUDEPATH += E:\Software\OpenCv\opencv\build\include

LIBS += -LE:\Software\OpenCv\opencv\build\x64\vc15\lib\
        -lopencv_world410d \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
