#ifndef VIEW_H
#define VIEW_H

#include "Defines.h"
#include "Entity.h"
#include "Consoles.h"
#include <vector>
#include <stack>
#include <fstream>
#include <cmath>
#include <ranges>
#include <mutex>

extern std::mutex renderMutex;

typedef std::vector<std::vector<std::vector<std::vector<Entity*>>>> Map;

typedef std::vector<std::vector<std::vector<Entity*>>> YAxis;
typedef std::vector<std::vector<Entity*>> XAxis;
typedef std::vector<Entity*> ItemList;

class View {

    int x_position;
    int y_position;
    int z_position;

    unsigned int xWinPos;
    unsigned int yWinPos;

    Sprite m_border;

    float zoom = 1.f;

    bool isClearNeeded;
     
public:

    View();
    virtual ~View();

    void Render(Map * map);
    virtual void Render();

    //Setter Functions
    void SetxPosition(int x);
    void SetyPosition(int y);
    void SetzPosition(int z);
    void SetZoom(float zoom);
    void SetisClearNeeded(bool isClearNeeded);

    //Getter Functions
    const int GetxPosition();
    const int GetyPosition();
    const int GetzPosition();
    const unsigned int GetxWindowPos();
    const unsigned int GetyWindowPos();
    const float GetZoom();
    const bool GetisClearNeeded();

    void Move(int x, int y, int z = 0);
    void MoveWindow(int x, int y);

    void ClearNeeded();

};

#endif
