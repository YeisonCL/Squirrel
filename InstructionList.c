#include "InstructionList.h"
#include <stdlib.h>
#include <stdio.h>

static int _nextInst;
Instruction **_instList = 0;
int _instSize = 0;

void createInstList(int pListSize){
	_instList 	= (Instruction **) malloc(sizeof(Instruction*)*pListSize); 	// Se crea una lista de punteros a punteros de instrucciones.
	_nextInst 	= 0; 														// Se inicializa la direccion de la siguiente instruccion en 0
    _instSize   = pListSize;
}

void addInstruction(Instruction *pInstruction) {
    Instruction **instruction = _instList + _nextInst*sizeof(Instruction*); 	// Cálculo de la posición de la nueva instruccion
    *instruction = pInstruction;                                                // Definir el valor del puntero
    _nextInst++;                                                                // Siguiente dirección
}

int nextInstruction() {
	return _nextInst;
}

int reserveInstruction(){
    int reserv = _nextInst;
    _nextInst++;
    return reserv;
}

void addReserveInst(Instruction *pInstruction, int pInstNum) {
    Instruction **instruction = _instList + pInstNum*sizeof(Instruction*);
    *instruction = pInstruction;
}

void printInstructionList(){
    int n = 0;
    for (n; n < _nextInst; n++){
        Instruction *inst = *(_instList + n*sizeof(Instruction*));
        const char *lit = getInstLit(inst->instrType);
        printf("%d: %s c:%d s:%d Rd:%d Rn:%d Rm:%d Rsa:%d src2type:%d imm:%d rot:%d immSeed:%d addOffset:%d ixMode:%d stype:%d\n", n, lit, inst->condition, inst->setFlags, inst->r_d, inst->r_n, inst->r_m, inst->r_sa, inst->src2Type, inst->imm_shmt, inst->rot, inst->immSeed, inst->addOffset, inst->indexMode, inst->shift_type);
    }
}

Instruction *getInstruction(int pInstNum){
    return *(_instList+sizeof(Instruction *)*pInstNum);
}

int getLastInstruction(){
    return _nextInst-1;
}
