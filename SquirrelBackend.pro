TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Registers.c \
    Memory.c \
    ConditionFlags.c \
    Operations.c \
    Simulation.c \
    Instructions.c \
    Compiled.c

HEADERS += \
    Registers.h \
    Memory.h \
    Operations.h \
    ConditionFlags.h \
    ARMYacc.tab.h \
    Simulation.h \
    Instructions.h \
    Compiled.h

DISTFILES +=

