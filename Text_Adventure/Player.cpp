#include "Player.h"


Player::Player() {

    m_inventory.clear();
    m_inventory.shrink_to_fit();
    m_MaxInventorySize = 30;
    m_currentLayer = nullptr;

}
Player::Player(std::vector<std::vector<std::vector<Entity>>>* currentLayer, char texture, Colors fg, Colors bg, bool isPassable, bool isVisable,float health, float mana,
        float strength, float dexterity, float stamina) {

    this->sprite.texture = texture;
    this->sprite.fg = fg;
    this->sprite.bg = bg;
    this->isPassable = isPassable;
    this->isVisable = isPassable;
    if ( health < 1 && mana < 0 && strength < 0 && dexterity < 0 && stamina < 0)
        this->stats = nullptr;
    else
        this->stats = new Status(health, mana, stamina, strength, dexterity);

    this->m_currentLayer = currentLayer;
}


Player::Player(std::vector<std::vector<std::vector<Entity>>> * currentLayer, char texture, Status * stats, Colors fg, Colors bg, bool isPassable, bool isVisable) {

    this->sprite.texture = texture;
    this->sprite.fg = fg;
    this->sprite.bg = bg;
    this->isPassable = isPassable;
    this->isVisable = isVisable;
    this->stats = stats;
    this->m_currentLayer = currentLayer;

}


Player::~Player() {

}
        
//Setters
void Player::SetInventory(std::vector<Entity> inv) {
    this->m_inventory = inv;
}

void Player::SetAttachedCamera(View * cam) {
    this->m_attachedCamera = cam;
}

void Player::SetMaxInventorySize(unsigned int invSize) {
    this->m_MaxInventorySize = invSize;
}

void Player::SetCurrentLayer(std::vector<std::vector<std::vector<Entity>>> * layer) {
    this->m_currentLayer = layer;
}

//Getters
std::vector<Entity>* Player::GetInventory() {
    return &this->m_inventory;
}

View * Player::GetCamera() {
    return m_attachedCamera;
}

unsigned int Player::GetInventorySize() {
    return this->m_MaxInventorySize;
}

std::vector<std::vector<std::vector<Entity>>> * Player::GetCurrentLayer() {
    return this->m_currentLayer;
}

bool Player::MovePlayer(int x, int y) {
    if (x + this->x_Position < 0)
        x = 0;
    else if (x + this->x_Position >= this->m_currentLayer->back().size())
        x = 0;
    if (y + this->y_Position < 0)
        y = 0;
    else if (y + this->y_Position >= this->m_currentLayer->size())
        y = 0;

    this->x_Position += x;
    this->y_Position += y;
    if (!this->m_currentLayer->back().back().back().GetisPassable()) {
        this->x_Position -= x;
        this->y_Position -= y;
    } 
    else {
        this->m_currentLayer->at(this->y_Position).at(this->x_Position).push_back(this->m_currentLayer->at(this->y_Position - y).at(this->x_Position).back());
        this->m_currentLayer->at(this->y_Position - y).at(this->x_Position - x).pop_back();
        if (this->m_attachedCamera != nullptr)
            this->m_attachedCamera->Move(x, y);
    }

    if (x == 0 && y == 0)
        return false;
    else
        return true;

}