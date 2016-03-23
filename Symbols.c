#include "Symbols.h"
#include "InstructionList.h"
#include <string.h>
#include <stdlib.h>

Symrec *_symTable = (Symrec *) 0;

/* Esta función añade un nuevo simbolo a la tabla */
Symrec *addSym(char* pIDVal) {
    Symrec *newNode = (Symrec *) malloc(sizeof(Symrec)); 	// Crear el espacio para el simbolo
    newNode->idval  = (char *) malloc(strlen(pIDVal)+1); 	// Crear el espacio para el texto del simbolo
	strcpy(newNode->idval, pIDVal); 						// Copiar el string de entrada al nuevo espacio de memoria

    newNode->code_offset = nextInstruction();               // Pedir el numero de la siguiente instrucción
    newNode->used = 0;
	newNode->next = _symTable; 								// Concatenar el nuevo nodo con el inicial de la tabla
	_symTable = newNode; 									// El nuevo nodo será el inicial
	return newNode; 										// Devolver el nuevo nodo
}

/* Esta función busca el valor de un símbolo en la tabla, 
es útil para saber si un símbolo ya existe */
Symrec *getSym(char* pIDVal) {
	Symrec *currentNode = _symTable;						// El inicio de la lista será el punto de partida para la busqueda

 	while (currentNode != 0 ) { 							// Iterar hasta llegar al final 
 		if (strcmp(currentNode->idval, pIDVal) == 0)		// Si los valores son iguales retornar el nodo actual
 			return currentNode;
 		currentNode = currentNode->next;					// Continuar al siguiente nodo
 	}
 	return 0; 												// Si no se encontró entonces retornar 0
}

/* Esta función devuelve un puntero al inicio de la tabla de simbolos */
Symrec *getSymTable(){
    return _symTable;
}

void destroySymb(Symrec *pSymbol){
    free(pSymbol->idval);
    free(pSymbol);
}

/* Esta función destruye la tabla de simbolos */
void destroySymbTable(){
    Symrec *symbol;
    Symrec *symTemp;
    while (symbol != 0){
        symTemp = symbol->next;
        destroySymb(symbol);
        symbol = symTemp;
    }
}
