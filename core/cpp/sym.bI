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
void env_init() {}

sym* sym::eval()	{									// object evaluator
	if (env[value]) return env[value];					// lookup in env[]
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		(*it) = (*it)->eval();							// recurse compute
	return this;										// default as is
}
