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

#include "Simulation.h"
#include "Registers.h"
#include "MemoryData.h"
#include "ARMYacc.tab.h"
#include "Instructions.h"
#include "ConditionFlags.h"
#include "Operations.h"
#include "Compiled.h"
#include "InstructionList.h"
#include "Facade.h"

void executeInstruction(Instruction *pInstruction); //Método encargado de ejecutar una instrucción.
void verifyInstruction(Instruction *pInstruction);
int verifyEQ();
int verifyNE();
int verifyCS();
int verifyCC();
int verifyMI();
int verifyPL();
int verifyVS();
int verifyVC();
int verifyHI();
int verifyLS();
int verifyGE();
int verifyLT();
int verifyGT();
int verifyLE();

void startSimulation() //Método que inicia la simulación.
{
    executeCompilation(COMPILEANDSIMULE);
    printf("\nStart simulation...\n");
    updateConsole();
    resetMemory();
    resetRegisters();
    resetFlags();
    int totalInstructions = getLastInstruction();
    while(*(_registers._R15) <= totalInstructions)
    {
        //DEBUGGING
        /*
        printf("\n\n--------------------------------------------------\n");
        printf("Instruccion: %d\n", *(_registers._R15));
        printf("\nRegistros PRE-Instruccion\n");
        printRegisters();
        printf("\nMemoria PRE-Instruccion\n");
        printDataMemory();
        printf("\nFlags PRE-Instruction\n");
        printFlags();
        */
        //DEBUGGING
        int oldPC = *(_registers._R15);
        executeInstruction(getInstruction(*(_registers._R15)));
        *(_registers._R15) = oldPC == *(_registers._R15) ? *(_registers._R15) + 1 : *(_registers._R15);
        updateFlags();
        updateRegisters();
        //DEBUGGING
        /*
        printf("\nRegistros POST-Instruccion\n");
        printRegisters();
        printf("\nMemoria POST-Instruccion\n");
        printDataMemory();
        printf("\nFlags POST-Instruction\n");
        printFlags();
        getchar();
        */
        //DEBUGGING
    }
    printf("\nEnd simulation...\n");
    updateConsole();
}

void executeInstruction(Instruction *pInstruction)
{
    if((pInstruction->condition == EQ && verifyEQ()) || (pInstruction->condition == NE && verifyNE()) || (pInstruction->condition == CS && verifyCS()) ||
            (pInstruction->condition == CC && verifyCC()) || (pInstruction->condition == MI && verifyMI()) || (pInstruction->condition == PL && verifyPL()) ||
            (pInstruction->condition == VS && verifyVS()) || (pInstruction->condition == VC && verifyVC()) || (pInstruction->condition == HI && verifyHI()) ||
            (pInstruction->condition == LS && verifyLS()) || (pInstruction->condition == GE && verifyGE()) || (pInstruction->condition == LT && verifyLT()) ||
            (pInstruction->condition == GT && verifyGT()) || (pInstruction->condition == LE && verifyLE()) || (pInstruction->condition == AL))
    {
         verifyInstruction(pInstruction);
    }
    else
    {
        ;
    }
}

int verifyEQ()
{
    if(_zero)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyNE()
{
    if(!_zero)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyCS()
{
    if(_carry)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyCC()
{
    if(!_carry)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyMI()
{
    if(_negative)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyPL()
{
    if(!_negative)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyVS()
{
    if(_overflow)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyVC()
{
    if(!_overflow)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyHI()
{
    if(!_zero * _carry)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyLS()
{
    if(_zero | !_carry)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyGE()
{
    if(!(_negative ^ _overflow))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyLT()
{
    if(_negative ^ _overflow)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyGT()
{
    if(!_zero * !(_negative ^ _overflow))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifyLE()
{
    if(_zero | (_negative ^ _overflow))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void verifyInstruction(Instruction *pInstruction)
{
    switch (pInstruction->instrType)
    {
        case AND:
            ANDInstruction(pInstruction);
            break;
        case EOR:
            EORInstruction(pInstruction);
            break;
        case SUB:
            SUBInstruction(pInstruction);
            break;
        case RSB:
            RSBInstruction(pInstruction);
            break;
        case ADD:
            ADDInstruction(pInstruction);
            break;
        case ADC:
            ADCInstruction(pInstruction);
            break;
        case SBC:
            SBCInstruction(pInstruction);
            break;
        case RSC:
            RSCInstruction(pInstruction);
            break;
        case TST:
            TSTInstruction(pInstruction);
            break;
        case TEQ:
            TEQInstruction(pInstruction);
            break;
        case CMP:
            CMPInstruction(pInstruction);
            break;
        case CMN:
            CMNInstruction(pInstruction);
            break;
        case ORR:
            ORRInstruction(pInstruction);
            break;
        case MOV:
            MOVInstruction(pInstruction);
            break;
        case LSL:
            LSLInstruction(pInstruction);
            break;
        case LSR:
            LSRInstruction(pInstruction);
            break;
        case ASR:
            ASRInstruction(pInstruction);
            break;
        case RRX:
            RRXInstruction(pInstruction);
            break;
        case ROR:
            RORInstruction(pInstruction);
            break;
        case BIC:
            BICInstruction(pInstruction);
            break;
        case MVN:
            MVNInstruction(pInstruction);
            break;
        case MUL:
            MULInstruction(pInstruction);
            break;
        case MLA:
            MLAInstruction(pInstruction);
            break;
        case UMULL:
            UMULLInstruction(pInstruction);
            break;
        case UMLAL:
            UMLALInstruction(pInstruction);
            break;
        case SMULL:
            SMULLInstruction(pInstruction);
            break;
        case SMLAL:
            SMLALInstruction(pInstruction);
            break;
        case STR:
            STRInstruction(pInstruction);
            break;
        case LDR:
            LDRInstruction(pInstruction);
            break;
        case STRB:
            STRBInstruction(pInstruction);
            break;
        case LDRB:
            LDRBInstruction(pInstruction);
            break;
        case STRH:
            STRHInstruction(pInstruction);
            break;
        case LDRH:
            LDRHInstruction(pInstruction);
            break;
        case LDRSB:
            LDRSBInstruction(pInstruction);
            break;
        case LDRSH:
            LDRSHInstruction(pInstruction);
            break;
        case B:
            BInstruction(pInstruction);
            break;
        case BL:
            BLInstruction(pInstruction);
            break;
        default:
            printf("ERROR: INVALID INSTRUCTION");
            break;
    }
}


#ifdef __cplusplus
}
#endif
