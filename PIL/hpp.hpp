// DO NOT EDIT: this file was autogened by PIL
#ifndef _H_PILH
#define _H_PILH

// metainfo constants

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/PIL"
#define AUTOGEN "DO NOT EDIT: this file was autogened by PIL"
#define LOGO "![logo](logo64x64.png)"

// standart includes

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef __MINGW32__
	#include <direct.h>
#else
	#include <sys/stat.h>
#endif
#include <vector>
#include <map>
using namespace std;

// generic AST-like dynamic object

struct sym {
	string tag;					// object class or data type
	string value;				// object value in string form
	sym(string,string);			// constructor from string form tag:value
	string dump(int depth=0);	// dump object in string form
	virtual sym* eval();		// evaluate (compute) object
	string tagval();			// <tag:value> string
	string pad(int);			// pad tagval with tabs
	vector<sym*> nest;			// nested objects tree
	void join(sym*);			// add nested object
};

#endif // _H_PILH
