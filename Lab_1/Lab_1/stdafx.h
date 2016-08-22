#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Winmm.lib")

// Additional headers the program requires
#include <mmsystem.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <deque>
#include <list>
#include <conio.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <sstream>

// Math Stuff
#define _USE_MATH_DEFINES
#include <math.h>

// Memory Leaks
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Using Namespaces here
using namespace std;
using namespace System;