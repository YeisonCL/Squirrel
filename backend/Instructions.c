#ifdef __cplusplus
extern "C" {
#endif

#include "Instructions.h"
#include "ParserMiscellaneous.h"
#include "ARMYacc.tab.h"
#include <stdlib.h>
#include <stdio.h>

const int EQ = 0;
const int NE = 1;

const int CS = 2;
const int HS = 2;

const int CC = 3;
const int LO = 3;

const int MI = 4;
const int PL = 5;
const int VS = 6;
const int VC = 7;
const int HI = 8;
const int LS = 9;
const int GE = 10;
const int LT = 11;
const int GT = 12;
const int LE = 13;
const int AL = 14;

const int POST_INDEX 	= 0;
const int OFFSET 		= 1;
const int PRE_INDEX 	= 2;

const int IMMEDIATE = 0;
const int REG_IMM 	= 1;
const int REG_REG 	= 2;

const int R0 	= 0;
const int R1 	= 1;
const int R2 	= 2;
const int R3 	= 3;
const int R4 	= 4;
const int R5 	= 5;
const int R6 	= 6;
const int R7 	= 7;
const int R8 	= 8;
const int R9 	= 9;
const int R10 	= 10;
const int R11 	= 11;
const int R12 	= 12;

const int R13 	= 13;
const int R14 	= 14;
const int R15 	= 15;

const int SP 	= 13;
const int LR 	= 14;
const int PC 	= 15;

const int POSITIVE_SIGN = 1;
const int NEGATIVE_SIGN = 0;

const char *getInstLit(int pInstCode){
    switch (pInstCode) {
    case AND:
        return "and";
        break;
    case EOR:
        return "eor";
        break;
    case SUB:
        return "sub";
        break;
    case RSB:
        return "rsb";
        break;
    case ADD:
        return "add";
        break;
    case ADC:
        return "adc";
        break;
    case SBC:
        return "sbc";
        break;
    case RSC:
        return "rsc";
        break;
    case TST:
        return "tst";
        break;
    case TEQ:
        return "teq";
        break;
    case CMP:
        return "cmp";
        break;
    case CMN:
        return "cmn";
        break;
    case ORR:
        return "orr";
        break;
    case MOV:
        return "mov";
        break;
    case LSL:
        return "lsl";
        break;
    case LSR:
        return "lsr";
        break;
    case ASR:
        return "asr";
        break;
    case RRX:
        return "rrx";
        break;
    case ROR:
        return "ror";
        break;
    case BIC:
        return "bic";
        break;
    case MVN:
        return "mvn";
        break;
    case MUL:
        return "mul";
        break;
    case MLA:
        return "mla";
        break;
    case UMULL:
        return "umull";
        break;
    case UMLAL:
        return "umlal";
        break;
    case SMULL:
        return "smull";
        break;
    case SMLAL:
        return "smlal";
        break;
    case STR:
        return "str";
        break;
    case LDR:
        return "ldr";
        break;
    case STRB:
        return "strb";
        break;
    case LDRB:
        return "ldrb";
        break;
    case STRH:
        return "strh";
        break;
    case LDRH:
        return "ldrh";
        break;
    case LDRSB:
        return "ldrsb";
        break;
    case LDRSH:
        return "ldrsh";
        break;
    case B:
        return "b";
        break;
    case BL:
        return "bl";
        break;
    default:
        printf("Internal error. Root intruction not defined.\n");
        return "";
        break;
    }
}

#ifdef __cplusplus
}
#endif
