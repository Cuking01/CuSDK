#pragma once

template<typename T>
constexpr bool is_lazy_eval_record_v=false;

template<typename T>
concept Lazy_Eval_Record_T=is_lazy_eval_record_v<T>;

template<typename T>
concept Reg_Like_T=Reg_T<T>||Reg_Pack_T<T>||Pack_CRef_T<T>;

template<typename T>
concept Imm_T=CInt_T<T>||CInt_Pack_T<T>;

template<typename T>
concept Lazy_Eval_Arg_T=Reg_Like_T<T>||Imm_T<T>||Lazy_Eval_Record_T<T>;

template<typename... T>
constexpr u2 lazy_eval_count=(Lazy_Eval_Record_T<T>+...+0u);

template<auto opt,Reg_T Reciver,Lazy_Eval_Arg_T... Args> requires (lazy_eval_count<Args...> <=1)
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

//三种格式，向量寄存器，掩码寄存器，立即数
template<Reg_T Reg>
struct FMT_Reg;
struct FMT_Imm;

template<typename T>
concept Instruction_FMT_Indicator=Instance_Of<FMT_Reg,T>||std::same_as<T,FMT_Imm>;

