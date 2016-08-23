#pragma once
#include "stdafx.h"

template <typename Offset, typename Symbol>
struct Cell
{
	Offset oX, oY;
	ConsoleColor fg, bg;
	Symbol sym;

	// Default Ctor
	Cell() { };

	// Inlined Overloaded Ctor
	Cell(Offset _oX, Offset _oY, ConsoleColor _fg, ConsoleColor _bg, Symbol _sym)
	{
		oX = _oX;
		oY = _oY;
		fg = _fg;
		bg = _bg;
		sym = _sym;
	}

	// Inlined Show Method
	bool Show(int _left, int _top) const
	{
		int newX = _left + oX;
		int newY = _top + oY;

		if (newX >= Console::WindowWidth || newY >= Console::WindowHeight - 3)
		{
			return false;
		}
		else
		{
			Console::SetCursorPosition(newX, newY);
			Console::ForegroundColor = fg;
			Console::BackgroundColor = bg;
			Console::Write(sym);
			return true;
		}
	}

	// Array Subscript Operator Overload
	Offset& operator[](int index)
	{
		if (index == 0)
		{
			return oX;
		}
		else if (index == 1)
		{
			return oY;
		}
		return 0;
	}

	// Array Subscript Operator Overload Constant
	const Offset& operator[](int index) const
	{
		if (index == 0)
		{
			return oX;
		}
		else if (index == 1)
		{
			return oY;
		}

		return 0;
	}
};