#include "bI.hpp"

// \\\ generic symbol type

biObject::biObject(string T,string V)		{ tag=T; value=V; }
biObject::biObject(biObject* T,biObject* V)	{ tag=T->value; value=V->value; }
biObject::biObject(biObject* P)				{ tag=P->tag; value=P->value; }

string biObject::pad(int depth) {
	string S;
	for(int i=0;i<depth;i++) S+="\t";	
	return S;
}

void biObject::join(biObject* X)	{ nest.push_back(X); }

string biObject::tagmark() { return "<"+tag+":"+value+">"; }

string biObject::dump(int depth) {
	// **** header ****
	string S="\n"+pad(depth);							// left padding
	S+=tagmark();
	// **** attributes ****
	if (attr.size()) {
		for ( map<string,biObject*>::iterator A = attr.begin();
			A != attr.end(); A++ )
				S += "\n"+pad(depth+1)+A->first+":"+A->second->value;
	}
	// **** nested symbols ***
	if (nest.size()) {
		for ( vector<biObject*>::iterator N = nest.begin();
			N != nest.end(); N++ )
				S += (*N)->dump(depth+1);
	}
	return S;											// return final string
}

biObject* biObject::eval() {
	// **** nested symbols ***
	for (
		vector<biObject*>::iterator N = nest.begin();
		N != nest.end();
		N++
		) (*N) = (*N)->eval();
	if (nest.size()==1) return nest[0];
	if (env[value]) return env[value]->eval();
	return this;
}

biObject* biObject::pfxminus()	{ value = "-"+value; return this; }
biObject* biObject::pfxplus()	{ value = "+"+value; return this; }

biObject* biObject::add(biObject* S) { value = value+"+"+S->value; return this; }
biObject* biObject::sub(biObject* S) { value = value+"-"+S->value; return this; }
biObject* biObject::mul(biObject* S) { value = value+"*"+S->value; return this; }
biObject* biObject::div(biObject* S) { value = value+"/"+S->value; return this; }

biObject* biObject::set(biObject* S) {
	if (tag == "const") return this; // yyerror(tagmark()+" is constant");
	if (nest.size()) nest[0]=S; else join(S);
	if (!env[value]) env[value] = this;
	return this;
}

// ///

// \\\ environment
map<string,biObject*> env;

void init_env() {
	env["TITLE"]=new biObject("str",
		"bI dynamic language system");
	env["AUTHOR"]=new biObject("str",
		AUTHOR);
	env["AUTOGEN"]=new biObject("str",
		"/************** DO NOT EDIT *************\n"
		"   this file was autogened by bI system  \n"
		" ************** DO NOT EDIT *************\n"	);
	env["pi"]=new biObject("const","pi");			// Pi
	env["pi"]->join(new biFloat(M_PI));
	env["e"] =new biObject("const","e");			// e
	env["e"]->join(new biFloat(M_E));
	env["c"] =new biObject("const","c");			// light speed
	env["c"]->join(new biFloat(299792458));
	env["G"] =new biObject("const","G");			// gravity const
	env["G"]->join(new biFloat(6.674e-11));
	env["g"] =new biObject("const","g");		// gravitational acceleration
	env["g"]->join(new biFloat(9.80665));
	env["h"] =new biObject("const","h");			// Plank constant
	env["h"]->join(new biFloat(6.626070040e-34));
}
// ///

// \\\ class
biClass::biClass(biObject* V):biObject(V) {
	if (bi_class) delete bi_class;
	toc.W(TOC::CLASS,value);
	// .cpp
	assert ( cpp = fopen((bi_module->value+"/"+value+".cpp").c_str(),"w") );
	fprintf(cpp,autogen("//",tagmark()).c_str());
	fprintf(cpp,"#include \"%s.hpp\"\n",bi_module->value.c_str());
	// .hpp
	assert ( hpp = fopen((bi_module->value+"/"+value+".hpp").c_str(),"w") );
	fprintf(hpp,autogen("//",tagmark()).c_str());
	fprintf(hpp,"#ifndef _H_%s\n#define _H_%s\n",value.c_str(),value.c_str());
	fprintf(bi_module->hpp,"#include \"%s.hpp\"\n",value.c_str());
	// Makefile dependencies
	fprintf(bi_module->make,"C_FILES += %s.cpp\n",value.c_str());
	fprintf(bi_module->make,"H_FILES += %s.hpp\n",value.c_str());
	fprintf(bi_module->make,"O_FILES += %s.o\n",value.c_str());
	fprintf(bi_module->make,"\n");
	bi_class = this;
}

biClass::~biClass() {
	fclose(cpp);
	if (attr["super"])
		fprintf(hpp,"class %s: public %s {\npublic:\n",
			value.c_str(),attr["super"]->value.c_str());
	else
		fprintf(hpp,"class %s {\npublic:\n",value.c_str());
	fprintf(hpp,"};\n");
	fprintf(hpp,"#endif // _H_%s\n",value.c_str());
	fclose(hpp);
	bi_class = NULL;
}

biClass *bi_class=NULL;
// ///

// \\\ operator
biOP::biOP(string s): biObject("op",s) {
	while (value[0] == ' ' || value[0] == '\t')
		value.erase(0,1);
	while (value[value.size()-1] == ' ' || value[value.size()-1] == '\t')
		value.erase(value.size()-1,1);
};

biObject* biOP::eval() {
	biObject::eval();
	/*
	if (nest.size()==1) {
		if (value=="-") return nest[0]->pfxminus();
		if (value=="+") return nest[0]->pfxplus();
	}
	*/
	if (nest.size()==2) {
		if (value=="+") return nest[0]->add(nest[1]);
//		if (value=="-") return nest[0]->sub(nest[1]);
//		if (value=="*") return nest[0]->mul(nest[1]);
		if (value=="/") return nest[0]->div(nest[1]);
		if (value=="=") return nest[0]->set(nest[1]);
	}
	return this;
}
// ///

// \\\ numeric types

// \\\\\\ integer

biInt::biInt(string V):biObject("int",V) { val = atoi(V.c_str()); }

string biInt::tagmark()	{ 
	ostringstream os; os << "<" << tag << ":" << val << ">"; 
	return os.str();
}

string biInt::dump(int depth) {	return "\n"+pad(depth)+tagmark(); }

biObject* biInt::pfxminus() { val=-val; return this; }
biObject* biInt::pfxplus()  {           return this; }

biObject* biInt::add(biObject* s)	{ 
	assert(s->tag=="int"); val = val + dynamic_cast<biInt*>(s)->val; return this;
}

biObject* biInt::sub(biObject* s)	{ 
	assert(s->tag=="int"); val = val - dynamic_cast<biInt*>(s)->val; return this;
}

biObject* biInt::mul(biObject* s)	{ 
	assert(s->tag=="int"); val = val * dynamic_cast<biInt*>(s)->val; return this;
}

biObject* biInt::div(biObject* s)	{ 
	assert(s->tag=="int"); val = val / dynamic_cast<biInt*>(s)->val; return this;
}

// //////

// \\\\\\ float

biFloat::biFloat(string V):biObject("float",V) { val = atof(V.c_str()); }
biFloat::biFloat(double V):biObject("float","") {
	ostringstream os; os << V; value = os.str(); val = V; }

string biFloat::tagmark() {
	ostringstream os; os.precision(width);
	os << "<" << tag << ":" << val << ">"; 
	return os.str();
}

string biFloat::dump(int depth) { return "\n"+pad(depth)+tagmark(); }

biObject* biFloat::pfxminus() { val = -val; return this; }
biObject* biFloat::pfxplus()  {             return this; }

// //////

// ///

// \\\ table of contents
TOC toc("bI.toc");

TOC::TOC(string s)	{ assert( fh=fopen(s.c_str(),"w") ); l1=l2=l3=cls=0; }
TOC::~TOC()			{ fclose(fh); }

void TOC::W(int lvl,string s) {
	fprintf(fh,"%4i\t",yylineno);
	switch (lvl) {
		case SECP:	fprintf(fh,"%i %s",++l1,s.c_str()); l2=0; l3=0;		break;
		case SEC:	fprintf(fh,"\t%i.%i %s",l1,++l2,s.c_str()); l3=0;	break;
		case SECM:	fprintf(fh,"\t\t%i.%i.%i %s",l1,l2,++l3,s.c_str());	break;
		case CLASS:	fprintf(fh,"\t\t\t\t%s\n",s.c_str());				break;
		default:	fprintf(fh,"%s",s.c_str());							break;
	}
}
// ///

// \\\ directive

biDirective::biDirective(string s):biObject(".directive",s) {
	// adaptive class generation for directives
	tag = "";
	while (value.size() && (value[0]!=' ' && value[0]!='\t')) {
		tag += value[0]; value.erase(0,1);
	}
	while (value.size() && (value[0]==' ' || value[0]=='\t'))
		value.erase(0,1);
	// std docfields
	if (tag==".title")   toc.W(0,"  title: "+value+"\n");
	if (tag==".author")  toc.W(0," author: "+value+"\n");
	if (tag==".license") toc.W(0,"license: "+value+"\n");
	if (tag==".github")  toc.W(0," github: "+value+"\n");
	if (tag==".tocline") toc.W(0,"-----------------------------------------\n");
	// contents generating
	if (tag==".sec+") toc.W(1,value+"\n");
	if (tag==".sec")  toc.W(2,value+"\n");
	if (tag==".sec-") toc.W(3,value+"\n");
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
	title  = value ;
	author = AUTHOR;
	about  = "info";
	// \\ file specific
	// directory
	mkdir(V.c_str());
	// Makefile
	assert ( make = fopen((value+"/Makefile").c_str(),"w") );
	fprintf(make,"%s",autogen("#",tagmark()).c_str());
	fprintf(make,"# title:  %s\n", title.c_str());
	fprintf(make,"# author: %s\n",author.c_str());
	fprintf(make,"\n");
	fprintf(make,"C_FILES = %s.cpp\n",value.c_str());
	fprintf(make,"H_FILES = %s.hpp\n",value.c_str());
	fprintf(make,"O_FILES = %s.o\n"  ,value.c_str());
	fprintf(make,"\n");
	assert ( readme = fopen((value+"/README.md").c_str(),"w") );
	fprintf(readme,"%s",autogen(">",dump()).c_str());
	// module cpp/hpp
	assert( cpp = fopen((value+"/"+value+".cpp").c_str(),"w") );
	fprintf(cpp,autogen("//",tagmark()).c_str());
	fprintf(cpp,"#include \"%s.hpp\"\n",value.c_str());
	fprintf(cpp,"int main(int argc, char *argv[]) { return 0; }\n");
	assert( hpp = fopen((value+"/"+value+".hpp").c_str(),"w") );
	fprintf(hpp,autogen("//",tagmark()).c_str());
	fprintf(hpp,"#ifndef _H_%s\n#define _H_%s\n",value.c_str(),value.c_str());
	// //
}

biModule::~biModule() {
	fprintf(make,
			"%s$(EXE): $(O_FILES)\n"
			"\t$(CXX) $(LDFLAGS) -o $@ $(O_FILES)\n\n",
			value.c_str());
	fprintf(make,
			"%%.o: %%.cpp %%.hpp\n"
			"\t$(CXX) $(CXXFLAGS) -c -o $@ $<\n\n");
	fclose(make);
	fprintf(readme,"# module: %s\n",value.c_str());
	fprintf(readme,"## %s\n",title.c_str());
	fprintf(readme,"%s\n",author.c_str());
	fprintf(readme,"\n%s\n\n",about.c_str());
	fclose(readme);
	// <module>.cpp
	fclose(cpp); 
	// <module>..hpp
	fprintf(hpp,"#endif // _H_%s\n",value.c_str());
	fclose(hpp);
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
	cout << "\n" << err << " # " << yylineno << " : [" << yytext << "]\n\n";
	cerr << "\n" << err << " # " << yylineno << " : [" << yytext << "]\n\n";
	exit(-1);
}

// system cleanup
void terminator() {
	if (bi_class)	delete bi_class;
	if (bi_module)	delete bi_module;
	exit(0);
}

int main() {
	init_env();
	W(autogen("#","main()"));
	yyparse();
	terminator(); /* fake */ return 0;
}

