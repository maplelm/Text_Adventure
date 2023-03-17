#pragma once

#define VIEW_HEIGHT 25
#define VIEW_WIDTH 50

// defining common entitys
#define AIR_ENTITY Entity air(' ',Colors::blue, Colors::blue, true,true,nullptr)
#define GRASS_ENTITY Entity  grass(' ', Colors::green, Colors::green, true,  true, nullptr)
#define DIRT_ENTITY Entity dirt('#', Colors::brown, Colors::brown, false, true, nullptr)
#define WIN
//#define MAC
//#define LIN
