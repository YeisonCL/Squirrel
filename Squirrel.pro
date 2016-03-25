TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Compiled.c \
    ConditionFlags.c \
    Instructions.c \
    Memory.c \
    Operations.c \
    Registers.c \
    Simulation.c \
    ARMYacc.tab.c \
    InstructionList.c \
    lex.yy.c \
    ParserMiscellaneous.c \
    RefList.c \
    Symbols.c \
    Facade.c \
    Configuration.c \
    main.c

HEADERS += \
    ARMYacc.tab.h \
    Compiled.h \
    ConditionFlags.h \
    Instructions.h \
    Memory.h \
    Operations.h \
    Registers.h \
    Simulation.h \
    InstructionList.h \
    ParserMiscellaneous.h \
    RefList.h \
    Symbols.h \
    Facade.h \
    Configuration.h

