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

#include "Facade.h"
#include "backend/ConditionFlags.h"
#include "backend/MemoryData.h"
#include "backend/Registers.h"
#include "backend/Compiled.h"
#include "backend/Simulation.h"
#include "backend/Configuration.h"
#include "backend/ParserMiscellaneous.h"
#include "backend/InstructionList.h"

struct LogicInterface *_logicInterface;

void instantiateConfigurationVariables() //Método que crea el espacio necesario para la memoria y registros.
{
    createAllRegisters();
    createMemory();
    createCompiledFileDirection();
    createNewSTDOUT();
    redirectSTDOUT();
}

void destroyConfigurationVariables() //Método que libera el espacio asignado para la memoria y registros.
{
    destroyAllRegisters();
    destroyMemory();
    destroyNewSTDOUT();
}

void executeCompile(const char *pFileDirection, char *pFileCompiledDirection) //Método que ejecuta la compilación.
{
    setCompiledFileDirection(pFileCompiledDirection);
    int errorsParser = executeParser(pFileDirection);
    updateConsole();
    if(errorsParser == 0)
    {
        executeCompilation(COMPILE);
    }
}

void executeSimulation(const char*pFileDirection) //Método que ejecuta la simulación.
{

    int errorsParser = executeParser(pFileDirection);
    updateConsole();
    if(errorsParser == 0)
    {
        startSimulation();
    }    
}

void updateConsole() //Método que actualiza la salida de la consola en la interfaz.
{
    fflush(stdout);
    updateConsoleCpp(_logicInterface, _newSTDOUT);
    cleanBuffer(_newSTDOUT);
}

void updateRegisters() //Método que actualiza los valores de los registros en la interfaz.
{
    updateTextRegistersCpp(_logicInterface, *(_registers._R0), *(_registers._R1), *(_registers._R2), *(_registers._R3), *(_registers._R4), *(_registers._R5), *(_registers._R6), *(_registers._R7), *(_registers._R8), *(_registers._R9), *(_registers._R10), *(_registers._R11), *(_registers._R12), *(_registers._R13), *(_registers._R14), *(_registers._R15));
}

void updateFlags() //Método que actualiza el valor de las banderas en la interfaz.
{
    updateTextFlagsCpp(_logicInterface, _carry, _negative, _zero, _overflow);
}

int *getMemory() //Método que devuelve el valor de la memoria actual.
{
    return _memory;
}

void setLogicInterface(struct LogicInterface* p)
{
    _logicInterface = p;
}
void resetMemoryFacade(){
    resetMemory();
}

#ifdef __cplusplus
}
#endif
