#pragma once

template<std::signed_integral To,std::signed_integral From>
To cast_s(From v)
{
	if(sizeof(From)<=sizeof(To))
		return v;
	constexpr From min=std::numeric_limits<To>::min();
	constexpr From max=std::numeric_limits<To>::max();

	cu_assert(is(v).in(min,max),"cast val over/underflow");

	return v;
}

template<std::unsigned_integral To,std::unsigned_integral From>
To cast_s(From v)
{
	if(sizeof(From)<=sizeof(To))
		return v;
	constexpr From max=std::numeric_limits<To>::max();

	cu_assert(v<=max,"cast val overflow");

	return v;
}

template<std::unsigned_integral To,std::signed_integral From>
To cast_s(From v)
{
	cu_assert(v>=0,"cast underflow");

	if(sizeof(From)<=sizeof(To))
		return v;
	constexpr From min=std::numeric_limits<To>::min();
	constexpr From max=std::numeric_limits<To>::max();

	cu_assert(is(v).in(min,max),"cast val over/underflow");

	return v;
}

template<std::signed_integral To,std::unsigned_integral From>
To cast_s(From v)
{
	if(sizeof(From)<sizeof(To))
		return v;

	constexpr From max=std::numeric_limits<To>::max();

	cu_assert(v<=max,"cast val overflow");

	return v;
}

template<std::integral From>
struct cast_s_auto
{
	From v;
	cast_s_auto(From v) noexcept:v(v){}

	template<std::integral To>
	operator To() const
	{
		return cast_s<To>(v);
	}
};
