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
concept Scale_Like_T=Scale_T<T>||Scale_Pack_T<T>;

template<typename T>
concept Addr_Like_T=Addr_T<T>||Addr_Pack_T<T>;

template<typename T>
concept Instruction_Arg_T=Reg_Like_T<T>||Imm_T<T>||Scale_Like_T<T>||Addr_Like_T<T>;

template<typename T>
concept Reciver_T=Reg_T<T>||Scale_T<T>||std::is_same_v<T,void>;

// template<Reciver_T T>
// struct Reciver_Pack_Helper;

// template<Reg_T T>
// struct Reciver_Pack_Helper<T>
// {
// 	using type=Pack_Ref<T>;
// };

// template<Scale_T T>
// struct Reciver_Pack_Helper<T>
// {
// 	using type=Scale_Pack_Ref<T>;
// };

template<auto opt,Reciver_T Reciver,Instruction_Arg_T... Args>
struct Lazy_Eval_Record;

template<Instruction_Arg_T T>
struct Lazy_Eval_Arg_Convert_Impl
{
	using type=T;
};

template<Reg_Pack_T T>
struct Lazy_Eval_Arg_Convert_Impl<T>
{
	using type=Pack_CRef<typename T::Reg_Type,T::size>;
};

// template<Scale_Pack_T T>
// struct Lazy_Eval_Arg_Convert_Impl<T>
// {
// 	using type=Scale_Pack_Ref<typename T::Scale_Type,T::size>;
// };

template<Reg_T T>
struct Lazy_Eval_Arg_Convert_Impl<T>
{
	using type=const T&;
};

template<Instruction_Arg_T T>
using Lazy_Eval_Arg_Convert=Lazy_Eval_Arg_Convert_Impl<T>::type;

template<auto opt,Instruction_Arg_T... Args>
constexpr bool is_lazy_eval_record_v<Lazy_Eval_Record<opt,Args...>> =true;

//五种格式，向量寄存器，掩码寄存器，立即数，标量，地址，其中前两者都用FMT_Reg
template<typename Reg> requires (Reg_T<Reg>||Vec_Reg_Format_T<Reg>)
struct FMT_Reg;
struct FMT_Imm;
template<Scale_T Scale>
struct FMT_Scale;
template<Addr_T Addr>
struct FMT_Addr;

template<typename T>
concept Instruction_FMT_Indicator=std::same_as<T,FMT_Imm>||Instance_Of<FMT_Reg,T>||Instance_Of<FMT_Scale,T>||Instance_Of<FMT_Addr,T>;

template<Reg_Like_T T>
struct Reg_Trait;

template<Reg_Like_T T>
using get_reg=typename Reg_Trait<T>::type;

template<Reg_Like_T T>
static constexpr u2 get_reg_num=Reg_Trait<T>::size;

template<typename A,typename B>
concept reg_same=std::same_as<get_reg<A>,get_reg<B>>;

