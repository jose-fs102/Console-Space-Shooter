#pragma once
#include "Image2D.h"
struct PlayerScore
{
	char name[32];
	int score, min, sec, milisec;
};

class Sprite : public Image2D
{
private:

	string name;
	int left, top, score = 0;
	int min = 0;
	int sec = 0;
	int milisec = 0;

public:

	// Default Ctor
	Sprite() { }

	// Overloaded Ctor
	Sprite(ConsoleColor _fg, ConsoleColor _bg, char const * const _text, unsigned int _id,
		char const * const _name, int _left, int _top);

	// Copy Ctor
	Sprite(Sprite const& obj);

	// Assignment Operator
	Sprite& operator=(Sprite const& obj);

	// Dtor
	virtual ~Sprite() { }

	// Accessors*************************************
	const char * const GetName(void) { return name.c_str(); }
	const int GetLeft(void) const { return left; }
	const int GetTop(void) const { return top; }
	int GetScore() const{ return score; }

	// Mutators*********************************************************************
	void SetName(const char * const _name) { name = _name; }
	void SetLeft(int _left) { left = _left; }
	void SetTop(int _top) { top = _top; }

	// Methods************************************************************

	// Show method for Sprite Class
	void Show();

	// Bool method to check the out of bounds
	bool OutOfBounds(int newX, int newY) const;

	// Bool method to check for collision
	bool Collides(int x, int y, unsigned short w, unsigned short h) const;

	// Sets the players score
	void AddToScore(int _add);
};