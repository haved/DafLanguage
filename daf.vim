" Vim syntax file
" Langauge: Daf (Acronym yet to be decided)
" Maintainer: HKrogstie <krogstie(full stop)havard (you know wh-) at g(oogle)mail (full stop) commercial>
" Latest Revision: 27 November 2015

if exists("b:current_syntax")
	finish
endif

syn keyword dafDefineAndLetKeywords let def
syn keyword dafDefinitionsKeyworks struct class extends interface implements impl
syn keyword controlStatementKeywords if else for while do match
syn keyword dafPrimitiveTypeKeywords int long float double boolean char u8 u16 s16 u32 s32 u64 s64
syn match dafNumber '\d\+'
syn match dafNumber '[-+]\d\+'
syn region dafString start='"' end='"' contained

syn region dafBlock start="{" end="}" fold transparent

syn keyword dafTodo contained TODO FIXME XXX NOTE
syn match dafComment "//.*$" contains=dafTodo
syn match dafPreProc "^#.*$"

let b:current_syntax = "daf"

hi def link dafDefineAndLetKeywords		Statement
hi def link dafDefinitionsKeywords		PreProc
hi def link dafControlStatementKeywords		Todo
hi def link dafPrimitiveTypeKeywords         	Type
hi def link dafString      			Constant
hi def link dafPreProc     			PreProc
hi def link dafNumber      			Constant
hi def link dafTodo        			Todo
hi def link dafComment     		
hi def link dafControlStatementKeywords		TodoComment
