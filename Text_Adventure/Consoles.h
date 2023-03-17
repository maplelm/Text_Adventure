#pragma once

#ifdef _WIN32

#include "windows.h"

#else

#include "ncurses.h"

#endif


namespace Consoles {

	void Init();
	char Update();
	void ResizeWindow(unsigned int width, unsigned int height);
	void DrawToScreen(unsigned int x, unsigned int y, char texture);

}
