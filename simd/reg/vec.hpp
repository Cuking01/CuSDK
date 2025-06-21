#pragma once

struct Vec_Reg_Base:Reg_Base
{
	
};

struct Vec_Reg_Format_Base{};

template<typename Ele_T,u2 Ele_N,typename MM_Base,typename FMT_Base> requires(sizeof(Ele_T)*Ele_N==sizeof(MM_Base))
struct Vec_Reg:MM_Base,FMT_Base
{
	using ele_type=Ele_T;
	static constexpr u2 ele_num=Ele_N;
	static constexpr u2 size=sizeof(ele_type)*ele_num;

	SIMD_OPT Vec_Reg(){}
	SIMD_OPT Vec_Reg(const ele_type*p){loadu(p);}

	template<Lazy_Eval_Record_T LER>
	SIMD_OPT Vec_Reg(LER ler){ler.eval(Pack_Ref<Vec_Reg,1>(*this));}

	using MM_Base::MM_Base;

	SIMD_OPT void load  (const ele_type*p){MM_Base::load(p);}
	SIMD_OPT void loadu (const ele_type*p){MM_Base::loadu(p);}
	SIMD_OPT void stream_load(const ele_type*p){MM_Base::stream_load(p);}
	SIMD_OPT void store (ele_type*p) const{MM_Base::store(p);}
	SIMD_OPT void storeu(ele_type*p) const{MM_Base::storeu(p);}
	SIMD_OPT void stream(ele_type*p) const{MM_Base::stream(p);}

	using Reg_Base::operator=;
	using MM_Base::operator=;

	std::string to_string() const
	{
		alignas(64) ele_type tmp[ele_num];
		store(tmp);
		std::string s="{";
		for(u2 i=0;i<ele_num;i++)
			s+=std::format("[{}:{}]",i,tmp[i]);
		return s+"}";
	}
	void print(const std::string&desc="") const
	{
		std::cout<<desc<<'\n'<<to_string()<<'\n';
	}
};

#include "vec/mm.hpp"
#include "vec/xmm.hpp"

#include "vec/ymm.hpp"

#include "vec/zmm.hpp"
