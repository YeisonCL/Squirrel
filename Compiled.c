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

#include "Compiled.h"
#include "Memory.h"
#include "Registers.h"
#include "Instructions.h"
#include "ARMYacc.tab.h"

const int COMPILE = 0;
const int COMPILEANDSIMULE = 1;

const int START = 1;
const int END = 0;

int compiledFile = 0;

void writeHeader(int pFile);
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
void saveCompiledInstruction(int pTypeCompilation, int pInstruction, int pIndex, int pFile);

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
    //COMPILAR INSTRUCCION
    verifyTypeCompilation(pTypeCompilation, END);
    printf("End compilation...\n");
}

void verifyTypeCompilation(int pTypeCompilation, int pControlFlag)
{
    if(pTypeCompilation == COMPILE && pControlFlag == START)
    {
        compiledFile = open("out.txt", O_RDWR);
        writeHeader(compiledFile);
    }
    if(pTypeCompilation == COMPILE && pControlFlag == END)
    {
        close(compiledFile);
    }
}

void writeHeader(int pFile)
{
    char *header = "*********************************************\n*		Instituto Tecnológico de Costa Rica  *\n*		Ingeniería en Computadores           *\n*		Arquitectura de Computadores         *\n*		I  Semestre 2016                     *\n*		                                     *\n*		Author: Yeison Cruz León             *\n*               Joseph Cruz Loaiza           *\n*		Carne: 201258348                     *\n*              201258359                     *\n**********************************************\n\n\n";
    write(pFile, header, strlen(header));
}

void saveCompiledInstruction(int pTypeCompilation, int pInstruction, int pIndex, int pFile)
{
    if(pTypeCompilation == COMPILE)
    {
        char *instructionStr = 0;
        char *indexStr = 0;
        sprintf(instructionStr, "%u", pInstruction);
        sprintf(indexStr, "%d", pIndex);
        strcat(indexStr, "\t");
        strcat(instructionStr, "\n");
        write(pFile, indexStr, strlen(indexStr));
        write(pFile, instructionStr, strlen(instructionStr));
    }
    else
    {
        _memory[pIndex] = pInstruction;
    }
}

int compileInstruction(Instruction *pInstruction)
{
    if(pInstruction->instruction == AND || pInstruction->instruction == EOR || pInstruction->instruction == SUB || pInstruction->instruction == RSB ||
            pInstruction->instruction == ADD || pInstruction->instruction == ADC || pInstruction->instruction == SBC || pInstruction->instruction == RSC ||
            pInstruction->instruction == TST || pInstruction->instruction == TEQ || pInstruction->instruction == CMP || pInstruction->instruction == CMN ||
            pInstruction->instruction == ORR || pInstruction->instruction == MOV || pInstruction->instruction == LSL || pInstruction->instruction == LSR ||
            pInstruction->instruction == ASR || pInstruction->instruction == RRX || pInstruction->instruction == ROR || pInstruction->instruction == BIC ||
            pInstruction->instruction == MVN)
    {
        return compileDataProcessingInstruction(pInstruction);
    }
    else if(pInstruction->instruction == MUL || pInstruction->instruction == MLA || pInstruction->instruction == UMULL || pInstruction->instruction == UMLAL ||
            pInstruction->instruction == SMULL || pInstruction->instruction == SMLAL)
    {
        return compileMultiplyInstruction(pInstruction);
    }
    else if(pInstruction->instruction == STR || pInstruction->instruction == LDR || pInstruction->instruction == STRB || pInstruction->instruction == LDRB ||
            pInstruction->instruction == STRH || pInstruction->instruction == LDRH || pInstruction->instruction == LDRSB || pInstruction->instruction == LDRSH)
    {
        return compileMemoryInstruction(pInstruction);
    }
    else if(pInstruction->instruction == B || pInstruction->instruction == BL)
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
    compiledInstruction = compiledInstruction + cmdBinaryCode(pInstruction->instruction);
    compiledInstruction = (unsigned int)compiledInstruction << 1;
    compiledInstruction = (pInstruction->instruction == TST  ||  pInstruction->instruction == TEQ || pInstruction->instruction == CMP || pInstruction->instruction == CMN) ? compiledInstruction + 1 : compiledInstruction + pInstruction->setFlags;
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
        if(pInstruction->instruction == LSR)
        {
            compiledInstruction = compiledInstruction + 1;
        }
        else if(pInstruction->instruction == ASR)
        {
            compiledInstruction = compiledInstruction + 2;
        }
        else if(pInstruction->instruction == RRX)
        {
            compiledInstruction = (unsigned int)compiledInstruction >> 7;
            compiledInstruction = (unsigned int)compiledInstruction << 7;
            compiledInstruction = compiledInstruction + 3;
        }
        else if(pInstruction->instruction == LSR)
        {
            compiledInstruction = compiledInstruction + 3;
        }
        else
        {
            compiledInstruction = compiledInstruction + pInstruction->shift_type;
        }
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_m;
        return compiledInstruction;
    }
    else if(pInstruction->src2Type == REG_REG)
    {
        compiledInstruction = (unsigned int)compiledInstruction << 4;
        compiledInstruction = compiledInstruction + pInstruction->r_sa;
        compiledInstruction = (unsigned int)compiledInstruction << 3;
        if(pInstruction->instruction == LSR)
        {
            compiledInstruction = compiledInstruction + 1;
        }
        else if(pInstruction->instruction == ASR)
        {
            compiledInstruction = compiledInstruction + 2;
        }
        else if(pInstruction->instruction == RRX)
        {
            compiledInstruction = (unsigned int)compiledInstruction >> 7;
            compiledInstruction = (unsigned int)compiledInstruction << 7;
            compiledInstruction = compiledInstruction + 3;
        }
        else if(pInstruction->instruction == LSR)
        {
            compiledInstruction = compiledInstruction + 3;
        }
        else
        {
            compiledInstruction = compiledInstruction + pInstruction->shift_type;
        }
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = pInstruction->instruction == RRX ? compiledInstruction + 0 : compiledInstruction + 1;
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
    compiledInstruction = compiledInstruction + cmdBinaryCode(pInstruction->instruction);
    compiledInstruction = (unsigned int)compiledInstruction << 1;
    compiledInstruction = (pInstruction->instruction == TST  ||  pInstruction->instruction == TEQ || pInstruction->instruction == CMP || pInstruction->instruction == CMN) ? compiledInstruction + 1 : compiledInstruction + pInstruction->setFlags;
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
    if(pInstruction->instruction == STR || pInstruction->instruction == LDR || pInstruction->instruction == STRB || pInstruction->instruction == LDRB)
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
        compiledInstruction = testMemoryInstruction(pInstruction->instruction, compiledInstruction, 1);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testIndexMode(pInstruction->indexMode, compiledInstruction, 1);
        compiledInstruction = (unsigned int)compiledInstruction << 1;
        compiledInstruction = testMemoryInstruction(pInstruction->instruction, compiledInstruction, 0);
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
            compiledInstruction = compiledInstruction + pInstruction->shift_type;
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
        compiledInstruction = testMemoryInstruction(pInstruction->instruction, compiledInstruction, 0);
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
            compiledInstruction = testOperationTwoInstruction(pInstruction->instruction, compiledInstruction);
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
            compiledInstruction = testOperationTwoInstruction(pInstruction->instruction, compiledInstruction);
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
        return 0;
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
        return 1;
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
        return 0;
    }
    else if(pIndexMode == OFFSET)
    {
        int result = pControlFlag == 0 ? pValue + 1 : pValue + 0;
        return result;
    }
    else if(pIndexMode == PRE_INDEX)
    {
        return 1;
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
    compiledInstruction = pInstruction->instruction == B ? compiledInstruction + 0 : compiledInstruction + 1;
    compiledInstruction = (unsigned int)compiledInstruction << 24;
    int PCPLUSTWO = *(_registers._R15) + 2;
    int BTA = pInstruction->imm_shmt;
    int immediateBranch = BTA - PCPLUSTWO;
    immediateBranch = (unsigned int)((unsigned int)immediateBranch << 8) >> 8;
    compiledInstruction = compiledInstruction + immediateBranch;
    return compiledInstruction;
}
