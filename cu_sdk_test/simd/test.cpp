#include "../../basis.h"
#include "../../simd.h"

template<typename T>
alignas(64) T a[64];

template<typename T>
alignas(64) T b[64];


int main() try
{
	using vec=VI32x8;
	using pvec=Pack<VI32x8,4>;

	

	a<s2>[0]=1;
	a<s2>[1]=1;
	a<s2>[2]=4;
	a<s2>[3]=5;
	a<s2>[4]=1;
	a<s2>[5]=4;
	a<s2>[6]=1;
	a<s2>[7]=9;

	vec v;
	v.load(a<s2>);

	pvec p(a<s2>);
	p.load(a<s2>);

	v.print();
	
	vec v2;

	v2=v+v;

	v2.print();

	Pack<VI32x8,4> p2=p+v-v2;

	p=p+v-v2;

	for(int i=0;i<4;i++)
		p[i].print();

}
catch(std::exception&e)
{
	puts(e.what());
}
