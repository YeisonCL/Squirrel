#ifndef SYMBOLS
#define SYMBOLS

#include "Instructions.h"

//Tabla de símbolos. Esta tabla únicamente contendrá información sobre labels para branches
struct symrec {
	char 			*idval; 		//valor de un identificador
	int 			code_offset; 	//offset en la memoria de instrucciones
    int             used;
	struct symrec 	*next; 			//siguiente de la lista
};

typedef struct symrec Symrec;

extern Symrec *_symTable;

Symrec *addSym();
Symrec *getSym();
Symrec *getSymTable();

void destroySymb(Symrec *pSymbol);

void destroySymbTable();

void destroyRefList();

#endif
