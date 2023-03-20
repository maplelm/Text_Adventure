#pragma once

#define VIEW_HEIGHT 25
#define VIEW_WIDTH 50

// defining common entitys
#define AIR_ENTITY Entity(" ",nullptr,Colors::blue, Colors::blue, true,true)
#define GRASS_ENTITY Entity(" ",nullptr,Colors::black, Colors::green, true,  true)
#define DIRT_ENTITY Entity("#",nullptr,Colors::brown, Colors::brown, false, true)
#define TREE_ENTITY Entity("t",nullptr,Colors::green, Colors::none, false, true)
#define SILT_ENTITY Entity("#", nullptr,Colors::silver, Colors::brown, false, true)
#define IRON_ENTITY Entity("#", nullptr,Colors::darkred, Colors::brown, false, true)
