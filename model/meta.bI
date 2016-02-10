# meta language test suite

# literals and basic composite types

[								# numbers
	[ -01 +00 003 				# integers
		[ 0x12AF , 0b1101 ]]	# machine numbers tuple (with , sepearator)
	[ -01.2 +003e-04 ]			# float numbers
]

# sample expression with function calls, literals and inline class inheritance
file('log','w',0).writeln(
	[ 01+-2.3/sin(constant:Pi)^e*ln(-5e+06) [ 0b1101 0x12AF] ]
)

# class inheritanse
pa:ir pa ir
