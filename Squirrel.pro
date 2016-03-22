TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Compiled.c \
    ConditionFlags.c \
    Instructions.c \
    Memory.c \
    Operations.c \
    Registers.c \
    Simulation.c

HEADERS += \
    ARMYacc.tab.h \
    Compiled.h \
    ConditionFlags.h \
    Instructions.h \
    Memory.h \
    Operations.h \
    Registers.h \
    Simulation.h

