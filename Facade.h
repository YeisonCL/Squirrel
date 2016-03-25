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

void instantiateConfigurationVariables(); //Método que crea el espacio necesario para la memoria, registros y nueva salida estandar.
void destroyConfigurationVariables(); //Método que libera el espacio asignado para la memoria, registros y nueva salida estandar.
void executeCompile(const char*pFileDirection); //Método que ejecuta la compilación.
void executeSimulation(const char*pFileDirection); //Método que ejecuta la simulación.
void updateConsole(); //Método que actualiza la salida de la consola en la interfaz.
void updateRegisters(); //Método que actualiza los valores de los registros en la interfaz.
void updateFlags(); //Método que actualiza el valor de las banderas en la interfaz.
void changeMemorySize(int pNewMemorySize); //Metodo que cambia el tamaño actual de la memoria.
int getClockTime(); //Método que devuelve el valor del tiempo de ejecución en segundos.
int *getMemory(); //Método que devuelve el valor de la memoria actual.

#endif
