TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tiffimage.cpp \
    image.cpp

QMAKE_CXXFLAGS += -std=c++11 #for GCC >= 4.7

exists(/opt/local/lib) {
    LIBS += -L/opt/local/lib
}

unix|win32: LIBS += -ltiff

HEADERS += \
    tiffimage.h \
    image.h
