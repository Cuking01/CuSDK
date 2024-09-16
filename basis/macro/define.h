#pragma once

#include"PP_TOOL.h"
#define PP_CONCAT(A, B) PP_CONCAT_IMPL(A, B)
#define PP_COMMA() PP_COMMA_IMPL()
#define PP_LPAREN() PP_LPAREN_IMPL()
#define PP_RPAREN() PP_RPAREN_IMPL()
#define PP_EMPTY() PP_EMPTY_IMPL()
#define PP_SECOND(...) PP_SECOND_IMPL(__VA_ARGS__)
#define PP_REMOVE_PARENS(x) PP_REMOVE_PARENS_IMPL(x)
#define PP_HAS_COMMA(...) PP_HAS_COMMA_IMPL(__VA_ARGS__)
#define PP_COMMA_V(...) PP_COMMA_V_IMPL(__VA_ARGS__)
#define PP_COMMA_IF(N) PP_COMMA_IF_IMPL(N)
#define PP_EMPTY_V(...) PP_EMPTY_V_IMPL(__VA_ARGS__)

#include"PP_INC.h"
#define PP_INC(x) PP_INC_IMPL(x)
#define PP_INC1(x) PP_INC(x)
#define PP_INC2(x) PP_INC1(PP_INC1(x))
#define PP_INC4(x) PP_INC2(PP_INC2(x))
#define PP_INC8(x) PP_INC4(PP_INC4(x))
#define PP_INC16(x) PP_INC8(PP_INC8(x))

#include"PP_DEC.h"
#define PP_DEC(x) PP_DEC_IMPL(x)

#include"PP_POW2.h"
#define PP_POW2(x) PP_POW2_IMPL(x)

#include"PP_BOOL.h"
#define PP_BOOL(x) PP_BOOL_IMPL(x)
#define PP_NOT(x) PP_NOT_IMPL(x)
#define PP_AND(x,y) PP_AND_IMPL(x,y)
#define PP_OR(x,y) PP_OR_IMPL(x,y)

#include"PP_IF.h"
#define PP_IF(b,b1,b2) PP_IF_IMPL(b,b1,b2)

#include"PP_ARR.h"
#define PP_GET_N(N,...) PP_GET_N_IMPL(N,__VA_ARGS__)
#define PP_GET_TUPLE_N(N,T) PP_GET_TUPLE_N_IMPL(N,T)
#define PP_IS_EMPTY(...) PP_IS_EMPTY_IMPL(__VA_ARGS__)
#define PP_VA_OPT_COMMA(...) PP_VA_OPT_COMMA_IMPL(__VA_ARGS__)
#define PP_GET_LEN(...) PP_GET_LEN_IMPL(__VA_ARGS__)

#include"PP_FOR.h"
#define PP_FOR_EACH(Fun,...) PP_FOR_EACH_IMPL(Fun,__VA_ARGS__)

#include"PP_IS_SYMBOL.h"
#define PP_IS_SYMBOL(symbol,x) PP_IS_SYMBOL_IMPL(symbol,x)
#define PP_IS_PARENS(x) PP_IS_PARENS_IMPL(x)

#include"PP_AUTO_IDENTIFIER.h"
#define PP_AUTO_IDENTIFIER(name,num,...) PP_AUTO_IDENTIFIER_IMPL(name,num,PP_IF(PP_IS_EMPTY(__VA_ARGS__),1,__VA_ARGS__))
#define PP_AUTO_IDENTIFIER_OP(name,num,op,op_final,...) PP_AUTO_IDENTIFIER_OP_IMPL(name,num,op,op_final,PP_IF(PP_IS_EMPTY(__VA_ARGS__),1,__VA_ARGS__))
