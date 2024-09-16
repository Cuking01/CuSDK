#pragma once

struct FP
{
	FP(const FP&)=delete;
	FP(FP&&fp2) noexcept:fp(fp2.fp){fp2.fp=nullptr;}
	FP(FILE*fp):fp(fp){if(!fp)throw std::runtime_error("fp is nullptr.");}
	FP(std::string_view file_name,const char*mode)
	{
		fp=fopen(file_name.data(),mode);
		if(!fp)throw std::runtime_error(std::format("file {} not found.",file_name));
	};
	FP& operator=(const FP&file)=delete;
	FP& operator=(FP&&file) noexcept
	{
		free(fp);
		fp=file.fp;
		file.fp=nullptr;
		return *this;
	}

	operator FILE*() noexcept {return fp;}

	~FP() noexcept {fclose(fp);}

private:
	FILE*fp;
};
