#include "Consoles.h"

bool Consoles::Init() {

#ifdef _WIN32

#else
    initscr();
    if (has_colors() == false) {
        std::cout << "Your terminal does not support color\n";
        return false;
    }
    cbreak();
    noecho();
    keypad(stdscr, true);

#endif

    return true;

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

void Consoles::DrawToScreen(unsigned int x, unsigned int y, std::string texture) {

//#ifdef _WIN32
    std::cout << "\x1b[" << y << ";" << x << "f" << texture;
//#else
//    move(y,x); 
//   refresh();
//    std::cout << texture;
//#endif

}

void Consoles::Close() {

#ifdef _WIN32

#else

    endwin();

#endif
}

