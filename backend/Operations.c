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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "Registers.h"
#include "Configuration.h"
#include "Operations.h"
#include "ConditionFlags.h"
#include "MemoryData.h"
#include "ParserMiscellaneous.h"
#include "ARMYacc.tab.h"

void ANDInstructionAux(Instruction *pInstruction, int *pRd);
void EORInstructionAux(Instruction *pInstruction, int *pRd);
void SUBInstructionAux(Instruction *pInstruction, int *pRd);
void ADDInstructionAux(Instruction *pInstruction, int *pRd);
void RSBInstructionAux(Instruction *pInstruction);
void ORRInstructionAux(Instruction *pInstruction);
void MOVInstructionAux(Instruction *pInstruction);
void LSLInstructionAux(Instruction *pInstruction);
void LSRInstructionAux(Instruction *pInstruction);
void ASRInstructionAux(Instruction *pInstruction);
void RORInstructionAux(Instruction *pInstruction);
void BICInstructionAux(Instruction *pInstruction);
void MVNInstructionAux(Instruction *pInstruction);
void RRXInstructionAux(Instruction *pInstruction);
void MULInstructionAux(Instruction *pInstruction);
void MLAInstructionAux(Instruction *pInstruction);
void UMULLInstructionAux(Instruction *pInstruction);
void UMLALInstructionAux(Instruction *pInstruction);
void SMULLInstructionAux(Instruction *pInstruction);
void SMLALInstructionAux(Instruction *pInstruction);
void STRInstructionAux(Instruction *pInstruction);
void LDRInstructionAux(Instruction *pInstruction);
void STRBInstructionAux(Instruction *pInstruction);
void LDRBInstructionAux(Instruction *pInstruction);
void STRHInstructionAux(Instruction *pInstruction);
void LDRHInstructionAux(Instruction *pInstruction);
void LDRSBInstructionAux(Instruction *pInstruction);
void LDRSHInstructionAux(Instruction *pInstruction);
void verifyCarryAndOverflowADD(int pSetFlags, unsigned int pOperatorOne, unsigned int pOperatorTwo);
void verifyCarryAndOverflowSUB(int pSetFlags, unsigned int pOperatorOne, unsigned int pOperatorTwo);

/*Data Procesing Instructions*/

void verifyCarryAndOverflowADD(int pSetFlags, unsigned int pOperatorOne, unsigned int pOperatorTwo)
{
    if(pSetFlags)
    {
        unsigned long long detectCarry = (unsigned long long)pOperatorOne + (unsigned long long)pOperatorTwo;
        _carry = detectCarry >> 32 == 0 ? 0 : 1;
        int conditionOne = (unsigned int)detectCarry >> 31 != (unsigned int)pOperatorOne >> 31 ? 1 : 0;
        int conditionTwo = (unsigned int)pOperatorOne >> 31 == (unsigned int)pOperatorTwo >> 31 ? 1 : 0;
        _overflow = conditionOne && conditionTwo;
    }
}

void verifyCarryAndOverflowSUB(int pSetFlags, unsigned int pOperatorOne, unsigned int pOperatorTwo)
{
    if(pSetFlags)
    {
        unsigned long long detectCarry = (unsigned long long)pOperatorOne + (unsigned long long)(~pOperatorTwo + 1);
        _carry = detectCarry >> 32 == 0 ? 0 : 1;
        int conditionOne = (unsigned int)detectCarry >> 31 != (unsigned int)pOperatorOne >> 31 ? 1 : 0;
        int conditionTwo = (unsigned int)pOperatorOne >> 31 != (unsigned int)pOperatorTwo >> 31 ? 1 : 0;
        _overflow = conditionOne && conditionTwo;
    }
}

void ANDInstruction(Instruction *pInstruction)
{
    ANDInstructionAux(pInstruction, getRegister(pInstruction->r_d));
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void ANDInstructionAux(Instruction *pInstruction, int *pRd)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *pRd= *(getRegister(pInstruction->r_n)) & pInstruction->imm_shmt;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) & newValueRegister;
    }
    else
    {
        ;
    }
}

void EORInstruction(Instruction *pInstruction)
{
    EORInstructionAux(pInstruction, getRegister(pInstruction->r_d));
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void EORInstructionAux(Instruction *pInstruction, int *pRd)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *pRd = *(getRegister(pInstruction->r_n)) ^ pInstruction->imm_shmt;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) ^ newValueRegister;
    }
    else
    {
        ;
    }
}

void SUBInstruction(Instruction *pInstruction)
{
    SUBInstructionAux(pInstruction, getRegister(pInstruction->r_d));
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void SUBInstructionAux(Instruction *pInstruction, int *pRd)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *pRd = *(getRegister(pInstruction->r_n)) - pInstruction->imm_shmt;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), pInstruction->imm_shmt);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) - newValueRegister;
        verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else
    {
        ;
    }
}

void RSBInstruction(Instruction *pInstruction)
{
    RSBInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void RSBInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *(getRegister(pInstruction->r_d)) =  pInstruction->imm_shmt - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, pInstruction->imm_shmt, *(getRegister(pInstruction->r_n)));

    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *(getRegister(pInstruction->r_d)) = newValueRegister - *(getRegister(pInstruction->r_n));
        verifyCarryAndOverflowSUB(pInstruction->setFlags, newValueRegister, *(getRegister(pInstruction->r_n)));
    }
    else
    {
        ;
    }
}

void ADDInstruction(Instruction *pInstruction)
{
    ADDInstructionAux(pInstruction, getRegister(pInstruction->r_d));
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void ADDInstructionAux(Instruction *pInstruction, int *pRd)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *pRd = *(getRegister(pInstruction->r_n)) + pInstruction->imm_shmt;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), pInstruction->imm_shmt);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *pRd = *(getRegister(pInstruction->r_n)) + newValueRegister;
        verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_n)), newValueRegister);
    }
    else
    {
        ;
    }
}

void ADCInstruction(Instruction *pInstruction)
{
    ADDInstructionAux(pInstruction, getRegister(pInstruction->r_d));
    verifyCarryAndOverflowADD(pInstruction->setFlags, *(getRegister(pInstruction->r_d)), _carry);
    *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_d)) + _carry;
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void SBCInstruction(Instruction *pInstruction)
{
    SUBInstructionAux(pInstruction, getRegister(pInstruction->r_d));
    verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_d)), !_carry);
    *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_d)) - !_carry;
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void RSCInstruction(Instruction *pInstruction)
{
    RSBInstructionAux(pInstruction);
    verifyCarryAndOverflowSUB(pInstruction->setFlags, *(getRegister(pInstruction->r_d)), !_carry);
    *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_d)) - !_carry;
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

/*Begin Set flags default*/

void TSTInstruction(Instruction *pInstruction)
{
    int *result = (int*) calloc(1, sizeof (int));
    ANDInstructionAux(pInstruction, result);
    _carry = 0;
    _zero = result == 0 ? 1 : 0;
    _negative = (int)((unsigned int)*result >> 31) == 0 ? 0 : 1;
    free(result);
}

void TEQInstruction(Instruction *pInstruction)
{
    int *result = (int*) calloc(1, sizeof (int));
    EORInstructionAux(pInstruction, result);
    _carry = 0;
    _zero = result == 0 ? 1 : 0;
    _negative = (int)((unsigned int)*result >> 31) == 0 ? 0 : 1;
    free(result);
}

void CMPInstruction(Instruction *pInstruction)
{
    int *result = (int*) calloc(1, sizeof (int));
    pInstruction->setFlags = 1;
    SUBInstructionAux(pInstruction, result);
    _zero = *result == 0 ? 1 : 0;
    _negative = (int)((unsigned int)*result >> 31) == 0 ? 0 : 1;
    free(result);
}

void CMNInstruction(Instruction *pInstruction)
{
    int *result = (int*) calloc(1, sizeof (int));
    pInstruction->setFlags = 1;
    ADDInstructionAux(pInstruction, result);
    _zero = *result == 0 ? 1 : 0;
    _negative = (int)((unsigned int)*result >> 31) == 0 ? 0 : 1;
    free(result);
}

/*End Set flags default*/

void ORRInstruction(Instruction *pInstruction)
{
    ORRInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void ORRInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | pInstruction->imm_shmt;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) | newValueRegister;
    }
    else
    {
        ;
    }
}

void MOVInstruction(Instruction *pInstruction)
{
    MOVInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void MOVInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *(getRegister(pInstruction->r_d)) = pInstruction->imm_shmt;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *(getRegister(pInstruction->r_d)) = newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = shiftOne + shiftTwo;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *(getRegister(pInstruction->r_d)) = newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        *(getRegister(pInstruction->r_d)) = shiftOne + shiftTwo;
    }
    else
    {
        ;
    }
}

void LSLInstruction(Instruction *pInstruction)
{
    LSLInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void LSLInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == REG_IMM)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
    }
    else if(pInstruction->src2Type == REG_REG)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->r_sa);
    }
    else
    {
        ;
    }
}

void LSRInstruction(Instruction *pInstruction)
{
    LSRInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void LSRInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == REG_IMM)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
    }
    else if(pInstruction->src2Type == REG_REG)
    {
        *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
    }
    else
    {
        ;
    }
}

void ASRInstruction(Instruction *pInstruction)
{
    ASRInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void ASRInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == REG_IMM)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *(getRegister(pInstruction->r_d)) = newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->r_sa;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        }
        *(getRegister(pInstruction->r_d)) = newValueRegister;
    }
    else
    {
        ;
    }
}

void RRXInstruction(Instruction *pInstruction)
{
    RRXInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void RRXInstructionAux(Instruction *pInstruction)
{
    *(getRegister(pInstruction->r_d)) = (int)((unsigned int)*(getRegister(pInstruction->r_d)) >> 1);
    if(_carry)
    {
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_d)) ^ 2147483648;
    }
    else
    {
        ;
    }
}

void RORInstruction(Instruction *pInstruction)
{
    RORInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void RORInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == REG_IMM)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d))  = shiftOne + shiftTwo;;
    }
    else if(pInstruction->src2Type == REG_REG)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        *(getRegister(pInstruction->r_d))  = shiftOne + shiftTwo;;
    }
    else
    {
        ;
    }
}

void BICInstruction(Instruction *pInstruction)
{
    BICInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void BICInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~pInstruction->imm_shmt;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int newValueRegister = shiftOne + shiftTwo;
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa)));
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        int newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        int newValueRegister = shiftOne + shiftTwo;
        *(getRegister(pInstruction->r_d)) = *(getRegister(pInstruction->r_n)) & ~newValueRegister;
    }
    else
    {
        ;
    }
}

void MVNInstruction(Instruction *pInstruction)
{
    MVNInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _carry = 0;
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void MVNInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        *(getRegister(pInstruction->r_d)) = ~pInstruction->imm_shmt;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        *(getRegister(pInstruction->r_d)) = ~((int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt));
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        *(getRegister(pInstruction->r_d)) = ~((int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt));
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt;
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        }
        *(getRegister(pInstruction->r_d)) = ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        *(getRegister(pInstruction->r_d)) = ~(shiftOne + shiftTwo);
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSL)
    {
        *(getRegister(pInstruction->r_d)) = ~((int)((unsigned int)*(getRegister(pInstruction->r_m)) << *(getRegister(pInstruction->r_sa))));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == LSR)
    {
        *(getRegister(pInstruction->r_d)) = ~((int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa))));
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ASR)
    {
        int newValueRegister = 0;
        if(*(getRegister(pInstruction->r_m)) < 0)
        {
            newValueRegister = *(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa));
        }
        else
        {
            newValueRegister = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> *(getRegister(pInstruction->r_sa)));
        }
        *(getRegister(pInstruction->r_d)) = ~newValueRegister;
    }
    else if(pInstruction->src2Type == REG_REG && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->r_sa));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->r_sa);
        *(getRegister(pInstruction->r_d)) = ~(shiftOne + shiftTwo);
    }
    else
    {
        ;
    }
}


/*Multiply Instructions*/

void MULInstruction(Instruction *pInstruction)
{
    MULInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void MULInstructionAux(Instruction *pInstruction)
{
     long long newValueRegister = *(getRegister(pInstruction->r_n)) * *(getRegister(pInstruction->r_m));
    *(getRegister(pInstruction->r_d)) = (unsigned int)newValueRegister;
}

void MLAInstruction(Instruction *pInstruction)
{
    MLAInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = *getRegister(pInstruction->r_d) == 0 ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_d) >> 31) == 0 ? 0 : 1;
    }
}

void MLAInstructionAux(Instruction *pInstruction)
{
    long long newValueRegister = (*(getRegister(pInstruction->r_n)) * *(getRegister(pInstruction->r_m))) + *(getRegister(pInstruction->r_sa));
    *(getRegister(pInstruction->r_d)) = (unsigned int)newValueRegister;
}

void UMULLInstruction(Instruction *pInstruction)
{
    UMULLInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = (*getRegister(pInstruction->r_d) == 0 &&  *getRegister(pInstruction->r_sa) == 0) ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_sa) >> 31) == 0 ? 0 : 1;
    }
}

void UMULLInstructionAux(Instruction *pInstruction)
{
    long long newValueRegister = (unsigned int)*(getRegister(pInstruction->r_n)) * (unsigned int)*(getRegister(pInstruction->r_m));
    *(getRegister(pInstruction->r_d)) = (unsigned int)newValueRegister; //LSB
    newValueRegister = (unsigned long long)newValueRegister >> 32;
    *(getRegister(pInstruction->r_sa)) = (unsigned int)newValueRegister; //MSB
}

void UMLALInstruction(Instruction *pInstruction)
{
    UMLALInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = (*getRegister(pInstruction->r_d) == 0 &&  *getRegister(pInstruction->r_sa) == 0) ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_sa) >> 31) == 0 ? 0 : 1;
    }
}

void UMLALInstructionAux(Instruction *pInstruction)
{

    long long newValueRegister = (unsigned int)*(getRegister(pInstruction->r_n)) * (unsigned int)*(getRegister(pInstruction->r_m));
    *(getRegister(pInstruction->r_d)) = (unsigned int)newValueRegister + *(getRegister(pInstruction->r_d)); //LSB
    newValueRegister = (unsigned long long)newValueRegister >> 32;
    *(getRegister(pInstruction->r_sa)) = (unsigned int)newValueRegister + *(getRegister(pInstruction->r_sa)) ; //MSB
}

void SMULLInstruction(Instruction *pInstruction)
{
    SMULLInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = (*getRegister(pInstruction->r_d) == 0 &&  *getRegister(pInstruction->r_sa) == 0) ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_sa) >> 31) == 0 ? 0 : 1;
    }
}

void SMULLInstructionAux(Instruction *pInstruction)
{
    long long newValueRegister = *(getRegister(pInstruction->r_n)) * *(getRegister(pInstruction->r_m));
    *(getRegister(pInstruction->r_d)) = (int)newValueRegister; //LSB
    newValueRegister = (unsigned long long)newValueRegister >> 32;
    *(getRegister(pInstruction->r_sa)) = (int)newValueRegister; //MSB
}

void SMLALInstruction(Instruction *pInstruction)
{
    SMLALInstructionAux(pInstruction);
    if(pInstruction->setFlags)
    {
        _zero = (*getRegister(pInstruction->r_d) == 0 &&  *getRegister(pInstruction->r_sa) == 0) ? 1 : 0;
        _negative = (int)((unsigned int)*getRegister(pInstruction->r_sa) >> 31) == 0 ? 0 : 1;
    }
}

void SMLALInstructionAux(Instruction *pInstruction)
{
    long long newValueRegister = *(getRegister(pInstruction->r_n)) * *(getRegister(pInstruction->r_m));
    *(getRegister(pInstruction->r_d)) = (int)newValueRegister + *(getRegister(pInstruction->r_d)); //LSB
    newValueRegister = (unsigned long long)newValueRegister >> 32;
    *(getRegister(pInstruction->r_sa)) = (int)newValueRegister + *(getRegister(pInstruction->r_sa)) ; //MSB
}

/*Memory Instructions*/

void STRInstruction(Instruction *pInstruction)
{
    STRInstructionAux(pInstruction);
}

void STRInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[(*getRegister(pInstruction->r_n))/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[(*getRegister(pInstruction->r_n))/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[(*getRegister(pInstruction->r_n))/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[(*getRegister(pInstruction->r_n))/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[address/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                _memory[(*getRegister(pInstruction->r_n))/4] = *getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void LDRInstruction(Instruction *pInstruction)
{
    LDRInstructionAux(pInstruction);
}

void LDRInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[(*getRegister(pInstruction->r_n))/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[(*getRegister(pInstruction->r_n))/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[(*getRegister(pInstruction->r_n))/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[(*getRegister(pInstruction->r_n))/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[address/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if(((*getRegister(pInstruction->r_n)) % 4) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if((*getRegister(pInstruction->r_n)) < _dataMemStart || (*getRegister(pInstruction->r_n)) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                *getRegister(pInstruction->r_d) = _memory[(*getRegister(pInstruction->r_n))/4];
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void STRBInstruction(Instruction *pInstruction)
{
    STRBInstructionAux(pInstruction);
}

void STRBInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *memInByte = (unsigned char)*getRegister(pInstruction->r_d);
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void LDRBInstruction(Instruction *pInstruction)
{
    LDRBInstructionAux(pInstruction);
}

void LDRBInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {                        
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            unsigned char *memInByte = (unsigned char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void STRHInstruction(Instruction *pInstruction)
{
    STRHInstructionAux(pInstruction);
}

void STRHInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *memInByte = (unsigned short)*getRegister(pInstruction->r_d);
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void LDRHInstruction(Instruction *pInstruction)
{
    LDRHInstructionAux(pInstruction);
}

void LDRHInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                unsigned short *memInByte = (unsigned short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void LDRSBInstruction(Instruction *pInstruction)
{
    LDRSBInstructionAux(pInstruction);
}

void LDRSBInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+address/4) + address%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            char *memInByte = (char *)((unsigned char*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
            *getRegister(pInstruction->r_d) = *memInByte;
            *getRegister(pInstruction->r_n) = address;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void LDRSHInstruction(Instruction *pInstruction)
{
    LDRSHInstructionAux(pInstruction);
}

void LDRSHInstructionAux(Instruction *pInstruction)
{
    if(pInstruction->src2Type == IMMEDIATE)
    {
        int address = pInstruction->addOffset == 1 ?  *getRegister(pInstruction->r_n) + pInstruction->imm_shmt : *getRegister(pInstruction->r_n) - pInstruction->imm_shmt;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSL)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) << pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == LSR)
    {
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt) : *getRegister(pInstruction->r_n) - (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ASR)
    {
        int newValueRegister = *(getRegister(pInstruction->r_m)) < 0 ? *(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt : (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + newValueRegister :  *getRegister(pInstruction->r_n) - newValueRegister;
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else if(pInstruction->src2Type == REG_IMM && pInstruction->shift_type == ROR)
    {
        int shiftOne = (int)((unsigned int)*(getRegister(pInstruction->r_m)) << (32 - pInstruction->imm_shmt));
        int shiftTwo = (int)((unsigned int)*(getRegister(pInstruction->r_m)) >> pInstruction->imm_shmt);
        int address = pInstruction->addOffset == 1 ? *getRegister(pInstruction->r_n) + (shiftOne + shiftTwo) : *getRegister(pInstruction->r_n) - (shiftOne + shiftTwo);
        if(pInstruction->indexMode == OFFSET)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
            }
        }
        else if(pInstruction->indexMode == PRE_INDEX)
        {
            if((address % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(address < _dataMemStart || address >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+address/4) + address%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else if(pInstruction->indexMode == POST_INDEX)
        {
            if((*getRegister(pInstruction->r_n) % 2) != 0)
            {
                printf("Execution error: Address not aligned.\n");
                _executionError = 1;
            }
            else if(*getRegister(pInstruction->r_n) < _dataMemStart || *getRegister(pInstruction->r_n) >= (_dataMemStart + _dataMemSize))
            {
                printf("Execution error: Address out of bound.\n");
                _executionError = 1;
            }
            else
            {
                short *memInByte = (short *)((unsigned short*)(_memory+*getRegister(pInstruction->r_n)/4) + *getRegister(pInstruction->r_n)%4);
                *getRegister(pInstruction->r_d) = *memInByte;
                *getRegister(pInstruction->r_n) = address;
            }
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

/*Branch Instructions*/

void BInstruction(Instruction *pInstruction)
{
    *(_registers._R15) = pInstruction->imm_shmt;
}
void BLInstruction(Instruction *pInstruction)
{
    *(_registers._R14) = *(_registers._R15) + 1;
    *(_registers._R15) = pInstruction->imm_shmt;
}

#ifdef __cplusplus
}
#endif
