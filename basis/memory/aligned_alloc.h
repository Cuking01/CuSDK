#pragma once

#ifdef _WIN32
	#define aligned_alloc _aligned_malloc
	#define aligned_free _aligned_free
#else
	#define aligned_free free
#endif



