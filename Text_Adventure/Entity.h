#ifndef ENTITY_H 
#define ENTITY_H

#include <iostream>
#include <string>

struct Status{
    Status(float health = 1, float mana = 0, float stamina = 0, float strength = 0, float dexterity = 0) {
        this->health  = health;
        this->maxHealth = health;
        this->mana = mana;
        this->maxMana = mana;
        this->stamina = stamina;
        this->maxStamina = stamina;
        this->strength = strength;
        this->maxStrength = strength;
        this->dexterity = dexterity;
        this->maxDexterity = dexterity;
    }

    float health;
    float maxHealth;
    float mana;
    float maxMana;
    float strength;
    float maxStrength;
    float dexterity;
    float maxDexterity;
    float stamina;
    float maxStamina;
};
typedef struct Status Status;

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

typedef struct {
    std::string texture;
    Colors fg;
    Colors bg;
}Sprite;

typedef struct {
    int x;
    int y;
    int z;
}Position;

class Entity {

protected:
    bool isPassable;
    bool isVisable;
    Status* stats;
    Sprite sprite;

    unsigned long entityId;

public:

    static std::string GetColor(bool isForeground, Sprite sprite);


    Entity();
    Entity(unsigned long id, std::string texture, Colors fg = Colors::none, Colors bg = Colors::none, bool isPassable = true, bool isVisable = true,
             float health = -1, float mana = -1, float strength = -1, float dexterity = -1, float stamina = -1);
    Entity(unsigned long id, std::string texture, Status * stats, Colors fg = Colors::none, Colors bg = Colors::none, bool isPassable = true, bool isVisable = true);
    Entity(Entity &e);
    

    virtual ~Entity();

    //Setter functions
    void SetSprite(Sprite sprite);
    void SetisPassable(bool isPassable);
    void SetisVisable(bool isVisable);
    void SetHealth(float health);
    void SetMana(float mana);
    void SetStrength(float strength);
    void SetDexterity(float dexterity);
    void SetStamina(float stamina);
    void SetStats(Status* stats);
    void SetForeground(Colors color);
    void SetBackground(Colors color);
    void SetMaxHealth(float health);
    void SetMaxMana(float mana);
    void SetMaxStamina(float stamina);
    void SetMaxStrength(float strength);
    void SetMaxDexterity(float dexterity);
    void SetEntityId(unsigned long id);

    //Getter functions
    const Sprite GetSprite();
    const bool  GetisPassable();
    const bool GetisVisable();
    const Status* GetStats();
    const std::string GetFg();
    const std::string GetBg();
    const std::string GetTexture();
    const unsigned long GetId();

    void TogglePassable();
    void ToggleVisable();

    void ChangeHealth(float health);
    void ChangeMana(float mana);
    void ChangeStrength(float strength);
    void ChangeDexterity(float dexterity);
    void ChangeStamina(float stamina);

    void ChangeMaxHealth(float health);
    void ChangeMaxMana(float mana);
    void ChangeMaxStamina(float stamina);
    void ChangeMaxStrength(float strength);
    void ChangeMaxDexterity(float dexterity);
};

#endif
