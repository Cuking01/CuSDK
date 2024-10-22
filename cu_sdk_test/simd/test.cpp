#include "../../basis.h"
#include "../../simd.h"

template<typename T>
alignas(64) T a[64];

template<typename T>
alignas(64) T b[64];

int main()
{
	using vec=VI32x8;
	using pvec=Pack<VI32x8,4>;

	vec v;
	pvec p;

	Lazy_Eval_Record<1,vec,pvec> a(v,p);
	Lazy_Eval_Record<1,decltype(a)> b(a);

	static_assert(a.has_lazy_eval==false);
	static_assert(b.has_lazy_eval==true);

}
