
MODULE	  "FSP skeleton"
TITLE	= 'Free Syntax Programming'
ABOUT	= 'tiny portable declarative programming translator'

next = (dir "mkdir")@'next' "generation"

		readme	= next+file@'README.md'		" README "

allfiles = [
		readme	= next+file@'README.md'		" README "
	files = [
		bi		= next+file@'fsp.bI'		# source
		log		= next+file@'fsp.blog'		# log
		yacc	= next+file@'ypp.ypp'		# parser
		lex		= next+file@'lpp.lpp'		# lexer
		hpp		= next+file@'hpp.hpp'		# headers
		meta	= next+file@'meta.hpp'		# metainfo defines (AUTHOR,TITLE,..)
		cpp		= next+file@'cpp.cpp'		# c++ core
		make	= next+file@'Makefile'		# project management scripts
	]
		bat		= next+file@'bat.bat'		# (g)vim helper /win32/
		gitignore = next+file@'.gitignore'	# ignore files in git repository
]

