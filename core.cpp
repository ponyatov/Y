#include "bI.hpp"

// \\\ generic symbol type

biObject::biObject(string T,string V)		{ tag=T; value=V; }
biObject::biObject(biObject* T,biObject* V)	{ tag=T->value; value=V->value; }

string pad(int depth) {
	string S;//="\n";
	for(int i=0;i<depth;i++) S+="\t";	
	return S;
}

string biObject::dump(int depth) {
	string S="\n"+pad(depth);								// left padding
	S+="<"+tag+":"+value+">";							// symbol header
	if (attr.size()) {									// dump attributes
		for ( map<string,biObject*>::iterator A = attr.begin();
			A != attr.end(); A++ )
				S += "\n"+pad(depth+1)+A->first+" : "+A->second->value;
	}
	if (nest.size()) {									// nested symbols
		for ( list<biObject*>::iterator N = nest.begin();
			N != nest.end(); N++ )
				S += (*N)->dump(depth+1);
	}
	return S;											// return final string
}

string biObject::eval() { return value; }

// ///

// \\\ environment
map<string,biObject*> env;

void init_env() {
	env["TITLE"]=new biObject("",
		"bI dynamic language system");
	env["AUTHOR"]=new biObject("(c)",
		AUTHOR);
	env["AUTOGEN"]=new biObject("",
		"/************** DO NOT EDIT *************\n"
		"   this file was autogened by bI system  \n"
		" ************** DO NOT EDIT *************\n"	);
}
// ///

// \\\ class
biObject *biCoreClass = new biObject("class","class");
map<string,biClass*> bi_class_registry;

biClass::biClass(string V):biObject("class",V) 			{
	bi_class_registry[V] = this;
}

biClass::biClass(biObject* S):biObject(biCoreClass,S)	{
	bi_class_registry[S->value] = this;
}

biClass::biClass(biObject* P,biObject* C):biObject(P,C) {
	tag = "class";
	attr["super"] = P;
	bi_class_registry[C->value] = this;
}
// ///

// \\\ operator
biOP::biOP(string s): biObject("op",s) {
	while (value[0] == ' ' || value[0] == '\t')
		value.erase(0,1);
	while (value[value.size()-1] == ' ' || value[value.size()-1] == '\t')
		value.erase(value.size()-1,1);
};
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
	// .file
	if (tag==".file") {
		if (bi_file) delete bi_file;	// autoclose prev file
		bi_file = new biFile(value);
	}
};
// ///

// \\\ file

biFile::biFile(string V):biObject(".file",V) {
	assert( fh = fopen((bi_module->value+"/"+value).c_str(),"w") );
}
biFile::~biFile()	{ fclose(fh); bi_file = NULL; }

void biFile::W(char   C)	{ fprintf(fh,"%c",C); }
void biFile::W(string S)	{ fprintf(fh,"%s",S.c_str()); }

biFile* bi_file = NULL;
// ///

// \\\ module
biModule::biModule(string V):biObject("module",V) {
	mkdir(V.c_str());
	assert ( make = fopen((value+"/Makefile").c_str(),"w") );
	fprintf(make,"%s",autogen("#",dump()).c_str());
	assert ( readme = fopen((value+"/README.md").c_str(),"w") );
	fprintf(readme,"%s",autogen(">",dump()).c_str());
	title = value;
	author = AUTHOR;
	about = "info";
}

biModule::~biModule() {
	fprintf(make,"# module: %s\n",value.c_str());
	fprintf(make,"# title:  %s\n",title.c_str());
	fprintf(make,"# author: %s\n",author.c_str());
	fprintf(make,"\n\n");
	fclose(make);
	fprintf(readme,"# module: %s\n",value.c_str());
	fprintf(readme,"## %s\n",title.c_str());
	fprintf(readme,"%s\n",author.c_str());
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

void W(char      C,bool to_file)		{ cout <<  C;
	if (to_file && bi_file) bi_file->W(C); }
void W(string    S,bool to_file)		{ cout <<  S;
	if (to_file && bi_file) bi_file->W(S); }
void W(string   *S,bool to_file)		{ cout << *S;
	if (to_file && bi_file) bi_file->W(*S); }
void W(biObject *O,bool to_file)		{ cout << O->dump();
	if (to_file && bi_file) bi_file->W(O->dump()); }
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

