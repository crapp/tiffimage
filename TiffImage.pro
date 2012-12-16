TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tiffimage.cpp \
    image.cpp

QMAKE_CXXFLAGS += -std=c++11 #for GCC >= 4.7

unix|win32: LIBS += -ltiff

HEADERS += \
    tiffimage.h \
    image.h
