
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
protocol:SSH

extension:DB		%doc:'RDBMS interfaces'
DB:MySQL
DB:SqLite
DB:query
DB:cursor
DB:database
DB:table
DB:user
DB:trigger

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

CAD:detail			%doc:'detail CAD model'
CAD:assembly		%doc:'assembly'
CAD:draft			%doc:'draft drawing'

CAD:dimension
CAD:tolerance

CAD:CAM				%doc:'CAM functions'
CAM:tool
CAM:stock
CAM:material
CAM:technology

technology:mill
technology:lathe
technology:pcb

class:syntax		%doc:'programming/data language syntax'
syntax:bi
	%ext = [ '.bI' '.blog' ]
syntax:cpp
	%ext = ['.c' '.cc' '.cpp' '.h' '.hh' '.hpp' ]
	%compiler:'g++'
	%comment = [ '//.\*' '/\\*.*\\*/']
cpp:purec
	%ext = [ '.c' '.h' ]
	%compiler:'gcc'
syntax:linker
	%ext = '.ld'
	%compiler:'ld'
syntax:flex
	%ext = [ '.l' '.lpp' ]
	%compiler:'flex'
syntax:bison
	%ext = [ '.y' '.ypp' ]
	%compiler:'bison'
syntax:make
	%ext = [ 'Makefile' '.mk' ]
syntax:batch
	%win32
	%ext = '.bat'
syntax:java
	%ext = [ '.class' '.java' ]
	%compiler:'javac'

sym:arch
arch:i386
arch:arm
arch:avr8
arm:cortexM
arch:mips

sym:cpu
cpu:i686 %arch=i386
cpu:bcm1176 %arch=arm

sym:os
os:win32
os:linux
os:android

sym:computer

sym:hardware
hardware:wifi
hardware:sd
hardware:hdd
hardware:usb
usb:usbhost
usb:usbotg
usb:usbserial			%doc:'FTDI-like connextors'

computer:pc
	%arch=i386
	%usbhost
computer:raspberry
	%arch=arm
	%usbhost
computer:mr3020
	%arch=mips
	%wifi %usbserial

sym:platform %os %cpu %abi %exe %triplet = {(cpu.arch)+'-'+exe+'-'+abi}

platform:win32
	%exe:'.exe'
	%arch = i386
platform:linux
	%exe:elf
	%arch = [ i386 arm mips ]
platform:android
	%arch=arm
	%exe:apk

canadian_cross = [
platform:build
platform:host
platform:target
]


extension:math		%doc:'coputaions'
math:symmath		%doc:'symbolic math computations'
math:nummath		%doc:'numeric math'

nummath:dsp			%doc:'digital signal processing'
nummath:crypto		%doc:'cryptography'

math:linear			%doc:'linear algebra'
math:algebra		%doc:'high order algebra'

math:solver			%doc:'generic solver class'

math:plot			%doc:'plotter interface'
plot:gnuplot
	%'2D' %'3D'
plot:graphviz
	%graph

math:discmath		%doc:'discrete math'
discmath:graph		%doc:'graph applications'

math:measure		%doc:'measurements'

measure:Kilo	%mult=1e3
measure:Kebi	%mult=2^10
measure:Mega	%mult=1e6
measure:Mebi	%mult=2^20
measure:Giga	%milt=1e9
measure:Gebi	%milt=2^30
measure:Terra	%mult=1e12
measure:Tebi	%mult=2^40

measure:frequency
measure:Hz			%doc:'frequency,hertz'
	%frequency
Hz:KHz %mult=Kilo
Hz:MHz %mult=Mega
Hz:GHz %mult=Giga

measure:bytesize	%doc:'memory sizes'
bytesize:Kb %mult=Kebi
bytesize:Mb %mult=Mebi
bytesize:Gb %mult=Gebi
bytesize:Tb %mult=Tebi

extension:cloud		%doc:'cloud/cluster supercomputing'
cloud:cluster		%doc:'cloud computer'
cloud:gomo			%doc:'homohenous'
cloud:hetero		%doc:'heterogenous'
cloud:node			%doc:'node'

HDD:SAS10K
	%size = 76,Gb
	%cache = 16,Mb
hardware:netcard
netcard:Ethernet
netcard:InfiniBand_QDR

cpu:IntelXeonX5560
	%vendor:Intel
	%brand='Xeon'
	%model='X5560'
	%HZ = 2.80,GHz
	%cache = 8,Mb
	%about = url:'https://en.wikipedia.org/wiki/Xeon'

computer:BladeCenter_HS22
	%cpu = 2 * IntelXeonX5560
	%RAM = 12,Mb
	%HDD = SAS10K,76,Gb
	%nethw = [ control,Ethernet compute,InfiniBand_QDR ]

BladeCenter_HS22:KorolevNode
cluster:Korolev		%doc:'supercluster Sergey Korolev (SSAU)'
	%about = url:'http://hpc.ssau.ru/node/6'
	%gomo,cluster
	%interface=SSH
	%master = node:''
	%nodes = 112 * KorolevNode

