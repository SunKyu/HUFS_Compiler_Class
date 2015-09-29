/*
 * util.c - commonly used utility functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "errormsg.h"

void* checked_malloc(int len)
{
	void *p = malloc(len);
	if (!p) {
		fprintf(stderr,"\nRan out of memory!\n");
		exit(1);
	}
	return p;
}

string String(char *s)
{
	string p = checked_malloc(strlen(s)+1);
	strcpy(p,s);
	return p;
}

char strbuf[BUFMAX];
int  bufptr;

void clearbuf()
{
   int i;
   bufptr = 0;
   for (i=0; i<BUFMAX; i++)
      strbuf[i] = 0;
}

void putbuf(char c)
{
   if (bufptr >= BUFMAX)
      EM_error("Too long string");
   else {
      strbuf[bufptr] = c;
      bufptr++;
   }
}
