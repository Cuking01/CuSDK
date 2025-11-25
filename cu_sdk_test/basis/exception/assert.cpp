#include "../../../include/basis/CuSDK/basis.h"

using namespace cusdk;

int main()
{
	try
	{
		cu_assert(0+1==2);
	}
	catch(std::exception&e)
	{
		printf("%s\n",e.what());
	}
	

	try
	{
		cu_assert(4+6==5,"exp calc");
	}
	catch(std::exception&e)
	{
		printf("%s\n",e.what());
	}
}

