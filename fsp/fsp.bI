
MODULE	  "FSP skeleton"
TITLE	= 'Free Syntax Programming'
ABOUT	= 'tiny portable declarative programming translator'

next = (dir "mkdir")@'next' "generation"

# README.md

readme	= next+file@'README.md'		" README "
readme += '# ![logo](https://github.com/ponyatov/icons/raw/master/'+LOGO+'.png)'
readme += ' '+MODULE+' : '+TITLE+'\n'
readme += '### '+ABOUT+'\n'
readme += '\n'+AUTHOR+'\n'
readme += '\nlicence: '+LICENSE+'\n'
readme += '\nGitHub: '+GITHUB+'\n'
readme += '\n### ![warning](https://github.com/ponyatov/icons/raw/master/'
readme += 'warning64x64.png) '
readme += 'Powered by bI language system\n'

# meta.hpp

meta	= next+file@'meta.hpp'		# metainfo defines (AUTHOR,TITLE,..)
meta += '#ifndef _H_META
										// ==== metainformation ====
#define _H_META\n'
meta += '
#define TITLE "'+TITLE+'"
#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev"
#define AUTOGEN "/***** DO NOT EDIT: this file was autogened by bI *****/"
#define LOGO "'+LOGO+'"
#define ABOUT "'+ABOUT+'"\n'
meta += '\n#endif // _H_META'

# FILES

allfiles = [
		readme
	files = [
		bi		= next+file@'fsp.bI'		" source "
		log		= next+file@'fsp.blog'		" log "
		yacc	= next+file@'ypp.ypp'		" parser "
		lex		= next+file@'lpp.lpp'		" lexer "
		hpp		= next+file@'hpp.hpp'		" headers "
		cpp		= next+file@'cpp.cpp'		" c++ core "
		make	= next+file@'Makefile'		" project management scripts "
		meta
		bat		= next+file@'bat.bat'		# (g)vim helper /win32/
	]
		gitignore = next+file@'.gitignore'	# ignore files in git repository
]

# bat.bat

bat += '@start .\n'
bat += '@gvim -c "colorscheme peachpuff" -p '+files/' '+'\n'

