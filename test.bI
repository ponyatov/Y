.sec bI core types test

#| block comment [[ |#
# line comment
[										" bI core data types "
	[									" numbers "
		[ -01 00 +003 ]					" integer "
		[ 0x12AF "hex" 0b1101 "bin" ]	" machine numbers "
		[								" floating point numbers "
			-02.34 "dotted"
			+04e-05 "exponential"
		]				
	]
	'string' symbol	X:Y "pa:ir"
	[ 1,2 3,4,5 ]						" tu:ples "
	[ <> <1> <1 2> <1,2> <3 4,5> ]		" <vectors> "
	[									" {la:mbda} usage samples "
		{ "empty lambda" }
		{X:Y} 				"constant {la:mbda}"
		{Z:Z}				"copy lambda"
	]
]

