######################################################################
# Automatically generated by qmake (3.0) Wed Sep 9 10:23:18 2015
######################################################################

TEMPLATE = app
TARGET = nail_art
INCLUDEPATH += .
QT       += core gui
QT       += widgets
QT += opengl core gui widgets
QMAKE_LIBDIR += "glu32_location"

win32-msvc2013 {
    INCLUDEPATH +=   ../qip_win/IP/header ../qip_win/MP/header
	LIBS	    += -L../qip_win/IP/lib  -L../qip_win/MP/lib    
	LIBS	    += -lIP -lMP
	QMAKE_CXXFLAGS += /MP /Zi
}

# Input
HEADERS += MainWindow.h
SOURCES += main.cpp MainWindow.cpp MainWindowUtil.cpp slots.cpp
