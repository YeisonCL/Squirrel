#ifndef LOGICINTERFACE_H
#define LOGICINTERFACE_H
#include <QObject>

class LogicInterface : public QObject
{
    Q_OBJECT

public:
    LogicInterface();
    void refreshRegs(int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7,
                     int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15);
    void refreshFlags(int pCarry, int pNegative, int pZero, int pOverflow);
    void print(char* pText);

public slots:
    void compile(char* pPath, char* pCompiledPath);
    void simulate(char* pPath);

signals:
    void signalRefreshRegs(int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7,
                    int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15);
    void signalRefreshFlags(int pCarry, int pNegative, int pZero, int pOverflow);
    void signalPrint(QString* pText);

private:

};

#endif // LOGICINTERFACE_H
