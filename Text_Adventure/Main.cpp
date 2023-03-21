/*
*
* To-do List:
*   -> Add functional menu class to get information about the game state to players
*   -> Get items and mosters working in the game
*   -> Get line of sight working the game
*   -> Start generating underground randomness (generate ore spawns and tunnels)
*   -> Improve render pipeline so game does not flash every frame and struggle to keep up with inputs
*   -> Make game flow in real time (no blocking input functions or if need on a different thread to the main game)
*   -> Add sounds
*   -> Add title screen
*   -> Add a more rebused coloring system (fix the issue were a Colors::none background erases the foreground as well)
*   -> Give entities more properties so player can interact with them.
* 
*/


#include <iostream>

//adding windows.h library when compiling on a windows system
#ifdef _WIN32
#include <windows.h>
#endif

#include "Game.h"

int main(int argc, char** argv) {

    Consoles::Init();

    // Hide cursor
    std::cout << "\x1b[?25l";

    Game app;
    app.Run();
     
    // Clear the screen and make cursor visible again
    std::cout << "\x1b[0m\x1b[H\x1b[J\x1b[?25h";

    Consoles::Close(); 

    return 0;

}
