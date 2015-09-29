/*
 * errormsg.c - functions used in all phases of the compiler to give
 *              error messages about the Tiger program.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"
#include "errormsg.h"


bool anyErrors= FALSE;

static string fileName = "";

static int lineNum = 1;

extern FILE *yyin;

void EM_newline(void)
{
   lineNum++;
}

void EM_error(char *message)
{
   int num=lineNum;

   anyErrors=TRUE;

   if (fileName) fprintf(stderr,"%s:",fileName);
   fprintf(stderr,"%d: ", num);
   fprintf(stderr, message);
   fprintf(stderr,"\n");

}

void EM_open(string fname)
{
   anyErrors=FALSE; fileName=fname; lineNum=1;
   yyin = fopen(fname,"r");
   if (!yyin) {EM_error("cannot open"); exit(1);}
}

