#pragma once

#define PP_CONCAT_IMPL(A, B) A##B
#define PP_COMMA_IMPL() ,
#define PP_LPAREN_IMPL() (
#define PP_RPAREN_IMPL() )
#define PP_EMPTY_IMPL()
#define PP_SECOND_IMPL(a,b,...) b
#define PP_REMOVE_PARENS_IMPL_IMPL(...) __VA_ARGS__
#define PP_REMOVE_PARENS_IMPL(x) PP_REMOVE_PARENS_IMPL_IMPL x
#define PP_COMMA_V_IMPL(...) ,
#define PP_HAS_COMMA_IMPL(...) PP_GET_N_63(__VA_ARGS__,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0)
#define PP_COMMA_IF_IMPL(N) PP_IF(N,PP_COMMA,PP_EMPTY)() 
#define PP_EMPTY_V_IMPL(...) 
