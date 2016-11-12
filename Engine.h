#pragma once

#include "GameBase.h"
#include <Windows.h>

class Engine
{
public:
	Engine();
	~Engine();

	void Initialize();

private:
	Gamebase * game;
};