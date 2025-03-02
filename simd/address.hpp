#pragma once

template<Addr_T T,u2 n>
struct Addr_Pack
{
	T ele[n];
	using Addr_Type=T;
	static constexpr u2 size=n;
	template<std::same_as<T>...Args> requires (sizeof...(Args)==n)
	ALWAYS_INLINE Addr_Pack(Args... args):ele{args...} {}

	template<std::size_t... ids>
	ALWAYS_INLINE Addr_Pack(T arg,u3 step,std::index_sequence<ids...>):Addr_Pack((T)((u0*)arg+ids*step)...) {}

	//等步长构造
	ALWAYS_INLINE Addr_Pack(T arg,u3 step):Addr_Pack(arg,step,std::make_index_sequence<n>()){}

	template<std::size_t... ids>
	ALWAYS_INLINE Addr_Pack(T x,std::index_sequence<ids...>):ele{(ids,x)...} {}

	ALWAYS_INLINE Addr_Pack(T x):Addr_Pack(x,std::make_index_sequence<n>()) {}

	ALWAYS_INLINE decltype(auto) operator[](this auto&self,u2 idx)
	{
		return self.ele[idx];
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT Addr_Pack(LER ler)
	{
		ler.eval(Addr_Pack_Ref<T,n>(*this));
	}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT void operator=(LER ler)
	{
		ler.eval(Addr_Pack_Ref<T,n>(*this));
	}
};

template<Addr_T Arg0,Addr_T... Args> requires (std::is_same_v<Arg0,Args>&&...)
Addr_Pack(Arg0,Args...)->Addr_Pack<Arg0,sizeof...(Args)+1>;



