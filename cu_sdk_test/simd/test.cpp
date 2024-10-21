#include "../../basis.h"
#include "../../simd.h"

template<typename T>
alignas(64) T a[64];

template<typename T>
alignas(64) T b[64];

int main()
{
	VU8x16 mm;
	mm.load(a<u0>);
	mm.store(b<u0>);
}
