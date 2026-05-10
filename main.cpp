#include "heterogeneous_set.hpp"

int main()
{
	using A = heterogeneous_set<1, 2, 3, 4, 5>;
	using B = A::remove<3>;
}
