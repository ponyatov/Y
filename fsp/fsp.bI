
MODULE	  "FSP skeleton"
TITLE	= 'Free Syntax Programming'
ABOUT	= 'tiny portable declarative programming translator'

.sec Files

next = (dir "mkdir")@'next' "generation"

# README.md

readme	= next+file@'README.md'		" README "
readme += '# ![logo](https://github.com/ponyatov/icons/raw/master/'+LOGO+'.png)'
readme += ' '+MODULE+' : '+TITLE+'\n'
readme += '### '+ABOUT+'\n'
readme += '\n'+AUTHOR+'\n'
readme += '\nlicence: '+LICENSE+'\n'
readme += '\nGitHub: '+GITHUB+'\n'
readme += '\n### ![warning](https://github.com/ponyatov/icons/raw/master/'
readme += 'warning64x64.png) '
readme += 'Powered by bI language system\n'

# meta.hpp

meta	= next+file@'meta.hpp'		# metainfo defines (AUTHOR,TITLE,..)
meta += '#ifndef _H_META
													// ==== metainformation ====
#define _H_META\n'
meta += '
#define TITLE "'+TITLE+'"
#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev"
#define AUTOGEN "/***** DO NOT EDIT: this file was autogened by bI *****/"
#define LOGO "'+LOGO+'"
#define ABOUT "'+ABOUT+'"\n'
meta += '\n#endif // _H_META'

# parser

yacc	= next+file@'ypp.ypp'		" parser "
yacc += '%{\n#include "hpp.hpp"\n%}\n'
yacc += '%defines %union { Sym*o; }\n'
yacc += '%token <o> SYM\n'
yacc += '%type  <o> ex\n'
yacc += '%%\n'
yacc += 'REPL : | REPL ex { W($2); } ;\n'
yacc += 'ex : SYM ;\n'
yacc += '%%\n'

# lexer

lex		= next+file@'lpp.lpp'		" lexer "
lex += '%{\n#include "hpp.hpp"\nstring LexString;\n%}\n'
lex += '%option noyywrap\n%option yylineno\n'
lex += '%%\n'
lex += '#[^\\n]*\t\t\t{}\n'
lex += '[a-zA-Z0-9_]+\t{ yylval.o = new Sym(yytext); return SYM; }\n'
lex += '[ \\t\\r\\n]+\t\t{}\n.\t\t\t\t{}\n'
lex += '%%\n'

# headers

hpp		= next+file@'hpp.hpp'		" headers "
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'

hpp += '
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
'

hpp += '
struct Sym {
	string tag;
	string val;
	Sym(string);
	virtual string dump();
};
'

hpp += '
extern void W(Sym*);\nextern void W(string);
'

hpp += '
// ========================================================== PARSER INTERFACE
													// == lexer interface ==
extern int yylex();									// parse next token
extern int yylineno;								// current source line
extern char* yytext;								// found token text
extern void incLude(Sym*inc);						// .include file
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
													// == parser interface ==
extern int yyparse();								// run parser
extern void yyerror(string);						// error callback
#include "ypp.tab.hpp"								// token defines for lexer
'

hpp += '\n#endif // _H_'+upcase@MODULE+'\n'

# c++ core

cpp		= next+file@'cpp.cpp'		" c++ core "
cpp += '#include "hpp.hpp"\n'
cpp += '#define YYERR "\\n\\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\\n\\n"\n'
cpp += 'void yyerror(string msg) { cerr<<YYERR; exit(-1); }\n'
cpp += 'int main () { return yyparse(); }\n'

cpp += '
// ======================================================= writers
void W(Sym* o)		{ cout << o->dump(); }
void W(string s)	{ cout << s; }
'

cpp += '
Sym::Sym(string V) { tag="sym"; val=V; }
string Sym::dump()	{ return "<"+tag+":"+val+">"; }
'

# Makefile

make	= next+file@'Makefile'		" project management scripts "
make += '.PHONY: exec\nexec: ./'+MODULE+'.exe\n\t./'+MODULE+'.exe < cpp.cpp\n'
make += 'C = cpp.cpp ypp.tab.cpp lex.yy.c\n'
make += 'H = hpp.hpp ypp.tab.hpp meta.hpp\n'
make += 'L =\n'
make += './'+MODULE+'.exe: $(C) $(H)\n\t$(CXX) $(CXXFLAGS) -o $@ $(C) $(L)\n'
make += '
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
'

# FILES

allfiles = [
		readme
	files = [
#		bi		= next+file@'fsp.bI'		" source "
#		log		= next+file@'fsp.blog'		" log "
		yacc lex hpp cpp make meta
		bat		= next+file@'bat.bat'		# (g)vim helper /win32/
	]
		gitignore = next+file@'.gitignore'	# ignore files in git repository
]

# bat.bat

bat += '@start .\n'
bat += '@gvim -c "colorscheme peachpuff" -p '+files/' '+'\n'


.sec Comment

X:Y

class:comment

comment@x

.sec Class subsystem

.end
X:Y
X='zzz'
X:Y


