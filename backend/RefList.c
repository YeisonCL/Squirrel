#ifdef __cplusplus
extern "C" {
#endif

#include "RefList.h"
#include <stdlib.h>
#include <string.h>

Symref *_refList  = (Symref *) 0;

/* Esta función añade una nueva referencia a la lista de referencias que debe ser posteriormente revisada*/
Symref *addRef(Instruction * pInstruction, char *pIDVal, int pSourceLine, int pInstNumber){
    Symref *ref        = (Symref *) malloc(sizeof(Symref));
    ref->instruction   = pInstruction;
    ref->idval         = (char *) malloc(strlen(pIDVal)+1);
    strcpy(ref->idval, pIDVal);
    ref->instNumber    = pInstNumber;
    ref->sourceLine    = pSourceLine;
    ref->next          = _refList;
    _refList           = ref;
    return ref;
}

/* Esta función devuelve un puntero a la lista de referencias*/
Symref *getRefList(){
    return _refList;
}

void destroyRef(Symref *pRef){
    free(pRef->idval);
    free(pRef);
}

/* Esta función destruye la lista de referencias */
void destroyRefList(){
    Symref *ref = _refList;
    Symref *refTemp;
    while (ref != 0){
        refTemp = ref->next;
        destroyRef(ref);
        ref = refTemp;
    }
    _refList = 0;
}

#ifdef __cplusplus
}
#endif
