#include "../../basis.h"

using namespace cusdk;

int main()
{
	using T1=std::vector<int>;
	using T2=int;
	
	static_assert(Instance_Of<std::vector,T1>);
	static_assert(!Instance_Of<std::vector,T2>);
}

