#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T10:21:01
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrajectoryBuilder
TEMPLATE = app


SOURCES += main.cpp\
        guimanager.cpp \
    task.cpp \
    messenger.cpp \
    physics.cpp

HEADERS  += guimanager.h \
    task.h \
    messenger.h \
    userheaders.h \
    physics.h

FORMS    += guimanager.ui

INCLUDEPATH += /home/songyan/xenomai/xenomai-2.6.5/include

INCLUDEPATH += /home/songyan/xenomai/xenomai-2.6.5/src/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lanalogy

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lnative

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lpsos

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lpthread_rt

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lrtdm

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lrtdm

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -luitron

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include


unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lvrtx

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lvxworks

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include

unix:!macx: LIBS += -L$$PWD/../../../usr/xenomai/lib/ -lxenomai

INCLUDEPATH += $$PWD/../../../usr/xenomai/include
DEPENDPATH += $$PWD/../../../usr/xenomai/include
