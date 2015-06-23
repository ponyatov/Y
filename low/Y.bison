%{
%}

%union {
	int token;
	std::string *string;
}

%start syntax

%%

syntax : COMMENT ;

%%
