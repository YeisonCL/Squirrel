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

#include "Memory.h"

int *_memory;

void createMemory() //Crear la memoria que usara ARM.
{
    _memory = (int*) calloc(512, sizeof (int));
    if (_memory == NULL)
    {
        printf("Could not allocate data memory.\n");
        exit(-1);
    }
    else
    {
        printf("Data memory allocated successfully.\n");
    }
}

void destroyMemory() //Destruir la memoria que usara ARM.
{
    free(_memory);
    printf("Data memory free successfully.\n");
}

void modifyMemory(int pAddress, int pData)
{
    _memory[pAddress] = pData;
}

void resetMemory()
{
    for(int i = 0; i <= 511; i = i +1)
    {
        _memory[i] = 0;
    }
}
