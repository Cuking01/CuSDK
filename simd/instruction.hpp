#pragma once

template<auto opt,Reg_T Reciver,Lazy_Eval_Arg_T... Args> requires (lazy_eval_count<Args...> <=1)
struct Lazy_Eval_Record
{
	template<typename Arg>
	static constexpr u2 arg_size()
	{
		if constexpr(Reg_T<Arg>||CInt_T<Arg>)return 0;
		else if constexpr(Lazy_Eval_Record_T<Arg>)return Arg::max_size;
		else return Arg::size;
	}

	static constexpr bool has_lazy_eval=lazy_eval_count<Args...>;
	static constexpr u2 max_size=std::max(arg_size<Args>()...);
	using Reciver_Type=Reciver;

	std::tuple<Lazy_Eval_Arg_Convert<Args>...> args;

	ALWAYS_INLINE Lazy_Eval_Record(const Args&... args):args{args...} {}

	template<u2 n,std::size_t idx,typename Arg>
	ALWAYS_INLINE void recurse_eval_helper(Pack_Ref<Reciver,n> pack_r){}

	template<u2 n,std::size_t idx,typename Arg> requires (is_lazy_eval_record_v<Arg>)
	ALWAYS_INLINE void recurse_eval_helper(Pack_Ref<Reciver,n> pack_r)
	{
		std::get<idx>(args).eval(pack_r.template as<typename Arg::Reciver_T>());
	}

	template<u2 n,std::size_t... ids> requires (sizeof...(ids)==sizeof...(Args))
	ALWAYS_INLINE void recurse_eval(Pack_Ref<Reciver,n> pack_r,std::index_sequence<ids...>)
	{
		((recurse_eval_helper<n,ids,decltype(std::get<ids>(args))>(pack_r)),...);
	}

	template<u2 idx,u2 n,Reg_Like_T T>
	ALWAYS_INLINE decltype(auto) extract(const T&arg,const Pack_Ref<Reciver,n>&)
	{
		if constexpr(Reg_T<T>)return (arg);
		else return arg[idx];
	}

	template<u2 idx,u2 n,Imm_T T>
	ALWAYS_INLINE consteval auto extract(const T&arg,const Pack_Ref<Reciver,n>&)
	{
		if constexpr(CInt_T<T>)return T::value;
		else return T::template get<idx>;
	}

	template<u2 idx,u2 n,Lazy_Eval_Record_T T>
	ALWAYS_INLINE const Reciver& extract(const T&arg,const Pack_Ref<Reciver,n>&pack_ref)
	{
		return pack_ref[idx];
	}

	template<u2 n,std::size_t extract_id,std::size_t...ids>
	SIMD_OPT void eval_one(Reciver&reciver,Pack_Ref<Reciver,n> pack_r,std::index_sequence<ids...>)
	{
		reciver=opt(extract<extract_id,n>(std::get<ids>(args),pack_r)...);
	}


	template<u2 n,std::size_t... ids>
	SIMD_OPT void eval_helper(Pack_Ref<Reciver,n> pack_r,std::index_sequence<ids...>)
	{
		((eval_one<n,ids>(pack_r[ids],pack_r,std::make_index_sequence<sizeof...(Args)>())),...);
	}

	template<u2 n> requires (max_size==0||n<=max_size)
	SIMD_OPT void eval(Pack_Ref<Reciver,n> pack_r)
	{
		if constexpr(has_lazy_eval)
			recurse_eval<n>(pack_r,std::make_index_sequence<sizeof...(Args)>());
		eval_helper<n>(pack_r,std::make_index_sequence<n>());
	}
};

template<Reg_T Reg>
struct FMT_Reg
{
	template<typename Arg>
	static constexpr bool check_type()
	{
		if constexpr(std::is_same_v<Reg,Arg>)return true;
		else if constexpr(Reg_Pack_T<Arg>||Pack_Ref_T<Arg>){return std::is_same_v<typename Arg::Reg_Type,Reg>;}
		else if constexpr(Lazy_Eval_Record_T<Arg>){return std::is_same_v<typename Arg::Reciver_Type,Reg>;}
		else return false;
	}

	template<typename Arg> requires (check_type<Arg>())
	static constexpr u2 get_size()
	{
		if constexpr(std::is_same_v<Reg,Arg>)return 0;
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

template<Instruction_FMT_Indicator... Formats>
struct Instruction_FMT
{
	static constexpr u2 arg_n=sizeof...(Formats);

	template<Lazy_Eval_Arg_T...Args> requires (sizeof...(Args)==arg_n)
	static constexpr bool check_type()
	{
		return ((Formats::template check_type<Args>())&&...);
	}

	template<Lazy_Eval_Arg_T...Args> requires (sizeof...(Args)==arg_n)
	static constexpr u2 get_size()
	{
		return std::max(Formats::template get_size<Args>()...);
	}

	template<Lazy_Eval_Arg_T... Args> requires (sizeof...(Args)==arg_n)
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
using make_fmt_helper=std::conditional_t<Reg_T<T>,FMT_Reg<T>,FMT_Imm>;

template<typename... T>
using IFMT=Instruction_FMT<make_fmt_helper<T>...>;
