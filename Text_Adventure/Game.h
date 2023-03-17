#ifndef GAME_H
#define GAME_H

#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "TestState.h"
#include "View.h"

class Game {

    std::stack<State*> m_stateStack;

    bool isRunning;

public:

    Game();
    virtual ~Game();

    void Render();
    void Update();
    void UserInput();

    void Run();
};

#endif
