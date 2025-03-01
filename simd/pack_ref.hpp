#pragma once

namespace Pack_Ref_Detail
{

	template<u2 mask,std::size_t n,std::size_t...ids>
	struct Make_Mask_Index_Sequence_Helper
	{
		using type=typename Make_Mask_Index_Sequence_Helper<mask,n-1,ids...>::type;
	};

	template<u2 mask,std::size_t n,std::size_t...ids> requires (n>0&&(n-1&~mask)==0)
	struct Make_Mask_Index_Sequence_Helper<mask,n,ids...>
	{
		using type=typename Make_Mask_Index_Sequence_Helper<mask,n-1,n-1,ids...>::type;
	};

	template<u2 mask,std::size_t n,std::size_t...ids> requires (n==0)
	struct Make_Mask_Index_Sequence_Helper<mask,n,ids...>
	{
		using type=std::index_sequence<ids...>;
	};

	template<u2 mask,std::size_t n>
	constexpr auto make_mask_index_sequence()
	{
		return typename Make_Mask_Index_Sequence_Helper<mask,n>::type{};
	}

	template<Reg_T Reg>
	struct Ref
	{
		Reg& ref;
	};

	template<Reg_T Reg>
	struct CRef
	{
		const Reg&ref;
	};

	struct Merge_Flag{};

	static constexpr Merge_Flag merge_flag{};

	template<u2 idx,typename Reg_Like0,typename... Reg_Likes>
	ALWAYS_INLINE decltype(auto) extract_ith_reg(Reg_Like0&&reg0,Reg_Likes&&...regs)
	{
		static constexpr u2 sz=get_reg_num<std::remove_cvref_t<Reg_Like0>>;
		if constexpr(idx<sz)
			return reg0[idx];
		else
			return extract_ith_reg<idx-sz,Reg_Likes...>(std::forward<Reg_Likes>(regs)...);
	}

	template<typename Reg_Like0,typename... Reg_Likes>
	constexpr bool all_reg_same=(reg_same<std::remove_cvref_t<Reg_Like0>,std::remove_cvref_t<Reg_Likes>>&&...);

	template<typename Reg_Like0,typename... Reg_Likes>
	struct common_reg_type_impl
	{
		using type=get_reg<std::remove_cvref_t<Reg_Like0>>;
	};

	template<typename... Reg_Likes>
	using common_reg_type=typename common_reg_type_impl<Reg_Likes...>::type;

	template<typename... Reg_Likes>
	constexpr u2 all_size_sum=(get_reg_num<std::remove_cvref_t<Reg_Likes>>+...+0);
}; //namespace Pack_Ref_Detail


template<Reg_T Reg,u2 n> requires (n>0)
struct Pack_Ref
{
	using Ref=Pack_Ref_Detail::Ref<Reg>;

	Ref ref[n];

	static constexpr u2 size=n;
	using Reg_Type=Reg;
	using ele_type=Reg::ele_type;
	static constexpr u2 ele_num=Reg::ele_num;

	template<std::size_t...ids>
	ALWAYS_INLINE Pack_Ref(Pack_Ref_Detail::Merge_Flag,auto regs,std::index_sequence<ids...>):
		ref{regs.template operator()<ids>()...}
	{}

	//合并构造的接口
	template<Reg_Lvalue_Like_T... Reg_Likes> 
		requires (std::is_same_v<Reg,get_reg<std::remove_cvref_t<Reg_Likes>>>&&...) //所有参数对应的寄存器相同，且等于本类的存储类型
	ALWAYS_INLINE Pack_Ref(Reg_Likes&&...reg_likes):
		Pack_Ref(Pack_Ref_Detail::merge_flag,
			[&reg_likes...]<u2 idx>()->decltype(auto)
			{
				return Pack_Ref_Detail::extract_ith_reg<idx,Reg_Likes...>(std::forward<Reg_Likes>(reg_likes)...);
			},
			std::make_index_sequence<n>()
		)
	{}

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_Ref(Reg&reg,std::index_sequence<ids...>)
		:ref{(ids,reg)...}
	{}

	ALWAYS_INLINE Pack_Ref(Reg&reg):Pack_Ref(reg,std::make_index_sequence<n>())
	{}

	// template<std::same_as<Reg>... Args> requires (sizeof...(Args)==n)
	// ALWAYS_INLINE Pack_Ref(Args&...args):ref{args...} {}

	ALWAYS_INLINE Reg& operator[](u2 idx) const {return ref[idx].ref;} 

	template<Reg_T T,std::size_t... ids>
	ALWAYS_INLINE Pack_Ref<T,n> as_impl(std::index_sequence<ids...>) const
	{
		return {ref[ids].ref.template as<T>()...};
	}

	template<Reg_T T>
	ALWAYS_INLINE Pack_Ref<T,n> as() const
	{
		return as_impl<T>(std::make_index_sequence<n>());
	}

	template<Lazy_Eval_Record_T LER>
	ALWAYS_INLINE void operator=(LER ler)
	{
		ler.eval(*this);
	}

	template<Reg_CLvalue_Like_T RHS,std::size_t... ids>
	ALWAYS_INLINE void mov_impl(RHS&& rhs,std::index_sequence<ids...>)
	{
		((ref[ids].ref=rhs[ids]),...);
	}

	template<Reg_CLvalue_Like_T RHS> requires ((Reg_T<std::remove_cvref_t<RHS>>||get_reg_num<std::remove_cvref_t<RHS>> >=n)&&reg_same<Reg,std::remove_cvref_t<RHS>>)
	ALWAYS_INLINE void operator=(RHS&& rhs)
	{
		mov_impl(std::forward<RHS>(rhs),std::make_index_sequence<n>());
	}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void load(const Args*...p) const {ls_opt<&Reg_Type::load>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void loadu(const Args*...p) const {ls_opt<&Reg_Type::loadu>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void stream_load(const Args*...p) const {ls_opt<&Reg_Type::stream_load>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void store(Args*...p) const {ls_opt<&Reg_Type::store>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void storeu(Args*...p) const {ls_opt<&Reg_Type::storeu>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void stream(Args*...p) const {ls_opt<&Reg_Type::stream>(p...);}

	template<std::integral...Args> requires (sizeof...(Args)>=2)
	ALWAYS_INLINE auto operator[](Args... args) const
	{
		return Pack_Ref<Reg,sizeof...(Args)>(ref[args].ref...);
	}
	
private:

	template<auto opt,typename... Ele_Ts,std::size_t... ids>
	SIMD_OPT void ls_impl(std::index_sequence<ids...>,Ele_Ts*...p) const 
	{
		(((ref[ids].ref.*opt)(p)),...);
	}

	template<auto opt,std::size_t... ids>
	SIMD_OPT void ls_helper(auto*p,std::index_sequence<ids...>isq) const 
	{
		ls_impl<opt>(isq,p+ids*ele_num...);
	}

	template<auto opt,typename... Ele_Ts>
	SIMD_OPT void ls_opt(Ele_Ts*...p) const 
	{
		if constexpr(sizeof...(Ele_Ts)==1)ls_helper<opt>(p...,std::make_index_sequence<n>());
		else ls_impl<opt>(std::make_index_sequence<n>(),p...);
	}

	template<std::size_t...ids>
	ALWAYS_INLINE auto mask_impl(std::index_sequence<ids...>) const
	{
		return Pack_Ref<Reg,sizeof...(ids)>(ref[ids].ref...);
	}
};


template<Reg_T Reg,u2 n> requires (n>0)
struct Pack_CRef
{
	using Ref=Pack_Ref_Detail::CRef<Reg>;

	Ref ref[n];

	static constexpr u2 size=n;
	using Reg_Type=Reg;
	using ele_type=Reg::ele_type;
	static constexpr u2 ele_num=Reg::ele_num;

	template<std::size_t...ids>
	ALWAYS_INLINE Pack_CRef(Pack_Ref_Detail::Merge_Flag,auto regs,std::index_sequence<ids...>):
		ref{regs.template operator()<ids>()...}
	{}

	//合并构造的接口 
	template<Reg_CLvalue_Like_T... Reg_Likes> 
		requires (std::is_same_v<Reg,get_reg<std::remove_cvref_t<Reg_Likes>>>&&...) //所有参数对应的寄存器相同，且等于本类的存储类型
	ALWAYS_INLINE Pack_CRef(Reg_Likes&&...reg_likes):
		Pack_CRef(Pack_Ref_Detail::merge_flag,
			[&reg_likes...]<u2 idx>()->decltype(auto)
			{
				return Pack_Ref_Detail::extract_ith_reg<idx,Reg_Likes...>(std::forward<Reg_Likes>(reg_likes)...);
			},
			std::make_index_sequence<n>()
		)
	{}

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_CRef(const Reg&reg,std::index_sequence<ids...>)
		:ref{(ids,reg)...}
	{}

	ALWAYS_INLINE Pack_CRef(const Reg&reg):Pack_CRef(reg,std::make_index_sequence<n>())
	{}

	ALWAYS_INLINE const Reg& operator[](u2 idx) const {return ref[idx].ref;}

	template<Reg_T T,std::size_t... ids>
	ALWAYS_INLINE Pack_CRef<T,n> as_impl(std::index_sequence<ids...>) const
	{
		return {ref[ids].ref.template as<T>()...};
	}

	template<Reg_T T>
	ALWAYS_INLINE Pack_CRef<T,n> as() const
	{
		return as_impl<T>(std::make_index_sequence<n>());
	}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void store(Args*...p) const {ls_opt<&Reg_Type::store>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void storeu(Args*...p) const {ls_opt<&Reg_Type::storeu>(p...);}

	template<std::same_as<ele_type>...Args> requires(sizeof...(Args)==n||sizeof...(Args)==1)
	SIMD_OPT void stream(Args*...p) const {ls_opt<&Reg_Type::stream>(p...);}

	template<std::integral...Args> requires (sizeof...(Args)>=2)
	ALWAYS_INLINE auto operator[](Args... args) const
	{
		return Pack_CRef<Reg,sizeof...(Args)>(ref[args].ref...);
	}

private:
	template<auto opt,typename... Ele_Ts,std::size_t... ids>
	SIMD_OPT void ls_impl(std::index_sequence<ids...>,Ele_Ts*...p)
	{
		(((ref[ids].ref.*opt)(p)),...);
	}

	template<auto opt,std::size_t... ids>
	SIMD_OPT void ls_helper(ele_type*p,std::index_sequence<ids...>isq)
	{
		ls_impl<opt>(isq,p+ids*ele_num...);
	}

	template<auto opt,typename... Ele_Ts>
	SIMD_OPT void ls_opt(Ele_Ts*...p)
	{
		if constexpr(sizeof...(Ele_Ts)==1)ls_helper<opt>(p...,std::make_index_sequence<n>());
		else ls_impl<opt>(std::make_index_sequence<n>(),p...);
	}

	template<std::size_t...ids>
	ALWAYS_INLINE auto mask_impl(std::index_sequence<ids...>) const
	{
		return Pack_CRef<Reg,sizeof...(ids)>(ref[ids].ref...);
	}
};


template<Reg_Lvalue_Like_T... Reg_Likes> requires (sizeof...(Reg_Likes)>0&&Pack_Ref_Detail::all_reg_same<Reg_Likes...>)
Pack_Ref(Reg_Likes&&...)->Pack_Ref<Pack_Ref_Detail::common_reg_type<Reg_Likes...>,Pack_Ref_Detail::all_size_sum<Reg_Likes...>>;

template<Reg_CLvalue_Like_T... Reg_Likes> requires (sizeof...(Reg_Likes)>0&&Pack_Ref_Detail::all_reg_same<Reg_Likes...>)
Pack_CRef(Reg_Likes&&...)->Pack_CRef<Pack_Ref_Detail::common_reg_type<Reg_Likes...>,Pack_Ref_Detail::all_size_sum<Reg_Likes...>>;

