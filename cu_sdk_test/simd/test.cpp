#include "../../basis.h"
#include "../../simd.h"

template<typename T>
alignas(64) T a[64];

template<typename T>
alignas(64) T b[64];


template<u2 n>
ALWAYS_INLINE void mul_mod(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,Pack_Ref<VU32x8,n> t,VU32x8& vmod,VU32x8& vmodp)
{

	using w64=VU64x4;
	auto ap=a.template as<w64>();
	auto bp=b.template as<w64>();
	auto tp=t.template as<w64>();

	tp=a*b; //t0

	ap=ap>>cint<32>;
	bp=bp>>cint<32>;
	bp=a*b; //t1

	ap=t*vmodp;
	tp=tp>>cint<32>;
	t=blend(t,b,cint<0b1010'1010>);
	bp=b*vmodp;

	ap=a*vmod;
	bp=b*vmod;
	
	a=a>>cint<32>;
	a=blend(a,b,cint<0b1010'1010>);
	
	t=t-a;
	t=t+vmod;
	b=t>vmod;
	b=b&vmod;
	t=t-b;
}

ALWAYS_INLINE void Transpose(Pack_Ref<VI32x8,8> mat,Pack_Ref<VI32x8,8> tmp)
{
	tmp(0,1,2,3)=permute2x(mat(0,1,2,3),mat(4,5,6,7),cint<0b0010'0000>);
	tmp(4,5,6,7)=permute2x(mat(0,1,2,3),mat(4,5,6,7),cint<0b0011'0001>);
	mat(0,1,4,5).as<VI64x4>()=unpacklo(tmp(0,1,4,5).as<VI64x4>(),tmp(2,3,6,7).as<VI64x4>());
	mat(2,3,6,7).as<VI64x4>()=unpackhi(tmp(0,1,4,5).as<VI64x4>(),tmp(2,3,6,7).as<VI64x4>());
	tmp=shuffle(mat,cint<0b1101'1000>);
	mat(0,2,4,6)=unpacklo(tmp(0,2,4,6),tmp(1,3,5,7));
	mat(1,3,5,7)=unpackhi(tmp(0,2,4,6),tmp(1,3,5,7));
}



int main() try
{
	for(int i=0;i<64;i++)
		a<s2>[i]=rand();
	Pack<VI32x8,8> mat(a<int>),tmp;
	for(int i=0;i<8;i++)
		mat[i].print(std::format("mat[{}]",i));
	Transpose(mat,tmp);
	for(int i=0;i<8;i++)
		mat[i].print(std::format("mat[{}]",i));

	// Pack<VU32x8,3> x(a<u2>),y(a<u2>+24);

	// VU32x8 vmod=_mm256_broadcastd_epi32(_mm_cvtsi32_si128(a<u2>[0]));
	// vmod.print("vmod");
}
catch(std::exception&e)
{
	puts(e.what());
}
