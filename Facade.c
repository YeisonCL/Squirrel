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

#include "Facade.h"
#include "Memory.h"
#include "Registers.h"
#include "Compiled.h"
#include "Simulation.h"
#include "Configuration.h"

void instantiateConfigurationVariables() //Método que crea el espacio necesario para la memoria y registros.
{
    createAllRegisters();
    createMemory();
    createNewSTDOUT();
    redirectSTDOUT();
}

void destroyConfigurationVariables() //Método que libera el espacio asignado para la memoria y registros.
{
    destroyAllRegisters();
    destroyMemory();
    destroyNewSTDOUT();
}

void changeMemorySize(int pNewMemorySize)
{
    _memorySize = pNewMemorySize;
    createNewMemory();
}

void executeCompile(const char*pFileDirection) //Método que ejecuta la compilación.
{
    int errorsParser = 0;
    //Ejecutar el parser
    updateConsole();
    if(errorsParser == 0)
    {
        executeCompilation(COMPILE);
    }

    else
    {
        prinft("\nCompilation not execute because many errors are found.\n");
        updateConsole();
    }
}

void executeSimulation(const char*pFileDirection) //Método que ejecuta la simulación.
{

    int errorsParser = 0;
    //Ejecutar el parser
    updateConsole();
    if(errorsParser == 0)
    {
        startSimulation();
    }
    else
    {
        prinft("\nSimulation not execute because many errors are found.\n");
        updateConsole();
    }
}

void updateConsole() //Método que actualiza la salida de la consola en la interfaz.
{
    fflush(stdout);
    //ENVIAR _newSTDOUT A LA INTERFAZ.
    cleanBuffer(_newSTDOUT);
}

void updateRegisters() //Método que actualiza los valores de los registros en la interfaz.
{
    //PASAR TODOS LOS REGISTROS A LA INTERFAZ.
}

void updateFlags() //Método que actualiza el valor de las banderas en la interfaz.
{
    //PASAR LAS BANDERAS A LA INTERFAZ.
}

int getClockTime() //Método que devuelve el valor del tiempo de ejecución en segundos.
{
    //ESPERAR RESPUESTA JEFFERSON
}

int *getMemory() //Método que devuelve el valor de la memoria actual.
{
    return _memory;
}
