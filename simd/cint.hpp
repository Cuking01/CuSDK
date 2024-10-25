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

	template<u2 idx,std::size_t... ids> requires (sizeof...(ids)==size&&idx<size)
	static constexpr auto get_impl(std::index_sequence<ids...>)
	{
		return ((idx==ids?cints:0)|...|0);
	}

	template<u2 idx>
	static constexpr auto get=get_impl<idx>(std::make_index_sequence<size>());

	constexpr auto operator[](u2 idx)
	{
		return get_impl(idx,std::make_index_sequence<size>());
	}

};


