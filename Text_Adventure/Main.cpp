
#include <iostream>
#include "Game.h"

//adding windows.h library when compiling on a windows system
#ifdef WIN
#include <windows.h>
#endif

int main(int argc, char** argv) {

// If on windows enable ansi codes for the command prompt
#ifdef WIN
    // Get the console output handle
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Enable virtual terminal processing
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    std::cout << "\x1b[?25l";

    Game app;
    app.Run();
     
    std::cout << "\x1b[0m\x1b[H\x1b[J\x1b[?25h";

    return 0;

}
