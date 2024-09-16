#pragma once

#define IS_VOID_void 
#define PP_IS_SYMBOL_IMPL(symbol,x) PP_IS_EMPTY(PP_CONCAT(IS_,PP_CONCAT(symbol,PP_CONCAT(_,x))))

#define PP_IS_PARENS_IMPL(x) PP_IS_EMPTY(PP_EMPTY_V x)
