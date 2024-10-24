#pragma once

template<Reg_T Reg,u2 n> requires (n>0)
struct Pack
{
	static constexpr u2 size=n;
	using Reg_Type=Reg;
	using ele_type=typename Reg::ele_type;
	static constexpr u2 ele_num=Reg::ele_num;

	Reg reg[n];

	ALWAYS_INLINE Reg& operator[](u2 idx){return reg[idx];}
	ALWAYS_INLINE const Reg& operator[](u2 idx) const {return reg[idx];}

	ALWAYS_INLINE Pack(){}

	template<std::same_as<ele_type>... Args> requires (sizeof...(Args)==n)
	SIMD_OPT Pack(const Args*...p):reg{p...} {}


	template<std::size_t... ids>
	SIMD_OPT Pack(const ele_type*p,std::index_sequence<ids...>):Pack(p+ids*ele_num...) {}

	SIMD_OPT Pack(const ele_type*p):Pack(p,std::make_index_sequence<n>()) {}

	template<std::same_as<ele_type>... Args,std::size_t... ids>
	SIMD_OPT void load_impl(std::index_sequence<ids...>,const Args*...p)
	{
		((reg[ids].load(p)),...);
	}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n)
	SIMD_OPT void load(const Args*...p)
	{
		load_impl(std::make_index_sequence<n>(),p...);
	}

	template<std::size_t... ids>
	SIMD_OPT void load_helper(const ele_type*p,std::index_sequence<ids...>isq)
	{
		load_impl(isq,p+ids*ele_num...);
	}

	SIMD_OPT void load(const ele_type*p)
	{
		load_helper(p,std::make_index_sequence<n>());
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT Pack(LER ler)
	{
		ler.eval(Pack_Ref<Reg,n>(*this));
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT void operator=(LER ler)
	{
		ler.eval(Pack_Ref<Reg,n>(*this));
	}
};




