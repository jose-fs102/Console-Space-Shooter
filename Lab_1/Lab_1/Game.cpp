#include "stdafx.h"
#include "Game.h"

//Extra Credit////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////
// 5 points	Use SoundPlayer to play a.WAV----YES
//
// 5 points	Draw a box around the field leaving the top row for the HUD and bottom row for the bit flags, then update bounds checking---YES
//
// 5 points	Display high - score statistics(min, max and average) for both time and score---YES
//
// 5 points	Change the name of the 6th player in the binary high - score file to “Number Six”---NO
//
// 5 points	Implement something interesting or cool that is not on this list for a max of 5 more points---NO
//
// 5 points	Replace vector of cells with a DList---YES
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sorting highscores and times
bool AscendingNameSort(PlayerScore& first, PlayerScore& last)
{
	if (strcmp(first.name, last.name) < 0)
		return true;

	return false;
}

bool DescendingNameSort(PlayerScore& first, PlayerScore& last)
{
	if (strcmp(first.name, last.name) > 0)
		return true;

	return false;
}

bool DescendingScoreSort(PlayerScore& score1, PlayerScore& score2)
{
	return score1.score > score2.score;
}

bool DescendingTimeMins(PlayerScore& time1, PlayerScore& time2)
{
	return time1.min > time2.min;
}

bool DescendingTimeSecs(PlayerScore& time1, PlayerScore& time2)
{
	return time1.sec > time2.sec;
}

bool DescendingTimeMili(PlayerScore& time1, PlayerScore& time2)
{
	return time1.milisec > time2.milisec;
}

// Ctor
Game::Game()
{
	Console::SetWindowSize(150, 50);
	Console::SetBufferSize(150, 50);
}

// Dtor
Game::~Game()
{
	auto iter = Ships.begin();
	for (; iter != Ships.end(); iter++)
	{
		delete *iter;
	}
	for (unsigned int i = 0; i < star.size(); i++)
	{
		delete star[i];
	}
#if 0
	for (unsigned int i = 0; i < crossHair.size(); i++)
	{
		delete crossHair[i];
	}
#endif
}

// Main Gameplay function
void Game::Play()
{
	Image2D ship1(ConsoleColor::Red, ConsoleColor::Black, "|0x0|", 0),
		ship2(ConsoleColor::Red, ConsoleColor::Black, "<-0->", 1),
		ship3(ConsoleColor::DarkGray, ConsoleColor::Black, "|O|", 2);

	// Saving to a file***********************************************************************************************************
	fstream fout;

	// Number of items in the file
	int count = 3;

	// Opens the file
	fout.open("Ships.txt", ios_base::out);

	// Checks to see if the file is open
	if (fout.is_open())
	{
		fout << count << '\n';

		fout << ship1.GetText() << '\t' << (unsigned int)ship1.GetFG() << '\t'
			<< (unsigned int)ship1.GetBG() << '\t' << ship1.GetID() << '\n';

		fout << ship2.GetText() << '\t' << (unsigned int)ship2.GetFG() << '\t'
			<< (unsigned int)ship2.GetBG() << '\t' << ship2.GetID() << '\n';

		fout << ship3.GetText() << '\t' << (unsigned int)ship3.GetFG() << '\t'
			<< (unsigned int)ship3.GetBG() << '\t' << ship3.GetID() << '\n';

		fout.close();
	}

	// Reading from a file************************************************************************************************************
	fstream fin;

	// Opens the file
	fin.open("Ships.txt", ios_base::in);

	// Image2D pointer
	Image2D* images;

	// Check to see if file is open
	if (fin.is_open())
	{
		// Variables to read
		char buffer[32];
		int fg, bg, id;

		// Reading the count
		fin >> count;
		fin.ignore(INT_MAX, '\n');

		// Allocation of memory for array
		images = new Image2D[count];

		// For loop to set the images into the array
		for (int i = 0; i < count; i++)
		{
			fin.get(buffer, 32, '\t');
			fin >> fg >> bg >> id;

			images[i].SetText(buffer);
			images[i].SetFG((ConsoleColor)fg);
			images[i].SetBG((ConsoleColor)bg);
			images[i].SetID(id);

			fin.ignore(INT_MAX, '\n');
		}

		cout << endl;
		// Closes the file
		fin.close();
	}

	//**********************************************************************************************************************************
	Sprite* Sprite_image = new Sprite[2];

	Sprite_image[0] = Sprite(images[0].GetFG(), images[0].GetBG(), images[0].GetText(), images[0].GetID(), "Player", 1, 29);
	Sprite_image[1] = Sprite(images[1].GetFG(), images[1].GetBG(), images[1].GetText(), images[1].GetID(), "Computer", 25, 2);

	// Number of items in the file******************************************************************************************************
	int sprite_count = 2;

	// Opens the file
	fout.open("Sprites.txt", ios_base::out);

	// Checks to see if the file is open
	if (fout.is_open())
	{
		fout << sprite_count << '\n';

		fout << Sprite_image[0].GetText() << '\t' << "Player" << '\t' << (unsigned int)Sprite_image[0].GetFG() << '\t'
			<< (unsigned int)Sprite_image[0].GetBG() << '\t' << Sprite_image[0].GetID() << '\n';

		fout << Sprite_image[1].GetText() << '\t' << "Computer" << '\t' << (unsigned int)Sprite_image[1].GetFG() << '\t'
			<< (unsigned int)Sprite_image[1].GetBG() << '\t' << Sprite_image[1].GetID() << '\n';

		fout.close();
	}

	// Opens the "Sprites.txt" where the new sprites are saved**************************************************************************
	fin.open("Sprites.txt", ios_base::in);

	Sprite* new_sprite_image;

	if (fin.is_open())
	{
		// Variables to catch
		char sprite_buffer[32];
		string name;
		int sprite_count, fg, bg, id;

		fin >> sprite_count;
		fin.ignore(INT_MAX, '\n');

		new_sprite_image = new Sprite[sprite_count];

		for (int i = 0; i < sprite_count; i++)
		{
			fin.get(sprite_buffer, 32, '\t');
			fin.ignore(INT_MAX, '\t');
			getline(fin, name, '\t');
			fin >> fg >> bg >> id;

			new_sprite_image[i].SetText(sprite_buffer);
			new_sprite_image[i].SetName(name.c_str());
			new_sprite_image[i].SetFG((ConsoleColor)fg);
			new_sprite_image[i].SetBG((ConsoleColor)bg);
			new_sprite_image[i].SetID(id);
			fin.ignore(INT_MAX, '\n');
		}

		// Closes the file
		fin.close();
	}
	//*********************************************************************************************************************************************************************************
	Console::Clear();

	cout << "Enter your name: ";
	getline(cin, player_name);

	if (player_name.length() == 0)
	{
		// Sets the player to the default 'Player' Name
		Ships.push_front(new Sprite(new_sprite_image[0].GetFG(), new_sprite_image[0].GetBG(), new_sprite_image[0].GetText(), new_sprite_image[0].GetID(), "Player", 1, 47));
	}
	else
	{
		Ships.push_front(new Sprite(new_sprite_image[0].GetFG(), new_sprite_image[0].GetBG(), new_sprite_image[0].GetText(), new_sprite_image[0].GetID(), player_name.c_str(), 1, 47));
	}

	// Creates the Opponent
	Ships.push_back(new Sprite(new_sprite_image[1].GetFG(), new_sprite_image[1].GetBG(), new_sprite_image[1].GetText(), new_sprite_image[1].GetID(), "Computer", 25, 2));
	//*********************************************************************************************************************************************************************************

	//****************************************************************
	starcount = rand() % 20 + 10;
	while (starcount % 2)
	{
		starcount = rand() % 20 + 10;
	}

	int counter = 0;

	while (counter < starcount)
	{
		for (;;)
		{
			int x, y;

			x = rand() % Console::WindowWidth;
			y = rand() % Console::WindowHeight;

			bool ok = true;

			for (unsigned int i = 0; i < star.size(); i++)
			{
				if (star[i]->oX == x && star[i]->oY == y)
				{
					ok = false;
					break;
				}
			}

			if (ok)
			{
				star.push_back(new Cell<signed short, wchar_t>((signed short)x, (signed short)y, ConsoleColor::Yellow, ConsoleColor::Black, L'*'));
				counter++;
				break;
			}

		}
	}

	//*********************************************************************************************************************************************************

	// Calls the menu fucntion
	for (; plays; ++frame)
	{
		Menu();
	}


	// Loop to keep the refresh() and input() running
	for (; bitflags & Alive; ++frame)
	{
		Refresh();
		Input();
		MissileBehavior();
		AI_Behavior();
	}

	Console::Clear();
	Console::ResetColor();

	// Summerizes game data
	cout << (*Ships.begin())->GetName() << " scored: " << (*Ships.begin())->GetScore() << " Points in \n";
	cout << min << "_Minute(s), " << sec << "_Second(s) and " << milisec << "_Miliseconds\n";

	// Saving as a Binary file**********************************************************************************************************
	strcpy_s(tempScore.name, 32, (*Ships.begin())->GetName());
	tempScore.score = (*Ships.begin())->GetScore();
	tempScore.min = min;
	tempScore.sec = sec;
	tempScore.milisec = milisec;
	scoreVec.push_back(tempScore);

	fstream bout;
	bout.open("High_Scores.bin", ios_base::binary | ios_base::out | ios_base::app);

	if (bout.is_open())
	{
		bout.write((char*)scoreVec.data(), sizeof(PlayerScore)* scoreVec.size());
		bout.close();
	}

	// Saving as a Text file************************************************************************************************************
	fout.open("High_Scores.txt", ios_base::out | ios_base::app);

	if (fout.is_open())
	{
		fout << (*Ships.begin())->GetName() << '\t' << (*Ships.begin())->GetScore() << '\t' << tempScore.min << '\t'
			<< tempScore.sec << '\t' << tempScore.milisec << '\n';

		fout.close();
	}
	//**********************************************************************************************************************************

	// Delete Dynamic memory
	delete[] images;
	delete[] Sprite_image;
	delete[] new_sprite_image;
}

// Menu
void Game::Menu()
{
	LockWindowUpdate(GetConsoleWindow());
	Console::Clear();

	Console::SetCursorPosition((Console::WindowWidth / 2), Console::WindowHeight / 2);
	cout << "\\(-_-\\)\n";
	Console::SetCursorPosition((Console::WindowWidth / 2) - 5, (Console::WindowHeight / 2) + 10);
	cout << "Use the NUMPAD select options \n";

	Console::SetCursorPosition((Console::WindowWidth / 2) - 5, (Console::WindowHeight / 2) + 2);
	cout << "Welcome " << (*Ships.begin())->GetName() << '\n';

	Console::SetCursorPosition((Console::WindowWidth / 2) - 5, (Console::WindowHeight / 2) + 3);
	cout << "1: Play Game \n";

	Console::SetCursorPosition((Console::WindowWidth / 2) - 5, (Console::WindowHeight / 2) + 4);
	cout << "2: Instructions \n";

	Console::SetCursorPosition((Console::WindowWidth / 2) - 5, (Console::WindowHeight / 2) + 5);
	cout << "3: High Scores \n";

	Console::SetCursorPosition((Console::WindowWidth / 2) - 5, (Console::WindowHeight / 2) + 6);
	cout << "4: Exit Game \n";

	if (count % 2 == 0)
	{
		Console::SetCursorPosition((Console::WindowWidth / 2), Console::WindowHeight / 2);
		cout << "(/-_-)/ \n";
	}

	if (GetAsyncKeyState(VK_NUMPAD1))
	{
		plays = false;
		return;
	}
	if (GetAsyncKeyState(VK_NUMPAD2))
	{
		Instructions();
	}
	if (GetAsyncKeyState(VK_NUMPAD3))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		DisplayHighScores();
	}
	if (GetAsyncKeyState(VK_NUMPAD4))
	{
		bitflags &= ~Alive;
		return;
	}
	count++;
	LockWindowUpdate(NULL);
	System::Threading::Thread::Sleep(1000);
}

// Instruction Method
void Game::Instructions() const
{
	Console::Clear();
	cout << "Use the WASD keys for your ship movement. \n";
	cout << "Use the NumPad 8 to fire your missile. \n\n";

	cout << "You must avoid the enemy missiles. If enemy lands a hit on your ship, \nYou reset to your starting position and the enemy speeds up its missile firing and drops another level towards you.\n";
	cout << "Each hit will earn you 10 points, same for the enemy.\n";
	cout << "Press F1 to toggle enemy movement on or off \n";
	cout << "Press F2 to toggle enemy missile fire on or off \n";
	cout << "Press F3 to activate Ghost mode, making you invunerable to enemy \n";

	system("pause");

	return;
}

// Display High Scores
void Game::DisplayHighScores()
{
	Console::Clear();
	fstream fin;

	//All Bin Output***************************************************************************************************************************************

	fin.open("High_Scores.bin", ios_base::in);

	if (fin.is_open())
	{
		cout << "1: Ascending By Name \n";
		cout << "2: Descending By Name \n";
		cout << "3: Score Descending \n";
	
		cin >> highscore_choice;

		while (highscore_choice < 1 && highscore_choice > 3)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			Console::Clear();

			cout << "1: Ascending By Name \n";
			cout << "2: Descending By Name \n";
			cout << "3: Score Descending \n";

			cin >> highscore_choice;
		}

		fin.seekg(0, ios_base::end);

		int fileSize = (int)fin.tellg();

		fin.seekg(0, ios_base::beg);

		cout << "File Size: " << fileSize << "bytes\n\n";

		highscores.resize(fileSize / sizeof(PlayerScore));

		cout << "Name\tScore\tMinutes\tSeconds\tMiliseconds\n";

		fin.read((char*)highscores.data(), fileSize);

		switch (highscore_choice)
		{
		case 1:
			Console::Clear();
			sort(highscores.begin(), highscores.end(), AscendingNameSort);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				cout << highscores[i].name << "\t" << highscores[i].score << "\t"
					<< highscores[i].min << "\t" << highscores[i].sec << "\t"
					<< highscores[i].milisec << "\n";
			}

			// Average, min, max score****************************************************
			cout << endl;
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				average = highscores[i].score + average;
			}

			cout << "Average Score: " << average / highscores.size() << "\n";
			sort(highscores.begin(), highscores.end(), DescendingScoreSort);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Score: " << highscores[i].score << endl;
				}
			}
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Score: " << highscores[i].score << endl;
			}
			//****************************************************************************
			//Average time

			cout << endl;
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				averageMintime = highscores[i].min + averageMintime;
				averageSectime = highscores[i].sec + averageSectime;
				averageMilisectime = highscores[i].milisec + averageMilisectime;
			}

			cout << "Average Time in minutes: " << averageMintime / highscores.size() << "\n";
			cout << "Average Time in Seconds: " << averageSectime / highscores.size() << "\n";
			cout << "Average Time in Miliseconds: " << averageMilisectime / highscores.size() << "\n\n";

			//Min Times******************************************************************
			sort(highscores.begin(), highscores.end(), DescendingTimeMins);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Minutes: " << highscores[i].min << endl;
				}
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeSecs);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Seconds: " << highscores[i].sec << endl;
				}
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeMili);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Miliseconds: " << highscores[i].milisec << endl;
				}
			}

			cout << endl;

			//**************************************************************************
			//Max times*****************************************************************
			sort(highscores.begin(), highscores.end(), DescendingTimeMins);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Minutes: " << highscores[i].min << endl;
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeSecs);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Seconds: " << highscores[i].sec << endl;
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeMili);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Miliseconds: " << highscores[i].milisec << endl;
			}
			//**************************************************************************
			break;

		case 2:
			Console::Clear();
			sort(highscores.begin(), highscores.end(), DescendingNameSort);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				cout << highscores[i].name << "\t" << highscores[i].score << "\t"
					<< highscores[i].min << "\t" << highscores[i].sec << "\t"
					<< highscores[i].milisec << "\n";
			}

			// Average, min, max score****************************************************
			cout << endl;
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				average = highscores[i].score + average;
			}

			cout << "Average Score: " << average / highscores.size() << "\n";
			sort(highscores.begin(), highscores.end(), DescendingScoreSort);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Score: " << highscores[i].score << endl;
				}
			}
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Score: " << highscores[i].score << endl;
			}
			//****************************************************************************
			//Average time

			cout << endl;
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				averageMintime = highscores[i].min + averageMintime;
				averageSectime = highscores[i].sec + averageSectime;
				averageMilisectime = highscores[i].milisec + averageMilisectime;
			}

			cout << "Average Time in minutes: " << averageMintime / highscores.size() << "\n";
			cout << "Average Time in Seconds: " << averageSectime / highscores.size() << "\n";
			cout << "Average Time in Miliseconds: " << averageMilisectime / highscores.size() << "\n\n";

			//Min Times******************************************************************
			sort(highscores.begin(), highscores.end(), DescendingTimeMins);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Minutes: " << highscores[i].min << endl;
				}
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeSecs);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Seconds: " << highscores[i].sec << endl;
				}
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeMili);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Miliseconds: " << highscores[i].milisec << endl;
				}
			}

			cout << endl;

			//**************************************************************************
			//Max times*****************************************************************
			sort(highscores.begin(), highscores.end(), DescendingTimeMins);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Minutes: " << highscores[i].min << endl;
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeSecs);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Seconds: " << highscores[i].sec << endl;
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeMili);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Miliseconds: " << highscores[i].milisec << endl;
			}
			//**************************************************************************
			break;

		case 3:
			Console::Clear();
			sort(highscores.begin(), highscores.end(), DescendingScoreSort);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				cout << highscores[i].name << "\t" << highscores[i].score << "\t"
					<< highscores[i].min << "\t" << highscores[i].sec << "\t"
					<< highscores[i].milisec << "\n";
			}

			// Average, min, max score****************************************************
			cout << endl;
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				average = highscores[i].score + average;
			}

			cout << "Average Score: " << average / highscores.size() << "\n";
			sort(highscores.begin(), highscores.end(), DescendingScoreSort);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Score: " << highscores[i].score << endl;
				}
			}
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Score: " << highscores[i].score << endl;
			}
			//****************************************************************************
			//Average time

			cout << endl;
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				averageMintime = highscores[i].min + averageMintime;
				averageSectime = highscores[i].sec + averageSectime;
				averageMilisectime = highscores[i].milisec + averageMilisectime;
			}

			cout << "Average Time in minutes: " << averageMintime / highscores.size() << "\n";
			cout << "Average Time in Seconds: " << averageSectime / highscores.size() << "\n";
			cout << "Average Time in Miliseconds: " << averageMilisectime / highscores.size() << "\n\n";

			//Min Times******************************************************************
			sort(highscores.begin(), highscores.end(), DescendingTimeMins);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Minutes: " << highscores[i].min << endl;
				}
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeSecs);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Seconds: " << highscores[i].sec << endl;
				}
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeMili);
			for (unsigned int i = 0; i < highscores.size(); i++)
			{
				if (i == highscores.size() - 1)
				{
					cout << "Min. Miliseconds: " << highscores[i].milisec << endl;
				}
			}

			cout << endl;

			//**************************************************************************
			//Max times*****************************************************************
			sort(highscores.begin(), highscores.end(), DescendingTimeMins);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Minutes: " << highscores[i].min << endl;
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeSecs);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Seconds: " << highscores[i].sec << endl;
			}

			sort(highscores.begin(), highscores.end(), DescendingTimeMili);
			for (unsigned int i = 0; i < 1; i++)
			{
				cout << "Max. Miliseconds: " << highscores[i].milisec << endl;
			}
			//**************************************************************************
			break;
		}

		fin.ignore(INT_MAX, '\n');
	}
	else
	{
		cout << "No records to show...\n";
	}
	fin.close();
	cin.clear();
	system("pause");

	Console::Clear();
	string filename;

	cout << "What name would you like to save your file under: ";
	cin.ignore(INT_MAX, '\n');

	getline(cin, filename, '\n');

	if (filename.length() == 0)
	{
		filename = "Default";
	}

	filename.append(".txt");

	unsigned int scores_number;

	cout << "How many entries do you want to save ( in octal ): ";
	cin >> oct >> scores_number >> dec;

	if (scores_number > highscores.size())
	{
		scores_number = highscores.size();
	}

	ofstream saving;

	saving.open(filename);

	if (saving.is_open())
	{
		for (unsigned int i = 0; i < scores_number; i++)
		{
			saving << highscores[i].name << "\t" << highscores[i].score << "\t"
				<< highscores[i].min << "\t" << highscores[i].sec << "\t"
				<< highscores[i].milisec << "\n";
		}
	}

	saving.close();
}

// Refresh the screen
void Game::Refresh()
{
	LockWindowUpdate(GetConsoleWindow());
	Console::Clear();

	// Showing Stars*******************************************
	for (unsigned int i = 0; i < star.size(); i++)
	{
		star[i]->Show(0, 2);
	}
	//*************************************************

	// Resets the color to blue
	Console::ResetColor();

	// Sets position for Score to refresh
	Console::SetCursorPosition(0, 0);
	cout << (*Ships.begin())->GetName() << "(s) Score:";
	cout << (*Ships.begin())->GetScore();

	cout << "    Enemy Score:";
	cout << (*next(Ships.begin()))->GetScore();

	cout << "    Lives: " << PlayerLives;

	// Sets position for border to refresh
	Console::SetCursorPosition(0, 1);
	Console::ForegroundColor = ConsoleColor::Blue;

	for (unsigned int i = 0; i < 150; i++)
	{
		cout << (char)0xDC;
	}

	for (unsigned int i = 2; i < 49; i++)
	{
		Console::SetCursorPosition(0, i);
		cout << (char)0xDE;
	}

	for (unsigned int i = 2; i < 49; i++)
	{
		Console::SetCursorPosition(149, i);
		cout << (char)0xDD;
	}
	Console::ResetColor();

	// Sets position for timer to be set and refresh every second
	Console::SetCursorPosition(135, 0);
	cout << "Time: " << min << ":" << sec;
	milisec = milisec + 100;
	if (milisec == 1000)
	{
		sec++;
		milisec = 0;
	}
	if (sec == 60)
	{
		min++;
		sec = 0;
	}

	Console::ResetColor();
	Console::SetCursorPosition(0, 48);
	Console::ForegroundColor = ConsoleColor::Blue;
	for (unsigned int i = 0; i < 150; i++)
	{
		cout << (char)0xDF;
	}
	Console::ResetColor();
	Console::SetCursorPosition(0, 49);
	cout << "Bitflags: ";

	//Display wich bits I have on
	Console::SetCursorPosition(11, 49);
	for (int i = 3; i >= 0; --i)
	{
		//0010
		if (bitflags & (1 << i))  //0001
			cout << 1;
		else
			cout << 0;

		//1000
	}
	cout << "    F1 to stop enemy movement, F2 to stop enemy firing, F3 to activate Ghost Mode.";
	// For loop to loop through the List and display*************************************************************************
	auto iter = Ships.begin();
	Sprite* s = dynamic_cast<Sprite*> (*iter);

	for (; iter != Ships.end(); iter++)
	{
		if ((*Ships.begin())->GetLeft() >= Console::WindowWidth - 4 || (*Ships.begin())->GetTop() >= Console::WindowHeight)
		{
			break;
		}
		else
		{
			(*iter)->Show();
		}
	}
	//*************************************************************************************************************************

	LockWindowUpdate(NULL);
	System::Threading::Thread::Sleep(20);
}

// Gets input from keyboard to move
void Game::Input()
{
	// Checks if 'esc' key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		bitflags &= ~Alive;
	}

	// Checks if Numpad 6 is pressed
	if (GetAsyncKeyState(VK_NUMPAD8))
	{
		// If Ships is touching the border of the console window, does not allow a missile to be created
		if ((*Ships.begin())->GetLeft() != Console::WindowWidth - 5)
		{
			PlaySound(L"raygun.wav", NULL, SND_FILENAME | SND_ASYNC);
			Ships.push_back(new Missile(ConsoleColor::Red, ConsoleColor::Black, "^", 0, "Missile", (*Ships.begin())->GetLeft() + 2, (*Ships.begin())->GetTop(), 0, 1));
		}
	}

	if (GetAsyncKeyState(VK_F1))
	{
		bitflags ^= AI_Move;
	}

	if (GetAsyncKeyState(VK_F2))
	{
		bitflags ^= AI_Shoot;
	}

	if (GetAsyncKeyState(VK_F3))
	{
		bitflags ^= Ghost;
	}

	//if (GetAsyncKeyState(VK_NUMPAD4))
	//{
	//	// If Ships is touching the border of the console window, does not allow a missile to be created
	//	if (Ships[0]->GetLeft() != Console::WindowWidth - 5)
	//	{
	//		ShootLeft = true;
	//		ShootRight = false;
	//		Ships.push_back(new Missile(ConsoleColor::Red, ConsoleColor::Black, "<-", "Missile", Ships[0]->GetLeft() - 2, Ships[0]->GetTop() + 2, 1, 0));
	//	}
	//}

	int dx, dy;
	dx = dy = 0;

	// Checks keyboard input
	if (GetAsyncKeyState('W'))  dy = -1;
	if (GetAsyncKeyState('S'))  dy = 1;
	if (GetAsyncKeyState('A'))  dx = -1;
	if (GetAsyncKeyState('D'))  dx = 1;

	if (dx || dy)
	{
		int newX_Sprite1 = (*Ships.begin())->GetLeft();
		int newY_Sprite1 = (*Ships.begin())->GetTop();

		newX_Sprite1 += dx; // Updating the position of the first sprite
		newY_Sprite1 += dy;

		// Checks the return type of out of bounds()
		if (!(*Ships.begin())->OutOfBounds(newX_Sprite1, newY_Sprite1))
		{
			// Checks the return type of Collides()
			if (!(*next(Ships.begin()))->Collides(newX_Sprite1, newY_Sprite1, (*Ships.begin())->GetWidth(), (*Ships.begin())->GetHeight()))
			{
				(*Ships.begin())->SetLeft(newX_Sprite1);
				(*Ships.begin())->SetTop(newY_Sprite1);
			}
		}
	}
}

// Method to check for missile behavior (Movement, Collision, Out Of Bounds)
void Game::MissileBehavior()
{
#if 0

	for (unsigned int i = 2; i < Ships.size(); i++)
	{
		Delta Mx, My;
		Mx = My = 0;
		Missile* m = dynamic_cast<Missile*> (Ships[i]);

		if (m->GetID() == 0)
		{
			m->GetDeltas(Mx, My);

			if (Mx || My)
			{
				int newLeft = m->GetLeft() + Mx;
				int newTop = m->GetTop() - My;

				// Checks to make sure the missile is not out of bounds
				if (!m->OutOfBounds(newLeft, newTop))
				{
					// Checks to see if the missile collides with the opponent
					if (!Ships[1]->Collides(newLeft, newTop, m->GetWidth(), m->GetHeight()))
					{
						m->SetLeft(newLeft);
						m->SetTop(newTop);
					}
					else
					{
						Ships[0]->AddToScore(10);
						Ships[1]->SetTop(2);
						newHeight = 3;
						delete Ships[i];
						Ships.erase(i);
					}
				}
				else
				{
					delete Ships[i];
					Ships.erase(i);
				}
			}
		}
		else if (m->GetID() == 1)
		{

			m->GetDeltas(Mx, My);

			if (Mx || My)
			{
				int newLeft = m->GetLeft() + Mx;
				int newTop = m->GetTop() + My;

				// Checks to make sure the missile is not out of bounds
				if (!m->OutOfBounds(newLeft, newTop))
				{
					// Checks to see if the missile collides with the opponent
					if (!Ships[0]->Collides(newLeft, newTop, m->GetWidth(), m->GetHeight()))
					{
						m->SetLeft(newLeft);
						m->SetTop(newTop);
					}
					else
					{
						Ships[1]->AddToScore(10);
						Ships[1]->SetTop(newHeight);
						++++newHeight;

						if (Ships[1]->GetTop() >= Console::WindowHeight)
						{
							Ships[1]->SetTop(2);
							newHeight = 3;
						}

						Ships[0]->SetLeft(1);
						Ships[0]->SetTop(49);
						framemod--;

						if (framemod == 0)
						{
							framemod = 10;
						}

						delete Ships[i];
						Ships.erase(i);
					}
				}
				else
				{
					delete Ships[i];
					Ships.erase(i);
				}
			}

		}
	}

	// (*Ships.begin())
	// (*next(Ships.begin()))
	// Iterators
#elif 1
	// Creates iterators to loop through created missiles
	auto iter = Ships.begin();

	// Since the missile begins at [2], moves the iterator to [2]
	++iter;
	++iter;

	while (iter != Ships.end())
	{
		Delta Mx, My;
		Mx = My = 0;
		Missile* m = dynamic_cast<Missile*> (*iter);

		if (m->GetID() == 0)
		{
			m->GetDeltas(Mx, My);

			if (Mx || My)
			{
				int newLeft = m->GetLeft() + Mx;
				int newTop = m->GetTop() - My;

				// Checks to make sure the missile is not out of bounds
				if (!m->OutOfBounds(newLeft, newTop))
				{
					// Checks to see if the missile collides with the opponent
					if (!(*next(Ships.begin()))->Collides(newLeft, newTop, m->GetWidth(), m->GetHeight()))
					{
						m->SetLeft(newLeft);
						m->SetTop(newTop);
					}
					else
					{
						//System::Media::SystemSounds::Asterisk->Play();
						PlaySound(L"explosion-01.wav", NULL, SND_FILENAME | SND_ASYNC);

						(*Ships.begin())->AddToScore(10);
						(*next(Ships.begin()))->SetTop(2);
						newHeight = 3;
						delete *iter;
						Ships.erase(iter--);
					}
				}
				else
				{
					delete *iter;
					Ships.erase(iter--);
				}
			}
		}
		else if (m->GetID() == 1)
		{
			if (!(bitflags & AI_Shoot))
			{
				m->GetDeltas(Mx, My);

				if (Mx || My)
				{
					int newLeft = m->GetLeft() + Mx;
					int newTop = m->GetTop() + My;

					// Checks to make sure the missile is not out of bounds
					if (!m->OutOfBounds(newLeft, newTop))
					{
						// Checks to see if the missile collides with the opponent
						if (!(*Ships.begin())->Collides(newLeft, newTop, m->GetWidth(), m->GetHeight()))
						{
							m->SetLeft(newLeft);
							m->SetTop(newTop);
						}
						else
						{
							if (!(bitflags & Ghost))
							{
								//System::Media::SystemSounds::Asterisk->Play();
								PlaySound(L"explosion-01.wav", NULL, SND_FILENAME | SND_ASYNC);

								(*next(Ships.begin()))->AddToScore(10);
								(*next(Ships.begin()))->SetTop(newHeight);
								++++newHeight;


								if ((*next(Ships.begin()))->GetTop() >= Console::WindowHeight - 3)
								{
									(*next(Ships.begin()))->SetTop(2);
									newHeight = 3;
								}

								(*Ships.begin())->SetLeft(1);
								(*Ships.begin())->SetTop(47);
								framemod--;

								if (framemod == 0)
								{
									framemod = 10;
								}

								delete *iter;
								Ships.erase(iter--);
								PlayerLives--;

								if (PlayerLives == 0)
								{
									bitflags &= ~Alive;
								}
							}
						}
					}
					else
					{
						delete *iter;
						Ships.erase(iter--);
					}
				}
			}
		}
		++iter;
	}
#endif
}

// AI's behavior
void Game::AI_Behavior()
{
	//Do most of your AI code here
	if (!(frame % 1))
	{
		if (!(bitflags & AI_Move))
		{
			int newX = (*next(Ships.begin()))->GetLeft() + enemyDir;

			if (!(*Ships.begin())->Collides(newX, (*next(Ships.begin()))->GetTop(), (*next(Ships.begin()))->GetWidth(), (*next(Ships.begin()))->GetHeight()))
			{
				if (newX > Console::WindowWidth - 6 || newX < 1)
				{
					enemyDir = -enemyDir;
				}
				else
				{
					(*next(Ships.begin()))->SetLeft(newX);
				}
			}
			else
			{
				if (!(bitflags & Ghost))
				{
					(*Ships.begin())->SetLeft(1);
					(*Ships.begin())->SetTop(47);

					PlaySound(L"explosion-01.wav", NULL, SND_FILENAME | SND_ASYNC);
					(*next(Ships.begin()))->AddToScore(100);
					(*next(Ships.begin()))->SetTop(newHeight);
					++++newHeight;
					PlayerLives--;

					if (PlayerLives == 0)
					{
						bitflags &= ~Alive;
					}
				}
			}
		}
	}
	if (!(bitflags & AI_Shoot))
	{
		if (!(frame % framemod))
		{
			Ships.push_back(new Missile(ConsoleColor::Red, ConsoleColor::Black, "!", 1, "Missile", (*next(Ships.begin()))->GetLeft() + 2, (*next(Ships.begin()))->GetTop(), 0, 1));
			MissileBehavior();
		}
	}
}