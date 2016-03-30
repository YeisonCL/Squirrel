/*********************************************/
/*		Instituto Tecnológico de Costa Rica  */
/*		Ingeniería en Computadores           */
/*		Arquitectura de Computadores         */
/*		II Semestre 2015                     */
/*		                                     */
/*		Author: Yeison Cruz León             */
/*              Joseph Cruz Loaiza           */
/*		Carné: 201258348                     */
/*             201258359                     */
/*********************************************/


#ifndef _FACADE_H
#define _FACADE_H

struct LogicInterface;

extern struct LogicInterface *_logicInterface;

struct regWrap {
    int r0;
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;
    int r7;
    int r8;
    int r9;
    int r10;
    int r11;
    int r12;
    int r13;
    int r14;
    int r15;
};

typedef struct regWrap RegWrap;

void instantiateConfigurationVariables(); //Método que crea el espacio necesario para la memoria, registros y nueva salida estandar.
void destroyConfigurationVariables(); //Método que libera el espacio asignado para la memoria, registros y nueva salida estandar.
void executeCompile(const char*pFileDirection, char *pFileCompiledDirection); //Método que ejecuta la compilación.
void executeSimulation(const char*pFileDirection); //Método que ejecuta la simulación.
int getClockTime(); //Método que devuelve el valor del tiempo de ejecución en segundos.
int *getMemory(); //Método que devuelve el valor de la memoria actual.


void updateConsole(); //Método que actualiza la salida de la consola en la interfaz.
void updateRegisters(); //Método que actualiza los valores de los registros en la interfaz.
void updateFlags(); //Método que actualiza el valor de las banderas en la interfaz.

void updateConsoleCpp(struct LogicInterface* p, char *pText);
void updateTextRegistersCpp(struct LogicInterface* p, int pRegister0, int pRegister1, int pRegister2, int pRegister3, int pRegister4, int pRegister5, int pRegister6, int pRegister7, int pRegister8, int pRegister9, int pRegister10, int pRegister11, int pRegister12, int pRegister13, int pRegister14, int pRegister15);
void updateTextFlagsCpp(struct LogicInterface* p, int pCarry, int pNegative, int pZero, int pOverflow);

void setLogicInterface(struct LogicInterface* p);

#endif
