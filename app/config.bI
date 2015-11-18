.file ST.config
\# $MODULE$ config file

\# Any program MUST HAVE scripting ability for CONFIGS and user EXTENSIONS.
\# $bICONFIG$

\# this is line comment

\# bI language supports int/float numbers, symbols, strings and nested lists
[ 1299999999999999993 4.5 [ -6e+77 some_sym]
[] [quit exit] 'string' [0x12AFFFFFFFFFFFF 0b1101] [%T %F %N %E %%] ]

#\# = operator can be used for assigning values
#TITLE = '[$MODULE$] $TITLE$' = xxx
#	= ( '= supports multiple assignment' = 'left associativity' )
#\# multiple assignent can be used for constructing complex objects
#FORM('About')
#	= 'About $MODULE$'
#	= Button 'OK'
.eof
.file ST.blog
.eof
