// generic symbolic object

sym::sym(string T,string V)	{ tag=T; value=V; }			// symbol constructor
void sym::join(sym*o)		{ nest.push_back(o); }		// add nested object

string sym::pad(int n)	{string S; for (int i=0;i<n;i++) S+="\\t"; return S;}
string sym::tagval()	{ return "<"+tag+":"+value+">"; }
string sym::dump(int depth) {							// dump symbol object
	string S = "\\n"+pad(depth)+tagval();				// header
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		S += (*it)->dump(depth+1);						// recurse with pad++
	return S;
}
map<string,sym*> env;									// global env[]ironment
void env_init() {
	// meta constants
	env["LOGO"]=new sym("logo",LOGO);
	env["LISP"]=new sym("lisp",LISP);
	env["AUTHOR"]=new sym("author",AUTHOR);
	env["LICENSE"]=new sym("license",LICENSE);
	env["GITHUB"]=new sym("github",GITHUB);
	env["AUTOGEN"]=new sym("autogen",AUTOGEN);
	env["bICONFIG"]=new sym("bIconfig",bICONFIG);
	env["MODULE"]=curr_module;
	env["FILES"]=new Str("");
	env["CFILES"]=new Str("cpp.cpp");
	env["HFILES"]=new Str("hpp.hpp");
	env["COLOR"]=new Str("$COLOR$");
	env["ABOUT"]=new Str("");
	// special symbols
	env["%T"]=new sym("true","%T");
	env["%F"]=new sym("false","%F");
	env["%N"]=new sym("nil","%N");
	env["%E"]=new sym("error","%E");
	env["%%"]=new sym("default","%%");
}

sym* sym::eval()	{									// object evaluator
	if (env[value]) return env[value];					// lookup in env[]
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		(*it) = (*it)->eval();							// recurse compute
	return this;										// default as is
}
