TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    team.cpp \
    tag.cpp \
    player.cpp \
    output.cpp \
    match.cpp \
    dsstring.cpp \
    tests.cpp

HEADERS += \
    team.h \
    tag.h \
    player.h \
    output.h \
    match.h \
    dsstring.h \
    Vector.h \
    catch.hpp
