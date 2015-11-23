// generic AST-like dynamic object

struct sym {
	string tag;					// object class or data type
	string value;				// object value in string form
	sym(string,string);			// constructor from string form tag:value
	vector<sym*> nest;			// nested objects tree
	void join(sym*);			// add nested object
	string pad(int);			// pad tagval with tabs
	string tagval();			// <tag:value> string
	string dump(int depth=0);	// dump object in string form
	virtual sym* eval();		// evaluate (compute) object
#	sym*(*fn)(sym*);			// for functions: pointer to lowlevel C++ fn()
#// predefined low-level functions defined on symbols and inherited objects
#	virtual sym* add(sym*);		// + to current object
};
extern map<string,sym*> env;	// \\\\ global environment: objects registry
extern void env_init();			// //
