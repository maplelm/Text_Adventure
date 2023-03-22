#include "Game.h"


Game::Game() {

    isRunning = true;
    renderHandle = nullptr;

}

Game::~Game() {
    if (renderHandle != nullptr)
    delete this->renderHandle;
}


void Game::Render() {
    while (!m_stateStack.empty()) {
        try {
            m_stateStack.top()->Render();
            if (!m_stateStack.empty())
                if (m_stateStack.top()->GetCameraHandle()->GetisClearNeeded()) {
                    std::cout << "\x1b[2J";
                    m_stateStack.top()->GetCameraHandle()->SetisClearNeeded(false);
                }
        }
        // catch memory access violations if thread tries to read the stack state when the stack is cleared
        catch (int e){
            return;
        }
    }
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
    //m_stateStack.push(new TestState(900,900,3, 0));
    m_stateStack.push(new TestState(100, 100, 3, 0));
    RenderThread();
    while (!m_stateStack.empty()) {

        //check for user input
        UserInput();
        // Update game state
        Update();
        // Render Game state
        //Render();
    }
    renderHandle->join();
}

void Game::RenderThread() {
    this->renderHandle = new std::thread(&Game::Render, this);
}