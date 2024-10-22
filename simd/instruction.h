#pragma once


template<typename T>
concept Reg_Like_T=Reg_T<T>||Reg_Pack_T<T>||Pack_Ref_T<T>;

template<typename T>
concept CInt_Like_T=std::integral<T>||CInt_Pack_T<T>;

template<typename T>
concept Lazy_Eval_Arg_T=Reg_Like_T<T>||CInt_Like_T<T>;

template<auto opt,Lazy_Eval_Arg_T... Args>
struct Lazy_Eval_Record;

template<Lazy_Eval_Arg_T T>
struct Lazy_Eval_Arg_Convert_Impl
{
	using type=T;
};

template<Reg_Pack_T T>
struct Lazy_Eval_Arg_Convert_Impl<T>
{
	using type=T::Reg_Type;
};

template<Reg_T T>
struct Lazy_Eval_Arg_Convert_Impl<T>
{
	using type=T&;
};

template<Lazy_Eval_Arg_T T>
using Lazy_Eval_Arg_Convert=Lazy_Eval_Arg_Convert_Impl<T>::type;

