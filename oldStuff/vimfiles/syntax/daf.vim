" Vim syntax file
" Langauge: Daf (Acronym yet to be decided)
" Maintainer: HKrogstie <krogstie(full stop)havard (you know wh-) at g(oogle)mail (full stop) commercial>
" Latest Revision: 27 November 2015

if exists("b:current_syntax")
	finish
endif

syn keyword dafControlAndDefKeywords let mut def if else for in while do match cast return break continue retry
syn keyword dafHeapStuff new delete
syn keyword dafDefinitionKeywords using namespace struct class abstract extends interface implements this pub func method const virtual override
syn keyword dafPrimitiveTypeKeywords int long float double bool char uint8 uint16 int16 uint32 int32 uint64 int64 usize true false
syn match dafIterator '=\.\.[<=>]'
syn match dafNumber '\<\d\+\>'
syn match dafNumber '\<\d\+\.\d*f\?'
syn match dafNumber '\.\d\+f\?'
syn match dafString '".*"'

syn region dafBlock start="{" end="}" fold transparent

syn keyword dafTodo contained TODO FIXME XXX NOTE
syn match dafComment "//.*$" contains=dafTodo
syn region dafComment start="/\*" end="\*/"
syn match dafPreProc "^#.*$"

let b:current_syntax = "daf"

hi def link dafControlAndDefKeywords		Statement
hi def link dafDefinitionKeywords		PreProc
hi def link dafPrimitiveTypeKeywords         	Type
hi def link dafHeapStuff         		Type
hi def link dafIterator				Type
hi def link dafString      			Constant
hi def link dafPreProc     			PreProc
hi def link dafNumber      			Constant
hi def link dafTodo        			Todo
hi def link dafComment				Comment	
