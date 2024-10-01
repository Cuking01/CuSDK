#pragma once

struct File
{
	File(const File&)=delete;
	File(File&&file2) noexcept:fp(file2.fp),file_name(file2.file_name){file2.fp=nullptr;}
	File(FILE*fp):fp(fp),file_name("unknown_file_name"){cu_assert(fp,"fp is nullptr.");}
	File(std::string_view file_name,const char*mode):file_name(file_name)
	{
		fp=fopen(file_name.data(),mode);
		cu_assert(fp,"file {} not found.",file_name);
	};
	File& operator=(const File&file)=delete;
	File& operator=(File&&file) noexcept
	{
		if(this==&file)return *this;

		free(fp);
		fp=file.fp;
		file_name=(std::string&&)file.file_name;
		file.fp=nullptr;
		return *this;
	}

	operator FILE*() noexcept {return fp;}
	std::string_view name() const noexcept{return file_name;}

	~File() noexcept {fclose(fp);}

private:
	FILE*fp;
	std::string file_name;
};
