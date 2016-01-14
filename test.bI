.sec bI core types test

#| block comment [[ |#
# line comment
[										" bI core data types "
	[									" == scalars nested list == "
	[										" numbers "
		[ -01 00 +003 ]						" integer "
		[ 									" machine numbers "
		< 0x012AF DEADBEEFh > "hex" 
		< 0b01101 00101001b > "binary"	# bin string, leading 0z must be saved
		]	
		[									" floating point numbers "
			-02.34 "dotted"
			+04e-05 "exponential"
		]				
	]
	'string' symbol	X:Y "pa:ir"
	]									# == composites ==
	[ 1,2 3,4,5 ]							" tu:ple "
	[ <> <1> <1 2> <1,2> <3 4,5> ]			" <vector> "
	[										" {la:mbda} "
		{ "empty lambda" }
		{X:Y} 				"constant {la:mbda}"
		{Z:Z}				"copy lambda"
	]
]

