.sec Objects

objects = ['
struct Sym {							// == Abstract Symbolic Type (AST) ==
// ---------------------------------------------------------------------------
	string tag;							// data type / class
	string val;							// symbol value
// --------------------------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*);
// -------------------------------------------------------------- par{}ameters
	map<string,Sym*> par;				// can be used as class slots
	void partag(Sym*);					// par[tag]=obj
	void parval(Sym*);					// par[val]=obj
// ------------------------------------------------------------------- dumping
	virtual string dump(int depth=0);	// dump symbol object as text
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:\'V\'> Str-like header string
	string pad(int);					// padding with tree decorators
// -------------------------------------------------------- compute (evaluate)
	virtual Sym* eval();
};'
'// =================================================================== SCALARS'
'struct Scalar: Sym { Sym*eval(); };'
'struct Str: Scalar {};'
'struct Int: Scalar {};'
'struct Num: Scalar {};'
'// ================================================================ COMPOSITES'
'struct List: Sym {};'
'// =============================================================== FUNCTIONALS'
'struct Op:Sym {};'
'struct Lambda:Sym {};'
'
extern void W(Sym*);								// \ ==== writers ====
extern void W(string);								// /
'
]

.sec Files

.inc ../lex/files

files = [
	MODULE+'.bI' MODULE+'.blog'
#	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' #'Makefile'
	yacc lex hpp cpp make
	'bat.bat' meta readme
]

.inc ../lex/bat

