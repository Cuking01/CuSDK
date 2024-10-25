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
	using pr=Pack_Ref<VI32x8,4>;
	

	a<s2>[0]=-1;
	a<s2>[1]=-1;
	a<s2>[2]=-4;
	a<s2>[3]=-5;
	a<s2>[4]=-1;
	a<s2>[5]=4;
	a<s2>[6]=1;
	a<s2>[7]=9;

	for(int i=0;i<64;i++)
		printf("%d\n",a<s2>[i]);

	VI32x8 v(a<s2>);
	v.load(a<s2>);

	Pack<VI32x8,4> p(a<s2>);
	p.load(a<s2>,a<s2>+16,a<s2>+24,a<s2>+48);
	//p.load(a<s2>+0,a<s2>+8);

	for(int i=0;i<4;i++)
		p[i].print("p[i]");

	Pack_Ref<VI32x8,4> rf(p);

	rf.load(a<s2>,a<s2>+16,a<s2>+24,a<s2>+48);
	//rf.load(a<s2>+0,a<s2>+8);

	v.print("v");
	
	vec v2;

	v2=v+v;

	v2.print("v2=v+v");

	Pack<VI32x8,4> p2=p+v;

	p2=p2-v2;

	p.load(a<s2>,a<s2>,a<s2>,a<s2>);
	p=shuffle(p,CInt_Pack<0x55,0x77,0x99,0xbb>());
	for(int i=0;i<4;i++)
		p[i].print(std::format(">>p[{}]",i));

	Pack<VI64x4,4> p64_=p*v;
	p64_[0].print("p64_");

	p=p+v;
	p=p-v2;

	for(int i=0;i<4;i++)
		p[i].print("p[i]=p[i]+v-v2");

	for(int i=0;i<4;i++)
		p2[i].print("p2[i]=p2[i]+v-v2");

	Pack<VI32x8,4> p3=p2&p;

	for(int i=0;i<4;i++)
		p3[i].print("p3[i]=p2[i]&p[i]");
}
catch(std::exception&e)
{
	puts(e.what());
}
