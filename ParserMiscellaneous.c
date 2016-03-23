#include "ParserMiscellaneous.h"
#include "Symbols.h"
#include "Instructions.h"
#include "InstructionList.h"
#include "ARMYacc.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int _errors = 0;
extern int yylineno;

/* Esta función se encarga de añadir un nuevo simbolo a la tabla 
*  realizando las validaciones necesarias, estos simbolos corresponden unicamente a labels
*  por lo que se solicita la siguiente instruccion pero no se modifica este puntero, dando así,
*  un puntero a la siguiente instrucción.
*/
void installSymb (char *pIDValue) {
	Symrec *search = getSym(pIDValue); 		// Buscar si el valor existe antes de añadirlo
	if (search == 0)
		addSym(pIDValue);					// Si no existe añadirlo, sino error.
	else {
        _errors++;
        printf("line: %d. CONTEXT ERROR: The identifier \"%s\" is already defined.\n", yylineno, pIDValue);
	}
}

void installRef(InstWrap pInst, char *pLabel, int pSourceLine){
    Instruction *instr = (Instruction *)malloc(sizeof(Instruction));    // Crear la instrucción
    instr->instrType    = pInst.instrCode;                              // Tipo de branch

    //INSTRUCCION QUE PIDE LA RAÍZ
    const char* rootInst    = getInstLit(pInst.instrCode);
    instr->condition        = getInstConditional(pInst.instSource, rootInst);    // Obtener si la instruccion tiene o no condicional

    addRef(instr, pLabel, pSourceLine, reserveInstruction());
}

/* Esta función valida los simbolos y referencias utilizados en el programa y completa las instrucciones */
void completeContext () {
    Symrec *iSymrec;                    // Nodo para iterar por la lista de simbolos
    Symref *iSymref = getRefList();     // Nodo para iterar sobre la lista de referencias
    int refFound;                       // Bandera que indica que se ha encontrado el simbolo de la referencia

    while (iSymref != 0) {
        iSymrec = getSymTable();        // Obtener la raíz de la tabla de simbolos
        refFound = 0;                   // Reiniciar la bandera

        while (!refFound && iSymrec != 0){                                  // Mientras no se haya encontrado el simbolo y no se acaben los simbolos entonces:
            if (strcmp(iSymref->idval, iSymrec->idval) == 0){               // Comparación de identificadores
                refFound = 1;                                               // Se ha encontrado el símbolo
                iSymref->instruction->imm_shmt = iSymrec->code_offset;      // Añadir la posicion de memoria a la que se debe de dar el salto
                addReserveInst(iSymref->instruction, iSymref->instNumber);  // Añadir la instrucción
                iSymrec->used = 1;                                          // Marcar el simbolo como utilizado
            } else {
                iSymrec = iSymrec->next;                                    // Siguiente simbolo
            }
        }
        if (!refFound) { // Si no se encuentra el símbolo error.
            printf("line: %d. CONTEXT ERROR: Label \"%s\" is not defined in the source code.\n", iSymref->sourceLine, iSymref->idval);
            _errors++;
        }

        iSymref = iSymref->next;    // Siguiente referencia
    }

}

int hex2dec(const char* pHex){
	return strtol(pHex, NULL, 16);
}

int haveSetFlags(const char* pInstr, const char* pRootInst){
	int rootLen 	= strlen(pRootInst);
	int instrLen 	= strlen(pInstr);
    int subResult   = instrLen - rootLen;
	return subResult == 1 || subResult == 3; 	// Si el largo difiere por 1 indica que se encuentra una S al final de la instrucción, si difiere por 3 tiene una S y un condicional
}

int getInstConditional(const char* pInstr, const char* pRootInst){
	int rootLen 	= strlen(pRootInst);
	int instrLen 	= strlen(pInstr);
	
	if (rootLen == instrLen) {
		return AL;
	}

    const char *substr = pInstr + instrLen - 2; 	// El substring es el tamaño del texto menos los dos últimos que corresponden a los caracteres de condición
 	char cond[3];
 	cond[0] = tolower(*substr);
 	cond[1] = tolower(*(substr+1));
 	cond[2] = '\0';

    if (strcmp(cond, "eq") == 0){
        return EQ;
    } else if (strcmp(cond, "ne") == 0) {
        return NE;
    } else if (strcmp(cond, "cs") == 0) {
        return CS;
    } else if (strcmp(cond, "hs") == 0) {
        return HS;
    } else if (strcmp(cond, "cc") == 0) {
        return CC;
    } else if (strcmp(cond, "lo") == 0) {
        return LO;
    } else if (strcmp(cond, "mi") == 0) {
        return MI;
    } else if (strcmp(cond, "pl") == 0) {
        return PL;
    } else if (strcmp(cond, "vs") == 0) {
        return VS;
    } else if (strcmp(cond, "vc") == 0) {
        return VC;
    } else if (strcmp(cond, "hi") == 0) {
        return HI;
    } else if (strcmp(cond, "ls") == 0) {
        return LS;
    } else if (strcmp(cond, "ge") == 0) {
        return GE;
    } else if (strcmp(cond, "lt") == 0) {
        return LT;
    } else if (strcmp(cond, "gt") == 0) {
        return GT;
    } else if (strcmp(cond, "le") == 0) {
        return LE;
    } else if (strcmp(cond, "al") == 0) {
        return AL;
    }
    return AL;
}

int getRegConstant(char *pReg) {
    if (strcmp(pReg, "R0") == 0 || strcmp(pReg, "r0") == 0)
        return R0;
    if (strcmp(pReg, "R1") == 0 || strcmp(pReg, "r1") == 0)
        return R1;
    if (strcmp(pReg, "R2") == 0 || strcmp(pReg, "r2") == 0)
        return R2;
    if (strcmp(pReg, "R3") == 0 || strcmp(pReg, "r3") == 0)
        return R3;
    if (strcmp(pReg, "R4") == 0 || strcmp(pReg, "r4") == 0)
        return R4;
    if (strcmp(pReg, "R5") == 0 || strcmp(pReg, "r5") == 0)
        return R5;
    if (strcmp(pReg, "R6") == 0 || strcmp(pReg, "r6") == 0)
        return R6;
    if (strcmp(pReg, "R7") == 0 || strcmp(pReg, "r7") == 0)
        return R7;
    if (strcmp(pReg, "R8") == 0 || strcmp(pReg, "r8") == 0)
        return R8;
    if (strcmp(pReg, "R9") == 0 || strcmp(pReg, "r9") == 0)
        return R9;
    if (strcmp(pReg, "R10") == 0 || strcmp(pReg, "r10") == 0)
        return R10;
    if (strcmp(pReg, "R11") == 0 || strcmp(pReg, "r11") == 0)
        return R11;
    if (strcmp(pReg, "R12") == 0 || strcmp(pReg, "r12") == 0)
        return R12;
    if (strcmp(pReg, "R13") == 0 || strcmp(pReg, "r13") == 0 || strcmp(pReg, "sp") == 0 || strcmp(pReg, "SP") == 0)
        return R13;
    if (strcmp(pReg, "R14") == 0 || strcmp(pReg, "r14") == 0 || strcmp(pReg, "lr") == 0 || strcmp(pReg, "LR") == 0)
        return R14;
    if (strcmp(pReg, "R15") == 0 || strcmp(pReg, "r15") == 0 || strcmp(pReg, "pc") == 0 || strcmp(pReg, "PC") == 0)
        return R15;
    printf("Internal error. Register not found.\n");
    return 0;
}


Instruction *dataInstr(InstWrap pInstWrap, int pRn, int pRd, Src2Wrap pSrc2){
    if (pSrc2.srcType == IMMEDIATE){
        return dataImmInstr(pInstWrap.instrCode, pInstWrap.instSource, pRn, pRd, pSrc2.imm_shmt);
    } else if (pSrc2.srcType == REG_IMM){
        return dataRegShImmInstr(pInstWrap.instrCode, pInstWrap.instSource, pRn, pRd, pSrc2.imm_shmt, pSrc2.shiftType, pSrc2.rm);
    } else if (pSrc2.srcType == REG_REG) {
        return dataRegShRegInstr(pInstWrap.instrCode, pInstWrap.instSource, pRn, pRd, pSrc2.rs, pSrc2.shiftType, pSrc2.rm);
    } else {
        printf("Internal error. Src2 type not defined.\n");
        return 0;
    }
}

Instruction *memInstr(InstWrap pInstWrap, int pRn, int pRd, int pIndexMode, Src2Wrap pSrc2){
    if (pInstWrap.instrCode == STR || pInstWrap.instrCode == LDR || pInstWrap.instrCode == STRB || pInstWrap.instrCode == LDRB){
        if (pSrc2.srcType == IMMEDIATE)
            return memImmInstr(pInstWrap.instrCode, pInstWrap.instSource, pSrc2.sign, pIndexMode, pRn, pRd, pSrc2.imm_shmt);
        else if (pSrc2.srcType == REG_IMM)
            return memRegInstr(pInstWrap.instrCode, pInstWrap.instSource, pSrc2.sign, pIndexMode, pRn, pRd, pSrc2.imm_shmt, pSrc2.shiftType, pSrc2.rm);
        else
            return 0;

    } else {
        if (pSrc2.srcType == IMMEDIATE)
            return extraMemImmInstr(pInstWrap.instrCode, pInstWrap.instSource, pSrc2.sign, pIndexMode, pRn, pRd, pSrc2.imm_shmt);
        else if (pSrc2.srcType == REG_REG)
            return extraMemRegInstr(pInstWrap.instrCode, pInstWrap.instSource, pSrc2.sign, pIndexMode, pRn, pRd, pSrc2.rm);
        else
            return 0;
    }
}

Instruction *dataImmInstr(int pInstruction, const char * pSourceInst, int pRn, int pRd, int pImm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    RotInfo *rot = valDataImm(pImm);
    if (rot == 0){
        yyerror(); printf(" CONTEXT ERROR: The immediate value must be of 8 bits or allows 4 bit ARM right rotation.\n");
        return 0;
    }

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);
    int setFlag = haveSetFlags(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= IMMEDIATE; 			// Se trata de una operación con inmediato
    inst->condition 	= cond;
    inst->setFlags 		= setFlag;
    inst->r_n 			= pRn;
    inst->r_d 			= pRd;
    inst->imm_shmt 		= pImm;
    inst->rot 			= rot->rot;
    inst->immSeed 		= rot->seed;
    free(rot);
    addInstruction(inst);
    return inst;
}

Instruction *dataRegShImmInstr(int pInstruction, const char *pSourceInst, int pRn, int pRd, int pShamnt, int pShiftType, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);
    int setFlag = haveSetFlags(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= REG_IMM; 			// se trata de una instruccion con shift por inmediato (shamnt)
    inst->condition 	= cond;
    inst->setFlags 		= setFlag;
    inst->r_n 			= pRn;
    inst->r_d 			= pRd;
    inst->imm_shmt 		= pShamnt;
    inst->shift_type 	= pShiftType;
    inst->r_m 			= pRm;
    addInstruction(inst);
    return inst;
}

Instruction *dataRegShRegInstr(int pInstruction, const char *pSourceInst, int pRn, int pRd, int pRs, int pShiftType, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);
    int setFlag = haveSetFlags(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= REG_REG; 			// se trata de una instruccion con shift registro - registro
    inst->condition 	= cond;
    inst->setFlags 		= setFlag;
    inst->r_n 			= pRn;
    inst->r_d 			= pRd;
    inst->r_sa			= pRs;
    inst->shift_type 	= pShiftType;
    inst->r_m 			= pRm;
    addInstruction(inst);
    return inst;
}

Instruction *multiplyInstr(int pInstruction, const char *pSourceInst, int pRd, int pRa, int pRm, int pRn){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);
    int setFlag = haveSetFlags(pSourceInst, instRoot);

    inst->instrType 	= pInstruction;
    // Definir las variables necesarias
    inst->condition 	= cond;
    inst->setFlags 		= setFlag;
    inst->r_d 			= pRd;
    inst->r_sa 			= pRa;
    inst->r_m 			= pRm;
    inst->r_n 			= pRn;
    addInstruction(inst);
    return inst;
}

Instruction *memImmInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pImm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= IMMEDIATE; 			// se trata de una instruccion con inmediato
    inst->condition 	= cond;
    inst->addOffset 	= pAddOffset;
    inst->indexMode 	= pIndexMode;
    inst->r_n 			= pRn;
    inst->r_d			= pRd;
    inst->imm_shmt 		= pImm;
    addInstruction(inst);
    return inst;
}

Instruction *memRegInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pShamnt, int pShiftType, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= REG_IMM; 			// se trata de una instruccion con registros
    inst->condition 	= cond;
    inst->addOffset 	= pAddOffset;
    inst->indexMode 	= pIndexMode;
    inst->r_n 			= pRn;
    inst->r_d 			= pRd;
    inst->imm_shmt 		= pShamnt;
    inst->shift_type 	= pShiftType;
    inst->r_m 			= pRm;
    addInstruction(inst);
    return inst;
}

Instruction *extraMemImmInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pImm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= IMMEDIATE; 		// se trata de una instruccion con inmediato
    inst->condition 	= cond;
    inst->addOffset 	= pAddOffset;
    inst->indexMode 	= pIndexMode;
    inst->r_n 			= pRn;
    inst->r_d 			= pRd;
    inst->imm_shmt 		= pImm;
    addInstruction(inst);
    return inst;
}

Instruction *extraMemRegInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pRm){
    Instruction *inst 	= (Instruction *) malloc(sizeof(Instruction)); 	// Pedir memoria
    inst->instrType 	= pInstruction;

    const char *instRoot = getInstLit(pInstruction);
    int cond = getInstConditional(pSourceInst, instRoot);

    // Definir las variables necesarias
    inst->src2Type 		= REG_IMM; 			// se trata de una instruccion con registros
    inst->condition 	= cond;
    inst->addOffset 	= pAddOffset;
    inst->indexMode 	= pIndexMode;
    inst->r_n 			= pRn;
    inst->r_d 			= pRd;
    inst->r_m 			= pRm;
    addInstruction(inst);
    return inst;
}

RotInfo *valDataImm(unsigned int pImm) {
    int rot = 0;
    unsigned int val = pImm;

    while (val > 255 && rot < 32) { 			// El inmediato tiene un tamaño de 8 bits -> 255 es la maxima representación. Para rot 30 es el maximo.
        rot += 2; 								// La rotación en ARM se hace en multiplos de 2
        val = (pImm<<rot) + (pImm>>(32-rot)); 	// Rotacion a la izquierda
    }

    if (val > 255)
        return 0;

    RotInfo *info 	= (RotInfo *) malloc (sizeof(RotInfo));
    info->rot 		= rot/2;
    info->seed 		= val;
    return info;
}
