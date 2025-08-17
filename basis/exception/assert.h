#pragma once


struct Assert_Failed: std::runtime_error
{
	Assert_Failed(
		const char*cond,
		std::string_view desc,
		const char* file_name,
		int line,
		const char* func_name,
		const char* compile_date,
		const char* compile_time
		)
		:std::runtime_error(std::format(
			"cu_assert failed!\n"
			"condition: [{}] is false.\n"
			"error desciption: {}.\n"
			"in file: [{}] line: [{}]\n"
			"in function: [{}]\n"
			"app version: [{}]\n"
			"cusdk version: [{}]\n"
			"compile time: [{} {}]\n",
			cond,desc,file_name,line,func_name,APP_VERSION_ID,CUSDK_VERSION_ID,compile_date,compile_time
		))
	{}

};

#define cu_assert_get_desc_help(format_or_string,...) PP_IF(PP_IS_EMPTY(__VA_ARGS__),format_or_string,std::format(format_or_string,__VA_ARGS__))
#define cu_assert_get_desc(...) PP_IF(PP_IS_EMPTY(__VA_ARGS__),"null",cu_assert_get_desc_help(__VA_ARGS__))
#define cu_assert(cond,...) do{if(!(cond)){throw Assert_Failed(#cond,cu_assert_get_desc(__VA_ARGS__),__FILE__,__LINE__,__func__,__DATE__,__TIME__);}}while(0)

#define cu_error(cond,...) cu_assert(false,__VA_ARGS__)
