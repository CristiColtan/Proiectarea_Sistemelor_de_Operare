%option noyywrap
%{
	#include "interpretor.tab.h"

	int lineNo = 1;
	int colNo = 1;
%}

%%
\/\/[^\n]*          		{ /* ignora comentariile de o linie */ }
\/\*([^*]|\*+[^*/])*\*+\/	{ /* ignora comentariile pe mai multe linii */ }
"}"							{ colNo++; return '}'; }
"{"							{ colNo++; return '{'; }
"%d"						{ colNo++; return TOK_MODULO_D; }
"%f"						{ colNo++; return TOK_MODULO_F; }
"&"							{ colNo++; return '&'; }
","							{ colNo++; return ','; }
"\""						{ colNo++; return TOK_GHILIMEA; }
"+"				        	{ colNo++; return TOK_PLUS; }
"-"				        	{ colNo++; return TOK_MINUS; }
"*"				        	{ colNo++; return TOK_MULTIPLY; }
"/"			        		{ colNo++; return TOK_DIVIDE; }
"("				        	{ colNo++; return TOK_LEFT; }
")"				        	{ colNo++; return TOK_RIGHT; }
";"				        	{ colNo++; return ';'; }
"="				        	{ colNo++; return '='; }
">"				        	{ colNo++; return TOK_GREATER_THAN; }
"<"				        	{ colNo++; return TOK_LESS_THAN; }
"=="			        	{ colNo+=2; return TOK_EQUALS; }
0|[1-9][0-9]*	        	{   yylloc.first_line = lineNo; 
				            	yylloc.first_column = colNo; 
					        	colNo+=strlen(yytext); 
					        	yylval.val_int = atoi(yytext); 
					        	return TOK_INT; }
[0-9]+\.[0-9]+    			{ 	yylloc.first_line = lineNo; 
				    			yylloc.first_column = colNo; 
				    			colNo+=strlen(yytext); 
				    			yylval.val_double = atof(yytext); 
				    			return TOK_DOUBLE; }
[0-9]+\.[0-9]+[fF]			{ 	yylloc.first_line = lineNo; 
				            	yylloc.first_column = colNo; 
				            	colNo+=strlen(yytext); 
				            	yylval.val_float = strtof(yytext, NULL); 
				            	return TOK_FLOAT; }
"int"			        	{ colNo+=3; return TOK_DECLARE_INT; }
"float"                	 	{ colNo+=5; return TOK_DECLARE_FLOAT; }
"double"                	{ colNo+=6; return TOK_DECLARE_DOUBLE; }
"print"		        		{ colNo+=5; return TOK_PRINT; }
"if"				    	{ colNo+=2; return TOK_IF; }
"else"			        	{ colNo+=4; return TOK_ELSE; }
"while"			        	{ colNo+=5; return TOK_WHILE; }
"printf"    				{ colNo+=6; return TOK_PRINTF; }
"scanf"     				{ colNo+=5; return TOK_SCANF; }
[a-zA-Z][a-zA-Z0-9_]*    	{ 	yylloc.first_line = lineNo; 
						    	yylloc.first_column = colNo; 
						    	colNo+=strlen(yytext); 
						    	yylval.sir = new char[strlen(yytext)+1]; 
						    	strcpy(yylval.sir,yytext); 
						    	return TOK_VARIABLE;}
[ ]			    	    	{ colNo++; }
\r\n			        	{ lineNo++; colNo=1; }
\n				        	{ lineNo++; colNo=1; }
.				        	{ colNo++; return TOK_ERROR; }
%%
