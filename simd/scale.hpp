#pragma once

template<Scale_T T,u2 n>
struct Scale_Pack
{
	T ele[n];
	using Scale_Type=T;
	static constexpr u2 size=n;
	template<std::same_as<T>...Args> requires (sizeof...(Args)==n)
	ALWAYS_INLINE Scale_Pack(Args... args):ele{args...} {}

	template<std::size_t... ids>
	ALWAYS_INLINE Scale_Pack(T x,std::index_sequence<ids...>):ele{(ids,x)...} {}

	ALWAYS_INLINE Scale_Pack(T x):Scale_Pack(x,std::make_index_sequence<n>()) {}

	ALWAYS_INLINE decltype(auto) operator[](this auto&self,u2 idx)
	{
		return self.ele[idx];
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT Scale_Pack(LER ler)
	{
		ler.eval(Scale_Pack_Ref<T,n>(*this));
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT void operator=(LER ler)
	{
		ler.eval(Scale_Pack_Ref<T,n>(*this));
	}
};

template<Scale_T Arg0,Scale_T... Args> requires (std::is_same_v<Arg0,Args>&&...)
Scale_Pack(Arg0,Args...)->Scale_Pack<Arg0,sizeof...(Args)+1>;

