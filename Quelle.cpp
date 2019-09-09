#include <SFML\Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#include <strsafe.h>

using namespace std;


int main(int argc, TCHAR *argv[]) {

	srand(time(NULL));

	TCHAR szOldTitle[MAX_PATH];
	TCHAR szNewTitle[MAX_PATH];

	// Save current console title.

	if (GetConsoleTitle(szOldTitle, MAX_PATH))
	{
		// Build new console title string.

		StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Showcase"));

		// Set console title to new title
		if (!SetConsoleTitle(szNewTitle))
		{
			_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
			return 1;
		}
		else
		{
			_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
		}
	}



	Game g;
	g.Init();

	while (g.isRunning())
	{
		g.Run();
	}

	return 0;
}


/*skillwindow muss geschlossen werden*/