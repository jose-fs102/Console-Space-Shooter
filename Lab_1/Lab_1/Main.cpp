// Lab_1.cpp : main project file.

#include "stdafx.h"
#include "Game.h"
#include"Util.h"

int main()
{
	// This will check for memory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

	srand(unsigned int(time(0)));

	Util::EOLWrap(false);

	// Game Object to access the Game class
	Game G_obj;

	// Game Object used to access the Game Play method
	G_obj.Play();

	Util::EOLWrap(true);

	cout << '\n';
	//Util::Pause();
	system("pause");
    return 0;
}