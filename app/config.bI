.file ST.config
\# $MODULE$ config file

\# Any program MUST HAVE scripting ability for CONFIGS and user EXTENSIONS.
\# $bICONFIG$

\# this is line comment

\# bI language supports int/float numbers, symbols, strings and nested lists
123 [ 4.5 [ -6e+7 some_sym] [] 'string' [0x12AF 0b1101] [%T %F %N %E] ]

#\# = operator can be used for assigning values
#TITLE = '[$MODULE$] $TITLE$' = xxx
#	= ( '= supports multiple assignment' = 'left associativity' )
#\# multiple assignent can be used for constructing complex objects
#FORM('About')
#	= 'About $MODULE$'
#	= Button 'OK'
.eof
