\# $AUTOGEN$
\# $bICONFIG$
\# $MODULE$ config file

.inc test/comment.bI
.inc test/numbers.bI

#\# bI language supports int/float numbers, symbols, strings and nested lists
#[ 1299999999999999993 4.5 [ -6e+77 some_sym]
#[] [quit exit] 'string' [0x12AFFFFFFFFFFFF 0b1101] [%T %F %N %E %%] ]

#\# = operator can be used for assigning values
#TITLE = '[$MODULE$] $TITLE$' = xxx
#	= ( '= supports multiple assignment' = 'left associativity' )
#\# multiple assignment can be used for constructing complex objects
#form:About
#	= ( Title = 'About ' + MODULE )
#	= ABOUT
#	= ( Buttons 
#		= button:OK 
#		= button:UPDATE 
#	)
#.eof
#.file ST.blog
.eof
