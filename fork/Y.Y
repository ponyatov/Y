# native system interfaces

native string ;
native FILE* ;
native class ;

class File {
	string Name;
	FILE* Handler;
	string Mode;
};

// syntax lexers

class Language {
	TokenList;
	Syntax;
};

class Parser {
	Language;
	File;
};
