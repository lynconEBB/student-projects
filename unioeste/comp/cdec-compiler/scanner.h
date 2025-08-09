#ifndef SCANNER_H
#define SCANNER_H

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Cd_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL Cd::Parser::symbol_type Cd::Scanner::getNextToken()

#include <iostream>
#include "parser.h"

namespace Cd {
    class Driver;

    class Scanner : public yyFlexLexer {
    public:
        Scanner(Driver &driver, std::istream& inStream) : m_driver(driver), yyFlexLexer(inStream, std::cout) {}
        virtual Cd::Parser::symbol_type getNextToken();

    private:
        Driver& m_driver;
    }; 
}

#endif