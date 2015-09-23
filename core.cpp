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

const char biClass::chead[]=
	"// this file was autogened by bI language system,\n"
	"// **************** DO NOT EDIT *****************\n"
	"// class: ";
void biClass::init(biObject *sym) {
	if (bi_class) delete bi_class; bi_class=this;
	cpp = new biFile(new string(*val+".cpp"),'w');
	hpp = new biFile(new string(*val+".hpp"),'w');
	cpp->W(chead+*dump()+"\n\n");
	cpp->W("#include \""+*val+".hpp\"\n\n");
	bi_module->o_dep(*val);
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
	hpp->W(chead+*dump()+"\n\nclass "+*val);
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
	fprintf(make,"\n.PHONY: default\ndefault: %s$(EXE)\n\n",val->c_str());
	o_dep("main");
	FILE *c=fopen((*val+"/main.cpp").c_str(),"w"); assert(c);
	fprintf(c,"int main() { return 0; }");
	FILE *h=fopen((*val+"/main.hpp").c_str(),"w"); assert(c);
};

biModule::~biModule() {
	fprintf(make,(*val+"$(EXE): $(O_FILES)\n\t$(CXX)"
			   " -o $@ $(O_FILES)\n\n").c_str());
	fclose(make);
}

void biModule::depends(string X,string Y,string C) {
	fprintf(make,"%s: %s\n\t%s\n\n",Y.c_str(),X.c_str(),C.c_str());
}

void biModule::o_dep(string cls) { 
	fprintf(make,"O_FILES += %s.o\n",cls.c_str());
	fprintf(make,"CPP_FILES += %s.cpp\n",cls.c_str());
	fprintf(make,"H_FILES += %s.hpp\n",cls.c_str());
	depends(
			cls+".cpp"+" "+cls+".hpp", 
			cls+".o", 
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
	if (*cls==".file")		{ 
		if (bi_file) delete bi_file; bi_file=new biFile(val,'w');} 
	if (*cls==".eof")		{
		if (bi_file) delete bi_file; bi_file=NULL;} 
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
	if (bi_class) delete bi_class;
	if (bi_file) delete bi_file;
	if (bi_module) delete bi_module;
	return 0;
}

