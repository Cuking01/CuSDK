#pragma once


struct Assert_Failed: std::runtime_error
{
	Assert_Failed(
		const char*cond,
		std::string_view desc,
		const char* file_name,
		int line,
		const char* compile_date,
		const char* compile_time
		)
		:std::runtime_error(std::format(
			"cu_assert failed!\n"
			"condition: [{}] is false.\n"
			"error desciption: {}.\n"
			"in file: [{}] line: [{}]\n"
			"version: [{}]\n"
			"compile time: [{} {}]\n",
			cond,desc,file_name,line,VERSION,compile_date,compile_time
		))
	{}

};

#define cu_assert_get_desc(...) PP_IF(PP_IS_EMPTY(__VA_ARGS__),"null",__VA_ARGS__)
#define cu_assert(cond,...) if(!(cond)){throw Assert_Failed(#cond,cu_assert_get_desc(__VA_ARGS__),__FILE__,__LINE__,__DATE__,__TIME__);}
