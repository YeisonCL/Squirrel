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
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "Compiled.h"
#include "Memory.h"
#include "Registers.h"
#include "Instructions.h"
#include "ParserMiscellaneous.h"
#include "ARMYacc.tab.h"
#include "InstructionList.h"

const int COMPILE = 0;
const int COMPILEANDSIMULE = 1;

const int START = 1;
const int END = 0;

FILE *compiledFile;
int i;

void writeHeader();
void verifyTypeCompilation(int pTypeCompilation, int pControlFlag);
int conditionalBinaryCode(int pConditional);
int cmdBinaryCode(int pInstruction);
int compileInstruction(Instruction *pInstruction);
int compileDataProcessingInstruction(Instruction *pInstruction);
int compileMultiplyInstruction(Instruction *pInstruction);
int compileMemoryInstruction(Instruction *pInstruction);
int compileBranchInstruction(Instruction *pInstruction);
int testIndexMode(int pIndexMode, int pValue, int pControlFlag);
int testMemoryInstruction(int pInstruction, int pValue, int pControlFlag);
int testOperationTwoInstruction(int pInstruction, int pValue);
void saveCompiledInstruction(int pTypeCompilation, int pInstruction, int pIndex);

int conditionalBinaryCode(int pConditional)
{
    if(pConditional == EQ)
    {
        return 0;
    }
    else if(pConditional == NE)
    {
        return 1;
    }
    else if(pConditional == CS)
    {
        return 2;
    }
    else if(pConditional == CC)
    {
        return 3;
    }
    else if(pConditional == MI)
    {
        return 4;
    }
    else if(pConditional == PL)
    {
        return 5;
    }
    else if(pConditional == VS)
    {
        return 6;
    }
    else if(pConditional == VC)
    {
        return 7;
    }
    else if(pConditional == HI)
    {
        return 8;
    }
    else if(pConditional == LS)
    {
        return 9;
    }
    else if(pConditional == GE)
    {
        return 10;
    }
    else if(pConditional == LT)
    {
        return 11;
    }
    else if(pConditional == GT)
    {
        return 12;
    }
    else if(pConditional == LE)
    {
        return 13;
    }
    else if(pConditional == AL)
    {
        return 14;
    }
    else
    {
        return 0;
    }
}

int cmdBinaryCode(int pInstruction)
{
    switch (pInstruction)
    {
        case AND:
            return 0;
            break;
        case EOR:
            return 1;
            break;
        case SUB:
            return 2;
            break;
        case RSB:
            return 3;
            break;
        case ADD:
            return 4;
            break;
        case ADC:
            return 5;
            break;
        case SBC:
            return 6;
            break;
        case RSC:
            return 7;
            break;
        case TST:
            return 8;
            break;
        case TEQ:
            return 9;
            break;
        case CMP:
            return 10;
            break;
        case CMN:
            return 11;
            break;
        case ORR:
            return 12;
            break;
        case MOV:
            return 13;
            break;
        case LSL:
            return 13;
            break;
        case LSR:
            return 13;
            break;
        case ASR:
            return 13;
            break;
        case RRX:
            return 13;
            break;
        case ROR:
            return 13;
            break;
        case BIC:
            return 14;
            break;
        case MVN:
            return 15;
            break;
        default:
            return 0;
            break;
    }
}

void executeCompilation(int pTypeCompilation)
{
    //pTypeCompilation == COMPILE -> Solo modo de compilacion (generación de archivo).
    //pTypeCompilation == COMPILEANDSIMULE -> Modo de compilación + simulación (no generación de archivo, guardado en memoria).

    printf("Start compilation...\n");
    verifyTypeCompilation(pTypeCompilation, START);
    int totalInstructions = getLastInstruction();
    for(i = 0; i <= totalInstructions; i = i + 1)
    {
        int compiledInstruction = compileInstruction(getInstruction(i));
        saveCompiledInstruction(pTypeCompilation, compiledInstruction, i);
    }
    verifyTypeCompilation(pTypeCompilation, END);
    printf("End compilation...\n");
}

void verifyTypeCompilation(int pTypeCompilation, int pControlFlag)
{
    if(pTypeCompilation == COMPILE && pControlFlag == START)
    {
        compiledFile = fopen("/root/Desktop/Squirrel/out.txt", "w");
        writeHeader();
    }
    else if(pTypeCompilation == COMPILE && pControlFlag == END)
    {
        fclose(compiledFile);
    }
}

void writeHeader()
{
    char *header = "******************************************\n"
                   "*   Instituto Tecnológico de Costa Rica  *\n"
                   "*   Ingeniería en Computadores           *\n"
                   "*   Arquitectura de Computadores         *\n"
                   "*   I  Semestre 2016                     *\n"
                   "*                                        *\n"
                   "*   Author: Yeison Cruz León             *\n"
                   "*           Joseph Cruz Loaiza           *\n"
                   "*   Carne: 201258348                     *\n"
                   "*          201258359                     *\n"
                   "******************************************\n\n\n";
    fprintf(compiledFile, header);
}

void saveCompiledInstruction(int pTypeCompilation, int pInstruction, int pIndex)
{
    if(pTypeCompilation == COMPILE)
    {
        char *instructionStr = (char*) calloc(32, sizeof (char));
        char *indexStr = (char*) calloc(32, sizeof (char));
        sprintf(instructionStr, "%X", (unsigned int)pInstruction);
        sprintf(indexStr, "%X", (unsigned int)pIndex);
        strcat(indexStr, "\t");
        strcat(instructionStr, "\n");
        fprintf(compiledFile, "0x");
        fprintf(compiledFile, indexStr);
        fprintf(compiledFile, "0x");
        fprintf(compiledFile, instructionStr);
        free(instructionStr);
        free(indexStr);
    }
    else
    {
        _memory[pIndex] = pInstruction;
    }
}

int compileInstruction(Instruction *pInstruction)
{
    if(pInstruction->instrType == AND || pInstruction->instrType == EOR || pInstruction->instrType == SUB || pInstruction->instrType == RSB ||
            pInstruction->instrType == ADD || pInstruction->instrType == ADC || pInstruction->instrType == SBC || pInstruction->instrType == RSC ||
            pInstruction->instrType == TST || pInstruction->instrType == TEQ || pInstruction->instrType == CMP || pInstruction->instrType == CMN ||
            pInstruction->instrType == ORR || pInstruction->instrType == MOV || pInstruction->instrType == LSL || pInstruction->instrType == LSR ||
            pInstruction->instrType == ASR || pInstruction->instrType == RRX || pInstruction->instrType == ROR || pInstruction->instrType == BIC ||
            pInstruction->instrType == MVN)
    {
        return compileDataProcessingInstruction(pInstruction);
    }
    else if(pInstruction->instrType == MUL || pInstruction->instrType == MLA || pInstruction->instrType == UMULL || pInstruction->instrType == UMLAL ||
            pInstruction->instrType == SMULL || pInstruction->instrType == SMLAL)
    {
        return compileMultiplyInstruction(pInstruction);
    }
    else if(pInstruction->instrType == STR || pInstruction->instrType == LDR || pInstruction->instrType == STRB || pInstruction->instrType == LDRB ||
            pInstruction->instrType == STRH || pInstruction->instrType == LDRH || pInstruction->instrType == LDRSB || pInstruction->instrType == LDRSH)
    {
        return compileMemoryInstruction(pInstruction);
    }
    else if(pInstruction->instrType == B || pInstruction->instrType == BL)
    {
        return compileBranchInstruction(pInstruction);
    }
    else
    {
        return 0;
    }
}

int compileDataProcessingInstruction(Instruction *pInstruction)
{
    int compiledInstruction = 0;
    compiledInstruction = compiledInstruction + conditionalBinaryCode(pInstruction->condition);
    compiledInstruction = (unsigned int)compiledInstruction << 3;
    compiledInstruction = pInstruction->src2Type == IMMEDIATE ? compiledInstruction + 1 : compiledInstruction;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + cmdBinaryCode(pInstruction->instrType);
    compiledInstruction = (unsigned int)compiledInstruction << 1;
    compiledInstruction = (pInstruction->instrType == TST  ||  pInstruction->instrType == TEQ || pInstruction->instrType == CMP || pInstruction->instrType == CMN) ? compiledInstruction + 1 : compiledInstruction + pInstruction->setFlags;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + pInstruction->r_n;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + pInstruction->r_d;
    if(pInstruction->src2Type == IMMEDIATE)
    {
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->rot;
        compiledInstruction = (unsigned int)compiledInstruction << 8;
        compiledInstruction = compiledInstruction + pInstruction->immSeed;
        return compiledInstruction;
    }
    else if(pInstruction->src2Type == REG_IMM)
    {
        compiledInstruction = (unsigned int)compiledInstruction << 5;
        compiledInstruction = compiledInstruction + pInstruction->imm_shmt;
        compiledInstruction = (unsigned int)compiledInstruction << 2;
        if(pInstruction->instrType == LSL)
        {
            compiledInstruction = compiledInstruction + 1;
        }
        else if(pInstruction->instrType == ASR)
        {
            compiledInstruction = compiledInstruction + 2;
        }
        else if(pInstruction->instrType == RRX)
        {
            compiledInstruction = (unsigned int)compiledInstruction >> 7;
            compiledInstruction = (unsigned int)compiledInstruction << 7;
            compiledInstruction = compiledInstruction + 3;
        }
        else if(pInstruction->instrType == LSR)
        {
            compiledInstruction = compiledInstruction + 3;
        }
        else
        {
            if(pInstruction->shift_type == LSR)
            {
                compiledInstruction = compiledInstruction + 1;
            }
            else if(pInstruction->shift_type == ASR)
            {
                compiledInstruction = compiledInstruction + 2;
            }
            else if(pInstruction->shift_type == ROR)
            {
                compiledInstruction = compiledInstruction + 3;
            }
            else
            {
                compiledInstruction = compiledInstruction + 0;
            }
        }
        compiledInstruction = (unsigned int)compiledInstruction << 5;
        compiledInstruction = compiledInstruction + pInstruction->r_m;
        return compiledInstruction;
    }
    else if(pInstruction->src2Type == REG_REG)
    {
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_sa;
        compiledInstruction = (unsigned int)compiledInstruction << 3;
        if(pInstruction->instrType == LSL)
        {
            compiledInstruction = compiledInstruction + 1;
        }
        else if(pInstruction->instrType == ASR)
        {
            compiledInstruction = compiledInstruction + 2;
        }
        else if(pInstruction->instrType == RRX)
        {
            compiledInstruction = (unsigned int)compiledInstruction >> 7;
            compiledInstruction = (unsigned int)compiledInstruction << 7;
            compiledInstruction = compiledInstruction + 3;
        }
        else if(pInstruction->instrType == LSR)
        {
            compiledInstruction = compiledInstruction + 3;
        }
        else
        {
            if(pInstruction->shift_type == LSR)
            {
                compiledInstruction = compiledInstruction + 1;
            }
            else if(pInstruction->shift_type == ASR)
            {
                compiledInstruction = compiledInstruction + 2;
            }
            else if(pInstruction->shift_type == ROR)
            {
                compiledInstruction = compiledInstruction + 3;
            }
            else
            {
                compiledInstruction = compiledInstruction + 0;
            }
        }
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = pInstruction->instrType == RRX ? compiledInstruction + 0 : compiledInstruction + 1;
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_m;
        return compiledInstruction;
    }
    else
    {
        return 0;
    }
}

int compileMultiplyInstruction(Instruction *pInstruction)
{
    int compiledInstruction = 0;
    compiledInstruction = compiledInstruction + conditionalBinaryCode(pInstruction->condition);
    compiledInstruction = (unsigned int)compiledInstruction << 7;
    compiledInstruction = compiledInstruction + cmdBinaryCode(pInstruction->instrType);
    compiledInstruction = (unsigned int)compiledInstruction << 1;
    compiledInstruction = (pInstruction->instrType == TST  ||  pInstruction->instrType == TEQ || pInstruction->instrType == CMP || pInstruction->instrType == CMN) ? compiledInstruction + 1 : compiledInstruction + pInstruction->setFlags;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + pInstruction->r_d;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + pInstruction->r_sa;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + pInstruction->r_m;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + 9;
    compiledInstruction = (unsigned int)compiledInstruction << 4;
    compiledInstruction = compiledInstruction + pInstruction->r_n;
    return compiledInstruction;
}

int compileMemoryInstruction(Instruction *pInstruction)
{
    int compiledInstruction = 0;
    compiledInstruction = compiledInstruction + conditionalBinaryCode(pInstruction->condition);
    if(pInstruction->instrType == STR || pInstruction->instrType == LDR || pInstruction->instrType == STRB || pInstruction->instrType == LDRB)
    {
        compiledInstruction = (unsigned int)compiledInstruction << 2;
        compiledInstruction = compiledInstruction + 1;
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = pInstruction->src2Type == IMMEDIATE ? compiledInstruction + 0 : compiledInstruction + 1;
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testIndexMode(pInstruction->indexMode, compiledInstruction, 0);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = pInstruction->addOffset ? compiledInstruction + 1 : compiledInstruction + 0;
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testMemoryInstruction(pInstruction->instrType, compiledInstruction, 1);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testIndexMode(pInstruction->indexMode, compiledInstruction, 1);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testMemoryInstruction(pInstruction->instrType, compiledInstruction, 0);
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_n;
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_d;
        if(pInstruction->src2Type == IMMEDIATE)
        {
            compiledInstruction = (unsigned int)compiledInstruction << 12;
            compiledInstruction = compiledInstruction + pInstruction->imm_shmt;
            return compiledInstruction;
        }
        else
        {
            compiledInstruction = (unsigned int)compiledInstruction << 5;
            compiledInstruction = compiledInstruction + pInstruction->imm_shmt;
            compiledInstruction = (unsigned int)compiledInstruction << 2;
            if(pInstruction->shift_type == LSR)
            {
                compiledInstruction = compiledInstruction + 1;
            }
            else if(pInstruction->shift_type == ASR)
            {
                compiledInstruction = compiledInstruction + 2;
            }
            else if(pInstruction->shift_type == ROR)
            {
                compiledInstruction = compiledInstruction + 3;
            }
            else
            {
                compiledInstruction = compiledInstruction + 0;
            }
            compiledInstruction = (unsigned int)compiledInstruction << 1;
            compiledInstruction = compiledInstruction + 1;
            compiledInstruction = (unsigned int)compiledInstruction << 4;
            compiledInstruction = compiledInstruction + pInstruction->r_m;
            return compiledInstruction;
        }
    }
    else
    {
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = testIndexMode(pInstruction->indexMode, compiledInstruction, 0);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = pInstruction->addOffset ? compiledInstruction + 1 : compiledInstruction + 0;
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = pInstruction->src2Type == IMMEDIATE ? compiledInstruction + 1 : compiledInstruction + 0;
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testIndexMode(pInstruction->indexMode, compiledInstruction, 1);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testMemoryInstruction(pInstruction->instrType, compiledInstruction, 0);
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_n;
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_d;
        if(pInstruction->src2Type == IMMEDIATE)
        {
            compiledInstruction = (unsigned int)compiledInstruction << 4;
            compiledInstruction = compiledInstruction + ((unsigned int)pInstruction->imm_shmt >> 4);
            compiledInstruction = (unsigned int)compiledInstruction << 1;
            compiledInstruction = compiledInstruction + 1;
            compiledInstruction = (unsigned int)compiledInstruction << 2;
            compiledInstruction = testOperationTwoInstruction(pInstruction->instrType, compiledInstruction);
            compiledInstruction = (unsigned int)compiledInstruction << 1;
            compiledInstruction = compiledInstruction + 1;
            compiledInstruction = (unsigned int)compiledInstruction << 4;
            compiledInstruction = compiledInstruction + ((unsigned int)((unsigned int)pInstruction->imm_shmt << 28) >> 28);
            return compiledInstruction;
        }
        else
        {
            compiledInstruction = (unsigned int)compiledInstruction << 5;
            compiledInstruction = compiledInstruction + 1;
            compiledInstruction = (unsigned int)compiledInstruction << 2;
            compiledInstruction = testOperationTwoInstruction(pInstruction->instrType, compiledInstruction);
            compiledInstruction = (unsigned int)compiledInstruction << 1;
            compiledInstruction = compiledInstruction + 1;
            compiledInstruction = (unsigned int)compiledInstruction << 4;
            compiledInstruction = compiledInstruction + pInstruction->r_m;
            return compiledInstruction;
        }
    }
}

int testOperationTwoInstruction(int pInstruction, int pValue)
{
    if(pInstruction == STRH)
    {
        return pValue + 1;
    }
    else if(pInstruction == LDRH)
    {
        return pValue + 1;
    }
    else if(pInstruction == LDRSB)
    {
        return pValue + 2;
    }
    else if(pInstruction == LDRSH)
    {
        return pValue + 3;
    }
    else
    {
        return 0;
    }
}

int testMemoryInstruction(int pInstruction, int pValue, int pControlFlag)
{
    if(pInstruction == STR)
    {
        return pValue;
    }
    else if(pInstruction == STRB)
    {
        int result = pControlFlag == 0 ? pValue + 0 : pValue + 1;
        return result;
    }
    else if(pInstruction == LDR)
    {
        int result = pControlFlag == 0 ? pValue + 1 : pValue + 0;
        return result;
    }
    else if(pInstruction == LDRB)
    {
        return pValue + 1;
    }
    else
    {
        return 0;
    }
}

int testIndexMode(int pIndexMode, int pValue, int pControlFlag)
{
    if(pIndexMode == POST_INDEX)
    {
        return pValue;
    }
    else if(pIndexMode == OFFSET)
    {
        int result = pControlFlag == 0 ? pValue + 1 : pValue + 0;
        return result;
    }
    else if(pIndexMode == PRE_INDEX)
    {
        return pValue + 1;
    }
    else
    {
        int result = pControlFlag == 0 ? pValue + 0 : pValue + 1;
        return result;
    }
}

int compileBranchInstruction(Instruction *pInstruction)
{
    int compiledInstruction = 0;
    compiledInstruction = compiledInstruction + conditionalBinaryCode(pInstruction->condition);
    compiledInstruction = (unsigned int)compiledInstruction << 2;
    compiledInstruction = compiledInstruction + 2;
    compiledInstruction = (unsigned int)compiledInstruction << 1;
    compiledInstruction = compiledInstruction + 1;
    compiledInstruction = (unsigned int)compiledInstruction << 1;
    compiledInstruction = pInstruction->instrType == B ? compiledInstruction + 0 : compiledInstruction + 1;
    compiledInstruction = (unsigned int)compiledInstruction << 24;
    int PCPLUSTWO = i + 2;
    int BTA = pInstruction->imm_shmt;
    int immediateBranch = BTA - PCPLUSTWO;
    immediateBranch = (unsigned int)((unsigned int)immediateBranch << 8) >> 8;
    compiledInstruction = compiledInstruction + immediateBranch;
    return compiledInstruction;
}
