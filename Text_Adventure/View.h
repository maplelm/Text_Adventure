#ifndef VIEW_H
#define VIEW_H

#include "Defines.h"
#include "Entity.h"
#include <vector>
#include <stack>
#include <fstream>


typedef std::vector<std::vector<std::vector<std::stack<Entity>>>> Map;

typedef std::vector<std::vector<std::stack<Entity>>> YAxis;
typedef std::vector<std::stack<Entity>> XAxis;
typedef std::stack<Entity> ItemList;

class View {

    int x_position;
    int y_position;
    int z_position;

    float zoom = 1.f;
     
public:

    View();
    virtual ~View();

    void Render(Map * map);

    //Setter Functions
    void SetxPosition(int x);
    void SetyPosition(int y);
    void SetzPosition(int z);
    void SetZoom(float zoom);

    //Getter Functions
    const int GetxPosition();
    const int GetyPosition();
    const int GetzPosition();
    const float GetZoom();

    void Move(int x, int y, int z = 0);

};

#endif
