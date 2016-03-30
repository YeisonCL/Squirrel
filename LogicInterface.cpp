#include "LogicInterface.h"
#include <iostream>

extern "C"
{
    #include "Facade.h"
}


using namespace std;

LogicInterface::LogicInterface()
{
    instantiateConfigurationVariables();
    setLogicInterface(this);
}

void LogicInterface::compile(char* pPath, char* pCompiledPath){
    executeCompile(pPath, pCompiledPath);
    free(pPath);
    free(pCompiledPath);
}

void LogicInterface::simulate(char* pPath){
    executeSimulation(pPath);
    free(pPath);
}

void LogicInterface::refreshRegs(int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7,
                 int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15){
    emit signalRefreshRegs(pRegister0, pRegister1, pRegister2, pRegister3, pRegister4, pRegister5, pRegister6, pRegister7, pRegister8, pRegister9, pRegister10, pRegister11, pRegister12, pRegister13, pRegister14, pRegister15);
}

void LogicInterface::refreshFlags(int pCarry, int pNegative, int pZero, int pOverflow){
    emit signalRefreshFlags(pCarry, pNegative, pZero, pOverflow);
}

void LogicInterface::print(char* pText){
    QString *s = new QString(pText);
    emit signalPrint(s);
}

extern "C" void updateConsoleCpp(LogicInterface* p, char *pText)
{
    p->print(pText);
}

extern "C" void updateTextRegistersCpp(LogicInterface* p, int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7, int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15)
{
    p->refreshRegs(pRegister0, pRegister1, pRegister2, pRegister3, pRegister4, pRegister5, pRegister6, pRegister7, pRegister8, pRegister9, pRegister10, pRegister11, pRegister12, pRegister13, pRegister14, pRegister15);
}

extern "C" void updateTextFlagsCpp(LogicInterface* p, int pCarry, int pNegative, int pZero, int pOverflow)
{
    p->refreshFlags(pCarry, pNegative, pZero, pOverflow);
}
