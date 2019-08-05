include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../../cmdparams.h \
        ../../constants.h \
        ../../parser.h \
        tst_testdate.h

SOURCES += \
        ../../cmdparams.cpp \
        ../../parser.cpp \
        main.cpp

DISTFILES +=
