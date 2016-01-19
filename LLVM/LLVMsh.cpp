#include "LLVMsh.hpp"

#define context llvm::getGlobalContext()
llvm::Module module(MODULE ".ll",context);
string ErrorInfo;

#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() {
	env_init(); yyparse();
	unique_ptr<llvm::tool_output_file> out (
		new llvm::tool_output_file(
			MODULE ".bc", ErrorInfo, llvm::sys::fs::OpenFlags::F_None));
	llvm::WriteBitcodeToFile(&module,out->os());
	out->keep();
	return 0;
}

Sym::Sym(string T,string V)	{ tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V) {}

void Sym::push(Sym*o)	{ nest.push_back(o); }

string Sym::tagval()	{
	ostringstream os; os <<"<"<<tag<<":"<<val<<">"; return os.str(); }
string Sym::dump(int)	{ return "\n"+tagval(); }

Sym* Sym::eval() {
	Sym* E = env[val]; if (E) return E;
	return this;
}

map<string,Sym*> env;
void env_init() {
	env["MODULE"] = new Str(MODULE);
}

Str::Str(string V):Sym("str",V) {}

//llvm::Value* Sym::ll() {
//	return new llvm::Value();
//	//return llvm::ConstantArray::get(&context, val.c_str());
//}

void W(char c)	{ cout << c; }
void W(Sym* o)	{ cout << o->dump(); }

Int::Int(string V):Sym("int","")	{ val = atoi(V.c_str()); }
string Int::tagval() {
	ostringstream os; os <<"<"<<tag<<":"<<val<<">"; return os.str(); }

Hex::Hex(string V):Int(V)			{ val = stol(V.substr(2),0,0x10); }
string Hex::tagval() { ostringstream os;
	os <<"<"<<tag<<":0x"<<hex<<uppercase<<val<<">"; return os.str(); }

Bin::Bin(string V):Sym("bin", "") {
	for (auto b : V.substr(2))
		val.push_back(b == '1');
}
string Bin::tagval() {
	ostringstream os; os<<"<"<<tag<<":0b";
	for (auto b:val) os<<b;
	os<<">"; return os.str();
}

Num::Num(string V):Sym("num","")	{ val = stod(V,0); }
string Num::tagval() {
	ostringstream os; os <<"<"<<tag<<":"<<val<<">"; return os.str(); }
