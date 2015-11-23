// dynamic symbolic object subsystem

Directive::Directive(string V):sym("",V) {
	while (value.size()&&(value[0]!='\\t'&&value[0]!=' ')) {	// shift val->tag
		tag += value[0]; value.erase(0,1); }
	while (value.size()&&(value[0]=='\\t'||value[0]==' ')) {	// shift spaces
		                 value.erase(0,1); }
	// file-specific operations
	if (tag==".inc") incFile(this);							// .include files
	if (tag==".file") {										// create new .file
		env["FILES"]->value+=value+" ";						// FILES+= filename
		value = curr_module->value+"/"+value;			// full name with module
		if (curr_file) delete curr_file; curr_file=new File(value,"w"); }
	if (tag==".eof") {										// end .file
		if (curr_file) delete curr_file; curr_file=NULL; }
												// .module metainfo directives
	if (tag==".title")	env["TITLE"]	=new sym("title",value);
	if (tag==".about")	env["ABOUT"]	=new sym("about",value);
	if (tag==".author")	env["AUTHOR"]	=new sym("author",value);
	if (tag==".license")env["LICENSE"]	=new sym("license",value);
	if (tag==".github")	env["GITHUB"]	=new sym("github",value);
	if (tag==".color")	env["COLOR"]	=new Str(value);
}

Module::Module(string V):sym("module",V) {					// define .module
	\#ifdef __MINGW32__
		mkdir(V.c_str());									// create win32 dir
	\#else
		mkdir(V.c_str(),0700);								// create POSIX dir
	\#endif
}
Module *curr_module = new Module("next");	// default module on system start

File::File(string V,string M):sym("file",V) {		// create file [Mode="r/w"]
	assert(fh=fopen(V.c_str(),M.c_str()));}
File::~File() { fclose(fh); }						// close file
File *curr_file = NULL;								// current out file for W()

Int::Int(string V):sym("int",V)	{}					// integer number
sym* Int::eval() {
	ostringstream os; os << atoll(value.c_str()); value=os.str();
	return this; }

Hex::Hex(string V):sym("hex",V) {}
sym* Hex::eval() { return this; }
Bin::Bin(string V):sym("bin",V) {}
sym* Bin::eval() { return this; }

Num::Num(string V):sym("num",V) {}					// float point number
sym* Num::eval() {
	ostringstream os; os << strtold(value.c_str(),NULL); value=os.str();
	return this; }

Str::Str(string V):sym("str",V)	{}					// string

													// compound data types
List::List():sym("[","]") {}						// [list]
Vector::Vector():sym("","") {}						// <vector>
Pair::Pair(sym*A,sym*B):sym(A->value,B->value) {}	// pa:ir
