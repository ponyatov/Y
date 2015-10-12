
.title		pure symbolic script engine
.github		https://github.com/ponyatov/Y/tree/dev/sym

.module 	sym

.sec		Kernel source file templates

.sec-		Project files

.file README.md
$'# ',TITLE
\#\#\# (self-computed source files)
$'\n',$AUTHOR,'\n\nlicense:\t',LICENSE,'\n\ngithub:\t\t',GITHUB
.eof

.file .gitignore
*~
*.swp
$MODULE,'.exe'
$MODULE,'.elf'
$MODULE,.bIog
$MODULE,.toc
$'/',MODULE,'/','\n/tmp/'
lex.yy.c
$MODULE,.tab.cpp
$MODULE,.tab.hpp
.eof

.file Makefile
\# $AUTOGEN
\# <module:$MODULE,'>'

.PHONY: all
$'all: ./',MODULE,'$(EXE)'
$'\t./',MODULE,'$(EXE) < ../',MODULE,'.bI > ',MODULE,'.bIog'

.PHONY: clean
clean:
$'\trm -rf ./',MODULE,'$(EXE) *~ ',MODULE,'.bIog tmp sym lex.yy.c ',MODULE,'.tab.?pp'
$'\ttouch ',MODULE,'.bIog'

.PHONY: upgrade
upgrade:
$'\tcp ',MODULE,'/README.md ./'
$'\tcp ',MODULE,'/vimedit.bat ./'
$'\tcp ',MODULE,'/.gitignore ./'
$'#\tcp ',MODULE,'/Makefile ./'
$'\tcp ',MODULE,'/',MODULE,'.ypp ./'
$'\tcp ',MODULE,'/',MODULE,'.lpp ./'
$'\tcp ',MODULE,'/',MODULE,'.hpp ./'
$'\tcp ',MODULE,'/',MODULE,'.cpp ./'

$'C = ',MODULE,'.cpp lex.yy.c ',MODULE,'.tab.cpp'
$'H = ',MODULE,'.hpp ',MODULE,'.tab.hpp'
$'./',MODULE,'$(EXE): $(C) $(H)'
	\$(CXX) \$(CXXFLAGS) -o \$\@ \$(C)
$'lex.yy.c: ',MODULE,'.lpp'
	flex \$<
$'sym.tab.cpp: ',MODULE,'.ypp'
	bison \$<
.eof

.sec-	Symbolic computing core

.file sym.ypp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
$'%{\n#include "',MODULE,'.hpp"\n%}'
%defines
%union {
	char c;
	string *s;
	biObject *o;
}
%token <c> CHAR EOL
%token <s> STR
%token <o> DIRECTIVE
# QX SX
# %token <o> FMODULE FFILE FEOF
# %token <o> SYM STR
%%
$MODULE,' :'
$'\t| ',MODULE,' DIRECTIVE\t\t{ W($2); }'
$'\t| ',MODULE,' STR\t\t\t{ W($2); }'
$'\t| ',MODULE,' EOL\t\t\t{ W($2); }'
$'\t| ',MODULE,' CHAR\t\t\t{ W($2); }'
;
%%
.eof

.file sym.lpp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
$'%{\n#include "',MODULE,'.hpp"'
\#define TC(X)		{ yylval.c = yytext[0]; 			return X; }
\#define T1(X)		{ yylval.c = yytext[1]; 			return X; }
\#define TS(X)		{ yylval.s = new string(yytext);	return X; }
\#define TO(C,X)		{ yylval.o = new C(yytext);			return X; }
%}
%option noyywrap
%option yylineno
%%
\\r				{}							/* drop DOS 0x0D char */
\\\\.				T1(CHAR)					/* escaped char */
^\\.[a-z]+[^\\n]*	TO(biDirective,DIRECTIVE)	/* .anydirective */
\\n				TC(EOL)						/* end of line (CR) */
.				TC(CHAR)					/* any other char */
%%
.eof

.file sym.hpp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
\#ifndef _H_$MODULE
\#define _H_$MODULE

\#define MODULE "$MODULE,'"'
\#define TITLE "$TITLE,'"'
\#define AUTHOR "$AUTHOR,'"'
\#define LICENSE "$LICENSE,'"'
\#define GITHUB "$GITHUB,'"'
\#define AUTOGEN "DO NOT EDIT: this file was autogened by bI language system"

\#include <map>							// \\ required std includes
\#include <vector>
\#include <iostream>
\#include <cstdlib>
\#include <cstdio>
\#include <cassert>						// /
\#ifdef __MINGW32__						// \\ win32 specific
\#include <direct.h>						// /
\#else									// \\ Linux & others POSIX-compatibles
\#include <sys/stat.h>					// /
\#endif
using namespace std;

struct biObject {
	string tag;							// object class name or data type
	string value;						// object value
	biObject(string,string);
	virtual string dump(int depth=0);	// dump	object in string form
};

struct biDirective: biObject {
	biDirective(string);
};

struct biModule: biObject {
	biModule(string);
};
extern biModule *bi_module;

										// syntax core interface
extern int yylex();						// \\ lexer
extern char *yytext;					// 		regexp-parsed text
extern int yylineno;					// /	current line number 
extern int yyparse();					// \\ parser
extern void yyerror(string);			// syntax error callback
$'#include "',MODULE,'.tab.hpp"'					// / parser defines

void W(char     ,bool to_file=true);	// \\ writers
void W(string   ,bool to_file=true);
void W(string*  ,bool to_file=true);
void W(biObject*,bool to_file=true);	// //

\#endif // _H_$MODULE
.eof

.file sym.cpp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
$'#include "',MODULE,'.hpp"'

// \\\\ Object
biObject::biObject(string T,string V)	{ tag = T; value = V; }
string biObject::dump(int depth)		{ return "<"+tag+":"+value+">"; }
// //

// \\\\ Directive
biDirective::biDirective(string V):biObject("",V) {
	// autogenerate tag & value
	while ( value.size() && (value[0] != ' ' && value[0] != '\\t') )
		{ tag += value[0]; value.erase(0,1); }
	while ( value.size() && (value[0] == ' ' || value[0] == '\\t') )
		{                  value.erase(0,1); }
	// process specific directive tag
	if (tag == ".module")	bi_module = new biModule(value);
}
// //

// \\\\ Module
biModule::biModule(string V):biObject("module",V) {
	mkdir(value.c_str());
}
biModule *bi_module = new biModule("tmp");
// //

// \\\\ writers
void W(char      c, bool to_file) { cout <<  c; }
#	if (to_file && bi_file) bi_file->W(c); }
void W(string    s, bool to_file) { cout <<  s; }
#	if (to_file && bi_file) bi_file->W(s); }
void W(string   *s, bool to_file) { cout << *s; }
#	if (to_file && bi_file) bi_file->W(*s); }
void W(biObject *o, bool to_file) { cout << o->dump(); }
#	if (to_file && bi_file) bi_file->W(o->dump()); }
// //

void yyerror(string msg) {
	cout << "\\n\\n" << msg << "\#" << yylineno << ":" << yytext << "\\n\\n";
	cerr << "\\n\\n" << msg << "\#" << yylineno << ":" << yytext << "\\n\\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
#	env_init();
#	cout << "\# " << AUTOGEN << "\\n";
#	cout << "\# <module:" << MODULE << ">\\n";
#	cout << "\# argv[0]:\\t" << argv[0] << "\\n\\n";
	return yyparse();
}
.eof

.sec-	.bat for module edit in (g)vim tabs

.file vimedit.bat
\@rem $AUTOGEN
gvim -p $MODULE,'.bI ',MODULE,'.bIog ',MODULE,'.toc ',FILES/' '
.eof

.end

.file sym.ypp
$'\t| ',MODULE,' FMODULE EOL\t{ W($2,false); W($3,false); }'
$'\t| ',MODULE,' FFILE EOL\t\t{ W($2,false); W($3,false); }'
$'\t| ',MODULE,' FEOF\t\t\t{ W($2,false); }'
$'\t| ',MODULE,' SX SYM\t\t{ W($2); W($3); }'
.eof

.file sym.lpp
\#define TO(C,X)		{ if (env[yytext]) yylval.o = env[yytext]; \
					else yylval.o = new biObject(C,yytext); return X; }
\#define TX(C,X)		{ if (env[yytext]) yylval.o = env[yytext]; \
					else yylval.o = new C(yytext); return X; }
string StringBuffer;

%x ss
%x xx

\\\\.					T1(CHAR)		/* escape char prefixed */
\#[^\\n]*\\n			{}				/* drop line comment */

'					{BEGIN(ss); StringBuffer="\'";}
<ss>'				{BEGIN(INITIAL);
					yylval.o = new biObject("str",StringBuffer+"\'"); return STR;}
<ss>\\\\				{StringBuffer+="\\\\";}
<ss>\\t				{StringBuffer+="\\t";}
<ss>\\n				{StringBuffer+="\\n";}
<ss>.				{StringBuffer += yytext;}

\\\$					{BEGIN(xx); TC(SX);}
<xx>[ \\t\\n,]			{BEGIN(INITIAL); TC(EOL);}
<xx>[a-zA-Z]+		TO("sym",SYM)

^\\.module[^\\n]*		TX(biDirective,FMODULE)		/* .module */
^\\.file[^\\n]*		TX(biDirective,FFILE)		/* .file */
^\\.eof				TX(biDirective,FEOF)		/* .eof */
^\\.title[^\\n]*		TX(biDirective,FMODULE)		/* .title */
^\\.author[^\\n]*		TX(biDirective,FMODULE)		/* .author */
^\\.github[^\\n]*		TX(biDirective,FMODULE)		/* .github */
^\\.license[^\\n]*	TX(biDirective,FMODULE)		/* .license */
^\\.sec[^\\n]*		TX(biDirective,FMODULE)		/* .sec */

%%
.eof

.file sym.hpp
extern map<string,biObject*> env;		// \\ environment (global var registry)
extern void env_init();					// /
struct biModule: biObject {
	biModule(string);
};
extern biModule *bi_module;
struct biFile: biObject {
	FILE *fh;
	biFile(string);
	~biFile();
	void W(char);
	void W(string);
};
extern biFile *bi_file;
								
.eof

.sec-	Low-Level symbolic engine code in C++

.file sym.cpp
// \\ Environment
map<string,biObject*> env;
void env_init() {
	\#ifdef __MINGW32__
		env["EXE"] = new biObject("const",".exe");
	\#else
		env["EXE"] = new biObject("const",".elf");
	\#endif
	env["AUTHOR"] = new biObject(".author",AUTHOR);
	env["LICENSE"] = new biObject(".license",LICENSE);
	env["GITHUB"] = new biObject(".github",GITHUB);
	env["FILES"] = new biObject("list","");
	env["AUTOGEN"] = new biObject(".autogen",AUTOGEN);
	// internal functions
}
// /


	if (tag == ".file")		bi_file = new biFile(value);
	if (tag == ".eof")		if (bi_file) delete bi_file;
}

	if (bi_file) delete bi_file;
	env["MODULE"] = this;
}
// /
// \\ File
biFile::biFile(string V):biObject("file",V) {
	if (bi_file) delete bi_file;
	assert ( fh = fopen((bi_module->value+"/"+value).c_str(),"w") );
	bi_file = this;
}
biFile::~biFile() { fclose(fh); bi_file = NULL; }
void biFile::W(char c)		{ fprintf(fh,"%c",c); }
void biFile::W(string s)	{ fprintf(fh,"%s",s.c_str()); }
biFile *bi_file = NULL;
// /
void W(char      c, bool to_file) { cout <<  c; 
	if (to_file && bi_file) bi_file->W(c); }
void W(string    s, bool to_file) { cout <<  s;
	if (to_file && bi_file) bi_file->W(s); }
void W(string   *s, bool to_file) { cout << *s;
	if (to_file && bi_file) bi_file->W(*s); }
void W(biObject *o, bool to_file) { cout << o->dump();
	if (to_file && bi_file) bi_file->W(o->dump()); }
// /
.eof


