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

	template<std::same_as<ele_type>...Args> requires (sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void load(const Args*...p) {ls_opt<&Reg_Type::load>(p...);}

	template<std::same_as<ele_type>...Args> requires (Vec_Reg_T<Reg>&&(sizeof...(Args)==n||sizeof...(Args)==1))
	SIMD_OPT void loadu(const Args*...p) {ls_opt<&Reg_Type::loadu>(p...);}

	template<std::same_as<ele_type>...Args> requires (Vec_Reg_T<Reg>&&(sizeof...(Args)==n||sizeof...(Args)==1))
	SIMD_OPT void stream_load(const Args*...p) {ls_opt<&Reg_Type::stream_load>(p...);}

	template<std::same_as<ele_type>...Args> requires (sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void store(Args*...p) const {ls_opt<&Reg_Type::store>(p...);}

	template<std::same_as<ele_type>...Args> requires (Vec_Reg_T<Reg>&&(sizeof...(Args)==n||sizeof...(Args)==1))
	SIMD_OPT void storeu(Args*...p) const {ls_opt<&Reg_Type::storeu>(p...);}

	template<std::same_as<ele_type>...Args> requires (Vec_Reg_T<Reg>&&(sizeof...(Args)==n||sizeof...(Args)==1))
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

	template<Reg_CLvalue_Like_T RHS,std::size_t... ids>
	void mov_impl(RHS&& rhs,std::index_sequence<ids...>)
	{
		((reg[ids]=rhs[ids]),...);
	}

	template<Reg_CLvalue_Like_T RHS> requires ((Reg_T<std::remove_cvref_t<RHS>>||get_reg_num<std::remove_cvref_t<RHS>> >=n)&&reg_same<Reg,std::remove_cvref_t<RHS>>)
	void operator=(RHS&& rhs)
	{
		mov_impl(std::forward<RHS>(rhs),std::make_index_sequence<n>());
	}

	template<std::integral...Args> requires (sizeof...(Args)>=2)
	ALWAYS_INLINE auto operator[](Args... ids)
	{
		return Pack_Ref<Reg,sizeof...(Args)>(reg[ids]...);
	}

	template<u2 msk>
	ALWAYS_INLINE auto mask()
	{
		return Pack_Ref<Reg,n>(*this).template mask<msk>();
	}

private:
	template<auto opt,typename... Ele_Ts,std::size_t... ids>
	SIMD_OPT void ls_impl(this auto&self,std::index_sequence<ids...>,Ele_Ts*...p)
	{
		(((self.reg[ids].*opt)(p)),...);
	}

	template<auto opt,std::size_t... ids>
	SIMD_OPT void ls_helper(this auto&self,auto*p,std::index_sequence<ids...>isq)
	{
		self.template ls_impl<opt>(isq,p+ids*ele_num...);
	}

	template<auto opt,typename... Ele_Ts>
	SIMD_OPT void ls_opt(this auto&self,Ele_Ts*...p)
	{
		if constexpr(sizeof...(Ele_Ts)==1)self.template ls_helper<opt>(p...,std::make_index_sequence<n>());
		else self.template ls_impl<opt>(std::make_index_sequence<n>(),p...);
	}
};



