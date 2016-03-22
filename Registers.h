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

#ifndef _REGISTERS_H
#define _REGISTERS_H

typedef struct
{
    int *_R0;
    int *_R1;
    int *_R2;
    int *_R3;
    int *_R4;
    int *_R5;
    int *_R6;
    int *_R7;
    int *_R8;
    int *_R9;
    int *_R10;
    int *_R11;
    int *_R12;
    int *_R13;
    int *_R14;
    int *_R15;
}Registers;

extern Registers _registers;

void createAllRegisters(); /*Función encargada de asignar memoria para cada uno de los 15 registros existentes*/
void destroyAllRegisters(); /*Función encargada de destruir toda la memoria asignada a cada uno de los 15 registros existentes*/
void modifyRegister(int pRegister, int pData);
int *getRegister(int pRegister);

#endif
