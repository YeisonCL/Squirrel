
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
int _memorySize = 0;

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
