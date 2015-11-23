// dynamic symbolic object subsystem

struct Directive:sym { Directive(string); };					// .directive
struct Module:sym { Module(string); };							// .module
extern Module *curr_module;									// current module
struct File:sym { File(string,string M="r"); FILE *fh; ~File(); };	// .file
extern File *curr_file;									// current output file

struct Int:sym { Int(string); sym* eval(); };//sym* add(sym*); };	// integer
struct Hex:sym { Hex(string); sym* eval(); };//sym* add(sym*); };	// hex
struct Bin:sym { Bin(string); sym* eval(); };//sym* add(sym*); };	// binary
struct Num:sym { Num(string); sym* eval(); };					// float number
struct Str:sym { Str(string); };								// string

#struct Op:sym { Op(string); };									// operator
#struct Dot:sym { Dot(); };										// some.dot
struct List:sym { List(); };//sym* add(sym*); };					// [list]
struct Vector:sym { Vector(); };								// <vector>
struct Pair:sym { Pair(sym*,sym*); };							// pa:ir

typedef sym* (*FN)(sym*);										// ptr to fn()
struct Fn:sym { Fn(string,FN); };								// function
#
#										// low-level fu()nctions
#extern sym* add(sym*o);
#extern sym* print(sym*o);
#extern sym* exit(sym*o);
