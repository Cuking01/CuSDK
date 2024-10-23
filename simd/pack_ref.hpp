#pragma once

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

	ALWAYS_INLINE Reg& operator[](u2 idx){return ref[idx].ref;} 

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

	ALWAYS_INLINE const Reg& operator[](u2 idx){return ref[idx].ref;}

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
};
