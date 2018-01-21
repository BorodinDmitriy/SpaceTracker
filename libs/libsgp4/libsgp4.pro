QT       -= gui

TARGET = libsgp4
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += CoordGeodetic.cpp      \
    	   CoordTopocentric.cpp   \
    	   DateTime.cpp           \
    	   DecayedException.cpp   \
    	   Eci.cpp                \
    	   Globals.cpp            \
    	   Observer.cpp           \
    	   OrbitalElements.cpp    \
    	   SGP4.cpp               \
    	   SatelliteException.cpp \
    	   SolarPosition.cpp      \
    	   TimeSpan.cpp           \
    	   Tle.cpp                \
    	   TleException.cpp       \
    	   Util.cpp               \
    	   Vector.cpp       

HEADERS += CoordGeodetic.h      \
    	   CoordTopocentric.h   \
    	   DateTime.h           \
    	   DecayedException.h   \
    	   Eci.h                \
           Globals.h            \
    	   Observer.h           \
    	   OrbitalElements.h    \
    	   SGP4.h               \
    	   SatelliteException.h \
    	   SolarPosition.h      \
    	   TimeSpan.h           \
    	   Tle.h                \
    	   TleException.h       \
    	   Util.h               \
    	   Vector.h
