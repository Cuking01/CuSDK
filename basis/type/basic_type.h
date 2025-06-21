#pragma once

#include<stdint.h>

typedef int8_t      s0;
typedef int16_t     s1;
typedef int32_t     s2;
typedef int64_t     s3;
typedef __int128_t  s4;

typedef uint8_t     u0;
typedef uint16_t    u1;
typedef uint32_t    u2;
typedef uint64_t    u3;
typedef __uint128_t u4;

typedef float       f2;
typedef double      f3;

using byte=u0;

namespace type_details
{
	template<u2 bits>
	struct sint_t;

	template<>
	struct sint_t<8>{using type=s0;};
	template<>
	struct sint_t<16>{using type=s1;};
	template<>
	struct sint_t<32>{using type=s2;};
	template<>
	struct sint_t<64>{using type=s3;};

	template<u2 bits>
	struct uint_t;

	template<>
	struct uint_t<8>{using type=u0;};
	template<>
	struct uint_t<16>{using type=u1;};
	template<>
	struct uint_t<32>{using type=u2;};
	template<>
	struct uint_t<64>{using type=u3;};
};

template<u2 bits>
using uint=type_details::uint_t<bits>::type;

template<u2 bits>
using sint=type_details::sint_t<bits>::type;



