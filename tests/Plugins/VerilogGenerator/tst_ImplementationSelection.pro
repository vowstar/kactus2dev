#-----------------------------------------------------------------------------
# File: tst_ImplementationSelection.pro
#-----------------------------------------------------------------------------
# Project: Kactus2
# Author: Janne Virtanen
# Date: 19.01.2017
#
# Description:
# Qt project file for running unit tests for Verilog implementation selection.
#-----------------------------------------------------------------------------

TEMPLATE = app

TARGET = tst_ImplementationSelection

QT += core xml gui testlib
CONFIG += c++11 testcase console

win32:CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../../../executable/ -lIPXACTmodels
    DESTDIR = ./release
}
else:win32:CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../../executable/ -lIPXACTmodelsd
    DESTDIR = ./debug
}
else:unix {
    LIBS += -L$$PWD/../../../executable/ -lIPXACTmodels
    DESTDIR = ./release
}

INCLUDEPATH += $$PWD/../../../
INCLUDEPATH += $$PWD/../../../executable
INCLUDEPATH += $$PWD/../../../executable/Plugins
INCLUDEPATH += $$DESTDIR

DEPENDPATH += $$PWD/../../../
DEPENDPATH += $$PWD/../../../executable
DEPENDPATH += $$PWD/../../../executable/Plugins
DEPENDPATH += .

OBJECTS_DIR += $$DESTDIR

MOC_DIR += ./generatedFiles
UI_DIR += ./generatedFiles
RCC_DIR += ./generatedFiles
include(tst_ImplementationSelection.pri)
