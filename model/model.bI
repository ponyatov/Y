TITLE = 'metamodel'
ABOUT = 'tiny language metamodel'
GITHUB = 'https://github.com/ponyatov/Y/tree/dev/'+MODULE+'/'
COLOR = 'peachpuff'
LOGO = 'warning64x64'

.sec Objects

objects_hpp = [
'struct Sym {							// Abstract Symbolic Type
	string tag;							// type/class
	string val;							// value
// --------------------------------------- constuructors
	Sym(string,string);					// <T:V>
	Sym(string);						// token
// --------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*);
// --------------------------------------- par{}ameters
	map<string,Sym*> par;
	void parval(Sym*);
// --------------------------------------- dumping
	virtual string dump(int depth=0);	// dump object to string
	virtual string tagval();			// <T:V>
	string tagstr();					// <T:\'V\'>
	string pad(int);
// --------------------------------------- compute/evaluate object
//	virtual Sym* eval();
// --------------------------------------- operators
	virtual Sym* pfxplus();				// +A	prefix
	virtual Sym* pfxminus();			// -A	prefix
};'
'// -------------------------------------- writers
extern void W(Sym*);
extern void W(string);
'
'struct Str: Sym { Str(string); string tagval(); };'
'
struct Hex: Sym { Hex(string); };
struct Bin: Sym { Bin(string); };
struct Int: Sym { Int(string); long val;   string tagval();
	Sym*pfxplus(); Sym*pfxminus(); };
struct Num: Sym { Num(string); double val; string tagval();
	Sym*pfxplus(); Sym*pfxminus(); };
'
'
struct List: Sym { List(); };
struct Tuple: Sym { Tuple(Sym*,Sym*); };
'
'
struct Op: Sym { Op(string); };
struct Lambda: Sym { Lambda(); };
'
]

objects_cpp = [
'// ------------------------------------------------------- writers
void W(Sym*o) { cout<<o->dump(); }
void W(string s) { cout<<s; }
'
'// ------------------------------------------------------- symbol
Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("",V) {}
string Sym::dump(int depth) { string S = "\\n"+pad(depth)+tagval();
	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)
		S+= ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S+= (*it)->dump(depth+1);
	return S; }
string Sym::tagval()	{ return "<"+tag+":"+val+">"; }
string Sym::tagstr()	{ return "<"+tag+":\'"+val+"\'>"; }
string Sym::pad(int n)	{ string S; for (int i=0;i<n;i++) S+=\'\\t\'; return S; }
void Sym::push(Sym*o)	{ nest.push_back(o); }
void Sym::parval(Sym*o)	{ par[o->val]=o; }
//Sym* Sym::eval() { return this; }
Sym* Sym::pfxplus()		{ val="+"+val; return this; }
Sym* Sym::pfxminus()	{ val="-"+val; return this; }
'
'// ------------------------------------------------------- string
Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
'
'// ------------------------------------------------------- hex/bin
Hex::Hex(string V):Sym("hex",V) {}
Bin::Bin(string V):Sym("bin",V) {}
'
'// ------------------------------------------------------- int
Int::Int(string V):Sym("int","") { val=atoi(V.c_str()); }
string Int::tagval() { ostringstream os;
	os << "<" << tag << ":" << val << ">"; return os.str(); }
Sym* Int::pfxplus() { return this; }
Sym* Int::pfxminus() { val=-val; return this; }
'
'// ------------------------------------------------------- num
Num::Num(string V):Sym("num","") { val=atof(V.c_str()); }
string Num::tagval() { ostringstream os;
	os << "<" << tag << ":" << val << ">"; return os.str(); }
Sym* Num::pfxplus() { return this; }
Sym* Num::pfxminus() { val=-val; return this; }
'
'// ------------------------------------------------------- [list]
List::List():Sym("[","]") {}
'
'// ------------------------------------------------------- tu,ple
Tuple::Tuple(Sym*A,Sym*B):Sym("","") { push(A); push(B); }
'
'// ------------------------------------------------------- operator
Op::Op(string V):Sym("op",V) {}
'
'// ------------------------------------------------------- {lambda}
Lambda::Lambda():Sym("^","^") {}
'
]

.sec Files

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

.sec Parser /yacc/

yacc = next + file @ 'ypp.ypp'
yacc += '%{\n#include "hpp.hpp"\n%}\n'
yacc += '%defines %union { Sym*o; }\t\t/* syntax tree element sturcture */\n'
yacc += '
%token <o> SYM NUM STR				/* scalars:  symbol number \'string\' */
%token <o> L R LQ RQ LB RB			/* brackets: ( ) [ ] { } */
%token <o> EQ AT DOT COMMA 			/* operators: = @ . , */
%token <o> COLON PERC				/* operators: : % */
%token <o> ADD SUB MUL DIV POW		/* operators: + - * / ^ */

%type <o> ex scalar 				/* expression scalar */
%type <o> list tuple lambda			/* [list] tu,ple {lambda} */

%left PFX
%left PERC
%left EQ
%left ADD SUB
%left MUL DIV
%left POW
%left COLON
%left COMMA 
'
#%type <o> tuple				/* tu,ple */
yacc += '%%\n'
yacc += 'REPL\t: | REPL ex { W($2); W("\\n"); } ;\n'
yacc += '
scalar	: SYM | NUM | STR ;
'
yacc += '
ex		: scalar
		| tuple
		| SYM L ex R		{ $$=new Op("@"); $$->push($1); $$->push($3); }
		| ex AT ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex COLON ex		{ $$=new Sym($1->val,$3->val); }
		| L ex R			{ $$=$2; }
		| LQ list RQ		{ $$=$2; }
		| LB lambda RB		{ $$=$2; }
		| ADD ex %prec PFX	{ $$=$2->pfxplus(); }
		| SUB ex %prec PFX	{ $$=$2->pfxminus(); }
		| ex EQ ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex ADD ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex SUB ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex MUL ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex DIV ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex POW ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex DOT ex			{ $$=$2; $$->push($1); $$->push($3); }
		| ex PERC ex		{ $$=$1; $$->push($3); }
;\n'
yacc += '
list	:					{ $$ = new List(); }
		| list ex			{ $$=$1; $$->push($2); } ;
'
yacc += '
tuple	: ex COMMA ex		{ $$ = new Tuple($1,$3); }
		| tuple COMMA ex	{ $$=$1; $$->push($3); } ;
'
yacc += '
lambda	:					{ $$ = new Lambda(); }
		| lambda SYM COLON	{ $$ = $1; $$->parval($2); }
		| lambda ex			{ $$=$1; $$->push($2); } ;
'
yacc += '%%\n'

yacc_hpp = [
'extern int yyparse();'
'extern void yyerror(string);'
'#include "ypp.tab.hpp"'
]

.sec Lexer /lex/

lex	= next + file @ 'lpp.lpp'
lex += '%{\n#include "hpp.hpp"\nstring LexString;\n%}\n'
lex += '%option noyywrap\n%option yylineno\n'
lex += 'S [\\+\\-]?\nN [0-9]+\n'
lex += '%x lexstring\n'
lex += '%%\n'
lex += '#[^\\n]*\t\t\t\t{}\t\t\t\t\t/* comment */\n'
lex += '\n\t\t\t\t\t\t\t\t\t\t/* string parser */
\'				{ BEGIN(lexstring); LexString=""; }
<lexstring>\'	{ BEGIN(INITIAL); yylval.o = new Str(LexString); return STR; }
<lexstring>\\\\t	{ LexString+=\'\\t\'; }
<lexstring>\\\\n	{ LexString+=\'\\n\'; }
<lexstring>\\\\.	{ LexString+=yytext[1]; }
<lexstring>.	{ LexString+=yytext[0]; }
'
lex += '
										/* numbers */
{S}{N}				TOC(Int,NUM)		/* integer */
0b[01]+				TOC(Bin,NUM)		/* binary */
0x[0-9A-F]+			TOC(Hex,NUM)		/* hexadecimal */
{S}{N}\.{N}			TOC(Num,NUM)		/* float */
{S}{N}[eE]{S}{N}	TOC(Num,NUM)		/* exponential */
\n'
lex += '
[a-zA-Z0-9_]+		TOC(Sym,SYM)		/* symbol */
'
lex += '
\\(					TOC(Op,L)			/* brackets */
\\)					TOC(Op,R)
\\[					TOC(Op,LQ)
\\]					TOC(Op,RQ)
\\{					TOC(Op,LB)
\\}					TOC(Op,RB)
'
lex += '
\\=					TOC(Op,EQ)			/* operators */
\\@					TOC(Op,AT)
\\.					TOC(Op,DOT)
\\,					TOC(Op,COMMA)
\\:					TOC(Op,COLON)
\\%					TOC(Op,PERC)
\\+					TOC(Op,ADD)
\\-					TOC(Op,SUB)
\\*					TOC(Op,MUL)
\\/					TOC(Op,DIV)
\\^					TOC(Op,POW)
'
lex += '\n[ \\t\\r\\n]+\t\t\t{}\t\t\t\t\t/* drop spaces */\n'
lex += '.\t\t\t\t\t{}\t\t\t\t\t/* drop undetected */\n'
lex += '%%\n'

lex_hpp = [
'extern int yylex();'
'extern int yylineno;'
'extern char* yytext;'
'#define TOC(C,X) { yylval.o = new C(yytext); return X; }'
]

.sec Headers /hpp/

hpp	= next + file @ 'hpp.hpp'
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n\n'
hpp += '#include "meta.hpp"\t\t\t\t\t\t// metainformation constants\n'
hpp += '
#include <iostream>\t\t\t\t\t\t// std. includes
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;
\n'
hpp += objects_hpp/'\n'+'\n'
hpp += '\t\t\t\t\t\t\t\t\t\t// lexer/parser interface\n'
hpp += lex_hpp/'\n'+'\n'
hpp += yacc_hpp/'\n'+'\n'
hpp += '\n#endif // _H_'+upcase@MODULE+'\n'

.sec C++ core /cpp/

cpp	= next + file @ 'cpp.cpp'
cpp += '#include "hpp.hpp"\n'
cpp += '#define YYERR "\\n\\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\\n\\n"\n'
cpp += 'void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }\n'
cpp += 'int main(int argc, char *argv[]) {
	cout << "#\\t" << MODULE << " : " << TITLE << "\\n#\\t" << ABOUT << "\\n";
	cout << "#\\t"<< /* (c) */ AUTHOR << "\\n";
	return yyparse(); }
'
cpp += objects_cpp/'\n'+'\n'

.sec Makefile

bi	= '../../meta/meta.bI'
log	= 'meta.blog'

.inc ../lex/tinymake


.sec (g)vim helper

files = [
	bi log yacc lex hpp cpp make
	'bat.bat' readme # meta win32rc
]

.inc ../lex/bat
