set mouse=a
set t_Co=256
set cursorline
syntax on
syntax enable
set number
map <F9> : !g++ % -o %<.out <CR>
map <F5> : !./%<.out < %<.in <CR>
set bg=light
set shiftwidth=2
set tabstop=2
set ai
set nu
set ruler
set incsearch
filetype indent on
hi Comment ctermfg=darkcyan
