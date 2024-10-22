#pragma once

struct XMM:Vec_Reg_Base
{
	union
	{
		__m128i i;
		__m128 f;
		__m128d d;
		__m128h h;
	};
};

#include "xmm/i.hpp"
#include "xmm/f.hpp"
#include "xmm/d.hpp"
#include "xmm/h.hpp"

