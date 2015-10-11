%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

extern int atoi(const char*);
%}

%start C S

letter		[A-Za-z]
digit		[0-9]
integer		{digit}+
float       {digit}+"."{digit}+(e[+-]?[0-9]+)?
ws			[\ \t]

%%

<INITIAL>\n		{ EM_newline(); continue; }
<INITIAL>{ws}		{ continue; }
<INITIAL>{integer}	{ yylval.ival = atoi(yytext); return INT; }
<INITIAL>{float}    { yylval.sval = String(yytext); return FLOAT; }
<INITIAL>","		{ return COMMA; }
<INITIAL>":"		{ return COLON; }
<INITIAL>";"		{ return SEMICOLON; }
<INITIAL>"("		{ return LPAREN; }
<INITIAL>")"            { return RPAREN; }
<INITIAL>"["            { return LBRACK; }
<INITIAL>"]"            { return RBRACK; }
<INITIAL>"{"            { return LBRACE; }
<INITIAL>"}"            { return RBRACE; }
<INITIAL>"."            { return DOT; }
<INITIAL>"+"            { return PLUS; }
<INITIAL>"-"            { return MINUS; }
<INITIAL>"*"            { return TIMES; }
<INITIAL>"/"            { return DIVIDE; }
<INITIAL>"="            { return EQ; }
<INITIAL>"<>"           { return NEQ; }
<INITIAL>"<"		{ return LT; }
<INITIAL>"<="		{ return LE; }
<INITIAL>">"		{ return GT; }
<INITIAL>">="		{ return GE; }
<INITIAL>"&"		{ return AND; }
<INITIAL>"|"		{ return OR; }
<INITIAL>":="		{ return ASSIGN; }
<INITIAL>array		{ return ARRAY; }
<INITIAL>if		{ return IF; }
<INITIAL>then		{ return THEN; }
<INITIAL>else		{ return ELSE; }
<INITIAL>while		{ return WHILE; }
<INITIAL>for		{ return FOR; }
<INITIAL>to		{ return TO; }
<INITIAL>do		{ return DO; }
<INITIAL>let		{ return LET; }
<INITIAL>in		{ return IN; }
<INITIAL>end		{ return END; }
<INITIAL>of		{ return OF; }
<INITIAL>break		{ return BREAK; }
<INITIAL>nil		{ return NIL; }
<INITIAL>function	{ return FUNCTION; }
<INITIAL>var		{ return VAR; }
<INITIAL>type		{ return TYPE; }
<INITIAL>{letter}({letter}|{digit}|_)*	{ yylval.sval= String(yytext); return ID; }
<INITIAL>"/*"		{ BEGIN C; continue; }
<INITIAL>\"		{ BEGIN S; clearbuf(); continue; }
<S>[^"\\\n]	{ putbuf(yytext[0]); continue; }
<S>\"		{ BEGIN INITIAL; yylval.sval = String(strbuf);
		  return STRING;
		}
<S>\n		{ EM_error("Unclosed string"); 
		  BEGIN INITIAL; continue;
		}
<S>\\t		{ putbuf('\\'); putbuf('t'); continue; }
<S>\\n		{ putbuf('\\'); putbuf('n'); continue; }
<S>\\\"		{ putbuf('\"'); continue; }
<S>\\\\		{ putbuf('\\'); continue; }
<S>\\		{ EM_error("Illegal string escape"); continue; }

<C>\n		{ EM_newline(); continue; }
<C>[^*/\n]	{ continue; }
<C>"/*"		{ continue; }
<C>"*/"		{ BEGIN INITIAL; continue; }
<C>[*/]		{ continue; }

.		{ EM_error("illegal token"); }

%%

