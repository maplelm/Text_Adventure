#pragma once

#include "Entity.h"
#include "View.h"
#include <vector>
#include <array>

class Player : public Entity
{
    private:

        std::vector<Entity> m_inventory;
        View * m_attachedCamera;
        std::vector<std::vector<std::stack<Entity>>> * currentLayer;
        unsigned int m_MaxInventorySize;


    public:

        Player();
        Player(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina);
        Player(char texture, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina);
        Player(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, Status* stats);
        Player(char texture, bool isPassable, bool isVisable, Status* stats);
        Player(char texture);
        virtual ~Player();
        
        //Setters
        void SetInventory(std::vector<Entity> inv);
        void SetAttachedCamera(View * cam);
        void SetMaxInventorySize(unsigned int invSize);

};
