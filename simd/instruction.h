#pragma once

template<typename T>
constexpr bool is_lazy_eval_record_v=false;

template<typename T>
concept Lazy_Eval_Record_T=is_lazy_eval_record_v<T>;

template<typename T>
concept Reg_Like_T=Reg_T<T>||Reg_Pack_T<T>||Pack_Ref_T<T>;

template<typename T>
concept CInt_Like_T=std::integral<T>||CInt_Pack_T<T>;

template<typename T>
concept Lazy_Eval_Arg_T=Reg_Like_T<T>||CInt_Like_T<T>||Lazy_Eval_Record_T<T>;

template<typename... T>
constexpr u2 lazy_eval_count=(Lazy_Eval_Record_T<T>+...+0u);

template<auto opt,Lazy_Eval_Arg_T... Args> requires (lazy_eval_count<Args...> <=1)
struct Lazy_Eval_Record;

template<Lazy_Eval_Arg_T T>
struct Lazy_Eval_Arg_Convert_Impl
{
	using type=T;
};

template<Reg_Pack_T T>
struct Lazy_Eval_Arg_Convert_Impl<T>
{
	using type=Pack_CRef<typename T::Reg_Type,T::size>;
};

template<Reg_T T>
struct Lazy_Eval_Arg_Convert_Impl<T>
{
	using type=const T&;
};

template<Lazy_Eval_Arg_T T>
using Lazy_Eval_Arg_Convert=Lazy_Eval_Arg_Convert_Impl<T>::type;

template<auto opt,Lazy_Eval_Arg_T... Args>
constexpr bool is_lazy_eval_record_v<Lazy_Eval_Record<opt,Args...>> =true;

