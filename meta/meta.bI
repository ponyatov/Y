
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

composite:list		%doc:'ordered plain list'

composite:tuple		%doc:'ordered comma-separated list'

composite:pair		%doc:'Lisp-like cons object'
	%(A%doc:'car')
	%(D%doc:'cdr')

composite:vector	%doc:'fixed-size data collection: linear vector'
	%int:size

vector:matrix		%doc:'2D vector-like math object (can be nested)'
	%int:width
	%int:height
	%size = {width*height}

composite:tree		%doc:'tree operations based on basic AST type'
	%(super%sym)

sym:functional		%doc:'functional objects'

functional:op		%doc:'operator'

op:binop			%doc:'binary operator: A op B'

binop:eq			%doc:'assignment'
	%lex = '='
binop:at			$doc:'apply (function)'
	%lex = '@'

functional:lambda	%doc:'lambda-function'

functional:fn		%doc:'internal of dynamic compiled machine-level function'

sym:extension		%doc:'extension classes'

extension:fileio	%doc:'file/dir manipulations'
	%size

fileio:dir			%doc:'directory'

fileio:file			%doc:'file'

fileio:volume		%doc:'logical data volume'
	%files

fileio:media		%doc:'physical media drive'
	%volumes

expression:gui		%doc:'geeneric GUI subsystem'

gui:color			%doc:'color data'
	%R%G%B
gui:pixel			%doc:'one pixel'
	%x %y %color
gui:vector			%doc:'vector data'
gui:bitmap			%doc:'pixel image'
	%(content % matrix:pixels)

gui:geometry		%doc:'position/size data'
	%x %y %w %h		# left corner x,y width height

gui:rect			%doc:'rectangular area'
	%geometry

rect:display		%doc:'logical display'
	%width %height
	%diagonal %aspect
	%dpi %colordepth

rect:window			%doc:'window element'
	%redraw

window:canvas		%doc:'drawable area'
	%server:paint
	%content:vector

window:button		%doc:'clickable window'
	%icon
	%text:label
	%event:click

window:editor		%doc:'generic text editor'
	%content:text

window:html			%doc:'HTML browser'
	%url

rect:icon			%doc:'icon element'
	%content:bitmap

extension:net		%doc:'network subsystem'

net:socket
net:protocol
protocol:IP
IP:TCP
IP:UDP
network:client
network:server
protocol:HTTP
protocol:FTP
protocol:TELNET
protocol:NTP
protocol:DNS
protocol:DHCP
protocol:SSL

extension:DBMS		%doc:'RDBMS interfaces'
DBMS:MySQL
DBMS:SqLite
DBMS:query
DBMS:cursor
DBMS:database
DBMS:table
DBMS:user
DBMS:trigger

extension:CAD		%doc:'CAD spectific tools'
CAD:EDA
EDA:Shematics		%doc:'electro shemes drawings/simulate'
EDA:PCB				%doc:'pcb router/editor'
EDA:SPICE			%doc:'ng-spice solver'

CAD:layer			%doc
CAD:primitive		%doc:'geometry primitive element'
	%layer
primitive:point		%doc:'3D space point'
primitive:line
primitive:arc

CAD:block			%doc:'blocked elements and connection pins'
block:pin			%doc:'block connection port'

EDA:element			%doc:'electrical element'
	%sch			# schematic specific
	%pcb			# pcb specific
	%model			# SPICE model
	%vendor			# STmicro
	%refdes			# Rnnn
	%value			# 10k


element:R			%doc:'generic resistor'
	%passive
element:L			%doc:'generic inductance'
	%passive
element:C			%doc:'generic capacitance'
	%passive

element:connector	%doc:'physical connector'
	%passive
element:DD			%doc:'ditital IC'
element:DA			%doc:'analog IC'

EDA:pcb				%doc:'pcb item'
pcb:padstack		
padstack:thru		%doc:'thruhole padstack'
padstack:smd		%doc:'smd padstack'

EDA:gerber			%doc:'GERBER data'
EDA:drill			%doc:'drill data'

pcb:board			%doc:'board outline and technology'

EDA:cable			%doc:'cable info'

EDA:router			%doc:'router interface'
router:SPECCTRA

