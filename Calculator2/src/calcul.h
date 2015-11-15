
/*************** calcul.h ********************/
/* Header file for definition using lex and main */

typedef union { int id;
		double num;
              } YYSTYPE;
extern YYSTYPE yylval;
#define NUM	257
#define IDENT	258
#define PRINT	259
#define ASSIGN	260
#define SEMI	261
#define NL	262
#define PLUS	'+'
#define MINUS	'-'
#define TIMES	'*'
#define DIVIDE	'/'
#define MOD	'%'

