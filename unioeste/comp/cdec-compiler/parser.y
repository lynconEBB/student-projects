%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines
%define api.parser.class { Parser }
%define api.namespace { Cd }

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%expect 1

// parser.h
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <variant>
    #include "tree.h"

    // Forward Declare
    struct SymbolInfo;
    enum class TokenType;

    namespace Cd {
        class Scanner;
        class Driver;
    }
}

// parser.cpp
%code top
{
    #include <iostream>
    #include "scanner.h"
    #include "parser.h"
    #include "driver.h"

    static Cd::Parser::symbol_type yylex(Cd::Scanner& scanner) {
        return scanner.getNextToken();
    }
}

%lex-param { Cd::Scanner& scanner }
%parse-param { Cd::Scanner& scanner }
%parse-param { Cd::Driver& driver }
%define parse.trace
%define parse.error custom

%token<TokenType> CHAR INT FLOAT DOUBLE VOID STRING
%token COMMA LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE SEMI ASSIGN REFER
%token IF ELSE WHILE FOR CONTINUE BREAK RETURN IMPORT PRINT SCAN
%token ADD SUB MUL DIV INC DEC OR AND NOT EQU REL
%token<std::variant<int, double, char, std::string>> ILIT FLIT CHLIT STRLIT
%token<SymbolInfo*> ID

%left COMMA
%right ASSIGN
%left OR
%left AND
%left EQU
%left REL
%left ADD SUB
%left MUL DIV
%right NOT INC DEC REFER MINUS
%left LPAREN RPAREN LBRACK RBRACK

%type<Node*> declaration declarations statement assignment values statements imports import
%type<Node*> literal array expression if_statement while_statement else_if optional_else tail for_statement
%type<Node*> type names variable initialization scalar_initialization vector_initialization io_statement

%start program

%%
program: 
    imports declarations statements
    {
        Node* node = new Node("program");
        node->addChild($1);
        node->addChild($2);
        node->addChild($3);
        driver.printAST(node);
    }
;
imports:
    imports import
    {
        $$ = new Node("imports");
        $$->addChild($1); 
        $$->addChild($2); 
    }
    | %empty
    {
        $$ = new Node("imports");
    }
;

import:
    IMPORT STRLIT SEMI
    {
        $$ = new Node("import");
        $$->addChild(new Node("IMPORT"));
        $$->addChild(new Node("STRLIT", TokenType::STR, std::get<std::string>($2)));
        $$->addChild(new Node("SEMI"));
    }
;

declarations:
    declarations declaration
    {
        Node* node = new Node("declarations");
        node->addChild($1);
        node->addChild($2);
        $$ = node;
    }
    | declaration
    {
        Node* node = new Node("declarations");
        node->addChild($1);
        $$ = node;
    }
;

declaration:
    type names SEMI 
    {
        $$ = new Node("declaration");
        $$->type = $1->type;
        $$->addChild($1);
        $$->addChild($2);
        $$->addChild(new Node("SEMI"));

        std::vector<Node*> variables = $2->getChildsByName("variable");
        for (Node* n : variables) {
            SymbolInfo* symbol = driver.m_symbolTable.find(std::get<std::string>(n->value)); 
            symbol->type = $1->type;
        }

        std::vector<Node*> initializations = $2->getChildsByName("scalar_initialization");
        for (Node* n : initializations) {
            if (n->type != $1->type) {
                std::cout << "[Erro semantico] Tentativa de atribuir valor do tipo" << typeToStr(n->type) << " a variavel " 
                << std::get<std::string>(n->children[0]->value) << " do tipo " << typeToStr($1->type) << " na linha: " 
                << driver.lineNumber << std::endl;
            } else {
                SymbolInfo* symbol = driver.m_symbolTable.find(std::get<std::string>(n->children[0]->value)); 
                symbol->type = $1->type;
                symbol->value = n->value;
            }
        }

        initializations = $2->getChildsByName("vector_initialization");
        for (Node* n : initializations) {
            if (n->children[4]->type != $1->type) {
                std::cout << "[Erro semantico] Tentativa de atribuir valor " << typeToStr(n->children[4]->type) << " a variavel " 
                << std::get<std::string>(n->children[0]->value) << " do tipo vetor de " << typeToStr($1->type) << " na linha: " 
                << driver.lineNumber << std::endl;
            } else {
                SymbolInfo* symbol = driver.m_symbolTable.find(std::get<std::string>(n->children[0]->value)); 
                symbol->type = $1->type;
            }
        }
    }
    | error SEMI {
        if (driver.declaring) {
            std::cout << "[Erro sintático] Não foi possível realizar a declaração da variavel na linha: " << driver.lineNumber << std::endl;
        } else {
            std::cout << "[Erro sintático] Sentença mal formatada na linha: " << driver.lineNumber << std::endl;
        }
        $$ = new Node("error");
    }
;

type:
    INT 
    { 
        $$ = new Node("type", $1); 
        $$->addChild(new Node("INT", $1));
    }
    | CHAR 
    { 
        $$ = new Node("type", $1); 
        $$->addChild(new Node("CHAR", $1));
    }  
    | FLOAT 
    {
        $$ = new Node("type", $1); 
        $$->addChild(new Node("FLOAT", $1));
    }
    | DOUBLE 
    { 
        $$ = new Node("type", $1); 
        $$->addChild(new Node("DOUBLE", $1));
    }
    | STRING 
    { 
        $$ = new Node("type", $1); 
        $$->addChild(new Node("STRING", $1));
    }
;

names:
    names COMMA variable
    {
        $$ = new Node("names");
        $$->addChild($1);
        $$->addChild(new Node("COMMA"));
        $$->addChild($3);
    }
    | names COMMA initialization
    {
        $$ = new Node("names");
        $$->addChild($1);
        $$->addChild(new Node("COMMA"));
        $$->addChild($3);
    }
    | variable
    {
        $$ = new Node("names");
        $$->addChild($1);
    }
    | initialization
    {
        $$ = new Node("names");
        $$->addChild($1);
    }
;

variable:
    ID
    {
        $$ = new Node("variable", TokenType::UNDEFINED, $1->name);
        $$->addChild(new Node("ID", TokenType::UNDEFINED, $1->name));
    }
    | ID array
    {
        $$ = new Node("variable", TokenType::ARRAY, $1->name);
        $$->addChild(new Node("ID", TokenType::ARRAY, $1->name));
        $$->addChild($2);
    }
;

array:
    LBRACK expression RBRACK
    {
        $$ = new Node("array",TokenType::ARRAY);
        $$->addChild(new Node("LBRACK"));
        $$->addChild($2);
        $$->addChild(new Node("RBRACK"));
    }
    | LBRACK ILIT RBRACK
    {
        $$ = new Node("array",TokenType::ARRAY);
        $$->addChild(new Node("LBRACK"));
        $$->addChild(new Node("ILIT", TokenType::INT, std::get<int>($2)));
        $$->addChild(new Node("RBRACK"));
    }
;

initialization:
    scalar_initialization
    { 
        $$ = new Node("initialization", $1->type, $1->value);
        $$->addChild($1);
    }
    | vector_initialization
    { 
        $$ = new Node("initialization");
        $$->addChild($1);
    }
;

scalar_initialization:
    ID ASSIGN literal
    {
        $$ = new Node("scalar_initialization", $3->type, $3->value); 
        $$->addChild(new Node("ID", $3->type, $1->name));
        $$->addChild(new Node("ASSIGN"));
        $$->addChild($3);
    }
;

vector_initialization:
    ID array ASSIGN LBRACE values RBRACE
    {
        $$ = new Node("vector_initialization");     
        $$->addChild(new Node("ID", TokenType::UNDEFINED, $1->name));
        $$->addChild($2);
        $$->addChild(new Node("ASSIGN"));
        $$->addChild(new Node("LBRACE"));
        $$->addChild($5);
        $$->addChild(new Node("RBRACE"));
    }
;

values:
    values COMMA literal
    {
        if ($3->type != $1->type) {
            std::cout << "[Error semantico] Tipos incopativeis detectados durante inicialiação do vetor na linha: " << driver.lineNumber << std::endl;
            $$ = new Node("error");
        } else {
            Node* node = new Node("values", $3->type, $3->value);     
            node->addChild($1);
            node->addChild(new Node("COMMA"));
            node->addChild($3);
            $$ = node;
        }
    }
    | literal
    {
        Node* node = new Node("values");     
        node->type = $1->type;
        node->value = $1->value;
        node->addChild($1);
        $$ = node;
    }
;

literal:
    ILIT
    { 
        Node* node = new Node("ILIT");     
        node->type = TokenType::INT;
        node->value = std::get<int>($1);
        $$ = node;
    }
    | FLIT
    {
        Node* node = new Node("FLIT");     
        node->type = TokenType::REAL;
        node->value = std::get<double>($1);
        $$ = node;
    }
    | CHLIT
    {
        Node* node = new Node("CHLIT");     
        node->type = TokenType::CHAR;
        node->value = std::get<char>($1);
        $$ = node;
    }
    | STRLIT
    {
        Node* node = new Node("STRLIT");     
        node->type = TokenType::STR;
        node->value = std::get<std::string>($1);
        $$ = node;
    }
;

expression:
    expression ADD expression
	{ 
        if ($1->type != $3->type) {
            std::cout << "[Erro Semantico] Tipos incopativeis encontrados durante uma expressão de soma na linha: " << driver.lineNumber << std::endl;
            $$ = new Node("error");
        } else {
            $$ = new Node("expression", $1->type, $1->value);
            $$->addChild($1);
            $$->addChild(new Node("ADD"));
            $$->addChild($3);
        }
	}
    | expression SUB expression
	{ 
        if ($1->type != $3->type) {
            error("[Erro Semantico] Tipos incopativeis encontrados durante uma expressão de subtracao");
            $$ = new Node("error");
        } else {
            $$ = new Node("expression", $1->type, $1->value);
            $$->addChild($1);
            $$->addChild(new Node("SUB"));
            $$->addChild($3);
        }
	}
	| expression MUL expression
	{
        if ($1->type != $3->type) {
            error("[Erro Semantico] Tipos incopativeis encontrados durante uma expressão de multiplicação");
            $$ = new Node("error");
        } else {
            $$ = new Node("expression", $1->type, $1->value);
            $$->addChild($1);
            $$->addChild(new Node("MUL"));
            $$->addChild($3);
        }
	}
	| expression DIV expression
	{
        if ($1->type != $3->type) {
            error("[Erro Semantico] Tipos incopativeis encontrados durante uma expressão de divisão");
            $$ = new Node("error");
        } else {
            $$ = new Node("expression", $1->type, $1->value);
            $$->addChild($1);
            $$->addChild(new Node("DIV"));
            $$->addChild($3);
        }
	}
	| ID INC
	{
        SymbolInfo* info = driver.m_symbolTable.find($1->name);
        $$ = new Node("expression", info->type, info->value);
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("INC"));
	}
	| INC ID
	{
        SymbolInfo* info = driver.m_symbolTable.find($2->name);
        $$ = new Node("expression", info->type, info->value);
        $$->addChild(new Node("INC"));
        $$->addChild(new Node("ID"));
	}
	| ID DEC
	{
        SymbolInfo* info = driver.m_symbolTable.find($1->name);
        $$ = new Node("expression", info->type, info->value);
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("DEC"));
	}
	| DEC ID
	{
        SymbolInfo* info = driver.m_symbolTable.find($2->name);
        $$ = new Node("expression", info->type, info->value);
        $$->addChild(new Node("DEC"));
        $$->addChild(new Node("ID", info->type, info->value));
	}
	| expression OR expression
	{
        $$ = new Node("expression", TokenType::INT);
        $$->addChild($1);
        $$->addChild(new Node("OR"));
        $$->addChild($3);
	}
	| expression AND expression
	{
        $$ = new Node("expression", TokenType::INT);
        $$->addChild($1);
        $$->addChild(new Node("AND"));
        $$->addChild($3);
	}
	| NOT expression
	{
        $$ = new Node("expression", TokenType::INT);
        $$->addChild(new Node("NOT"));
        $$->addChild($2);
	}
	| expression EQU expression
	{
        $$ = new Node("expression", TokenType::INT);
        $$->addChild($1);
        $$->addChild(new Node("EQU"));
        $$->addChild($3);
	}
	| expression REL expression
	{
        $$ = new Node("expression", TokenType::INT);
        $$->addChild($1);
        $$->addChild(new Node("REL"));
        $$->addChild($3);
	}
	| LPAREN expression RPAREN
	{
        $$ = new Node("expression", $2->type, $2->value);
        $$->addChild(new Node("LPAREN"));
        $$->addChild($2);
        $$->addChild(new Node("RPAREN"));
	}
	| variable
	{ 
        SymbolInfo* info = driver.m_symbolTable.find(std::get<std::string>($1->value));
        $$ = new Node("expression", info->type, info->value);
        $$->addChild($1);
	}
	| literal
	{
        $$ = new Node("expression", $1->type, $1->value);
        $$->addChild($1);
	}
;

statements:
    %empty
    {
        $$ = new Node("statements");
    }
    | statements statement
    {
        driver.declaring = false;
        $$ = new Node("statements");
        $$->addChild($1);
        $$->addChild($2);
    }
;

if_statement:
	IF LPAREN expression RPAREN tail else_if optional_else
	{
        $$ = new Node("if_statement");
        $$->addChild(new Node("IF"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("RPAREN"));
        $$->addChild($5);
        $$->addChild($6);
        $$->addChild($7);
	}
	| IF LPAREN expression RPAREN tail optional_else
	{
        $$ = new Node("if_statement");
        $$->addChild(new Node("IF"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("RPAREN"));
        $$->addChild($5);
        $$->addChild($6);
	}
    | IF error RBRACE
    {
        std::cout << "[Erro sintático] Bloco if com erro terminado na linha: " << driver.lineNumber << std::endl;
        $$ = new Node("error");
    }
;

else_if:
	else_if ELSE IF LPAREN expression RPAREN tail
	{
        $$ = new Node("else_if");
        $$->addChild($1);
        $$->addChild(new Node("ELSE"));
        $$->addChild(new Node("IF"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($5);
        $$->addChild(new Node("RPAREN"));
        $$->addChild($7);
	}
	| ELSE IF LPAREN expression RPAREN tail
	{
        $$ = new Node("else_if");
        $$->addChild(new Node("ELSE"));
        $$->addChild(new Node("IF"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($4);
        $$->addChild(new Node("RPAREN"));
        $$->addChild($6);
	}
    | ELSE error RBRACE
    {
        std::cout << "[Erro sintático] Bloco else com erro terminado na linha: " << driver.lineNumber << std::endl;
        $$ = new Node("error");
    }
;

optional_else:
	ELSE tail
	{
        $$ = new Node("optional_else");
        $$->addChild(new Node("ELSE"));
        $$->addChild($2);
	}
	| %empty {
        $$ = new Node("optional_else");
	}
;

for_statement: 
    FOR LPAREN assignment SEMI expression SEMI ID INC RPAREN tail
    {
        $$ = new Node("for_statement");
        $$->addChild(new Node("FOR"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("SEMI"));
        $$->addChild($5);
        $$->addChild(new Node("SEMI"));
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("INC"));
        $$->addChild(new Node("RPAREN"));
        $$->addChild($10);
    }
    | FOR LPAREN assignment SEMI expression SEMI ID DEC RPAREN tail
    {
        $$ = new Node("for_statement");
        $$->addChild(new Node("FOR"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("SEMI"));
        $$->addChild($5);
        $$->addChild(new Node("SEMI"));
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("DEC"));
        $$->addChild(new Node("RPAREN"));
        $$->addChild($10);
    }
    | FOR error RBRACE
    {
        std::cout << "[Erro sintático] Bloco FOR com erro terminado na linha: " << driver.lineNumber << std::endl;
        $$ = new Node("error");
    }
;

while_statement: 
    WHILE LPAREN expression RPAREN tail
    {
        $$ = new Node("while_statement");
        $$->addChild(new Node("WHILE"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("RPAREN"));
        $$->addChild($5);
    }
    | WHILE error RBRACE
    {
        std::cout << "[Erro sintático] Bloco WHILE com erro terminado na linha: " << driver.lineNumber << std::endl;
        $$ = new Node("error");
    }
;

tail: 
    LBRACE statements RBRACE
    { 
        $$ = new Node("tail");
        $$->addChild(new Node("LBRACE"));
        $$->addChild($2);
        $$->addChild(new Node("RBRACE"));
    }
;

assignment: 
    variable ASSIGN expression
    {
        SymbolInfo* info = driver.m_symbolTable.find(std::get<std::string>($1->value));

        if (info->type == TokenType::UNDEFINED) {
            std::cout << "[Erro semantico] Não é possivel atribuir valor a variavel " << std::get<std::string>($1->value)
            << " pois não foi declarada, erro ocorrido na linha: " << driver.lineNumber << std::endl;
            $$ = new Node("error");
        }else if (info->type != $3->type) {
                std::cout << "[Erro semantico] Tentativa de atribuir valor " << typeToStr($3->type) << " a variavel " 
                << std::get<std::string>($1->value) << " do tipo " << typeToStr(info->type) << " na linha: " 
                << driver.lineNumber << std::endl;
            $$ = new Node("error");
        } else {
            $$ = new Node("assignment");
            $$->addChild($1);
            $$->addChild(new Node("ASSIGN"));
            $$->addChild($3);
        }
    }
;

io_statement:
    PRINT LPAREN literal RPAREN
    {
        $$ = new Node("statement");
        $$->addChild(new Node("PRINT"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("RPAREN"));
    }
    | PRINT LPAREN variable RPAREN
    {

        $$ = new Node("statement");
        $$->addChild(new Node("PRINT"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("RPAREN"));
    }
    | SCAN LPAREN variable RPAREN
    {
        $$ = new Node("statement");
        $$->addChild(new Node("SCAN"));
        $$->addChild(new Node("LPAREN"));
        $$->addChild($3);
        $$->addChild(new Node("RPAREN"));
    }
;

statement:
    if_statement
	{ 
        $$ = new Node("statement");
        $$->addChild($1);
	}
	| for_statement
	{ 
        $$ = new Node("statement");
        $$->addChild($1);
	}
	| while_statement
	{
        $$ = new Node("statement");
        $$->addChild($1);
	}
	| assignment SEMI
	{
        $$ = new Node("statement");
        $$->addChild($1);
        $$->addChild(new Node("SEMI"));
	}
	| CONTINUE SEMI
	{ 
        $$ = new Node("statement");
        $$->addChild(new Node("CONTINUE"));
        $$->addChild(new Node("SEMI"));
	}
	| BREAK SEMI
	{ 
        $$ = new Node("statement");
        $$->addChild(new Node("BREAK"));
        $$->addChild(new Node("SEMI"));
	}
	| ID INC SEMI
	{
        $$ = new Node("statement");
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("INC"));
        $$->addChild(new Node("SEMI"));
	}
	| INC ID SEMI
	{
        $$ = new Node("statement");
        $$->addChild(new Node("INC"));
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("SEMI"));
	}
	| ID DEC SEMI
	{
        $$ = new Node("statement");
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("DEC"));
        $$->addChild(new Node("SEMI"));
	}
	| DEC ID SEMI
	{
        $$ = new Node("statement");
        $$->addChild(new Node("DEC"));
        $$->addChild(new Node("ID"));
        $$->addChild(new Node("SEMI"));
	}
    | io_statement SEMI
    {
        $$ = new Node("statement");
        $$->addChild($1);
        $$->addChild(new Node("SEMI"));
    }
;

%%

void Cd::Parser::error(const std::string& message) 
{
    std::cout << "[Error sintático] Na linha: " << driver.lineNumber << " aaaa " <<  message << std::endl;
}

void Cd::Parser::report_syntax_error (const context& ctx) const
{
    int res = 0;
    std::cout << "[Erro sintático] ";
    // Report the tokens expected at this point.
    {
        symbol_kind_type expected[10];

        std::cout << "Esperava-se ";
        int n = ctx.expected_tokens(expected, 10);
        for (int i = 0; i < n; ++i) {
            if (i != 0)
                std::cout << " ou ";

            std::cout << symbol_name (expected[i]);
        }
    }

    {
    symbol_kind_type lookahead = ctx.token();
    if (lookahead != symbol_kind::S_YYEMPTY)
      std::cout << " porém foi colocado " << symbol_name (lookahead);
    }
    std::cout << " na linha " << driver.lineNumber << '\n';
}