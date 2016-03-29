#ifndef REF_LIST
#define REF_LIST

#include "Instructions.h"

struct symref {
    Instruction     *instruction;   // Instrucción asociada, contiene el Instruction de un branch
    char            *idval;         // Etiqueta a la que se hace referencia en el branch
    int             sourceLine;     // Línea de código fuente en la que se utiliza, para msj de error
    int             instNumber;     // Espacio de instruccion reservado donde debe ser insertada posteriormente la instrucción
    struct symref   *next;          // Siguiente referencia de la lista
};

typedef struct symref Symref;

extern Symref *_refList;            // Raíz de la lista de referencias

Symref *addRef(Instruction * pInstruction, char *pIDVal, int pSourceLine, int pInstNumber);     // Añade una referencia a la lista
Symref *getRefList();                                   // Devuelve la raíz de la lista de referencias
void destroyRef(Symref *pRef);                          // Destructor de una única referencia, no destruye la instrucción asociada
void destroyRefList();                                  // Destruye la lista de referencias, no destruye las instrucciones asociadas

#endif
