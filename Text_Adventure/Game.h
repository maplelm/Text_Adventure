#ifndef GAME_H
#define GAME_H

#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>

#include "TestState.h"
#include "View.h"

extern std::mutex renderMutex;

class Game {

    std::stack<State*> m_stateStack;

    bool isRunning;
    std::thread * renderHandle;

public:

    Game();
    virtual ~Game();

    void Render();
    void Update();
    void UserInput();

    void Run();
    void RenderThread();
};

#endif
