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

	template<std::same_as<ele_type>... Args> requires (sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT Pack(const Args*...p) {loadu(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void load(const Args*...p) {ls_opt<&Reg_Type::load>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void loadu(const Args*...p) {ls_opt<&Reg_Type::loadu>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void stream_load(const Args*...p) {ls_opt<&Reg_Type::stream_load>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void store(Args*...p) const {ls_opt<&Reg_Type::store>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void storeu(Args*...p) const {ls_opt<&Reg_Type::storeu>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void stream(Args*...p) const {ls_opt<&Reg_Type::stream>(p...);}

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

	template<std::unsigned_integral auto...ids> requires (sizeof...(ids)==n)
	ALWAYS_INLINE auto shuffle() const
	{
		return Pack_Ref<Reg,n>(reg[ids]...);
	}

private:
	template<auto opt,typename... Ele_Ts,std::size_t... ids>
	SIMD_OPT void ls_impl(std::index_sequence<ids...>,Ele_Ts*...p)
	{
		(((reg[ids].*opt)(p)),...);
	}

	template<auto opt,std::size_t... ids>
	SIMD_OPT void ls_helper(const ele_type*p,std::index_sequence<ids...>isq)
	{
		ls_impl<opt>(isq,p+ids*ele_num...);
	}

	template<auto opt,typename... Ele_Ts>
	SIMD_OPT void ls_opt(Ele_Ts*...p)
	{
		if constexpr(sizeof...(Ele_Ts)==1)ls_helper<opt>(p...,std::make_index_sequence<n>());
		else ls_impl<opt>(std::make_index_sequence<n>(),p...);
	}
};



