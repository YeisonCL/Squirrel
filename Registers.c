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

#include <stdio.h>
#include <stdlib.h>

#include "Registers.h"
#include "Instructions.h"
#include "Facade.h"

Registers _registers;

void createAllRegisters() /*Función encargada de asignar memoria para cada uno de los 15 registros existentes*/
{
    _registers._R0 = (int*) calloc(1, sizeof (int));
    _registers._R1 = (int*) calloc(1, sizeof (int));
    _registers._R2 = (int*) calloc(1, sizeof (int));
    _registers._R3 = (int*) calloc(1, sizeof (int));
    _registers._R4 = (int*) calloc(1, sizeof (int));
    _registers._R5 = (int*) calloc(1, sizeof (int));
    _registers._R6 = (int*) calloc(1, sizeof (int));
    _registers._R7 = (int*) calloc(1, sizeof (int));
    _registers._R8 = (int*) calloc(1, sizeof (int));
    _registers._R9 = (int*) calloc(1, sizeof (int));
    _registers._R10 = (int*) calloc(1, sizeof (int));
    _registers._R11 = (int*) calloc(1, sizeof (int));
    _registers._R12 = (int*) calloc(1, sizeof (int));
    _registers._R13 = (int*) calloc(1, sizeof (int));
    _registers._R14 = (int*) calloc(1, sizeof (int));
    _registers._R15 = (int*) calloc(1, sizeof (int));
    if (_registers._R0 == NULL || _registers._R1 == NULL || _registers._R2 == NULL || _registers._R3 == NULL || _registers._R4 == NULL || _registers._R5 == NULL ||
            _registers._R6 == NULL || _registers._R7 == NULL || _registers._R8 == NULL || _registers._R9 == NULL || _registers._R10 == NULL || _registers._R11 == NULL ||
            _registers._R12 == NULL || _registers._R13 == NULL || _registers._R14 == NULL || _registers._R15 == NULL)
    {
        printf("\nCould not allocate memory for some register.\n");
        updateConsole();
        exit(-1);
    }
    else
    {
        printf("\nMemory allocated successfully for all registers.\n");
        updateConsole();
    }
}

void resetRegisters()
{
    for(int i  = 0; i <= 15; i = i + 1)
    {
        *(getRegister(i)) = 0;
    }
}

void destroyAllRegisters() /*Función encargada de destruir toda la memoria asignada a cada uno de los 15 registros existentes*/
{
    free(_registers._R0);
    free(_registers._R1);
    free(_registers._R2);
    free(_registers._R3);
    free(_registers._R4);
    free(_registers._R5);
    free(_registers._R6);
    free(_registers._R7);
    free(_registers._R8);
    free(_registers._R9);
    free(_registers._R10);
    free(_registers._R11);
    free(_registers._R12);
    free(_registers._R13);
    free(_registers._R14);
    free(_registers._R15);
    printf("\nMemory free successfully for all registers.\n");
    updateConsole();
}

int *getRegister(int pRegister)
{
    if(pRegister == R0)
    {
        return _registers._R0;
    }
    else if(pRegister == R1)
    {
        return _registers._R1;
    }
    else if(pRegister == R2)
    {
        return _registers._R2;
    }
    else if(pRegister == R3)
    {
        return _registers._R3;
    }
    else if(pRegister == R4)
    {
        return _registers._R4;
    }
    else if(pRegister == R5)
    {
        return _registers._R5;
    }
    else if(pRegister == R6)
    {
        return _registers._R6;
    }
    else if(pRegister == R7)
    {
        return _registers._R7;
    }
    else if(pRegister == R8)
    {
        return _registers._R8;
    }
    else if(pRegister == R9)
    {
        return _registers._R9;
    }
    else if(pRegister == R10)
    {
        return _registers._R10;
    }
    else if(pRegister == R11)
    {
        return _registers._R11;
    }
    else if(pRegister == R12)
    {
        return _registers._R12;
    }
    else if(pRegister == R13)
    {
        return _registers._R13;
    }
    else if(pRegister == R14)
    {
        return _registers._R14;
    }
    else if(pRegister == R15)
    {
        return _registers._R15;
    }
    else
    {
        return NULL;
    }
}

void modifyRegister(int pRegister, int pData)
{
    *(getRegister(pRegister)) = pData;
}

//DEBUGGING
void printRegisters()
{
    for(int i  = 0; i <= 15; i = i + 1)
    {
        printf("R%d: %d\t", i, *(getRegister(i)));
    }
}
//DEBUGGING
