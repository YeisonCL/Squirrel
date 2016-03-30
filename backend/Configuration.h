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

#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

extern char *_newSTDOUT;
extern int _memorySize;
extern int _dataMemStart;
extern int _dataMemSize;
extern int _instrMemStart;
extern int _instMemSize;

void createNewSTDOUT();
void destroyNewSTDOUT();
void redirectSTDOUT();
void cleanBuffer(char *pBuffer);

#endif
