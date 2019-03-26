#-------------------------------------------------
#
# Project created by QtCreator 2019-03-24T12:52:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv_qt_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    CalculationThread.cpp \
    DataManager.cpp \
    algorithms/featureDetectorBase.cpp \
    algorithms/FeatureDetectorSIFT.cpp \
    parameterset_widget.cpp \
    parameter_set.cpp

HEADERS  += mainwindow.h \
    utils.h \
    CalculationThread.h \
    DataManager.h \
    algorithms/featureDetectorBase.h \
    algorithms/FeatureDetectorSIFT.h \
    parameterset_widget.h \
    parameter_set.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$(OPENCV_DIR)\include

LIBS += -L$$(OPENCV_DIR)\x64\vc15\lib \
         -lopencv_world410d \
         -lopencv_world410
