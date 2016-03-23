#ifndef INSTRUCTION_LIST
#define INSTRUCTION_LIST

#include "Instructions.h"

extern Instruction **_instList;
extern int _instSize;

void createInstList(int pListSize);                             // Crea el espacio en memoria para la lista de instrucciones
void addInstruction(Instruction *pInstruction);                 // Añade una instrucción a la lista de instrucciones
int nextInstruction();                                          // Devuelve la dirección que ocupará la siguiente instrucción
int reserveInstruction();                                       // Reserva un espacio en memoria donde puede ir ubicada una instruccion
void addReserveInst(Instruction *pInstruction, int pInstNum);   // Añade una instrucción a un espacio de memoria anterior
Instruction *getInstruction(int pInstNum);                      // Obtiene una instruccion segun su numero
int getLastInstruction();                                       // Devuelve la ultima instruccion
void printInstructionList();

#endif
