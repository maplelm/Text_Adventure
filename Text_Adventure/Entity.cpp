#include "Entity.h"

// Private Functions
std::string Entity::GetColor(bool isForeground, Sprite sprite) {
    std::string base = "\x1b[";
    std::string advBaseFg = "\x1b[38;5;";
    std::string advBaseBg = "\x1b[48;5;";
    if (isForeground) {
        switch (sprite.fg) {
        case white: return base + "37m"; break;
        case black: return base + "30m"; break;
        case red: return base + "31m"; break;
        case darkRed: return advBaseFg + "52m"; break;
        case green: return base + "32m"; break;
        case yellow: return base + "33m"; break;
        case blue: return base + "34m"; break;
        case brown: return advBaseFg + "130m"; break;
        case silver: return advBaseFg + "249m"; break;
        case gold: return advBaseFg + "220m"; break;
        case none: return base + "0m"; break;
        default: return ""; break;
        }
    }
    else {
        switch (sprite.bg) {
        case white: return base + "47m"; break;
        case black: return base + "40m"; break;
        case red: return base + "41m"; break;
        case darkRed: return advBaseBg + "52m"; break;
        case green: return base + "42m"; break;
        case yellow: return base + "43m"; break;
        case blue: return base + "44m"; break;
        case brown: return advBaseBg + "130m"; break;
        case silver: return advBaseBg + "249m"; break;
        case gold: return advBaseBg + "220m"; break;
        case none: return base + "0m"; break;
        default: return ""; break;
        }
    }
}


//Constructors and Destructors
Entity::Entity() {

    entityId = 0;
    sprite.texture = ' ';
    sprite.fg = Colors::none;
    sprite.bg = Colors::none;
    isPassable = true;
    isVisable = true;
    stats = nullptr;

}

Entity::Entity(unsigned long id, std::string texture, Colors fg, Colors bg, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina) {
    
    this->entityId = id;
    this->sprite.texture = texture;
    this->sprite.fg = fg;
    this->sprite.bg = bg;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    if (health < 1 || mana < 1 || stamina < 1 || strength < 0 || dexterity < 0)
        this->stats = nullptr;
    else {
        this->stats = new Status;
        this->stats->health = health;
        this->stats->maxHealth = health;
        this->stats->mana = mana;
        this->stats->maxMana = mana;
        this->stats->strength = strength;
        this->stats->dexterity = dexterity;
        this->stats->stamina = stamina;
        this->stats->maxStamina = stamina;
        this->stats->maxStrength = strength;
        this->stats->maxDexterity = dexterity;
    }
}

Entity::Entity(unsigned long id, std::string texture, Status* stats, Colors fg, Colors bg, bool isPassable, bool isVisable) {
    
    this->entityId = id;
    this->sprite.texture = texture;
    this->sprite.fg = fg;
    this-> sprite.bg = bg;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    this->stats = stats;
}

Entity::Entity(Entity &e) {
    this->entityId = e.entityId;
    this->sprite = e.sprite;
    this->isPassable = e.isPassable;
    this->isVisable = e.isVisable;
    if (e.stats != nullptr){
        this->stats = new Status;
        this->stats->health = e.stats->health;
        this->stats->mana = e.stats->mana;
        this->stats->stamina = e.stats->stamina;
        this->stats->strength = e.stats->strength;
        this->stats->dexterity = e.stats->dexterity;
        this->stats->maxHealth = e.stats->maxHealth;
        this->stats->maxMana = e.stats->maxMana;
        this->stats->maxStamina = e.stats->maxStamina;
        this->stats->maxStrength = e.stats->maxStrength;
        this->stats->maxDexterity = e.stats->maxDexterity;
    }
    else {
        this->stats = nullptr;
    }
}

Entity::~Entity() {

    if (stats != nullptr)
        delete stats;

}

//Setter fucntions
void Entity::SetSprite(Sprite sprite) {
    this->sprite = sprite;
}

void Entity::SetisPassable(bool isPassable) {
    this->isPassable = isPassable;
}

void Entity::SetisVisable(bool isVisable) {
    this->isVisable = isVisable;
}

void Entity::SetHealth(float health) {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return;
    }
    stats->health = health;
}

void Entity::SetMana(float mana) {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return;
    }
    stats->mana = mana;
}

void Entity::SetStrength(float strength) {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return;
    }
    stats->strength = strength;
}

void Entity::SetDexterity(float dexterity) {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return;
    }
    stats->dexterity = dexterity;
}

void Entity::SetStamina(float stamina) {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return;
    }
    stats->stamina = stamina;
}

void Entity::SetStats(Status* stats) {
    this->stats = stats;
}

;void Entity::SetForeground(Colors color) {
    sprite.fg = color;
}

void Entity::SetBackground(Colors color) {
    sprite.bg = color;
}

void Entity::SetMaxHealth(float health) {
    if (stats == nullptr)
        return ;
    if (health < 1)
        health = 1;
    else
        stats->maxHealth = health;
}

void Entity::SetMaxMana(float mana) {
    if (stats == nullptr)
        return ;
    if (mana < 0)
        mana = 0;
    else
        stats->maxMana = mana;
}

void Entity::SetMaxStamina(float stamina) {
    if (stats == nullptr)
        return ;
    if (stamina < 0)
        stamina = 0;
    else
        stats->stamina = stamina;
}

void Entity::SetMaxStrength(float strength) {
    if (stats == nullptr)
        return;
    if(strength < 0)
        strength = 0;
    else
        stats->strength = strength;
}

void Entity::SetMaxDexterity(float dexterity) {
    if(stats == nullptr)
        return;
    if(dexterity < 0)
        dexterity = 0;
    else
        stats->maxDexterity = dexterity;
}

void Entity::SetEntityId(unsigned long id) {
    this->entityId = id;
}


//Getter fucntions
const Sprite Entity::GetSprite() {
    return this->sprite;
}

const bool Entity::GetisPassable() {
    return this->isPassable;
}

const bool Entity::GetisVisable() {
    return this->isVisable;
}

const Status* Entity::GetStats() {
    if (stats == nullptr)
        std::cout << "stats where not initialized!" << std::endl;
    return stats;
}

const std::string Entity::GetFg() {
    return GetColor(true, this->sprite);
}

const std::string Entity::GetBg() {
    return GetColor(false, this->sprite);
}

const std::string Entity::GetTexture() {
    return sprite.texture;
}

const unsigned long Entity::GetId() {
    return entityId;
}


void Entity::TogglePassable() {
    if (isPassable)
        isPassable = false;
    else
        isPassable = true;
}

void Entity::ToggleVisable() {
    if (this->isVisable)
        isVisable = false;
    else
        isVisable = true;
}


void Entity::ChangeHealth(float health) {
    if (stats == nullptr)
        return;
    if (stats->health + health < 0)
        stats->health = 0;
    else
        stats->health += health;
}

void Entity::ChangeMana(float mana) {
    if (stats == nullptr)
        return;
    if (stats->mana + mana < 0)
        stats->mana = 0;
    else
        stats->mana += mana;
}

void Entity::ChangeStrength(float strength) {
    if (stats == nullptr)
        return;
    if (stats->strength + strength < 0)
        stats->strength = 0;
    else
        stats->strength += strength;
}

void Entity::ChangeDexterity(float dexterity) {
    if (stats == nullptr)
        return;
    if (stats->dexterity + dexterity < 0)
        stats->dexterity = 0;
    else
        stats->dexterity += dexterity;
}

void Entity::ChangeStamina(float stamina) {
    if (stats == nullptr)
        return;
    if (stats->stamina + stamina < 0)
        stats->stamina = 0;
    else
        stats->stamina += stamina;
}

void Entity::ChangeMaxHealth(float health) {
    if (stats == nullptr)
        return;
    if (stats->maxHealth + health < 1)
        stats->maxHealth = 1;
    else
        stats->maxHealth += health;
}

void Entity::ChangeMaxMana(float mana) {
    if (stats == nullptr)
        return;
    if (stats->maxMana + mana < 0)
        stats->maxMana = 0;
    else
        stats->maxMana += mana;
}

void Entity::ChangeMaxStamina(float stamina) {
    if (stats == nullptr)
        return;
    if (stats->maxStamina + stamina < 0)
        stamina = 0;
    else
        stats->maxStamina += stamina;
}

void Entity::ChangeMaxStrength(float strength) {
    if (stats == nullptr)
        return;
    if (stats->maxStrength + strength < 0)
        stats->maxStrength = 0;
    else
        stats->maxStrength += strength;
}

void Entity::ChangeMaxDexterity(float dexterity) {
    if (stats == nullptr)
        return;
    if (stats->maxDexterity + dexterity < 0)
        stats->maxDexterity = 0;
    else
        stats->maxDexterity += dexterity;
}
