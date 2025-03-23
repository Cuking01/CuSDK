#include "../../basis.h"
#include "../../simd.h"

template<typename T>
alignas(64) T a[1<<20];

template<typename T>
alignas(64) T b[1<<20];


template<u2 n>
ALWAYS_INLINE void jmod(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> tmp,const VU32x8&vmod)
{
	tmp=a.template as<VI32x8>() > vmod.template as<VI32x8>();
	tmp=tmp&vmod;
	a=a-tmp;
}

template<u2 n,bool j_mod=true>
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

	ap=t*vmodp;  //t0
	
	tp=tp>>cint<32>;
	t=blend(t,b,cint<0b1010'1010>);
	
	bp=b*vmodp; //t1
	ap=a*vmod;

	t=t+vmod;
	bp=b*vmod;
	
	ap=ap>>cint<32>;
	a=blend(a,b,cint<0b1010'1010>);
	a=t-a;

	if constexpr(j_mod)
		jmod<n>(a,t,vmod);
}

template<u2 n,bool j_mod=true>
ALWAYS_INLINE void mul_mod_4(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,Pack_Ref<VU32x8,n> t0,Pack_Ref<VU32x8,n> t1,const VU32x8& vmod,const VU32x8& vmodp)
{
	using w64=VU64x4;
	auto ap=a.template as<w64>();
	auto bp=b.template as<w64>();
	auto tp0=t0.template as<w64>();
	auto tp1=t1.template as<w64>();

	tp0=a*b;
	ap=ap>>cint<32>;
	bp=bp>>cint<32>;

	tp1=a*b;

	ap=t0*vmodp;  //t0
	bp=t1*vmodp;  //t1
	
	tp0=tp0>>cint<32>;
	t0=blend(t0,t1,cint<0b1010'1010>);

	ap=a*vmod;
	bp=b*vmod;

	t0=t0+vmod;
	
	ap=ap>>cint<32>;
	a=blend(a,b,cint<0b1010'1010>);
	a=t0-a;

	if constexpr(j_mod)
		jmod<n>(a,t0,vmod);
}

template<u2 n>
ALWAYS_INLINE void to_mogo(Pack_Ref<VU32x8,n> x,Pack_Ref<VU32x8,n> t0,Pack_Ref<VU32x8,n> t1,const VU32x8&vyi,const VU32x8&vmod)
{
	using w64=VU64x4;

	auto xp=x.template as<w64>();
	auto tp0=t0.template as<w64>();
	auto tp1=t1.template as<w64>();

	x=x<<cint<2>;
	tp1=xp>>cint<32>;
	tp0=x*vyi;
	tp1=t1*vyi;
	tp0=tp0>>cint<32>;
	t1=t1+x;
	t0=t0+x;
	tp1=tp1>>cint<32>;
	tp0=t0*vmod;
	tp1=t1*vmod;
	tp1=tp1<<cint<32>;
	x=blend(t0,t1,cint<0xaa>);
	t0[0]=t0[0]^t0[0];
	x=t0[0]-x;
}

template<u2 n>
ALWAYS_INLINE void mogo_to(Pack_Ref<VU32x8,n> x,Pack_Ref<VU32x8,n> t0,Pack_Ref<VU32x8,n> t1,VU32x8&vmod,VU32x8&vmodp)
{
	using w64=VU64x4;

	auto xp=x.template as<w64>();
	auto tp0=t0.template as<w64>();
	auto tp1=t1.template as<w64>();

	tp0=x*vmodp;
	xp=xp>>cint<32>;
	tp1=x*vmodp;
	tp0=t0*vmod;
	tp1=t1*vmod;
	tp0=tp0>>cint<32>;
	x=blend(t0,t1,cint<0xaa>);
	x=vmod-x;
	jmod<n>(x,t0,vmod);
}

void mul_mod_s(u2 a,u2 b,u2 mod,u2 modp)
{
	u3 x=(u3)a*b;
	u2 xh=x>>32;
	u2 xl=x;
	u2 m0=(u3)xl*modp;
	u2 q0=(u3)m0*mod>>32;
	u2 ans=xh-q0;
	printf("xh=%u xl=%u m0=%u q0=%u ans=%u\n",xh,xl,m0,q0,ans);
}

ALWAYS_INLINE void Transpose(Pack_Ref<VI32x8,8> mat,Pack_Ref<VI32x8,8> tmp)
{
	tmp[0,1,2,3]=permute2x(mat[0,1,2,3],mat[4,5,6,7],cint<0b0010'0000>);
	tmp[4,5,6,7]=permute2x(mat[0,1,2,3],mat[4,5,6,7],cint<0b0011'0001>);
	mat[0,1,4,5].as<VI64x4>()=unpacklo(tmp[0,1,4,5].as<VI64x4>(),tmp[2,3,6,7].as<VI64x4>());
	mat[2,3,6,7].as<VI64x4>()=unpackhi(tmp[0,1,4,5].as<VI64x4>(),tmp[2,3,6,7].as<VI64x4>());
	tmp=shuffle(mat,cint<0b1101'1000>);
	mat[0,2,4,6]=unpacklo(tmp[0,2,4,6],tmp[1,3,5,7]);
	mat[1,3,5,7]=unpackhi(tmp[0,2,4,6],tmp[1,3,5,7]);
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

u2 pow(u2 a,u2 b)
{
	u2 ans=1;
	while(b)
	{
		if(b&1)ans=(u3)ans*a;
		a=(u3)a*a;
		b>>=1;
	}
	return ans;
}

void test_to_mogo()
{
	static constexpr u2 mod=998244353;
	static constexpr u2 yi=((1ull<<62)+mod-1)/mod-(1ull<<32);
	for(int i=0;i<32;i++)
		a<u2>[i]=i;

	Pack<VU32x8,4> x(a<u2>),t0,t1;
	VU32x8 vyi=set1(yi);
	VU32x8 vmod=set1(mod);
	to_mogo<4>(x,t0,t1,vyi,vmod);

	for(int i=0;i<4;i++)
		x[i].print(std::format("x[{}]",i));

	VU32x8 vmodp=set1(pow(mod,(1u<<31)-1));
	mogo_to<4>(x,t0,t1,vmod,vmodp);

	for(int i=0;i<4;i++)
		x[i].print(std::format("x[{}]",i));
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

void arr_mul_mod1(u2*a,u2*b,u2 size,u2 mod,u2 modp)
{
	Pack<VU32x8,3> pa,pb,t0,t1;
	VU32x8 vmod=set1(mod);
	VU32x8 vmodp=set1(modp);
	for(int i=0;i<size;i+=24)
	{
		pa.load(a+i);
		pb.load(b+i);
		mul_mod_4<3>(pa,pb,t0,t1,vmod,vmodp);
		pa.store(a+i);
	}
}

void arr_mul_mod2(u2*a,u2*b,u2 size,u2 mod,u2 modp)
{
	Pack<VU32x8,4> pa,pb,t;
	VU32x8 vmod=set1(mod);
	VU32x8 vmodp=set1(modp);
	for(int i=0;i<size;i+=32)
	{
		pa.load(a+i);
		pb.load(b+i);
		mul_mod<4>(pa,pb,t,vmod,vmodp);
		pa.store(a+i);
	}
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

	Pack<VU32x8,3> tmp,tmp1;
	mul_mod_4<3>(x,y,tmp,tmp1,vmod,vmodp);

	for(int i=0;i<3;i++)
		x[i].print(std::format("x[{}]",i));
}

void test_mul_mod_speed1()
{
	static constexpr u2 mod=998244353;
	s3 ri,np;
	s3 r=1ull<<32;
	exgcd(r,mod,ri,np);
	const u2 modp=(np%r+r)%r;

	int start=clock();

	for(int i=0;i<1600000;i++)
	{
		arr_mul_mod1(a<u2>,b<u2>,1<<11,mod,modp);
	}
	int end=clock();

	printf("%d\n",end-start);

}

void test_mul_mod_speed2()
{
	static constexpr u2 mod=998244353;
	s3 ri,np;
	s3 r=1ull<<32;
	exgcd(r,mod,ri,np);
	const u2 modp=(np%r+r)%r;

	int start=clock();

	for(int i=0;i<1600000;i++)
	{
		arr_mul_mod2(a<u2>,b<u2>,1<<11,mod,modp);
	}
	int end=clock();

	printf("%d\n",end-start);

}

int main() try
{
	// Pack<VU32x8,4> a;
	// const Pack_Ref<VU32x8,2> pr1=a[0,1];
	// VU32x8 b,c;

	// Pack_Ref pr2(pr1,b,a,c);

	// a=set1(1u);
	// b=set1(2u);
	// c=set1(3u);
	// for(int i=0;i<8;i++)
	// 	pr2[i].print();

	// Pack_CRef pr3(pr1,b,std::as_const(a),c);

	// for(int i=0;i<8;i++)
	// 	pr3[i].print();
	//test_mul_mod();
	//test_mul_mod_speed1();
	//test_mul_mod_speed2();
	//test_to_mogo();

	VU64x8 x;
	Pack_CRef<VU64x8,4> rx(x);
	Pack_CRef<VU64x8,4> rx2(x,x,x,x);
	Pack_CRef<VU64x8,4> rx3(rx,rx2,x,x);
}
catch(std::exception&e)
{
	puts(e.what());
}
