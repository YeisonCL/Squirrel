#ifndef INSTRUCTIONS
#define INSTRUCTIONS

struct instrType { 	// Estructura que soporta todos los campos variables de todos los tipos de instrucción
    int instrType; 	// Especifica el tipo de instrucción, los tipos se obtienen del archivo producido por el parser
	int condition; 		// Indica si la instrucción depende de una condición para ejecutarse
	int setFlags;		// Indica si la instrucción debe hacer set de las banderas del procesador
	int src2Type; 		// Indica el tipo de Src2
	int r_n; 			// Registro Rn
	int r_d; 			// Registro Rd
	// inmediato:
	int rot; 			// Indica la rotación que afectará al inmediato
	int imm_shmt; 		// Almacena el valor del inmediato o el shamnt
	int immSeed; 		// Semilla de inmediato que al aplicar la rotación se obtiene el valor deseado, utilizada en instrucciones de datos
	// register-shift-imm:
	int shift_type;		// Indica el tipo de operacion de SHIFT que afectará a un registro, 
						// no se debe confundir con las instrucciones de SHIFT del set.
	int r_m;			// Registro Rm
	// register-shift-reg:
	int r_sa; 			// Registros Rs, Ra

	// memoria:
	int addOffset;		// Indica si el offset debe ser restado o sumado a la base
	int indexMode;		// Indica el tipo de indexamiento
};

struct rotInfo { 		// Estructura utilizada en la validación de las instrucciones de datos con inmediatos, contiene la información de rotación
	int rot; 			// Indica la rotación
	int seed; 			// Indica el valor a rotar
};

typedef struct instrType Instruction;
typedef struct rotInfo RotInfo;

// Constantes para condiciones
extern const int EQ; 
extern const int NE; 

extern const int CS;  
extern const int HS;  

extern const int CC;  
extern const int LO;  

extern const int MI;  
extern const int PL;  
extern const int VS;  
extern const int VC;  
extern const int HI; 
extern const int LS;  
extern const int GE;  
extern const int LT;  
extern const int GT; 
extern const int LE;  
extern const int AL; 

// Modos de indexamiento
extern const int POST_INDEX; 	
extern const int OFFSET; 		
extern const int PRE_INDEX; 	

// Constantes para tipos Src2
extern const int IMMEDIATE; 
extern const int REG_IMM; 	
extern const int REG_REG; 	

// Constantes para registros
extern const int R0; 	
extern const int R1; 	
extern const int R2; 	
extern const int R3; 	
extern const int R4; 	
extern const int R5; 	
extern const int R6; 	
extern const int R7; 	
extern const int R8; 	
extern const int R9; 	
extern const int R10; 	
extern const int R11; 	
extern const int R12; 	

extern const int R13; 	
extern const int R14; 	
extern const int R15; 	

extern const int SP; 	
extern const int LR;
extern const int PC; 	

// Signo
extern const int POSITIVE_SIGN;
extern const int NEGATIVE_SIGN;

const char *getInstLit(int pInstCode);                                 // Obtiene el texto raiz de la instruccion sin bandera de set ni condicionales. i.e. "ADD", utilizada para encontrar condicionales y bandera de set


#endif
