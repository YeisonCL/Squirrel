#include "Instructions.h"

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


Instruction *dataImmInstr(int pInstruction, int pCond, int pSetFlags, int pRn, int pRd, int pImm, int pRot, int pImmSeed){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= IMMEDIATE; 			// Se trata de una operación con inmediato
	inst->condition 	= pCond;
	inst->setFlags 		= pSetFlags;
	inst->r_n 			= pRn;
	inst->r_d 			= pRd;
	inst->imm_shmt 		= pImm;
	inst->rot 			= pRot;
	inst->immSeed 		= pImmSeed;
	return inst;
}

Instruction *dataRegShmtInstr(int pInstruction, int pCond, int pSetFlags, int pRn, int pRd, int pShamnt, int pShiftType, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= REG_IMM; 			// se trata de una instruccion con shift por inmediato (shamnt)
	inst->condition 	= pCond;
	inst->setFlags 		= pSetFlags;
	inst->r_n 			= pRn;
	inst->r_d 			= pRd;
	inst->imm_shmt 		= pShamnt;
	inst->shift_type 	= pShiftType;
	inst->r_m 			= pRm;
	return inst;
}

Instruction *dataRegRegInstr(int pInstruction, int pCond, int pSetFlags, int pRn, int pRd, int pRs, int pShiftType, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= REG_REG; 			// se trata de una instruccion con shift registro - registro
	inst->condition 	= pCond;
	inst->setFlags 		= pSetFlags;
	inst->r_n 			= pRn;
	inst->r_d 			= pRd;
	inst->r_sa			= pRs;
	inst->shift_type 	= pShiftType;
	inst->r_m 			= pRm;
	return inst;
}

Instruction *multiplyInstr(int pInstruction, int pCond, int pSetFlags, int pRd, int pRa, int pRm, int pRn){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->condition 	= pCond;
	inst->setFlags 		= pSetFlags;
	inst->r_d 			= pRd;
	inst->r_sa 			= pRa;
	inst->r_m 			= pRm;
	inst->r_n 			= pRn;
	return inst;
}

Instruction *memImmInstr(int pInstruction, int pCond, int pAddOffset, int pIndexMode, int pRn, int pRd, int pImm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= IMMEDIATE; 			// se trata de una instruccion con inmediato
	inst->condition 	= pCond;
	inst->addOffset 	= pAddOffset;
	inst->indexMode 	= pIndexMode;
	inst->r_n 			= pRn;
	inst->r_d			= pRd;
	inst->imm_shmt 		= pImm;
	return inst;
}

Instruction *memRegInstr(int pInstruction, int pCond, int pAddOffset, int pIndexMode, int pRn, int pRd, int pShamnt, int pShiftType, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= REG_REG; 			// se trata de una instruccion con registros
	inst->condition 	= pCond;
	inst->addOffset 	= pAddOffset;
	inst->indexMode 	= pIndexMode;
	inst->r_n 			= pRn;
	inst->r_d 			= pRd;
    inst->imm_shmt 		= pShamnt;
	inst->shift_type 	= pShiftType;
	inst->r_m 			= pRm;
	return inst;
}

Instruction *extraMemImmInstr(int pInstruction, int pCond, int pAddOffset, int pIndexMode, int pRn, int pRd, int pImm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= IMMEDIATE; 		// se trata de una instruccion con inmediato
	inst->addOffset 	= pAddOffset;
    inst->indexMode 	= pIndexMode;
	inst->r_n 			= pRn;
	inst->r_d 			= pRd;
	inst->imm_shmt 		= pImm;
    inst->condition     = pCond;
	return inst;
}

Instruction *extraMemRegInstr(int pInstruction, int pCond, int pAddOffset, int pIndexMode, int pRn, int pRd, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->src2Type 		= REG_REG; 			// se trata de una instruccion con registros
	inst->condition 	= pCond;
	inst->addOffset 	= pAddOffset;
	inst->indexMode 	= pIndexMode;
	inst->r_n 			= pRn;
	inst->r_d 			= pRd;
	inst->r_m 			= pRm;
	return inst;
}

Instruction *branchInstr(int pInstruction, int pCond, int pImm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
	inst->instruction 	= pInstruction; 
	// Definir las variables necesarias
	inst->condition 	= pCond;
	inst->imm_shmt 		= pImm;
	return inst;
}

RotInfo *valDataImm(int pImm) {
	int rot = 0;
	int val = pImm;
	
	while (val <= 255 && rot < 30) { 		// El inmediato tiene un tamaño de 8 bits -> 255 es la maxima representación. Para rot 30 es el maximo.
		rot += 2; 							// La rotación en ARM se hace en multiplos de 2
        val = (pImm<<rot) + (pImm>>(32-rot)); 	// Rotacion a la izquierda
	}
	
	if (val > 255)
		return 0;

    RotInfo *info 	= (RotInfo *) malloc (sizeof(RotInfo));
	info->rot 		= rot/2;
	info->seed 		= val;
	return info;
}
