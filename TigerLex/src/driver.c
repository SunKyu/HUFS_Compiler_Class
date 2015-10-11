/*
 * driver.c
 *
 *  Created on: 2010. 9. 1.
 *      Author: cskim
 */
#include <stdio.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"

YYSTYPE yylval;

int yylex(); /* prototype for the lexing function */



string toknames[] = {
"ID", "STRING", "INT", "COMMA", "COLON", "SEMICOLON", "LPAREN",
"RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT", "PLUS",
"MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT", "GE",
"AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR",
"TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
"VAR", "TYPE", "FLOAT", "DOTDOT"
};


string tokname(tok) {
  return tok<257 || tok>301 ? "BAD_TOKEN" : toknames[tok-257];
}

int main(int argc, char **argv)
{
   string fname; int tok;
   //if (argc!=2) {fprintf(stderr,"usage: a.out filename\n"); exit(1);}
   fname= argv[1];
   EM_open(fname);
   for(;;) {
      tok=yylex();
      if (tok==0) break;
      switch(tok) {
      case ID: case STRING:
         printf("%s (%s)\n",tokname(tok),yylval.sval);
         break;
      case INT:
         printf("%s (%d)\n",tokname(tok),yylval.ival);
         break;
      case FLOAT:
         printf("%s (%s)\n", tokname(tok), yylval.sval);
         break;
      default:
         printf("%s \n",tokname(tok));
      }
   }
   return 0;
}

