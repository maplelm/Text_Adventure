#ifndef STATE_H
#define STATE_H

#include <conio.h>
#include <vector>
#include <stack>
#include <cstdlib>

#include "Entity.h"
#include "View.h"

//typedef std::vector<std::vector<std::stack<Entity>>> Layer;

class State {
protected:

    Map m_map;

    View m_camera;

    bool m_isRunning;

    //Creates the map structure to specified dimentions (stacks are empty)
    void InitMap(int width, int height, int depth);
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
