#ifndef STATE_H
#define STATE_H

#ifdef _WIN32
#include <conio.h>
#endif

#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Entity.h"
#include "View.h" 

class State {
protected:

    // array that keeps track of all entities in the tilemap
    Map m_map; 
    
    // this is what draws the state to the screen, it is the camera
    View m_camera; 

    // If false state will shutdown
    bool m_isRunning;

    //Used if state is going to be a chunk in a bigger map
    unsigned int xPos;
    unsigned int yPos;

    // Keeps track of the ground level of the map, will get rid of this as the map gets more dynamic
    unsigned int m_groundLevel;

    //Creates the map structure to specified dimentions (stacks are empty)
    void InitMap(int width, int height, int depth, int groundLevel = 1);
    void CellAuto2d(Entity target, Entity blank, unsigned int layer, unsigned int r = 1);
    
    // Not Implemented Yet
    void CellAuto3d(Entity target, Entity blank, unsigned int CLayer, unsigned int r = 1);

public:

    State();
    State(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed = 0);

    virtual ~State();

    virtual void Render(bool fullMap = false);
    virtual void Update() = 0;
    virtual void UserInput() = 0;

    void AddEntityToTile(unsigned int x, unsigned int y, unsigned int z, Entity entity);

    const bool IsOpen();

};

#endif
