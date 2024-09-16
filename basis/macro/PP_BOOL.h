#pragma once


#define PP_NOT_0 1
#define PP_NOT_1 0

#define PP_AND_00 0
#define PP_AND_01 0
#define PP_AND_10 0
#define PP_AND_11 1

#define PP_OR_00 0
#define PP_OR_01 1
#define PP_OR_10 1
#define PP_OR_11 1

#define PP_BOOL_trans0() ~,0
#define PP_BOOL_IMPL(x) PP_SECOND(PP_CONCAT(PP_BOOL_trans,x)(),1)
#define PP_NOT_IMPL(x) PP_CONCAT(PP_NOT_,PP_BOOL(x))
#define PP_AND_IMPL(x,y) PP_CONCAT(PP_CONCAT(PP_AND_,PP_BOOL(x)),PP_BOOL(y))
#define PP_OR_IMPL(x,y) PP_CONCAT(PP_CONCAT(PP_OR_,PP_BOOL(x)),PP_BOOL(y))
