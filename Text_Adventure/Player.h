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
        std::vector<std::vector<std::vector<Entity>>> * m_currentLayer;
        unsigned int m_MaxInventorySize;
        unsigned int x_Position;
        unsigned int y_Position;
        unsigned int z_Position;


    public:

        Player();
        Player(std::vector<std::vector<std::vector<Entity>>> * currentLayer, char texture, Colors fg = Colors::none, Colors bg = Colors::none, bool isPassable = true, bool isVisable = true,
             float health = -1, float mana = -1, float strength = -1, float dexterity = -1, float stamina = -1);
        Player(std::vector<std::vector<std::vector<Entity>>> * currentLayer, char texture, Status * stats, Colors fg = Colors::none, Colors bg = Colors::none, bool isPassable = true, bool isVisable = true);
        
        virtual ~Player();
        
        //Setters
        void SetInventory(std::vector<Entity> inv);
        void SetAttachedCamera(View * cam);
        void SetMaxInventorySize(unsigned int invSize);
        void SetCurrentLayer (std::vector<std::vector<std::vector<Entity>>>* layer);
        void SetLocation(int x, int y, int z);

        //Getters
        std::vector<Entity>* GetInventory();
        View * GetCamera();
        unsigned int GetInventorySize();
        std::vector<std::vector<std::vector<Entity>>> * GetCurrentLayer();

        bool MovePlayer(int x, int y);

};
