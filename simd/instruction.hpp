#pragma once




template<auto opt,Lazy_Eval_Arg_T... Args> requires (lazy_eval_count<Args...> <=1)
struct Lazy_Eval_Record 
{
	static constexpr bool has_lazy_eval=lazy_eval_count<Args...>;

	std::tuple<Lazy_Eval_Arg_Convert<Args>...> args;

	ALWAYS_INLINE Lazy_Eval_Record(const Args&... args):args{args...} {}
};



