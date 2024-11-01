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
