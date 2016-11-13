#include "engine.h"

int main()
{
	Engine * e = new Engine;

	e->Initialize();

	delete e;

	return 0;

}
