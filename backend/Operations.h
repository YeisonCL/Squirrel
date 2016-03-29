/*********************************************/
/*		Instituto Tecnológico de Costa Rica  */
/*		Ingeniería en Computadores           */
/*		Arquitectura de Computadores         */
/*		II Semestre 2015                     */
/*		                                     */
/*		Author: Yeison Cruz León             */
/*              Joseph Cruz Loaiza           */
/*		Carné: 201258348                     */
/*             201258359                     */
/*********************************************/

#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include "Instructions.h"

/*Data Procesing Instructions*/

void ANDInstruction(Instruction *pInstruction);
void EORInstruction(Instruction *pInstruction);
void SUBInstruction(Instruction *pInstruction);
void RSBInstruction(Instruction *pInstruction);
void ADDInstruction(Instruction *pInstruction);
void ADCInstruction(Instruction *pInstruction);
void SBCInstruction(Instruction *pInstruction);
void RSCInstruction(Instruction *pInstruction);
void TSTInstruction(Instruction *pInstruction);
void TEQInstruction(Instruction *pInstruction);
void CMPInstruction(Instruction *pInstruction);
void CMNInstruction(Instruction *pInstruction);
void ORRInstruction(Instruction *pInstruction);
void MOVInstruction(Instruction *pInstruction);
void LSLInstruction(Instruction *pInstruction);
void LSRInstruction(Instruction *pInstruction);
void ASRInstruction(Instruction *pInstruction);
void RRXInstruction(Instruction *pInstruction);
void RORInstruction(Instruction *pInstruction);
void BICInstruction(Instruction *pInstruction);
void MVNInstruction(Instruction *pInstruction);

/*Multiply Instructions*/

void MULInstruction(Instruction *pInstruction);
void MLAInstruction(Instruction *pInstruction);
void UMULLInstruction(Instruction *pInstruction);
void UMLALInstruction(Instruction *pInstruction);
void SMULLInstruction(Instruction *pInstruction);
void SMLALInstruction(Instruction *pInstruction);

/*Memory Instructions*/

void STRInstruction(Instruction *pInstruction);
void LDRInstruction(Instruction *pInstruction);
void STRBInstruction(Instruction *pInstruction);
void LDRBInstruction(Instruction *pInstruction);
void STRHInstruction(Instruction *pInstruction);
void LDRHInstruction(Instruction *pInstruction);
void LDRSBInstruction(Instruction *pInstruction);
void LDRSHInstruction(Instruction *pInstruction);

/*Branch Instructions*/

void BInstruction(Instruction *pInstruction);
void BLInstruction(Instruction *pInstruction);

#endif
