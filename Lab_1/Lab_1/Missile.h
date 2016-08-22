#pragma once
#include "Sprite.h"
typedef signed char Delta;

class Missile : public Sprite
{
private:

	// Vector
	vector<Delta> deltas;

public:

	// Overloaded Ctor
	Missile(ConsoleColor fg, ConsoleColor bg, char const * const text, unsigned int _id,
		char const * const name, int left, int top, Delta dX, Delta dY);

	// Dtor
	~Missile();

	// Accessors****************************
	const void GetDeltas(Delta& _dX, Delta& _dY) { _dX = deltas[0]; _dY = deltas[1]; }

	// Mutators*****************************
	const void SetDeltas(Delta _dX, Delta _dY) { deltas[0] = _dX; deltas[1] = _dY; }

	// Methods******************************

};