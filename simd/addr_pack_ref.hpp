#pragma once

template<Addr_T T,u2 n>
struct Addr_Pack_Ref
{
	struct Ref
	{
		T&ref;
	};

	Ref ref[n];

	using Addr_Type=T;
	static constexpr u2 size=n;

	template<std::same_as<T>... Args> requires (sizeof...(Args)==n)
	ALWAYS_INLINE Addr_Pack_Ref(Args&...args):ref{args...} {}

	template<std::size_t... ids>
	ALWAYS_INLINE Addr_Pack_Ref(T&arg,std::index_sequence<ids...>):ref{(ids,arg)...} {}

	ALWAYS_INLINE Addr_Pack_Ref(T&arg):Addr_Pack_Ref(arg,std::make_index_sequence<n>()) {}

	template<std::size_t...ids>
	ALWAYS_INLINE Addr_Pack_Ref(Addr_Pack<T,n>&pack,std::index_sequence<ids...>):ref{pack[ids]...}{}

	ALWAYS_INLINE Addr_Pack_Ref(Addr_Pack<T,n>&pack):Addr_Pack_Ref(pack,std::make_index_sequence<n>()) {}

	ALWAYS_INLINE Addr_Pack_Ref(const Addr_Pack_Ref&)=default;

	ALWAYS_INLINE decltype(auto) operator[](this auto&self,u2 idx)
	{
		return self.ref[idx].ref;
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT void operator=(LER ler)
	{
		ler.eval(*this);
	}
};
