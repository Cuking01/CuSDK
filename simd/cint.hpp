#pragma once

template<std::integral auto cint> requires (cint>=0&&cint<256)
struct CInt
{
	static constexpr auto value=cint;
};

template<std::integral auto... cints> requires ((cints>=0&&cints<256)&&...)
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

template<std::integral auto cint_v>
constexpr CInt<cint_v> cint;

template<std::integral auto... cints_v>
constexpr CInt_Pack<cints_v...> cints;
