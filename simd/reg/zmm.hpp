#pragma once

struct ZMM
{
	union
	{
		__m512i i;
		__m512 f;
		__m512d d;
		__m512h h;
	};
};



