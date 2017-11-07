#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T23:03:12
#
#-------------------------------------------------

QT       -= gui

TARGET = space-tracker-lib
TEMPLATE = lib
CONFIG += staticlib c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += spacetrackerlib.cpp \
    controllers/orbit/orbitcontroller.cpp \
    controllers/mathsgp4.cpp

HEADERS += spacetrackerlib.h \
    controllers/orbit/orbitcontroller.h \
    controllers/mathsgp4.h \
    information.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/libsgp4/release/ -llibsgp4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/libsgp4/debug/ -llibsgp4
else:unix: LIBS += -L$$OUT_PWD/../lib/libsgp4/ -llibsgp4

INCLUDEPATH += $$PWD/../lib/libsgp4
DEPENDPATH += $$PWD/../lib/libsgp4

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libsgp4/release/liblibsgp4.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libsgp4/debug/liblibsgp4.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libsgp4/release/libsgp4.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libsgp4/debug/libsgp4.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libsgp4/liblibsgp4.a
