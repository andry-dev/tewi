let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +37 include/Video/Vertex.h
badd +8 src/Video/Sprite.cpp
badd +24 include/Video/Sprite.h
badd +0 shaders/shader.vert
badd +0 shaders/shader.frag
badd +10 include/Video/TextureManager.h
badd +0 src/MainGame.cpp
badd +0 src/Video/TextureManager.cpp
argglobal
silent! argdel *
set stal=2
edit src/Video/TextureManager.cpp
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 39 + 41) / 82)
exe '2resize ' . ((&lines * 39 + 41) / 82)
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
let s:l = 31 - ((30 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
31
normal! 036|
lcd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
wincmd w
argglobal
edit /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program/include/Video/TextureManager.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 13 - ((6 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
13
normal! 048|
lcd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 39 + 41) / 82)
exe '2resize ' . ((&lines * 39 + 41) / 82)
tabedit /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program/shaders/shader.frag
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 25 + 41) / 82)
exe '2resize ' . ((&lines * 53 + 41) / 82)
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
let s:l = 21 - ((20 * winheight(0) + 12) / 25)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
21
normal! 026|
lcd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
wincmd w
argglobal
edit /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program/shaders/shader.vert
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 12 - ((11 * winheight(0) + 26) / 53)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
12
normal! 0
lcd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
wincmd w
exe '1resize ' . ((&lines * 25 + 41) / 82)
exe '2resize ' . ((&lines * 53 + 41) / 82)
tabedit /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program/include/Video/Sprite.h
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 39 + 41) / 82)
exe '2resize ' . ((&lines * 39 + 41) / 82)
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
let s:l = 27 - ((26 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
27
normal! 030|
lcd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
wincmd w
argglobal
edit /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program/src/Video/Sprite.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 15 - ((14 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
15
normal! 0
wincmd w
exe '1resize ' . ((&lines * 39 + 41) / 82)
exe '2resize ' . ((&lines * 39 + 41) / 82)
tabedit /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program/src/MainGame.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
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
let s:l = 39 - ((38 * winheight(0) + 24) / 48)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
39
normal! 031|
lcd /mnt/ntfs_e/Projects/CPP/VulkanTest/main_program
tabnext 1
set stal=1
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
