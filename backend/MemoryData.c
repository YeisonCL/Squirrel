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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#include "MemoryData.h"
#include "Facade.h"
#include "Configuration.h"

int *_memory;

void createMemory() //Crear la memoria que usara ARM.
{
    _memory = (int*) calloc(512, sizeof (int));
    if (_memory == NULL)
    {
        printf("\nCould not allocate data memory.\n");
        exit(-1);
    }
    else
    {
        printf("\nData memory allocated successfully.\n");
    }
}

void destroyMemory() //Destruir la memoria que usara ARM.
{
    free(_memory);
    printf("\nData memory free successfully.\n");
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

//DEBUGGING
void printDataMemory()
{
    for(int i = 256; i <= 511; i = i +1)
    {
        printf("%d: %d \t", i * 4, _memory[i]);
    }
}

//DEBUGGING

#ifdef __cplusplus
}
#endif
