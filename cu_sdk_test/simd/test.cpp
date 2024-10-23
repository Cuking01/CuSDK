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

	v.load(a<s2>);
	pvec p;
	for(int i=0;i<4;i++)
		p[i].load(a<s2>);

	Lazy_Eval_Record<_mm256_add_epi32,vec,vec,pvec> a(v,p);
	Lazy_Eval_Record<_mm256_add_epi32,vec,decltype(a),pvec> b(a,p);

	static_assert(a.has_lazy_eval==false);
	static_assert(b.has_lazy_eval==true);

	vec v2;
	v2=v+v;
	// ;

	 printf("%d\n",IFMT<VI32x8,VI32x8>::check<vec,vec>());
}
