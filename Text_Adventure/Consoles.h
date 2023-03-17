#pragma once

#ifdef _WIN32

#include "windows.h"

#else

#include "ncurses.h"

#endif

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>


namespace Consoles {

	bool Init();
	char Update();
	void ResizeWindow(unsigned int width, unsigned int height);
	void DrawToScreen(unsigned int x, unsigned int y, std::string texture);
    void Close();

}

