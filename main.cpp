#include "Engine.h"
#ifdef Testing
#else
int main()
{
	Engine * e = new Engine();

	delete e;

	system("pause");

	return 0;

}
#endif
