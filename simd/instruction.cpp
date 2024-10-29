#pragma once

#define make_i_1(name,instrction,ret,iflag,other_req,FMT1) \
template<typename A> requires(IFMT<FMT1>::check<A>()&&(iflag)&&(other_req)) \
SIMD_OPT auto name(const A&a) \
{ \
	return Lazy_Eval_Record<instrction,ret,A>(a); \
}


#define make_i_2(name,instrction,ret,iflag,other_req,FMT1,FMT2) \
template<typename A,typename B> requires(IFMT<FMT1,FMT2>::check<A,B>()&&(iflag)&&(other_req)) \
SIMD_OPT auto name(const A&a,const B&b) \
{ \
	return Lazy_Eval_Record<instrction,ret,A,B>(a,b); \
}

#define make_i_3(name,instrction,ret,iflag,other_req,FMT1,FMT2,FMT3) \
template<typename A,typename B,typename C> requires(IFMT<FMT1,FMT2,FMT3>::check<A,B,C>()&&(iflag)&&(other_req)) \
SIMD_OPT auto name(const A&a,const B&b,const C&c) \
{ \
	return Lazy_Eval_Record<instrction,ret,A,B,C>(a,b,c); \
}


#include "instruction/application-targeted.cpp"
#include "instruction/arithmetic.cpp"
#include "instruction/bit-manipulation.cpp"
#include "instruction/cast.cpp"
#include "instruction/compare.cpp"
#include "instruction/convert.cpp"
#include "instruction/cryptography.cpp"
#include "instruction/elementary-math-functions.cpp"
#include "instruction/general-support.cpp"
#include "instruction/load.cpp"
#include "instruction/logical.cpp"
#include "instruction/mask.cpp"
#include "instruction/miscellaneous.cpp"
#include "instruction/move.cpp"
#include "instruction/os-targeted.cpp"
#include "instruction/probability-or-statistics.cpp"
#include "instruction/random.cpp"
#include "instruction/set.cpp"
#include "instruction/shift.cpp"
#include "instruction/special-math-functions.cpp"
#include "instruction/store.cpp"
#include "instruction/string-compare.cpp"
#include "instruction/swizzle.cpp"
#include "instruction/trigonometry.cpp"
#include "instruction/unknown.cpp"


#undef make_i_1
#undef make_i_2
#undef make_i_3
