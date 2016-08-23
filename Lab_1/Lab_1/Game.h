#pragma once

#include "Image2D.h"
#include "Sprite.h"
#include "Missile.h"
#include "Cell.h"
#include "Dlist.h"

#define Alive (1)
#define Ghost (1 << 1) // 2
#define AI_Move (1 << 2) // 4
#define AI_Shoot (1 << 3) // 8

class Game
{

private:

	// Vectors
	list<Sprite*> Ships;
	vector<PlayerScore> scoreVec;
	vector<PlayerScore> highscores;

	// PlayerScore structure objects
	PlayerScore tempScore;
	PlayerScore inputRecord;

	// Cell Vectors (Now DList)
	DList<Cell<signed short, wchar_t>*> star;
	DList<Cell<signed short, wchar_t>*> crossHair;

	// Strings
	string player_name;

	// Int Variables
	int milisec = 100;
	int sec = 0;
	int min = 0;
	int frame = 0;
	int AI_count = 0;
	int enemyDir = 1;
	int highscore_choice;
	int starcount;
	int framemod = 10;
	int newHeight = 3;
	int PlayerLives = 10;
	int average = 0;
	int averageMintime = 0;
	int averageSectime = 0;
	int averageMilisectime = 0;
	int count = 0;

	// Char Variables
	char bitflags = 1;

	bool plays = true;

public:

	// Default Ctor
	Game();

	// Dtor
	~Game();

	// Methods
	void Menu();
	void Instructions() const;
	void DisplayHighScores();
	void Play();
	void Refresh();
	void Input();
	void MissileBehavior();
	void AI_Behavior();
};