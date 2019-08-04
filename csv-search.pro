TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cmdparams.cpp \
        main.cpp \
        parser.cpp

HEADERS += \
    cmdparams.h \
    constants.h \
    parser.h
