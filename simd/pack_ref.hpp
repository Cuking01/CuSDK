#pragma once

template<Reg_T Reg,u2 n>
struct Pack_Ref
{
	struct Ref
	{
		Reg& ref;
	};

	Ref ref[n];

	template<std::size_t... ids>
	Pack_Ref(Pack<Reg,n>&pack,std::index_sequence<ids...>)
		:ref{pack[ids]...}
	{}

	Pack_Ref(Pack<Reg,n>&pack):Pack_Ref(pack,std::make_index_sequence<n>())
	{}

	ALWAYS_INLINE Reg& operator[](u2 idx){return ref[idx].ref;} 
};


template<Reg_T Reg,u2 n>
struct Pack_CRef
{
	struct Ref
	{
		const Reg& ref;
	};

	Ref ref[n];

	template<std::size_t... ids>
	Pack_CRef(const Pack<Reg,n>&pack,std::index_sequence<ids...>)
		:ref{pack[ids]...}
	{}

	Pack_CRef(const Pack<Reg,n>&pack):Pack_CRef(pack,std::make_index_sequence<n>())
	{}

	ALWAYS_INLINE Reg& operator[](u2 idx){return ref[idx].ref;} 
};
