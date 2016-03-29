#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T21:24:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SquirrelARM
TEMPLATE = app


SOURCES += \
    about.cpp \
    main.cpp \
    memory.cpp \
    squirrelmain.cpp \
    Facade.c \
    backend/ARMYacc.tab.c \
    backend/Compiled.c \
    backend/ConditionFlags.c \
    backend/Configuration.c \
    backend/InstructionList.c \
    backend/Instructions.c \
    backend/lex.yy.c \
    backend/MemoryData.c \
    backend/Operations.c \
    backend/ParserMiscellaneous.c \
    backend/RefList.c \
    backend/Registers.c \
    backend/Simulation.c \
    backend/Symbols.c \
    LogicInterface.cpp

HEADERS  += \
    about.h \
    Facade.h \
    memory.h \
    squirrelmain.h \
    backend/ARMFlex \
    backend/ARMYacc \
    backend/ARMYacc.tab.h \
    backend/Compiled.h \
    backend/ConditionFlags.h \
    backend/Configuration.h \
    backend/InstructionList.h \
    backend/Instructions.h \
    backend/MemoryData.h \
    backend/Operations.h \
    backend/ParserMiscellaneous.h \
    backend/RefList.h \
    backend/Registers.h \
    backend/Simulation.h \
    backend/Symbols.h \
    LogicInterface.h

RESOURCES += \
    resources.qrc

FORMS += \
    about.ui \
    memory.ui \
    squirrelmain.ui

CONFIG   += c++11
CONFIG   += -lpthread

DISTFILES += \
    backend/src.armv4
