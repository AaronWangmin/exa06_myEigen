#-------------------------------------------------
#
# Project created by QtCreator 2017-06-20T13:18:50
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = exa06_myEigen
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    adjustparameter.cpp \
    weightobservation.cpp \
    coefficientb.cpp \
    gpshead.cpp \
    ephemerisgps.cpp \
    broadcast.cpp \
    positionsat.cpp

HEADERS += \
    adjustparameter.h \
    weightobservation.h \
    coefficientb.h \
    gpshead.h \
    ephemerisgps.h \
    broadcast.h \
    positionsat.h
