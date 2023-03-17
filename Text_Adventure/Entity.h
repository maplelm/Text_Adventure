#ifndef ENTITY_H 
#define ENTITY_H

#include <iostream>
#include <string>

typedef struct {
    float health;
    float mana;
    float strength;
    float dexterity;
    float stamina;
}Status;

typedef enum {
    white,
    black,
    red,
    darkRed,
    green,
    yellow,
    blue,
    brown,
    silver,
    gold,
    none,
}Colors;

typedef enum {
    player = 0,
    terrain,
    item,
    npc,
}Type;

typedef struct {
    char texture;
    Colors fg;
    Colors bg;
}Sprite;

class Entity {

protected:
    bool isPassable;
    bool isVisable;
    Status* stats;
    Sprite sprite;

    std::string GetColor(bool isForeground);

public:

    /* TEST CODE */
    Type type = Type::terrain;
    /************************************/

    Entity();
    Entity(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina);
    Entity(char texture, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina);
    Entity(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, Status* stats);
    Entity(char texture, bool isPassable, bool isVisable, Status* stats);
    Entity(char texture);
    virtual ~Entity();

    //Setter functions
    void SetSprite(Sprite sprite);
    void SetisPassable(bool isPassable);
    void SetHealth(float health);
    void SetMana(float mana);
    void SetStrength(float strength);
    void SetDexterity(float dexterity);
    void SetStamina(float stamina);
    void SetStats(Status* stats);
    void SetForeground(Colors color);
    void SetBackground(Colors color);

    //Getter functions
    const Sprite GetSprite();
    const bool  GetIsPassable();
    const float GetHealth();
    const float GetMana();
    const float GetStrength();
    const float GetDexterity();
    const float GetStamina();
    const Status* GetStats();
    const std::string GetFg();
    const std::string GetBg();
    const char GetTexture();

    void TogglePassable();
    void ToggleVisable();
};

#endif
