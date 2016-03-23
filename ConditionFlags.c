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

#include "ConditionFlags.h"

int _negative = 0;
int _zero = 0;
int _carry = 0;
int _overflow = 0;

//DEBUGGING
void printFlags()
{
    printf("Negative: %d Zero: %d Carry: %d Overflow: %d", _negative, _zero, _carry, _overflow);
}
//DEBUGGING
