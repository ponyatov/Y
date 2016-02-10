
# =================================================== meta language test suite

# literals and basic composite types

[								# numbers
	[ -01 +00 003 				# integers
		[ 0x12AF , 0b1101 ]]	# machine numbers tuple (with , sepearator)
	[ -01.2 +003e-04 ]			# float numbers
]

# sample expression with function calls, literals and inline class inheritance
file('log','w',0).writeln(
	[ 01+ -2.3/sin(constant:Pi)^e*ln(-5e+06) 0b1101 , 0x12AF ]
)

# class inheritance and instantiation, with alternative function call syntax
class:A		# base class
A:B			# inherit class with mods
% var				# custom variable
% init = {X: var=X}	# constructor
% del				# immediate destructor

A B			# super and inherited classes
A@X			# A apply to X	( bI direct apply syntax )	
B(Y)		# B apply to Y	(traditional named function apply syntax)

# ========================================= bI language declarative definition

language:bI

%files = [
	file:source %syntax:bi %extension:'.bI'
	file:log					%doc:'core execution debug log'
	file:parser % syntax:flex	%doc:'token definitions using regexps'
	file:lexer % syntax:bison	%doc = bI,'grammar'
	file:headers % syntax:cpp
	file:meta % syntax:cpp		%doc:'program module metainfo'
	file:cppcore % syntax:cpp
	misc = [
		file:'.gitignore' 		%doc:'temp/generated file extenstion masks'
		file:'bat.bat'			%doc = '(g)vim helper',win32
		file:'rc.rc'			%doc = 'win32 resource compiler script'
		file:LOGO				%doc:'logo icon'
	]

]

class:comment
	%lex = '#[^\\n]*'
	%token = COMMENT

class:sym			%doc:'Abstract/Algebraic Symbolic Type (AST)'

sym:scalar			%doc:'Scalar types baseclass'

scalar:int			%doc:'integer'
	%lex = '{S}{N}'
	%token = NUM

scalar:machine
	%token = NUM
machine:hex			%doc:'hexadecimal'
	%lex = '0x[0-9A-F]+'
machine:bin			%doc:'binary vector'
	%lex = '0b[01]+'

scalar:num			%doc:'floating number'
	%lex = [ '{S}{N}\\.{N}' '{S}{N}[eE]{S}{N}' ]
	%token = NUM

sym:composite		%doc:'composite data types'

composte:list		%doc:'ordered plain list'

composite:tuple		%doc:'ordered comma-separated list'

composite:pair		%doc:'Lisp-like cons object'
	%(A%doc:'car')
	%(D%doc:'cdr')

composite:vector	%doc:'fixed-size data collection'
