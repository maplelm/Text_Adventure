#include "Entity.h"

// Private Functions
std::string Entity::GetColor(bool isForeground) {
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

    sprite.texture = ' ';
    sprite.fg = Colors::none;
    sprite.bg = Colors::none;
    isPassable = true;
    isVisable = true;
    stats = nullptr;

}

Entity::Entity(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina) {
    
    this->sprite.texture = texture;
    this->sprite.fg = fg;
    this->sprite.bg = bg;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    this->stats->health = health;
    this->stats->mana = mana;
    this->stats->strength = strength;
    this->stats->dexterity = dexterity;
    this->stats->stamina = stamina;
}

Entity::Entity(char texture, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina) {
    this->sprite.texture = texture;
    this->sprite.fg = Colors::none;
    this->sprite.bg = Colors::none;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    this->stats = new Status;
    this->stats->health = health;
    this->stats->mana = mana;
    this->stats->strength = strength;
    this->stats->dexterity = dexterity;
    this->stats->stamina = stamina;
}

Entity::Entity(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, Status* stats) {
    this->sprite.texture = texture;
    this->sprite.fg = fg;
    this-> sprite.bg = bg;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    this->stats = stats;
}

Entity::Entity(char texture, bool isPassable, bool isVisable, Status* stats) {
    this->sprite.texture = texture;
    this->sprite.fg = Colors::none;
    this->sprite.bg = Colors::none;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    this->stats = stats;
}

Entity::Entity(char texture) {
    this->sprite.texture = texture;
    this->sprite.fg = Colors::none;
    this->sprite.bg = Colors::none;
    isPassable = false;
    isVisable = true;
    stats = nullptr;
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

//Getter fucntions
const Sprite Entity::GetSprite() {
    return this->sprite;
}

const bool Entity::GetIsPassable() {
    return this->isPassable;
}

const float Entity::GetHealth() {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return -1;
    }
    return stats->health;
}

const float Entity::GetMana() {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return -1;
    }
    return stats->mana;
}

const float Entity::GetStrength() {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return -1;
    }
    return stats->strength;
}

const float Entity::GetDexterity() {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return -1;
    }
    return stats->dexterity;
}

const float Entity::GetStamina() {
    if (stats == nullptr) {
        std::cout << "stats where not initialized!" << std::endl;
        return -1;
    }
    return stats->stamina;
}

const Status* Entity::GetStats() {
    if (stats == nullptr)
        std::cout << "stats where not initialized!" << std::endl;
    return stats;
}

const std::string Entity::GetFg() {
    return GetColor(true);
}

const std::string Entity::GetBg() {
    return GetColor(false);
}

const char Entity::GetTexture() {
    return sprite.texture;
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

