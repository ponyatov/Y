/* DO NOT EDIT: this file was autogened by bI language system */
/* <module:sym> */
#ifndef _H_sym
#define _H_sym

#define MODULE "sym"
#define TITLE "pure symbolic script engine"
#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev/sym"
#define AUTOGEN "DO NOT EDIT: this file was autogened by bI language system"

#include <map>					// \ required std includes
#include <vector>
#include <iostream>
#include <cstdlib>				// /
#ifdef __MINGW32__				// \ win32 specific
#include <direct.h>				// /
#else							// \ Linux & others POSIX-compatibles
#include <sys/stat.h>			// /
#endif
using namespace std;
								// syntax core interface
extern int yylex();				// \ lexer
extern char *yytext;			// 		regexp-parsed text
extern int yylineno;			// /	current line number 
extern int yyparse();			// \ parser
extern void yyerror(string);	// syntax error callback
#include "sym.tab.hpp"			// / parser defines
								
void W(char);					// \ writers
void W(string);					// //
void W(string*);				// //
#endif // _H_sym
