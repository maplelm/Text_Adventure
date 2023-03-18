#include "Player.h"


Player::Player() {

    m_inventory.clear();
    m_inventory.shrink_to_fit();
    m_MaxInventorySize = 30;

}

Player::Player(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina) {

}

Player::Player(char texture, bool isPassable, bool isVisable, float health, float mana, float strength, float dexterity, float stamina) {

}

Player::Player(char texture, Colors fg, Colors bg, bool isPassable, bool isVisable, Status* stats) {

}

Player::Player(char texture, bool isPassable, bool isVisable, Status* stats) {

}

Player::Player(char texture) {

}

Player::~Player() {

}
        
//Setters
void Player::SetInventory(std::vector<Entity> inv) {

}

void Player::SetAttachedCamera(View * cam) {

}

void Player::SetMaxInventorySize(unsigned int invSize) {

}
