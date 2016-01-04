// dynamic symbolic object subsystem

struct Directive:sym { Directive(string); };				// .directive
struct Module:sym {											// .module
	Module(string); ~Module();
	static void CurrSet(Module*); };			
extern Module *curr_module;									// current module
struct File:sym {											// .file
	File(string,string M="r"); ~File(); FILE *fh;
	static void CurrSet(File*); };							// set curr_file
extern File *curr_file;									// current output file

														// scalar types:
struct Int:sym { Int(string); sym* eval(); };				// integer
struct Hex:sym { Hex(string); sym* eval(); };				// hex
struct Bin:sym { Bin(string); sym* eval(); };				// binary
struct Num:sym { Num(string); sym* eval(); Num(double); };	// float number
struct Str:sym { Str(string); };							// string

														// compound types:
#struct Op:sym { Op(string); };								// operator
#struct Dot:sym { Dot(); };									// some.dot
struct List:sym	  { List(); };								// [list]
struct Vector:sym { Vector(); };							// <vector>
struct Pair:sym	  { Pair(sym*,sym*); };						// pa:ir

typedef sym*(*FN)(sym*);									// ptr to fn()
struct Lambda:sym { Lambda(); };							// {lambda}
struct Fn:sym { Fn(string,FN); };							// function

													// low-level fu()nctions
extern void fn_init();													
#extern sym* add(sym*o);
#extern sym* print(sym*o);
#extern sym* exit(sym*o);
