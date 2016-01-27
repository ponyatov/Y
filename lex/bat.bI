bat = next + file @ 'bat.bat'		# (g)vim helper
bat += '@start .\n'
bat += '@gvim -c "colorscheme peachpuff" -p '+files/' '+'\n'

