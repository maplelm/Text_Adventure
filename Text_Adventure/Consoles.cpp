#include "Consoles.h"

void Consoles::Init() {

#ifdef _WIN32

#else

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

#endif

}

char Consoles::Update() { 

#ifdef _WIN32
    char input = _getch();
#else
    char input = getch();
#endif
	return input;
}

void Consoles::ResizeWindow(unsigned int width, unsigned int height) {

}

void Consoles::DrawToScreen(unsigned int x, unsigned int y, char texture) {

}

void Consoles::Close() {

#ifdef _WIN32

#else

    endwin();

#endif
}

