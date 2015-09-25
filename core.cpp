#include "bI.hpp"

// object

biObject::biObject(const char* C) { 
	cls = new string(C);
	val = new string();
}

biObject::biObject(const char* C,const char* V) { 
	cls = new string(C);
	val = new string(V);
}

biObject::biObject(const char* C,char* V) { 
	cls = new string(C);
	val = new string(V);
}

biObject::biObject(const char* C,string* V) { 
	cls = new string(C);
	val = V;
}

biObject::biObject(string* C,string* V) { 
	cls = C;
	val = V;
}

string* biObject::dump()	{ return new string("<"+*cls+":"+*val+">"); }
string* biObject::eval()	{ return val; }

void biObject::join(biObject*)	{}

// generic class

void biClass::init(biObject *sym) {
	if (bi_class) delete bi_class; bi_class=this;
	cpp = new biFile(new string(*val+".cpp"),'w');
	hpp = new biFile(new string(*val+".hpp"),'w');
	cpp->W(autogen("//",*dump()));
	cpp->W("#include \""+*val+".hpp\"\n\n");
	bi_module->files(*val);
	bi_class_reg[*val]=val;
}
biClass::biClass(biObject *sym):biObject("class",sym->val) {
	init(sym);
	super="";
}
biClass::biClass(biObject *sym,biObject *sup):biObject("class",sym->val) {
	init(sym);
	super=*sup->val;
}
biClass::~biClass()	{ 
	hpp->W(autogen("//",*dump()));
	if (super.size())	hpp->W(" : public "+super+" {\n");
	else				hpp->W(" {\n");
	for (list<string>::iterator f = fld.begin(); f!=fld.end(); f++)
		hpp->W(*f);
	hpp->W("}\n\n");
	delete cpp; bi_class=NULL; 
	delete hpp;
}
string* biClass::dump() {
	if (super.size())	return new string("<"+*cls+":"+*val+",super:"+super+">");
	else				return biObject::dump();
}

biClass* bi_class=NULL;
map<string,string*> bi_class_reg;

// list

biList::biList():biObject("list","()")				{}
biList::biList(biObject* X):biObject("list","()")	{ join(X); }
void biList::join(biObject* X)						{ L.push_back(X); }

string* biList::dump() {
	string* s = new string("<"+*cls+":(");
	for (list<biObject*>::iterator it=L.begin(); it!=L.end(); it++) {
		*s += *((*it)->dump());
	}
	*s += ")>";
	return s; 
}

// string

biString::biString(char *V):biObject("str",V) {}

// pair

biPair::biPair(biObject* X,biObject* Y):biObject("pair","") {
	A=X; B=Y; 
}

string* biPair::dump()	{ return new string("("+*A->dump()+":"+*B->dump()+")"); }
string* biPair::eval()	{ return new string("("+*A->eval()+":"+*B->eval()+")"); }

// module

biModule::biModule(const char*m):biObject("module",m) {
#ifdef __MINGW32__
	mkdir(val->c_str());
#else
	mkdir(val->c_str(),0744);
#endif
	assert(make = fopen((*val+"/Makefile").c_str(),"w"));
	fprintf(make,"%s",autogen("#",*dump()).c_str());
	fprintf(make,".PHONY: default\ndefault: %s$(EXE)\n\n",val->c_str());
	files("main");
	assert(cpp=fopen((*val+"/"+*val+".cpp").c_str(),"w"));
	fprintf(cpp,"%s",autogen("//",*dump()).c_str());
	assert(hpp=fopen((*val+"/"+*val+".hpp").c_str(),"w"));
	fprintf(hpp,"%s",autogen("//",*dump()).c_str());
};

biModule::~biModule() {
	fprintf(make,(*val+"$(EXE): $(O_FILES)\n\t$(CXX)"
			   " -o $@ $(O_FILES)\n\n").c_str());
	fclose(make);
	fclose(cpp);
	fclose(hpp);
}

void biModule::depends(string X,string Y,string C) {
	fprintf(make,"%s: %s\n\t%s\n\n",X.c_str(),Y.c_str(),C.c_str());
}

void biModule::files(string cls) { 
	fprintf(make,"O_FILES += %s.o\n",cls.c_str());
	fprintf(make,"C_FILES += %s.cpp\n",cls.c_str());
	fprintf(make,"H_FILES += %s.hpp\n",cls.c_str());
	depends(
			cls+".o", 
			cls+".cpp"+" "+cls+".hpp", 
			"$(CXX) $(CXXFLAGS) -c -o $@ $<");
}

biModule *bi_module = new biModule("tmp");

// file

biFile::biFile(string *name,char m): biObject("file",name) {
	mode=m;
	string fname = string(*bi_module->val+"/"+*val);
	switch (mode) {
		case 'r': assert(fh=fopen(fname.c_str(),"r")); break;
		case 'w': assert(fh=fopen(fname.c_str(),"w")); break;
		default: yyerror(string("file mode ")+*dump());
	}
}
biFile::~biFile() { fclose(fh); }

string* biFile::dump()	{
	ostringstream os; 
	os << "<" << *cls << ":" << *val ;
	os << ",mode:" << mode << ",open:" << (fh==NULL ? "F" : "T") << ">";
	return new string(os.str());
}

void biFile::W(string s)	{ fprintf(fh,"%s",s.c_str());	}
void biFile::W(char c)		{ fprintf(fh,"%c",c);			}

biFile *bi_file = NULL;

// tex

TEX tex("bI.tex");

string TEX::fix(string s) {
	string T;
	for ( string::iterator c=s.begin(); c!=s.end(); c++) { switch (*c) {
		case '^':
		case '[':
		case ']':
		case '<': T+="\\textless "; break;
		case '>': T+="\\textgreater "; break;
		case '\\': T+=""; break;
		case '#': T+="\\#"; break;
		case '$': T+="\\$"; break;
		case '%': T+="\\%"; break;
		default: T+=*c; break;
	}}
	return T;
}

void TEX::W(string x)		{ body+=fix(x); }
void TEX::sec(int l,string x)		{ 
	switch (l) {
		case +1: body+="\\section{"+fix(x)+"}\n"; break;
		case -1: body+="\\subsubsection{"+fix(x)+"}\n"; break;
		default: body+="\\subsection{"+fix(x)+"}\n"; break;
	}}

TEX::TEX(const char *fn)	{ assert(fh=fopen(fn,"w")); }
TEX::~TEX()					{ 
	head+="\\documentclass[10pt]{article}\n";
	head+="\\usepackage[a5paper,landscape,margin=5mm]{geometry}\n";
	head+="\\title{"+title+"}\n";
	head+="\\author{"+author+"}\n";
	head+="\\begin{document}\n\\maketitle\n\\tableofcontents\n\n";
	foot+="\\end{document}\n";
	fprintf(fh,"%s",head.c_str());
	fprintf(fh,"%s",body.c_str());
	fprintf(fh,"%s",foot.c_str());
	fclose(fh); 
}

// directive

biDirective::biDirective(char *V):biObject("",V) {
	// autorename class
	while (val->at(0)!=' '&&val->at(0)!='\t') {
		*cls += val->at(0);
		val->erase(0,1);
		if (val->size()==0) break;
	}
	if (val->size())
		while (val->at(0)==' '||val->at(0)=='\t') val->erase(0,1);

	if (*cls==".title") 	tex.title=tex.fix(*val);
	if (*cls==".author") 	tex.author=tex.fix(*val);
	if (*cls==".sec")		tex.sec(0,*val);
	if (*cls==".sec+")		tex.sec(+1,*val);
	if (*cls==".sec-")		tex.sec(-1,*val);
	if (*cls==".module")	{
		if (bi_module) delete bi_module; bi_module=new biModule(val->c_str()); }
	if (*cls==".file")		{ 
		if (bi_file) delete bi_file; bi_file=new biFile(val,'w'); }
	if (*cls==".eof")		{
		if (bi_file) delete bi_file; bi_file=NULL; }
}

// lexer

biLexer::biLexer(biObject* s):biObject("lexer",s->val)	{
	bi_module->files(*val+".lex");
	bi_module->depends(*val+".lex.cpp",*val+".lpp","flex -o"+*val+".lex.cpp -P"+*val+" $<");
	lpp = new biFile(new string(*val+".lpp"),'w');
	lpp->W(
		"%{\n"
		"#include \""+*val+".lex.hpp\"\n"
		"#define T(C,X)	{ yylval.s=new sym(C,yytext); return X; }\n"
		"%}\n\n"
		"\%option noyywrap\n"
		"\%option yylineno\n\n"
	);
	hpp = new biFile(new string(*val+".lex.hpp"),'w');
	hpp->W(autogen("//",*dump()));
	bi_lexer=this;
}
biLexer *bi_lexer = NULL;

biLexer::~biLexer()		{
	lpp->W("%%\n");
	lpp->W("%%\n\n");
	delete lpp,hpp;
}

// autogenerated marker creator

string autogen(string pfx, string obj) {
	return string(
	pfx+" ************** DO NOT EDIT *************\n"+
	pfx+"   this file was autogened by bI system  \n"+
	pfx+" ************** DO NOT EDIT *************\n"+
	pfx+" "+obj+"\n\n"
	);
}

// writers

void W(string* s, bool tofile)	{ 
	cout << *s; 
	if (tofile&&bi_file) bi_file->W(*s); }
void W(string  s, bool tofile)	{ 
	cout <<  s; 
	if (tofile&&bi_file) bi_file->W( s); }
void W(char c, bool tofile)	{ 
	cout << c; 
	if (tofile&&bi_file) bi_file->W( c); }

// main

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	cout << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() { 
	yyparse(); 
	if (bi_lexer) delete bi_lexer;
	if (bi_class) delete bi_class;
	if (bi_file) delete bi_file;
	if (bi_module) delete bi_module;
	return 0;
}

