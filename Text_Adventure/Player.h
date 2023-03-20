#pragma once

#include "Entity.h"
#include "View.h"
#include <vector>
#include <array>

class Player : public Entity
{
    private:

        ItemList m_inventory;
        View * m_attachedCamera;
        unsigned int m_MaxInventorySize;
        unsigned int x_Position;
        unsigned int y_Position;
        unsigned int z_Position;


    public:

        Player();
        Player(char texture, Colors fg = Colors::none, Colors bg = Colors::none, bool isPassable = true, bool isVisable = true,
             float health = -1, float mana = -1, float strength = -1, float dexterity = -1, float stamina = -1);
        Player(char texture, Status * stats, Colors fg = Colors::none, Colors bg = Colors::none, bool isPassable = true, bool isVisable = true);
        
        virtual ~Player();
        
        //Setters
        void SetInventory(ItemList inv);
        void SetAttachedCamera(View * cam);
        void SetMaxInventorySize(unsigned int invSize);
        void SetLocation(int x, int y, int z);

        //Getters
        ItemList * GetInventory();
        View * GetCamera();
        unsigned int GetInventorySize(); 
};
