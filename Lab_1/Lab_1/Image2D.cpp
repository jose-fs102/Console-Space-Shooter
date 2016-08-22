#include "stdafx.h"
#include "Image2D.h"

// Default Ctor
Image2D::Image2D()
{
	
}

// Overloaded Ctor
Image2D::Image2D(ConsoleColor _fg, ConsoleColor _bg, char const * const _text, unsigned int _id) : text(_text)
{
	//SetText(_text);
	fg = _fg;
	bg = _bg;
	id = _id;
	Calc_Width_Height();
}

// Copy Ctor
Image2D::Image2D(Image2D const& obj)
{
	SetText(obj.text.c_str());
	fg = obj.fg;
	bg = obj.bg;
}

// Assignment Operator
Image2D& Image2D::operator=(Image2D const& obj)
{
	if (this != &obj)
	{
		SetText(obj.text.c_str());
		fg = obj.fg;
		bg = obj.bg;
		id = obj.id;
	}

	return *this;
}

// Dtor
Image2D::~Image2D()
{
	
}

// SetText Method
void Image2D::SetText(const char * const _text)
{
	text = _text;
	Calc_Width_Height();
}

// Show Method
void Image2D::Show()
{
	Console::ForegroundColor = fg;
	Console::BackgroundColor = bg;

	cout << text;

	Console::ResetColor();
}

void Image2D::Calc_Width_Height()
{
	// Calculate width and height here
	width = 0;
	height = 1;

	for (unsigned int i = 0; i < strlen(text.c_str()); i++)
	{
		if (text[i] == '\n') // For every new line, increase the height by one
		{
			height++;
		}
		else // otherwise increase the width by one
		{
			width++;
		}
	}

	width /= height;
}