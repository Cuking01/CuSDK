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

	ap=b*vmodp; //t1
	
	bp=bp<<cint<32>;
	t=blend(t,b,cint<0b1010'1010>);
	t[0].print("t[0]");
	bp=t*vmodp;  //t0

	ap=a*vmod;
	bp=b*vmod;
	
	bp=bp>>cint<32>;
	a=blend(b,a,cint<0b1010'1010>);
	a[0].print("asn[0]");
	t=t-a;
	t[0].print("ans[0]");
	t=t+vmod;
	t[0].print("ans[0]");
	b=t.template as<VI32x8>() > vmod.template as<VI32x8>();
	b[0].print("jmod");
	b=b&vmod;
	b[0].print("jmod");
	a=t-b;
}

void mul_mod_s(u2 a,u2 b,u2 mod,u2 modp)
{
	u3 x=(u3)a*b;
	u2 xh=x>>32;
	u2 xl=x;
	u2 m0=(u3)xl*modp;
	u2 q0=(u3)m0*mod>>32;
	u2 ans=xl-q0;
	printf("xh=%u xl=%u m0=%u q0=%u ans=%u\n",xh,xl,m0,q0,ans);
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

s3 exgcd(s3 a,s3 b,s3&x,s3&y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }

    s3 r=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return r;
}

void test_transpose()
{
	for(int i=0;i<64;i++)
		a<s2>[i]=rand();
	Pack<VI32x8,8> mat(a<int>),tmp;
	for(int i=0;i<8;i++)
		mat[i].print(std::format("mat[{}]",i));
	Transpose(mat,tmp);
	for(int i=0;i<8;i++)
		mat[i].print(std::format("mat[{}]",i));
}

void test_mul_mod()
{
	for(int i=0;i<64;i++)
		a<u2>[i]=rand();

	Pack<VU32x8,3> x(a<u2>),y(a<u2>+24);

	static constexpr u2 mod=998244353;
	s3 ri,np;
	s3 r=1ull<<32;
	exgcd(r,mod,ri,np);
	const u2 modp=(np%r+r)%r;

	mul_mod_s(41,292,mod,modp);

	VU32x8 vmod=set1(mod);
	VU32x8 vmodp=set1(modp);
	vmod.print("vmod");
	vmodp.print("vmodp");

	for(int i=0;i<3;i++)
		x[i].print(std::format("x[{}]",i));
	for(int i=0;i<3;i++)
		y[i].print(std::format("y[{}]",i));

	Pack<VU32x8,3> tmp;
	mul_mod<3>(x,y,tmp,vmod,vmodp);

	for(int i=0;i<3;i++)
		x[i].print(std::format("x[{}]",i));
}

int main() try
{
	test_mul_mod();

	
}
catch(std::exception&e)
{
	puts(e.what());
}
