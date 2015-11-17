%{
#include	<stdio.h>
static double store [26];

%}

%union { double num;
	 int id;
       }

%token	<num>	NUM
%token	<id>	IDENT
%token	PRINT	ASSIGN	SEMI	NL  COMMA
%token	'+'	'-'	'*'	'/'	'('	')'
%type	<num>	expression	term	term1	factor	factor1     exp1     print2
/* precedence table */
%left	'+' '-'
%left	'*' '/'
%left	UMINUS

%%

program
	: statements
	  { printf ("END\n"); }
statements
	: statements SEMI statement
	| statements NL statement
	| statement
statement
	: IDENT ASSIGN expression
	  { store [$<id>1-'a'] = $<num>3; }
	| PRINT '('print2')'
	| /* empty */

exp1
    : statement
    | exp1 SEMI statement

expression
	: expression '+' term1
	  { $$ = $1 + $3; }
	| expression '-' term1
	  { $$ = $1 - $3; }
	| term
term
	: term '*' factor1
	  { $$ = $1 * $3; }
	| term '/' factor1
	  { $$ = $1 / $3; }
    | factor
	| '(' exp1 COMMA expression ')' { $$ =$4 ;}
term1
	: term1 '*' factor1
	  { $$ = $1 * $3; }
	| term1 '/' factor1
	  { $$ = $1 / $3; }
    | factor1
	| '(' exp1 COMMA expression ')' {$$ = $4;}
factor
	: '(' expression ')'
	  { $$ = $2; }
	| '-' '(' expression ')' %prec UMINUS
	  { $$ = -$3; }
	| IDENT
	  { $$ = store [$<id>1-'a']; }
	| '-' IDENT		%prec UMINUS
	  { $$ = -store [$<id>1-'a']; }
	| NUM
	| '-' NUM		%prec UMINUS
	  { $$ = -$<num>2; }
factor1
	: '(' expression ')'
	  { $$ = $2; }
	| IDENT
	  { $$ = store [$<id>1-'a']; }
	| NUM

print2
    : expression { printf("%f\n", $<num>1);}
    | print2 COMMA expression { printf("%f\n", $<num>3); }

%%
/*
void yyerror (char* s) {
	printf ("***Error:%s\n", s);
}
*/
int main ()
{
	yyparse ();
}
