#include "stdafx.h"
#include "Sprite.h"

// Default Ctor is inlined in Sprite.h
// Dtor is inlined in Sprite.h

// Overloaded Ctor
Sprite::Sprite(ConsoleColor _fg, ConsoleColor _bg, char const * const _text, unsigned int _id,
	char const * const _name, int _left, int _top) : Image2D(_fg, _bg, _text, _id), name(_name)
{
	SetLeft(_left);
	SetTop(_top);
}

// Copy Ctor
Sprite::Sprite(Sprite const& obj) : Image2D(obj)
{

	SetName(obj.name.c_str());
	SetLeft(obj.left);
	SetTop(obj.top);
}

// Assignment Operator
Sprite& Sprite::operator=(Sprite const& obj)
{
	if (this != &obj)
	{
		Image2D::operator=(obj);
		SetName(obj.name.c_str());
		SetLeft(obj.left);
		SetTop(obj.top);
	}

	return *this;
}

// Show method for Sprite class
void Sprite::Show()
{
	Console::SetCursorPosition(left, top);
	Console::ForegroundColor = this->GetFG();
	Console::BackgroundColor = this->GetBG();

	char Char_Text[32];
	strcpy_s(Char_Text, 32, GetText());
	int tempTop = top;
	for (unsigned int i = 0; i < strlen(GetText()); i++)
	{
		if (Char_Text[i] == '\n')
		{
			Console::SetCursorPosition(left, ++tempTop);
		}
		else
			cout << Char_Text[i];
	}

	Console::ResetColor();
}

// Out of bounds method
bool Sprite::OutOfBounds(int newX, int newY) const
{
	//Out of bounds check
	if ((newX >= 1 && newX <= Console::WindowWidth - GetWidth() - 1) && (newY >= 2 && newY <= Console::WindowHeight - 3))
	{
		return false;
	}
	return true;
}

// Collision method
bool Sprite::Collides(int x, int y, unsigned short w, unsigned short h) const
{
	if (x >= GetLeft() + GetWidth() || x + w <= GetLeft() || y >= GetTop() + GetHeight() || y + h <= GetTop())
	{
		return false;
	}
	return true;
}

void Sprite::AddToScore(int _add)
{
	score += _add;
}