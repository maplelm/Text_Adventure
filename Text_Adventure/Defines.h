#pragma once

#define VIEW_HEIGHT 25
#define VIEW_WIDTH 50

// defining common entitys
#define AIR_ENTITY Entity air(' ',nullptr,Colors::blue, Colors::blue, true,true)
#define GRASS_ENTITY Entity  grass(' ',nullptr,Colors::green, Colors::green, true,  true)
#define DIRT_ENTITY Entity dirt('#',nullptr,Colors::brown, Colors::brown, false, true)
