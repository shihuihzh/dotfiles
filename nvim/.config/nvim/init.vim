" ========== Plugin ==========
" Initialize plugin system
call plug#begin('~/.vim/plugged')

Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'preservim/nerdtree', { 'on':  'NERDTreeToggle' }
Plug 'Xuyuanp/nerdtree-git-plugin'
Plug 'tiagofumo/vim-nerdtree-syntax-highlight'
Plug 'ryanoasis/vim-devicons'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'mhinz/vim-startify'

"Plug 'flazz/vim-colorschemes'
" Plug 'dracula/vim', { 'as': 'dracula' }
" Plug 'morhetz/gruvbox'
Plug 'sainnhe/gruvbox-material'

Plug 'francoiscabrol/ranger.vim'
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'

Plug 'honza/vim-snippets'
Plug 'tpope/vim-commentary'
Plug 'tpope/vim-surround'
Plug 'machakann/vim-highlightedyank'
Plug 'sheerun/vim-polyglot'
Plug 'nvim-treesitter/nvim-treesitter', {'do': ':TSUpdate'}

" Plug 'rust-lang/rust.vim'
" Plug 'pappasam/coc-jedi', { 'do': 'yarn install --frozen-lockfile && yarn build' }
call plug#end()

" ========== Options ==========
" indent
set autoindent
set expandtab
set shiftwidth=4
set smarttab
set tabstop=4

" search
set hlsearch
set ignorecase
set incsearch
set smartcase

" Text
syntax enable

" UI
set hidden
set termguicolors
set laststatus=2
set ruler
set wildmenu
set number
let g:gruvbox_material_transparent_background = 1
colorscheme gruvbox-material
filetype plugin on
"set spell

" ========== Key Mapping ==========
let mapleader = ' '
nnoremap <leader><CR> :nohlsearch<CR>
imap jj <ESC>
nnoremap <silent><C-x> :q<CR>
" nnoremap <silent><C-X> :qa<CR>

" Code enhance
inoremap <C-E> <ESC>A;<CR>


" Terminal
nnoremap <silent><leader>t :below 10split term://zsh<CR>A
tnoremap <silent><C-x> <C-\><C-N>:q<CR>
tnoremap <silent><ESC> <C-\><C-N>

" Window
tnoremap <silent><A-h> <C-\><C-N><C-w>h
tnoremap <silent><A-j> <C-\><C-N><C-w>j
tnoremap <silent><A-k> <C-\><C-N><C-w>k
tnoremap <silent><A-l> <C-\><C-N><C-w>l
inoremap <silent><A-h> <C-\><C-N><C-w>h
inoremap <silent><A-j> <C-\><C-N><C-w>j
inoremap <silent><A-k> <C-\><C-N><C-w>k
inoremap <silent><A-l> <C-\><C-N><C-w>l
nnoremap <silent><A-h> <C-w>h
nnoremap <silent><A-j> <C-w>j
nnoremap <silent><A-k> <C-w>k
nnoremap <silent><A-l> <C-w>l
nnoremap <silent><C-H> <C-W><C-lt>
nnoremap <silent><C-L> <C-W><C-char-62>
nnoremap <silent><C-J> <C-W><C-kMinus>
nnoremap <silent><C-K> <C-W><C-kPlus>


" ========== Plugin Setting ==========
" ---------- COC ----------
function! s:check_back_space() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

function! s:show_documentation()
  if (index(['vim','help'], &filetype) >= 0)
    execute 'h '.expand('<cword>')
  elseif (coc#rpc#ready())
    call CocActionAsync('doHover')
  else
    execute '!' . &keywordprg . " " . expand('<cword>')
  endif
endfunction

" complete
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"
inoremap <silent><expr> <M-CR> coc#refresh()
inoremap <silent><expr> <cr> pumvisible() ? coc#_select_confirm(): "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"
" GoTo code navigation.
nmap <silent> [g <Plug>(coc-diagnostic-prev)
nmap <silent> ]g <Plug>(coc-diagnostic-next)
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)
nnoremap <silent> K :call <SID>show_documentation()<CR>

" Symbol renaming.
nmap <leader>rn <Plug>(coc-rename)

" Formatting selected code.
" xmap <leader>f  <Plug>(coc-format-selected)
" nmap <leader>f  <Plug>(coc-format-selected)

" Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)

" Remap keys for applying codeAction to the current buffer.
nmap <leader>ac  <Plug>(coc-codeaction)
" Apply AutoFix to problem on the current line.
nmap <leader>qf  <Plug>(coc-fix-current)

" multi cursor
nmap <silent> <C-c> <Plug>(coc-cursors-position)
nmap <silent> <C-C> <Plug>(coc-cursors-word)
xmap <silent> <C-C> <Plug>(coc-cursors-range)
" use normal command like `<leader>xi(`
nmap <leader>x  <Plug>(coc-cursors-operator)

" ---------- Nerd Tree ----------
nnoremap <silent><leader>f :NERDTreeToggle<CR>
let NERDTreeShowHidden=1
" autocmd vimenter * NERDTree

" ---------- FZF ----------
nnoremap <silent><C-p> :Files<CR>
nnoremap <silent><leader>e :History<CR>

" ---- airline ----
let g:airline_powerline_fonts = 1
" let g:airline#extensions#tabline#enabled = 1

" ---- vim ranger ----
let g:ranger_map_keys = 0

" ---- highlightedyank ----
let g:highlightedyank_highlight_duration = 200

"========= vimspector =====
let g:vimspector_enable_mappings = 'HUMAN'
packadd! vimspector
function! JavaStartDebugCallback(err, port)
  execute "cexpr! 'Java debug started on port: " . a:port . "'"
  call vimspector#LaunchWithSettings({ "configuration": "Java Launch", "DAPPort": a:port })
endfunction

function JavaStartDebug()
  call CocActionAsync('runCommand', 'vscode.java.startDebugSession', function('JavaStartDebugCallback'))
endfunction
nnoremap <silent> <leader><F5> :call JavaStartDebug()<CR>

" ========= TreeSitter =======
lua <<EOF
require'nvim-treesitter.configs'.setup {
  ensure_installed = "all", -- one of "all", "maintained" (parsers with maintainers), or a list of languages
  highlight = {
    enable = true,              -- false will disable the whole extension
    disable = {  },  -- list of language that will be disabled
  },
}
EOF
