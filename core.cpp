#include "bI.hpp"

/*

// object

biObject::biObject(const char* C) { cls = new string(C); val = new string(); }
biObject::biObject(const char* C,const char* V) { cls = new string(C); val = new string(V); }
biObject::biObject(const char* C,char* V) { cls = new string(C); val = new string(V); }
biObject::biObject(const char* C,string* V) { cls = new string(C); val = V; }
biObject::biObject(string* C,string* V) { cls = C; val = V; }

string smux(string x,int y) { string s; for (int i=0;i<y;i++) s+=x; return s; }

string* biObject::dump(int depth) {
	string *S = new string(smux("\t",depth)+"<" + *cls + ":" + *val + ">\n");
	for (list<biObject*>::iterator it=L.begin(); it!=L.end(); it++ )
		*S += *((*it)->dump(depth+1));
	return S;
}
string* biObject::eval()	{ return val; }

map<string,biObject*> env;

void init_env() {
	env["bILS"]=new biObject("",
		"bI language system");
	env["AUTHOR"]=new biObject("(c)",
		"(c) Dmitry Ponyatov <dponyatov@gmail.com>, all right reserved"	);
	env["AUTOGEN"]=new biObject("",
		"/************** DO NOT EDIT *************\n"
		"   this file was autogened by bI system  \n"
		" ************** DO NOT EDIT *************\n"	);
}

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
string* biClass::dump(int depth) {
	if (super.size())	return new string("<"+*cls+":"+*val+",super:"+super+">");
	else				return biObject::dump();
}

biClass* bi_class=NULL;
map<string,string*> bi_class_reg;

// list

biList::biList():biObject("list","")				{}
biList::biList(biObject* X):biObject("list","")		{ L.push_back(X); }

// string

biString::biString(char *V):biObject("str",V) {}

// pair

biPair::biPair(biObject* X,biObject* Y):biObject("pair","") { 
	L.push_back(X); L.push_back(Y);
}

// module

biModule::biModule(const char*m):biObject("module",m) {
#ifdef __MINGW32__
	mkdir(val->c_str());
#else
	mkdir(val->c_str(),0744);
#endif
	assert(make = fopen((*val+"/Makefile").c_str(),"w"));
	fprintf(make,"%s",autogen("#",*dump()).c_str());
	lex_used=false;
	env[string("MODULE")]=this;
};

biModule::~biModule() {
	fprintf(make,"%s",head.c_str());
	fprintf(make,".PHONY: default\ndefault: ./%s$(EXE)\n\n",val->c_str());
	files(*val);
	fprintf(make,"%s",body.c_str());
	assert(cpp=fopen((*val+"/"+*val+".cpp").c_str(),"w"));
	fprintf(cpp,"%s",autogen("//",*dump()).c_str());
	fprintf(cpp,("#include \""+*val+".hpp\"\n\n").c_str());
	assert(hpp=fopen((*val+"/"+*val+".hpp").c_str(),"w"));
	fprintf(hpp,"%s",autogen("//",*dump()).c_str());
	fprintf(hpp,("#ifndef _H_"+*val+"\n#define _H_"+*val+"\n\n").c_str());
	if (lex_used) {
		fprintf(cpp,"int main() { yylex(); }\n");
//		fprintf(make,("\t./"+*val+"$(EXE) < test.bI > log.log\n").c_str());
	} else {
		fprintf(cpp,"int main() {};\n");
	}
	fprintf(make,("\n./"+*val+"$(EXE): $(O_FILES)\n\t$(CXX)"
			   " -o $@ $(O_FILES)\n\n").c_str());
	fclose(make);
	fclose(cpp);
	fprintf(hpp,"%s",hbody.c_str());
	fprintf(hpp,("#endif // _H_"+*val+"\n\n").c_str());
	fclose(hpp);
}

void biModule::depends(string X,string Y,string C) { 
	body += X+" : "+Y+"\n\t"+C+"\n\n"; }
void biModule::headmake(string X,string Y,string C) {
	head = X+" : "+Y+"\n\t"+C+"\n\n"; }

void biModule::files(string cls) {
	body += "O_FILES += "+cls+".o\n";
	body += "C_FILES += "+cls+".cpp\n";
	body += "H_FILES += "+cls+".hpp\n";
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

string* biFile::dump(int depth)	{
	ostringstream os; 
	os << "<" << *cls << ":" << *val ;
	os << ",mode:" << mode << ",open:" << (fh==NULL ? "F" : "T") << ">";
	return new string(os.str());
}

void biFile::W(string s)	{ fprintf(fh,"%s",s.c_str());	}
void biFile::W(char c)		{ fprintf(fh,"%c",c);			}

biFile *bi_file = NULL;

biTest::biTest(string* name):biFile(new string(*name+".bI"),'w') {
	W(autogen("#","<test:"+*name+">"));
	bi_module->headmake(*name+".log",*val+" ./"+*bi_module->val+"$(EXE)",
			"./"+*bi_module->val+"$(EXE) < $< > $@"
			);
	bi_file=this;
}

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
	if (*cls==".test")		{ 
		if (bi_file) delete bi_file; bi_file=new biTest(val); }
	if (*cls==".eof")		{
		if (bi_file) delete bi_file; bi_file=NULL; }
}

// lexer

biLexer::biLexer(biObject* s):biObject("lexer",s->val)	{
	bi_module->files(*val+".lex");
	bi_module->depends(*val+".lex.cpp",*val+".lpp","flex -o"+*val+".lex.cpp $<");//-P"+*val+" $<");
/*
	lpp = new biFile(new string(*val+".lpp"),'w');
	lpp->W(
		"%{\n"
		"#include \""+*val+".lex.hpp\"\n"
		"#define T(C,X)	{ yylval.s=new sym(C,yytext); return X; }\n"
		"%}\n\n"
		"\%option noyywrap\n"
		"\%option yylineno\n\n"
	);
//
	hpp = new biFile(new string(*val+".lex.hpp"),'w');
	hpp->W(autogen("//",*dump()));
	bi_module->hbody += "#include \""+*val+".lex.hpp\"\n\n";
	hpp->W(
			"#include <iostream>\n"
			"#include <cstdio>\n"
			"#include <cstdlib>\n"
			"#include <cassert>\n\n"
			"#include <list>\n"
			"#include <map>\n\n"
			"using namespace std;\n\n"
			"extern int yylex();\n"
			"extern int yylineno;\n"
			"extern char* yytext;\n\n"
			);
	bi_lexer=this;
	bi_module->lex_used=true;
}
biLexer *bi_lexer = NULL;

biLexer::~biLexer()		{
//	lpp->W("%%\n");
//	lpp->W("\n%%\n\n");
//	delete lpp;
	delete hpp;
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

void terminator() {
	if (bi_lexer) delete bi_lexer;
	if (bi_class) delete bi_class;
	if (bi_file) delete bi_file;
	if (bi_module) delete bi_module;
	exit(0);
}

int main() { 
	init_env();
	terminator(); 
}
*/

// \\ textout writers
void W(string   S,bool to_file)		{ cout <<  S; }
void W(string  *S,bool to_file)		{ cout << *S; }
// //

// parser error

void yyerror(string err) {
	cout << "\n" << err << " # " << yylineno << " : " << yytext << "\n\n";
	cerr << "\n" << err << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main()	{ return yyparse(); }

