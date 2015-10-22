" this is sample _vimrc file for win32 (g)Vim 
" with keymaps and dark colors (modified pablo colroscheme)
" .github: https://github.com/ponyatov/winhome/blob/master/_vimrc

source $VIMRUNTIME\..\_vimrc

"set encoding=utf-8

colorscheme pablo
au ColorScheme * highlight LineNr ctermfg=darkblue guifg=darkblue
au ColorScheme * highlight ColorColumn ctermbg=darkblue guibg=darkblue
au ColorScheme * highlight Todo ctermbg=blue ctermfg=white guibg=blue guifg=white
au ColorScheme * highlight String ctermfg=magenta guifg=magenta
au ColorScheme * highlight Number ctermfg=green guifg=green

set number
set colorcolumn=80

syntax on
filetype on
set tabstop=4 softtabstop=0 noexpandtab shiftwidth=4

nnoremap <F2> :w<CR>
inoremap <F2> <ESC>:w<CR><INS>
nnoremap <F4> :w<CR>:!mingw32-make EXE=.exe clean<CR>
inoremap <F4> <ESC>:w<CR>:!mingw32-make EXE=.exe clean<CR>
inoremap <F9> <ESC>:syn off<CR>:syn on <CR><INS>
nnoremap <F9> :syn off<CR>:syn on <CR>
nnoremap <F12> :w<CR>:!mingw32-make EXE=.exe<CR>
inoremap <F12> <ESC>:w<CR>:!mingw32-make EXE=.exe<CR>

noremap <c-t> :tabf<space>
noremap <c-w> ZZ
inoremap <c-t> <ESC>:tabf<space>
inoremap <c-w> <ESC>ZZ

if has("gui_running")
	set columns=88 lines=44
endif

