// symbolic object realization

sym::sym(string T,string V)	{ tag=T; value=V; }			// symbol constructor
void sym::join(sym*o)	{ nest.push_back(o); }			// add nested object

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

sym* sym::eval() {										// object evaluator
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		(*it) = (*it)->eval();							// recurse compute
	if (env[value])	return env[value];					// look up val in env[]
	else			return this;						// return as is
}
