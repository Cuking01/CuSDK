#include "../../basis.h"
#include "../../simd.h"

template<typename T>
alignas(64) T a[64];

template<typename T>
alignas(64) T b[64];

int main()
{
	CInt_Pack<1,2,3,4,5,6> x;
	CInt_Pack<x.get<2>,x.get<4>> y;
	printf("%d %d\n",y.get<0>,y.get<1>);
}
