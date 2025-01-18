#pragma once

#ifdef _WIN32
	#define aligned_alloc _aligned_alloc
	#define aligned_free _alogned_free
#else
	#define aligned_free free
#endif



