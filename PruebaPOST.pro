######################################################################
# Automatically generated by qmake (3.0) mi�r. abr. 8 23:39:45 2015
######################################################################

TEMPLATE = app
TARGET = PruebaPOST
INCLUDEPATH += . src/gui src/base src/core
QT += widgets network
CONFIG += debug_and_release

# Input
HEADERS += src/base/config.hh \
           src/core/control.hh \
           src/core/json.hh \
           src/gui/mainarea.hh \
           src/gui/mainwindow.hh
SOURCES += src/main.cc \
           src/base/config.cc \
           src/core/control.cc \
           src/core/json.cc \
           src/gui/mainarea.cc \
           src/gui/mainwindow.cc
