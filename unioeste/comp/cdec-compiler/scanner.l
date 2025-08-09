%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Cd_"

%{
	#include <iostream>
	#include <cstdio>
	#include "scanner.h"
	#include "symTable.h"
	#include "driver.h"
	#include "parser.h"

	#define ERROR(MESSAGE) std::cout << "[Erro léxico]> Cadeia: " << yytext\
						   << " - " << MESSAGE << " na linha " << m_driver.lineNumber << '\n'
	
	#define RETURN_TOKEN(TOK_TYPE, ...) \
					const Cd::Parser::symbol_type& type = Cd::Parser::make_##TOK_TYPE(__VA_ARGS__); \
					m_driver.m_symbolTable.insert(yytext, type); \
					return type
%}

%x MULTI_COMMENT

alpha 			[a-zA-Z]
digit 			[0-9]
alnum 			{alpha}|{digit}
printable		[ -~]
whitespace  	[ \t\r\f]
invalid       	[%$#@¨`\^?:]

ID 				{alpha}+{alnum}*
INVAL_ID    	({invalid}|{alnum})+

ILIT			-?{digit}{1,9}
INVAL_ILIT_1 	-?{digit}{9,}
INVAL_ILIT_2    -?{digit}+({invalid}|{alnum})+

FLIT			-?{digit}{0,7}"."{digit}{0,7}
INVAL_FLIT_1    -?{digit}*({invalid}|{alnum})+"."({invalid}|{alnum})+
INVAL_FLIT_2	-?{digit}+"."{digit}+

CHLIT			(\'{printable}\')|(\'\\[nftrbv]\')
STRING			\"{printable}*\"

%%

"//".*					{ } 

"/*"					{ BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT>"*/" 	{ BEGIN(INITIAL); }
<MULTI_COMMENT>[^\n]+	{ }	
<MULTI_COMMENT>"\n"		{ m_driver.lineNumber += 1; }
<MULTI_COMMENT><<EOF>>  { 
						  ERROR("Comentario em bloco nao terminado"); 
						  return Cd::Parser::make_YYEOF();
						}

"continue"				{ RETURN_TOKEN(CONTINUE); }
"break"					{ RETURN_TOKEN(BREAK); }
"return"				{ RETURN_TOKEN(RETURN); }
"else"					{ RETURN_TOKEN(ELSE); }
"while"					{ RETURN_TOKEN(WHILE); }
"for"					{ RETURN_TOKEN(FOR); }
"if"					{ RETURN_TOKEN(IF); }
"import"				{ RETURN_TOKEN(IMPORT);}
"print"					{ RETURN_TOKEN(PRINT);}
"scan"					{ RETURN_TOKEN(SCAN);}
"void"					{ RETURN_TOKEN(VOID, TokenType::VOID); }
"char"  		     	{ RETURN_TOKEN(CHAR, TokenType::CHAR); }
"int"					{ RETURN_TOKEN(INT, TokenType::INT);}
"float"					{ RETURN_TOKEN(FLOAT, TokenType::REAL);}
"double"				{ RETURN_TOKEN(DOUBLE, TokenType::REAL);}
"str"					{ RETURN_TOKEN(STRING, TokenType::STR);}

"!"						{ RETURN_TOKEN(NOT); }
"=="   				    { RETURN_TOKEN(EQU); }
"!="                    { RETURN_TOKEN(EQU); }
">"	                 	{ RETURN_TOKEN(REL); }
"<"                     { RETURN_TOKEN(REL); }
">="                    { RETURN_TOKEN(REL); }
"<="                    { RETURN_TOKEN(REL); }
"+" 					{ RETURN_TOKEN(ADD); }
"-"                     { RETURN_TOKEN(SUB); }
"*"						{ RETURN_TOKEN(MUL); }
"/"						{ RETURN_TOKEN(DIV); }
"++"	   			    { RETURN_TOKEN(INC); }
"--"                    { RETURN_TOKEN(DEC); }
"||"					{ RETURN_TOKEN(OR); }
"&&"					{ RETURN_TOKEN(AND); }


";"						{ RETURN_TOKEN(SEMI); }
","						{ RETURN_TOKEN(COMMA); }
"="						{ RETURN_TOKEN(ASSIGN); }
"&"						{ RETURN_TOKEN(REFER); }
"("						{ RETURN_TOKEN(LPAREN); }
")"						{ RETURN_TOKEN(RPAREN); }
"]"						{ RETURN_TOKEN(RBRACK); }
"["						{ RETURN_TOKEN(LBRACK); }
"{"						{ RETURN_TOKEN(LBRACE); }
"}"						{ RETURN_TOKEN(RBRACE); }

{ID}     				{ 
							SymbolInfo* info = m_driver.m_symbolTable.insert(yytext);
							Cd::Parser::symbol_type type = Cd::Parser::make_ID(info);
							info->classType = Cd::Parser::symbol_name(type.type_get());
							return type;
						}
{ILIT} 					{ 
	      					const Cd::Parser::symbol_type& type = Cd::Parser::make_ILIT(atoi(yytext)); 
							SymbolInfo* info = m_driver.m_symbolTable.insert(yytext, type);
							info->type = TokenType::INT;
							info->value = atoi(yytext);
							return type;
						}
{INVAL_ILIT_1}	 		{ ERROR("Constante inteira excedeu o limite");  }
{INVAL_ILIT_2}	 		{ ERROR("Constante inteira com caractere invalido");  }

{FLIT} 					{ 
	      					const Cd::Parser::symbol_type& type = Cd::Parser::make_FLIT(atof(yytext)); 
							SymbolInfo* info = m_driver.m_symbolTable.insert(yytext, type);
							info->type = TokenType::REAL;
							info->value = atof(yytext);
							return type;
 						}
{INVAL_FLIT_2}	 		{ ERROR("Constante real excedeu o limite"); }
{INVAL_FLIT_1}	 		{ ERROR("Constante real com caractere invalido"); }

{CHLIT} 				{ 
	      					const Cd::Parser::symbol_type& type = Cd::Parser::make_CHLIT(yytext[1]); 
							SymbolInfo* info = m_driver.m_symbolTable.insert(yytext, type);
							info->type = TokenType::CHAR;
							info->value = yytext[1];
							return type;
 						}
{STRING} 				{ 
	      					const Cd::Parser::symbol_type& type = Cd::Parser::make_STRLIT(yytext); 
							SymbolInfo* info = m_driver.m_symbolTable.insert(yytext, type);
							info->type = TokenType::STR;
							info->value = yytext;
							return type;
 						}

{INVAL_ID}      		{ ERROR("Identificador com caractere invalido");  }

<<EOF>>         		{ return Cd::Parser::make_YYEOF(); }

"\n"					{ m_driver.lineNumber += 1; }
{whitespace}+			{ }	

.						{ ERROR("Token invalido"); }

%%