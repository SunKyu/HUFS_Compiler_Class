/*
 * lexer.c
 *
 *  Created on: 2012. 9. 20.
 *      Author: cskim
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"
#include <string.h>

FILE *yyin;

char ch = -1;
int state = 0;

enum { DIGIT, LETTER, SPECIAL, WHITESPACE };
char* keywordsymbols[] ={"array", "if", "then", "else", "while", "for", "to", "do", "let", "in", "end", "of", "break", "nil", "function", "var", "type"};

int charClass(char ch){
	if (ch >= '0' && ch <= '9')
		return DIGIT;
	else if ((ch >= 'a' && ch <= 'z') || (ch >='A' && ch <='Z') || ch == '$' || ch == '_')
		return LETTER;
	else if ((ch == ' ' || ch == '\t' || ch == '\n'))
		return WHITESPACE;
	else
		return SPECIAL;
}

int yylex(){
	clearbuf();
	if (ch == -1)
		ch = getc(yyin);

	while (1){

		switch (state) {
		case 0://start state
			if (charClass(ch) == DIGIT){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 1;
			}
			else if (charClass(ch) == LETTER){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 2;
			}
			else {
				state = 99;//white space or special state
			}
			break;
		case 1://int type
			if (charClass(ch) == DIGIT){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 1;
			}
			else {
				yylval.ival = atoi(String(strbuf));
				state = 0;
				return INT;
			}
			break;
		case 2://string 
			if (charClass(ch) == DIGIT || charClass(ch) == LETTER){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 2;
			}
			else { 
				yylval.sval = String(strbuf);
                int index= -1;
                for (int i = 0; i<17 ; i++){
                    if (!strcmp(keywordsymbols[i], strbuf)){
                        index = i;
                        break;
                    }
                }
				state = 0;
                if(index != -1){
                    return index + 283;
                }
				return ID;
			}
			break;
		case 99:
			if (charClass(ch) == WHITESPACE){
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 0;
			}
			else {//special state
				//int tok = ch;
				//ch = getc(yyin);
                switch (ch){
                    case '/'://comment
                        ch = getc(yyin);
                        if(ch == '*'){
                            do {
                                while(ch != '*') ch = getc(yyin);
                                ch = getc(yyin);
                            }while(ch != '/');
                            break;
                        }
                        else{
                            ungetc(ch,yyin);
                            ch = -1;
                            state = 0;
                            return DIVIDE;
                        }
                    case ':'://assign
                        ch = getc(yyin);
                        if(ch == '='){
                            state = 0;
                            ch = -1;
                            return ASSIGN;
                        }
                        else{
                            ungetc(ch, yyin);
                            state =0;
                            ch = -1;
                            return COLON;
                        }
                        break;
                    case '[':
                        state = 0;
                        ch = -1;
                        return LBRACK;
                    case ',':
                        state =0;
                        ch = -1;
                        return COMMA;
                    case ']':
                        state = 0;
                        ch = -1;
                        return RBRACK;
                    case '(':
                        ch = -1;
                        state = 0;
                        return LPAREN;
                    case ')':
                        ch = -1;
                        state = 0;
                        return RPAREN;
                    case '{':
                        ch = -1;
                        state = 0;
                        return LBRACE;
                    case '}':
                        ch = -1;
                        state = 0;
                        return RBRACE;
                    case '.':
                        ch = -1;
                        state =0;
                        return DOT;
                    case '-':
                        state = 0;
                        ch = -1;
                        return MINUS;
                    case '+':
                        state = 0;
                        ch = -1;
                        return PLUS;
                    case '*':
                        state = 0;
                        ch = -1;
                        return TIMES;
                    case '!':
                        ch = getc(yyin);
                        if (ch == '='){
                            state = 0;
                            ch = -1;
                            return NEQ;
                        }
                        break;
                    case '<':
                        ch = getc(yyin);
                        if (ch == '='){
                            state =0;
                            ch = -1;
                            return LE;
                        }
                        else {
                            ungetc(ch, yyin);
                            state =0;
                            ch = -1;
                            return LT;
                        }
                    case '>':
                        ch = getc(yyin);
                        if (ch == '='){
                            state =0;
                            ch = -1;
                            return GE;
                        }
                        else {
                            ungetc(ch, yyin);
                            state =0;
                            ch = -1;
                            return GT;
                        }

                    
                    case '"':
                        ch = getc(yyin);
                        while(ch != '"'){
                            if (ch =='\\'){
                                ch = getc(yyin);
                                if (ch =='"'){
                                    putbuf(ch);
                                    ch = getc(yyin);
                                }
                                else if(ch =='\\'){
                                    putbuf(ch);
                                    ch = getc(yyin);
                                }
                                else if(ch =='n'){
                                    putbuf('\\');
                                    putbuf(ch);
                                    ch = getc(yyin);
                                }
                                //ch = getc(yyin);
                                continue;
                            }
                            putbuf(ch);
                            ch = getc(yyin);
                        }
				        yylval.sval = String(strbuf);
                        ch = -1;
                        state = 0;
                        return STRING;
                    case ';':
                        state = 0;
                        ch = -1;
                        return SEMICOLON;
                    case '&':
                        state =0;
                        ch = -1;
                        return AND;
                    case '|':
                        state =0;
                        ch = -1;
                        return OR;

                    case '='://equal
                        state = 0;
                        ch = -1;
                        return EQ;
                    
                }
				if (ch==EOF) return 0;
                ch = getc(yyin);
			}
			break;
		}
	}
}
