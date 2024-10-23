#pragma once

template<std::integral auto cint>
struct CInt
{
	static constexpr auto value=cint;
};

template<std::integral auto... cints>
struct CInt_Pack
{
	static constexpr u2 size=sizeof...(cints);

	template<std::size_t... ids>
	static constexpr auto get_impl(u2 idx,std::index_sequence<ids...>) requires (sizeof...(ids)==size&&idx<size)
	{
		return ((idx==ids?cints:0)|...|0);
	}

	template<u2 idx>
	static constexpr auto get=get_impl(idx,std::make_index_sequence<size>());

	constexpr auto operator[](u2 idx)
	{
		return get_impl(idx,std::make_index_sequence<size>());
	}

};


