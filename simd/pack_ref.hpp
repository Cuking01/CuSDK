#pragma once

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

template<Reg_T Reg,u2 n> requires (n>0)
struct Pack_Ref
{
	struct Ref
	{
		Reg& ref;
	};

	Ref ref[n];

	static constexpr u2 size=n;
	using Reg_Type=Reg;
	using ele_type=Reg::ele_type;
	static constexpr u2 ele_num=Reg::ele_num;

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_Ref(Pack<Reg,n>&pack,std::index_sequence<ids...>)
		:ref{pack[ids]...}
	{}

	ALWAYS_INLINE Pack_Ref(Pack<Reg,n>&pack):Pack_Ref(pack,std::make_index_sequence<n>())
	{}

private:
	//多个类似寄存器的东西合并成一个的辅助类，用于标记实现此功能的构造函数们，暂且称为合并构造
	struct Merge_Impl_Flag{};
	static constexpr Merge_Impl_Flag merge_impl_flag{};

	//合并构造的递归终点，寄存器都排列好了，直接展开
	template<typename... Regs,int>
	ALWAYS_INLINE Pack_Ref(Merge_Impl_Flag,Regs&...regs):ref{regs...} {}

	//展开第i个寄存器类似物，此重载是Pack或者Pack_Ref的情况
	template<typename... Regs,int,typename Reg_Like0,typename... Reg_Likes,std::size_t...ids>
		requires (!Reg_T<std::remove_reference_t<Reg_Like0>>)
	ALWAYS_INLINE Pack_Ref(Merge_Impl_Flag,Regs&...regs,Reg_Like0&&reg_like0,Reg_Likes&&...reg_likes,std::index_sequence<ids...>):
		Pack_Ref<Regs...,decltype((ids,std::declval<Reg>()))...,0,Reg_Likes...>
		(
			merge_impl_flag,
			regs...,
			reg_like0[ids]...,
			std::forward<Reg_Likes>(reg_likes)...
		)
	{}

	//展开第i个寄存器类似物，此重载是Reg的情况
	template<typename... Regs,int,typename Reg_Like0,typename... Reg_Likes,std::size_t...ids>
		requires (Reg_T<std::remove_reference_t<Reg_Like0>>)
	ALWAYS_INLINE Pack_Ref(Merge_Impl_Flag,Regs&...regs,Reg_Like0&&reg_like0,Reg_Likes&&...reg_likes,std::index_sequence<ids...>):
		Pack_Ref<Regs...,Reg,0,Reg_Likes...>(merge_impl_flag,regs...,reg_like0,std::forward<Reg_Likes>(reg_likes)...)
	{}

	//递归展开所有寄存器类似物
	template<typename... Regs,int,typename Reg_Like0,typename... Reg_Likes>
	ALWAYS_INLINE Pack_Ref(Merge_Impl_Flag,Regs&...regs,Reg_Like0&&reg_like0,Reg_Likes&&...reg_likes):
		Pack_Ref<Regs...,0,Reg_Like0,Reg_Likes...>
		(
			merge_impl_flag,
			regs...,
			std::forward<Reg_Like0>(reg_like0),
			std::forward<Reg_Likes>(reg_likes)...,
			std::make_index_sequence<get_reg_num<Reg_Like0>>()
		)
	{}
public:
	//合并构造的接口
	template<Reg_Lvalue_Like_T... Reg_Likes> 
		requires (std::is_same_v<Reg,get_reg<std::remove_cvref_t<Reg_Likes>>>&&...) //所有参数对应的寄存器相同，且等于本类的存储类型
	ALWAYS_INLINE Pack_Ref(Reg_Likes&&...reg_likes):
		Pack_Ref<0,Reg_Likes...>(merge_impl_flag,std::forward<Reg_Likes>(reg_likes)...)
	{}

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_Ref(Reg&reg,std::index_sequence<ids...>)
		:ref{(ids,reg)...}
	{}

	ALWAYS_INLINE Pack_Ref(Reg&reg):Pack_Ref(reg,std::make_index_sequence<n>())
	{}

	template<std::same_as<Reg>... Args> requires (sizeof...(Args)==n)
	ALWAYS_INLINE Pack_Ref(Args&...args):ref{args...} {}

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
	void operator=(LER ler)
	{
		ler.eval(*this);
	}

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

	template<std::integral...Args> requires (sizeof...(Args)>=2)
	ALWAYS_INLINE auto operator[](Args... args) const
	{
		return Pack_Ref<Reg,sizeof...(Args)>(ref[args].ref...);
	}

	template<u2 msk>
	ALWAYS_INLINE auto mask() const
	{
		return mask_impl(make_mask_index_sequence<msk,n>());
	}
	
private:

	template<auto opt,typename... Ele_Ts,std::size_t... ids>
	SIMD_OPT void ls_impl(std::index_sequence<ids...>,Ele_Ts*...p)
	{
		(((ref[ids].ref.*opt)(p)),...);
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

	template<std::size_t...ids>
	ALWAYS_INLINE auto mask_impl(std::index_sequence<ids...>) const
	{
		return Pack_Ref<Reg,sizeof...(ids)>(ref[ids].ref...);
	}
};


template<Reg_T Reg,u2 n> requires (n>0)
struct Pack_CRef
{
	struct Ref
	{
		const Reg& ref;
	};

	Ref ref[n];

	static constexpr u2 size=n;
	using Reg_Type=Reg;
	using ele_type=Reg::ele_type;
	static constexpr u2 ele_num=Reg::ele_num;

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_CRef(const Pack_Ref<Reg,n>&pref,std::index_sequence<ids...>)
		:ref{pref[ids]...}
	{}

	ALWAYS_INLINE Pack_CRef(Pack_Ref<Reg,n> pref):Pack_CRef(pref,std::make_index_sequence<n>()){}

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_CRef(const Pack<Reg,n>&pack,std::index_sequence<ids...>)
		:ref{pack[ids]...}
	{}

	ALWAYS_INLINE Pack_CRef(const Pack<Reg,n>&pack):Pack_CRef(pack,std::make_index_sequence<n>())
	{}

	template<std::size_t... ids>
	ALWAYS_INLINE Pack_CRef(const Reg&reg,std::index_sequence<ids...>)
		:ref{(ids,reg)...}
	{}

	ALWAYS_INLINE Pack_CRef(const Reg&reg):Pack_CRef(reg,std::make_index_sequence<n>())
	{}

	template<std::same_as<Reg>... Args> requires (sizeof...(Args)==n)
	ALWAYS_INLINE Pack_CRef(const Args&...args):ref{args...} {}

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

	template<u2 msk>
	ALWAYS_INLINE auto mask() const
	{
		return mask_impl(make_mask_index_sequence<msk,n>());
	}

private:
	template<auto opt,typename... Ele_Ts,std::size_t... ids>
	SIMD_OPT void ls_impl(std::index_sequence<ids...>,Ele_Ts*...p)
	{
		(((ref[ids].ref.*opt)(p)),...);
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

	template<std::size_t...ids>
	ALWAYS_INLINE auto mask_impl(std::index_sequence<ids...>) const
	{
		return Pack_CRef<Reg,sizeof...(ids)>(ref[ids].ref...);
	}
};
