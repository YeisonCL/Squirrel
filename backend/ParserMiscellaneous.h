#ifndef PARSER_MISCELLANEOUS
#define PARSER_MISCELLANEOUS

#include "Symbols.h"
#include "Instructions.h"
#include "RefList.h"

struct instWrap {
    int             instrCode;
    const char*     instSource;
};

struct src2wrap {
    int     srcType;
    int     imm_shmt;
    int     rm;
    int     rs;
    int     shiftType;
    int     sign;
};

typedef struct instWrap InstWrap;
typedef struct src2wrap Src2Wrap;

extern int _errors;

void installSymb (char *pIDValue);                                                      // Valida una etiqueta y la añade a la tabla de simbolos
void installRef(InstWrap pInst, char *pLabel, int pSourceLine);      // Construye la instrucción de branch y añade la referencia a la lista
void completeContext();                                                                 // Se encarga de validar, completar y añadir las instruciones de la lista de referencias a la lista de instrucciones

extern void yyerror();                                                  // Tiene que ser definida en el archivo lex
int hex2dec(const char *pHex);                                          // Esta función pasa un número hexadecimal a decimal
int haveSetFlags(const char* pInstr, const char* pRootInst);            // Esta función indica si la instrucción debe hacer set de las banderas
int getInstConditional(const char* pInstr, const char* pRootInst);      // Esta función obtiene el tipo de condicional que tiene la instrucción

int getRegConstant(char *pReg);                                         // Devuelve el valor de constante según el archivo Instructions.h que representa al registro
int checkBitSize(int pNum, int pSize);                                  // Revisa el tamaño de un numero según su cantidad de bits, dentro de los rangos soportados: 5, 8, 12, 24

// Funciones para generar Instruction según los tipos de instrucciones de ARM
Instruction *dataInstr(InstWrap pInstWrap, int pRn, int pRd, Src2Wrap pSrc2);
Instruction *memInstr(InstWrap pInstWrap, int pRn, int pRd, int pIndexMode, Src2Wrap pSrc2);

Instruction *dataImmInstr(int pInstruction, const char * pSourceInst, int pRn, int pRd, int pImm);
Instruction *dataRegShImmInstr(int pInstruction, const char *pSourceInst, int pRn, int pRd, int pShamnt, int pShiftType, int pRm);
Instruction *dataRegShRegInstr(int pInstruction, const char *pSourceInst, int pRn, int pRd, int pRs, int pShiftType, int pRm);
Instruction *multiplyInstr(int pInstruction, const char *pSourceInst, int pRd, int pRa, int pRm, int pRn);
Instruction *memImmInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pImm);
Instruction *memRegInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pShamnt, int pShiftType, int pRm);
Instruction *extraMemImmInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pImm);
Instruction *extraMemRegInstr(int pInstruction, const char *pSourceInst, int pAddOffset, int pIndexMode, int pRn, int pRd, int pRm);

int executeParser(const char* pFileDirection);

// Funciones para validación de datos
RotInfo *valDataImm(unsigned int pImm);

#endif
