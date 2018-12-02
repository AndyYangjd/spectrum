TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

OBJECTS_DIR += ../temp
DESTDIR +=../bin

TARGET = spec
SOURCES += main.cpp \
    spec.cpp

INCLUDEPATH +=\
    /usr/src/linux-headers-4.4.0-21/include/linux\
    /usr/local/include/opencv\
    /usr/local/include/opencv2

HEADERS += \
    spec.h\
    dcache.h

LIBS += \
-L/usr/local/lib\
    -lopencv_core\
    -lopencv_highgui\
    -lopencv_imgcodecs\
    -lopencv_imgproc\
    -lopencv_video\
    -lopencv_videoio\
    -lopencv_videostab
