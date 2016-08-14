let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd /mnt/ntfs_e/Projects/CPP/sdl-scratch/tewi
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +0 include/Video/Camera2D.h
badd +36 src/Video/Camera2D.cpp
badd +147 ~/.vimrc
argglobal
silent! argdel *
edit src/Video/Camera2D.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 155 + 156) / 312)
exe 'vert 2resize ' . ((&columns * 156 + 156) / 312)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 36 - ((35 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
36
normal! 025|
lcd /mnt/ntfs_e/Projects/CPP/sdl-scratch/tewi
wincmd w
argglobal
edit /mnt/ntfs_e/Projects/CPP/sdl-scratch/tewi/include/Video/Camera2D.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 25 - ((24 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
25
normal! 030|
lcd /mnt/ntfs_e/Projects/CPP/sdl-scratch/tewi
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 155 + 156) / 312)
exe 'vert 2resize ' . ((&columns * 156 + 156) / 312)
tabnext 1
if exists('s:wipebuf') && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
