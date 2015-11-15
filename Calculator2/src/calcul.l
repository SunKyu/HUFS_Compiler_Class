%{
/* Lexical Analysis for Calculator */
#include "calcul.tab.h"
double	atof();

%}

%option noyywrap

letter		[a-z]
digit		[0-9]
digits		{digit}+
exponent	[eE][-+]?{digits}
number		({digits}|{digits}"."{digits})({exponent})?
operator        [-+*/()]
whitespace	[ \t]

%%

{number}	{ yylval.num = atof(yytext);
		  return NUM;
                }
{letter}        { yylval.id = yytext[0];
		  return IDENT;
                }
print           { return PRINT; }
=               { return ASSIGN; }
;               { return SEMI; }
\n              { return NL; }
{operator}      { return yytext[0]; }
{whitespace}    ;
.               ; /* Do nothing for illegal character */


