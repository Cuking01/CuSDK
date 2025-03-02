#pragma once

template<u2 n>
struct Pack_Void
{
	int x;
	ALWAYS_INLINE int& operator[](u2 idx){return x;}
};

template<auto opt,Reciver_T Reciver,Instruction_Arg_T... Args>
struct Lazy_Eval_Record
{
	template<typename Arg>
	static constexpr u2 arg_size()
	{
		if constexpr(Reg_T<Arg>||CInt_T<Arg>||Scale_T<Arg>||Addr_T<Arg>)return 0;
		else if constexpr(Lazy_Eval_Record_T<Arg>)return Arg::max_size;
		else return Arg::size;
	}

	static constexpr u2 max_size=std::max({arg_size<Args>()...});
	using Reciver_Type=Reciver;
	

	std::tuple<Lazy_Eval_Arg_Convert<Args>...> args;

	ALWAYS_INLINE Lazy_Eval_Record(const Args&... args):args{args...}
	{
		if constexpr(std::is_same_v<Reciver_Type,void>)
		{
			Pack_Void<max_size==0?1:max_size> pack_void;
			this->eval(pack_void);
		}
	}

	template<u2 n,typename Reciver_Derived> requires ((max_size==0||n<=max_size)&&(std::derived_from<Reciver_Derived,Reciver>))
	SIMD_OPT void eval(Pack_Ref<Reciver_Derived,n> pack_r) const
	{
		eval_helper(pack_r,std::make_index_sequence<n>());
	}

	template<u2 n,typename Reciver_Scale> requires ((max_size==0||n<=max_size)&&(std::is_same_v<Reciver_Scale,Reciver>))
	SIMD_OPT void eval(Scale_Pack_Ref<Reciver_Scale,n> pack_r) const
	{
		eval_helper(pack_r,std::make_index_sequence<n>());
	}

	template<u2 n,typename Reciver_Addr> requires ((max_size==0||n<=max_size)&&(std::is_same_v<Reciver_Addr,Reciver>))
	SIMD_OPT void eval(Addr_Pack_Ref<Reciver_Addr,n> pack_r) const
	{
		eval_helper(pack_r,std::make_index_sequence<n>());
	}

	template<u2 n> requires (max_size==0||n<=max_size)
	SIMD_OPT void eval(Pack_Void<n> pack_r) const
	{
		eval_helper(pack_r,std::make_index_sequence<n>());
	}

	template<Scale_T Scale>
	SIMD_OPT operator Scale() const
	{
		Scale scale;
		eval(Scale_Pack_Ref<Scale,1>(scale));
		return scale;
	}

private:
	template<u2 idx,Reg_Like_T T>
	ALWAYS_INLINE decltype(auto) extract(const T&arg,const auto&) const
	{
		if constexpr(Reg_T<T>)return (arg);
		else return arg[idx];
	}

	template<u2 idx,Imm_T T>
	ALWAYS_INLINE consteval auto extract(const T&arg,const auto&) const
	{
		if constexpr(CInt_T<T>)return T::value;
		else return T::template get<idx>;
	}

	template<u2 idx,Scale_Like_T T>
	ALWAYS_INLINE auto extract(const T&arg,const auto&pack_ref) const
	{
		if constexpr(Scale_Pack_T<T>)return arg[idx];
		else return arg;
	}

	template<u2 idx,Addr_Like_T T>
	ALWAYS_INLINE auto extract(const T&arg,const auto&pack_ref) const
	{
		if constexpr(Addr_Pack_T<T>)return arg[idx];
		else return arg;
	}

	template<std::size_t extract_id,std::size_t...ids>
	SIMD_OPT void eval_one(auto&reciver,auto&pack_r,std::index_sequence<ids...>) const
	{
		if constexpr(std::is_same_v<Reciver_Type,void>)
			opt(extract<extract_id>(std::get<ids>(args),pack_r)...);
		else
			reciver=opt(extract<extract_id>(std::get<ids>(args),pack_r)...);
	}


	template<std::size_t... ids>
	SIMD_OPT void eval_helper(auto&pack_r,std::index_sequence<ids...>) const
	{
		((eval_one<ids>(pack_r[ids],pack_r,std::make_index_sequence<sizeof...(Args)>())),...);
	}


};

template<typename Reg> requires (Reg_T<Reg>||Vec_Reg_Format_T<Reg>)
struct FMT_Reg
{
	template<typename Arg>
	static constexpr bool check_type()
	{
		if constexpr(std::derived_from<Arg,Reg>)return true;
		else if constexpr(Reg_Pack_T<Arg>||Pack_CRef_T<Arg>){return std::derived_from<typename Arg::Reg_Type,Reg>;}
		else if constexpr(Lazy_Eval_Record_T<Arg>){return std::derived_from<typename Arg::Reciver_Type,Reg>;}
		else return false;
	}

	template<typename Arg> requires (check_type<Arg>())
	static constexpr u2 get_size()
	{
		if constexpr(std::derived_from<Arg,Reg>)return 0;
		else if constexpr(Lazy_Eval_Record_T<Arg>)return Arg::max_size;
		else return Arg::size;
	}
};

struct FMT_Imm
{
	template<typename Arg>
	static constexpr bool check_type()
	{
		return CInt_T<Arg>||CInt_Pack_T<Arg>;
	}

	template<typename Arg> requires (check_type<Arg>())
	static constexpr u2 get_size()
	{
		if constexpr(CInt_T<Arg>)return 0;
		else return Arg::size;
	}
};

template<Scale_T Scale>
struct FMT_Scale
{
	template<typename Arg>
	static constexpr bool check_type()
	{
		if constexpr(Scale_Pack_T<Arg>||Scale_Pack_Ref_T<Arg>)return std::is_same_v<typename Arg::Scale_Type,Scale>;
		else return std::is_same_v<Arg,Scale>;
	}

	template<typename Arg> requires(check_type<Arg>())
	static constexpr u2 get_size()
	{
		if constexpr(Scale_Pack_T<Arg>||Scale_Pack_Ref_T<Arg>)return Arg::size;
		else return 0;
	}

};

template<Addr_T Addr>
struct FMT_Addr
{
	template<typename Arg>
	static constexpr bool check_type()
	{
		if constexpr(Addr_Pack_T<Arg>||Addr_Pack_Ref_T<Arg>)return std::is_convertible_v<typename Arg::Addr_Type,Addr>;
		else return std::is_convertible_v<Arg,Addr>;
	}

	template<typename Arg> requires(check_type<Arg>())
	static constexpr u2 get_size()
	{
		if constexpr(Addr_Pack_T<Arg>||Addr_Pack_Ref_T<Arg>)return Arg::size;
		else return 0;
	}
};

template<Instruction_FMT_Indicator... Formats>
struct Instruction_FMT
{
	static constexpr u2 arg_n=sizeof...(Formats);

	template<Instruction_Arg_T...Args> requires (sizeof...(Args)==arg_n)
	static constexpr bool check_type()
	{
		return ((Formats::template check_type<Args>())&&...);
	}

	template<Instruction_Arg_T...Args> requires (sizeof...(Args)==arg_n)
	static constexpr u2 get_size()
	{
		return std::max({Formats::template get_size<Args>()...});
	}

	template<Instruction_Arg_T... Args> requires (sizeof...(Args)==arg_n)
	static constexpr bool check()
	{
		if constexpr(check_type<Args...>())
		{
			constexpr auto size=get_size<Args...>();
			return ((is(Formats::template get_size<Args>()).one_of(0,size))&&...);
		}
		else return false;
	}
};



template<typename T>
struct Make_Fmt_Helper{using type=FMT_Imm;};

template<Reg_T T>
struct Make_Fmt_Helper<T>{using type=FMT_Reg<T>;};

template<Vec_Reg_Format_T T> requires(!Reg_T<T>)
struct Make_Fmt_Helper<T>{using type=FMT_Reg<T>;};

template<Scale_T T>
struct Make_Fmt_Helper<T>{using type=FMT_Scale<T>;};

template<Addr_T T>
struct Make_Fmt_Helper<T>{using type=FMT_Addr<T>;};

// 因为conditional_t不能惰性实例化FMT_Reg<T>，导致传入非寄存器类型时出错，改用上面的类+特化实现
// template<typename T>
// using make_fmt_helper=std::conditional_t<Reg_T<T>,FMT_Reg<T>,FMT_Imm>;

template<typename... T>
using IFMT=Instruction_FMT<typename Make_Fmt_Helper<T>::type...>;

template<Reg_Like_T T>
struct Reg_Trait
{
	using type=T;
	static constexpr u2 size=1;
};

template<typename T> requires (Reg_Pack_T<T>||Pack_Ref_T<T>)
struct Reg_Trait<T>
{
	using type=typename T::Reg_Type;
	static constexpr u2 size=T::size;
};

