#include "Game.h"


Game::Game() {

    isRunning = true;

}

Game::~Game() {

}


void Game::Render() {

    if (m_stateStack.empty())
        return;
    
    std::cout << "\x1b[s\x1b[H\x1b[J";
    m_stateStack.top()->Render();
    std::cout << "\x1b[u";

}

void Game::Update() {

    if (m_stateStack.empty())
        return;

    while (!m_stateStack.top()->IsOpen()) {
        m_stateStack.pop();
        if (m_stateStack.empty())
            return;
    }
    
    m_stateStack.top()->Update();

}

void Game::UserInput() {

    if (m_stateStack.empty())
        return;
    
    m_stateStack.top()->UserInput();

}


////////////////////
// Main Game Loop //
////////////////////
void Game::Run() {

    std::cout << "Welcome to my adventure Game!" << std::endl;

    // Creating init states
    m_stateStack.push(new TestState(1000,1000,3, 0));

    while (!m_stateStack.empty()) {

        //check for user input
        UserInput();
        // Update game state
        Update();
        // Render Game state
        Render();
    }
}
