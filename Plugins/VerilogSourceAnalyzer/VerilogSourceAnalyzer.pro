# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = VerilogSourceAnalyzer

QT += core xml widgets
CONFIG += c++11 plugin release

DEFINES += VERILOGSOURCEANALYZER_LIB

INCLUDEPATH += ./generatedFiles \
    ./../.. \
    . \
    ./generatedFiles/release
LIBS += -L"./../../executable" \
    -lIPXACTmodels

DESTDIR = ../../executable/Plugins

DEPENDPATH += .
MOC_DIR += ./generatedFiles/release
OBJECTS_DIR += release
UI_DIR += ./generatedFiles
RCC_DIR += ./generatedFiles

include(VerilogSourceAnalyzer.pri)

target.path = $$plugin_path
INSTALLS += target
