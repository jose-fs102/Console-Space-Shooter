#pragma once
class Image2D
{
private:

	string text;
	unsigned short width, height;

	ConsoleColor fg;
	ConsoleColor bg;

	int id;
public:

	// Default Ctor
	Image2D();

	// Overloaded Ctor
	Image2D(ConsoleColor fg, ConsoleColor bg, char const * const text, unsigned int id);

	// Copy Ctor
	Image2D(Image2D const& obj);

	// Assigment Operator
	Image2D& operator=(Image2D const& obj);

	// Dtor
	~Image2D();

	// Accessors
	const char * const GetText(void) const { return text.c_str(); }
	const ConsoleColor GetFG(void) const { return fg; }
	const ConsoleColor GetBG(void) const { return bg; }
	const unsigned short GetWidth(void) const { return width; }
	const unsigned short GetHeight(void) const { return height; }
	const unsigned int GetID(void) const { return id; }

	

	// Mutators
	void SetText(const char * const _text);
	void SetFG(ConsoleColor _fg) { fg = _fg; }
	void SetBG(ConsoleColor _bg) { bg = _bg; }
	void SetID(unsigned int _id) { id = _id; }

	// Show Method
	virtual void Show();

	void Calc_Width_Height();
};