#include "bI.hpp"

/*

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

*/

// \\\ generic symbol type

biObject::biObject(string T,string V)		{ tag=T; value=V; }
biObject::biObject(biObject* T,biObject* V)	{ tag=T->value; value=V->value; }

string biObject::dump(int depth) {
	return "<"+tag+":"+value+">";
/*	
	string S="\n"; for(int i=0;i<depth;i++) S+="\t";	// left padding
	S+="<"+tag+":"+value+">";							// symbol header
														// nested symbols
	return S;//+"\n";									// return final string
*/
}

string biObject::eval() { return value; }

// ///

// \\\ environment
map<string,biObject*> env;

void init_env() {
	env["TITLE"]=new biObject("",
		"bI dynamic language system");
	env["AUTHOR"]=new biObject("(c)",
		"(c) " AUTHOR);
	env["AUTOGEN"]=new biObject("",
		"/************** DO NOT EDIT *************\n"
		"   this file was autogened by bI system  \n"
		" ************** DO NOT EDIT *************\n"	);
}
// ///

// \\\ directive

FILE *toc=fopen("bI.toc","w");
int toc1,toc2,toc3;

biDirective::biDirective(string s):biObject(".directive",s) {
	// adaptive class generation for directives
	tag = "";
	while (value.size() && (value[0]!=' ' && value[0]!='\t')) {
		tag += value[0]; value.erase(0,1);
	}
	while (value.size() && (value[0]==' ' || value[0]=='\t'))
		value.erase(0,1);
	// contents generating
	if (tag==".sec+") fprintf(toc,"%i %s\n"       ,++toc1,value.c_str()),toc2=0,toc3=0;
	if (tag==".sec")  fprintf(toc,"\t%i.%i %s\n"  ,toc1,++toc2,value.c_str()),toc3=0;
	if (tag==".sec-") fprintf(toc,"\t\t%i.%i.%i %s\n",toc1,toc2,++toc3,value.c_str());
};
// ///

// \\\ module
biModule::biModule(string V):biObject("module",V) {
	mkdir(V.c_str());
	assert ( make = fopen((value+"/Makefile").c_str(),"w") );
	fprintf(make,"%s\n",autogen("#",dump()).c_str());
	assert ( readme = fopen((value+"/README.md").c_str(),"w") );
	title = value;
	author = AUTHOR;
	about = "info";
}

biModule::~biModule() {
	fclose(make);
	fprintf(readme,"# module: %s\n",value.c_str());
	fprintf(readme,"## %s\n",title.c_str());
	fprintf(readme,"(c) %s\n",author.c_str());
	fprintf(readme,"\n%s\n\n",about.c_str());
	fclose(readme);
}

biModule* bi_module = new biModule("tmp");
// ///

// \\ textout writers

// autogenerated marker creator

string autogen(string pfx, string obj) {
	return string(
	pfx+" ************** DO NOT EDIT *************\n"+
	pfx+"   this file was autogened by bI system  \n"+
	pfx+" ************** DO NOT EDIT *************\n"+
	pfx+" "+obj+"\n"
	);
}

void W(char      C,bool to_file)		{ cout <<  C; }
void W(string    S,bool to_file)		{ cout <<  S; }
void W(string   *S,bool to_file)		{ cout << *S; }
void W(biObject *O,bool to_file)		{ cout << O->dump(); }
// //

// parser error

void yyerror(string err) {
	cout << "\n" << err << " # " << yylineno << " : " << yytext << "\n\n";
	cerr << "\n" << err << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

// system cleanup
void terminator() {
	if (bi_module) delete bi_module;
	exit(0);
}

int main() {
	init_env();
	W(autogen("#","main()"));
	yyparse();
	terminator(); /* fake */ return 0;
}

