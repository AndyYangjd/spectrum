TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR += ../temp
DESTDIR +=../bin

TARGET = spectrum
SOURCES += main.cpp \
    spec.cpp

INCLUDEPATH +=\
    /usr/local/include/opencv\
    /usr/local/include/opencv2

HEADERS += \
    spec.h\

LIBS += \
-L/usr/local/lib\
    -lopencv_core\
    -lopencv_highgui\
    -lopencv_imgcodecs\
    -lopencv_imgproc\

DISTFILES += \
    readme.txt
