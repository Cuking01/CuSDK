#pragma once

namespace k_reg_details
{
	template<u2 w>
	struct mmask_t;

	template<>struct mmask_t<8>{using type=__mmask8;};
	template<>struct mmask_t<16>{using type=__mmask16;};
	template<>struct mmask_t<32>{using type=__mmask32;};
	template<>struct mmask_t<64>{using type=__mmask64;};

	template<u2 w>
	using mmask=mmask_t<w>::type;
};

struct K_Reg_Base:Reg_Base{};

template<u2 w> requires (w==8||w==16||w==32||w==64)
struct K_Reg:K_Reg_Base
{
	using ele_type=k_reg_details::mmask<w>;
	static constexpr u2 ele_num=1;

	ele_type k;

	SIMD_OPT K_Reg():k(u3(0)){}
	template<uint_at_least<w> T>
	SIMD_OPT K_Reg(T x)
	{
		if constexpr(w==8) k=_cvtu32_mask8(x);
		else if constexpr(w==16) k=_cvtu32_mask16(x);
		else if constexpr(w==32) k=_cvtu32_mask32(x);
		else k=_cvtu64_mask64(x);
	};

	SIMD_OPT K_Reg(const ele_type*p){load(p);};
	SIMD_OPT K_Reg(ele_type k):k(k){}
	template<Lazy_Eval_Record_T LER>
	SIMD_OPT K_Reg(LER ler){ler.eval(Pack_Ref<K_Reg,1>(*this));}

	SIMD_OPT operator ele_type() const {return k;}
	SIMD_OPT void operator=(const ele_type&k){this->k=k;}
	SIMD_OPT void load(const ele_type*p)
	{
		if constexpr(w==8)k=_load_mask8(p);
		else if constexpr(w==16)k=_load_mask16(p);
		else if constexpr(w==32)k=_load_mask32(p);
		else k=_load_mask64(p);
	}

	SIMD_OPT void store(ele_type*p)
	{
		if constexpr(w==8)k=_store_mask8(p);
		else if constexpr(w==16)k=_store_mask16(p);
		else if constexpr(w==32)k=_store_mask32(p);
		else k=_store_mask64(p);
	}

};

using K8=K_Reg<8>;
using K16=K_Reg<16>;
using K32=K_Reg<32>;
using K64=K_Reg<64>;
