/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_ARMYACC_TAB_H_INCLUDED
# define YY_YY_ARMYACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEW_LINE = 258,
    IDENTIFIER = 259,
    MOV = 260,
    AND = 261,
    EOR = 262,
    SUB = 263,
    RSB = 264,
    ADD = 265,
    ADC = 266,
    SBC = 267,
    RSC = 268,
    TST = 269,
    TEQ = 270,
    ORR = 271,
    BIC = 272,
    MVN = 273,
    CMP = 274,
    CMN = 275,
    LSL = 276,
    LSR = 277,
    ASR = 278,
    RRX = 279,
    ROR = 280,
    MUL = 281,
    MLA = 282,
    UMULL = 283,
    UMLAL = 284,
    SMULL = 285,
    SMLAL = 286,
    STR = 287,
    LDR = 288,
    STRB = 289,
    LDRB = 290,
    STRH = 291,
    LDRH = 292,
    LDRSB = 293,
    LDRSH = 294,
    B = 295,
    BL = 296,
    REGISTER = 297,
    HEX = 298,
    NUMBER = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "ARMYacc" /* yacc.c:1909  */
 /* SEMANTIC RECORD */
	char *literal; 	// para los string o literales: REGISTER IDENTIFIER HEX
	int num;

#line 104 "ARMYacc.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ARMYACC_TAB_H_INCLUDED  */
