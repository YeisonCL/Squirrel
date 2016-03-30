
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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Configuration.h"

char *_newSTDOUT;

int _executionError  = 0;
int _memorySize     = 2048;     // Tamaño total de la memoria
int _dataMemStart   = 1024;     // Inicio de la memoria de datos
int _dataMemSize    = 1024;     // Tamaño de la memoria de datos
int _instrMemStart  = 0;        // Inicio de la memoria de programa
int _instMemSize    = 1024;     // Tamaño de la memoria de programa

char *_compiledFileDirection = "";

void createCompiledFileDirection()
{
    _compiledFileDirection = (char*)calloc(1024, sizeof(char));
}

void setCompiledFileDirection(char *pDirection)
{
    strcpy(_compiledFileDirection, pDirection);
}

void createNewSTDOUT()
{
    _newSTDOUT = (char*)calloc(65536, sizeof(char));
}

void destroyNewSTDOUT()
{
    free(_newSTDOUT);
}

void redirectSTDOUT()
{
    freopen("/dev/null", "a", stdout);
    setbuf(stdout, _newSTDOUT);
}

void cleanBuffer(char *pBuffer)
{
    int sizeBuffer = strlen(pBuffer);
    int i = 0;
    while(*(pBuffer + i) != 0 && i != sizeBuffer)
    {
        *(pBuffer + i) = 0;
        i = i + 1;
    }
}

#ifdef __cplusplus
}
#endif
