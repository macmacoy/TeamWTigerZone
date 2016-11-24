#include "Engine.h"
// #include "Engine.cpp"
#ifdef Testing
#else
int main()
{
	Engine * e = new Engine(0);

	delete e;

	system("pause");

	return 0;

}
#endif
