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

#ifndef _MEMORY_H
#define _MEMORY_H

extern int *_memory;

void createNewMemory(); //Metodo que crea nueva memoria con nuevo espacio.
void createMemory(); //Crear la memoria que usara ARM.
void destroyMemory(); //Destruir la memoria que usara ARM.
void modifyMemory(int pAddress, int pData);
void resetMemory();


//DEBUGGING
void printDataMemory();
//DEBUGGING

#endif
