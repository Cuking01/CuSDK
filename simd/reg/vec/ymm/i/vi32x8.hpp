#pragma once

struct VI32x8:YMM_I
{
	using ele_type=s2;
	static constexpr u2 ele_num=8;
	VI32x8(){}
	VI32x8(const s2*p){loadu(p);}
	SIMD_OPT void load  (const s2*p){i=_mm256_load_si256((const __m256i*)p);}
	SIMD_OPT void loadu (const s2*p){i=_mm256_loadu_si256((const __m256i*)p);}
	SIMD_OPT void store (s2*p) const{_mm256_store_si256((__m256i*)p,i);}
	SIMD_OPT void storeu(s2*p) const{_mm256_storeu_si256((__m256i*)p,i);}
	SIMD_OPT void stream(s2*p) const{_mm256_stream_si256((__m256i*)p,i);}
	SIMD_OPT operator __m256i()const{return i;}

	using Reg_Base::operator=;
	using YMM_I::operator=;

	std::string to_string() const
	{
		alignas(64) s2 tmp[8];
		store(tmp);
		std::string s="{int32x8";
		for(u2 i=0;i<8;i++)
			s+=std::format("|[{}]:{}",i,tmp[i]);
		return s+"}";
	}
	void print() const
	{
		std::cout<<to_string()<<'\n';
	}
};
