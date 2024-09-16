#include<stdio.h>
#define PP_CONCAT_IMPL(A, B) A##B
#define PP_COMMA_IMPL() ,
#define PP_LPAREN_IMPL() (
#define PP_RPAREN_IMPL() )
#define PP_EMPTY_IMPL()
#define PP_SECOND_IMPL(a,b,...) b
#define PP_REMOVE_PARENS_IMPL_IMPL(...) __VA_ARGS__
#define PP_REMOVE_PARENS_IMPL(x) PP_REMOVE_PARENS_IMPL_IMPL x

int fun()
{
	static int x;
}

int main()
{
	freopen("a.txt","w",stdout);
	
	for(int i=1;i<128;i++)
	{
		//#define PP_AUTO_IDENTIFIER_IMPL_127(name,id,op,op_final,step) op(name,id) PP_AUTO_IDENTIFIER_IMPL_126(name,PP_CONCAT(PP_INC,step)(id),op,op_final,step)
		printf("#define PP_AUTO_IDENTIFIER_IMPL_%d(name,id,op,op_final,step) op(name,id) PP_AUTO_IDENTIFIER_IMPL_%d(name,PP_CONCAT(PP_INC,step)(id),op,op_final,step)\n",i,i-1);
		
	}
}