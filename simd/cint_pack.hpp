#pragma once

template<std::integral auto... cints>
struct CInt_Pack
{
	static constexpr u2 size=sizeof...(cints);

	template<u2 idx,std::size_t... ids>
	static consteval auto get_impl(std::index_sequence<ids...>) requires (sizeof...(ids)==size&&idx<size)
	{
		return ((idx==ids?cints:0)|...|0);
	}

	template<u2 idx>
	static constexpr auto get=get_impl<idx>(std::make_index_sequence<size>());

};


