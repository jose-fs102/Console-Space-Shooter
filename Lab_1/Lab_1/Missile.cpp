#include "stdafx.h"
#include "Missile.h"


// Overloaded Ctor
Missile::Missile(ConsoleColor _fg, ConsoleColor _bg, char const * const _text, unsigned int _id,
	char const * const _name, int _left, int _top, Delta _dX, Delta _dY) : Sprite(_fg, _bg, _text, _id, _name, _left, _top)
{
	deltas.resize(2);

	deltas[0] = _dX;
	deltas[1] = _dY;
}

// Dtor
Missile::~Missile()
{
	// Empty for now
}