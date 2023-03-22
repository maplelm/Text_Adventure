#ifndef TESTSTATE_H
#define TESTSTATE_H

#include "State.h"
#include "Consoles.h"

#include "Player.h"

class TestState : public State {

public:

    TestState(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed);
    virtual  ~TestState();

    void Update() override;
    void UserInput() override;

    void PlacePlayer();
    void GenerateTerrain(unsigned int seed);
};

#endif
