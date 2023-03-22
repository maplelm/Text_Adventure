#pragma once

#define VIEW_HEIGHT 25
#define VIEW_WIDTH  50

// Defining common values to make hard coded values more readable
#define VISABLE    true
#define INVISABLE  false
#define PASSABLE   true
#define INPASSABLE false
#define NO_STATS   nullptr

// Defining ENTITY IDs for hardcoded values
#define AIR_ID   1
#define GRASS_ID 2
#define DIRT_ID  3
#define TREE_ID  4
#define SILT_ID  5
#define IRON_ID  6

//Defining Colors
#define COLOR_WHITE   Colors::white
#define COLOR_BLACK   Colors::black
#define COLOR_RED     Colors::red
#define COLOR_DARKRED Colors::darkRed
#define COLOR_GREEN   Colors::green
#define COLOR_YELLOW  Colors::yellow
#define COLOR_BLUE    Colors::blue
#define COLOR_BROWN   Colors::brown
#define COLOR_SILVER  Colors::silver
#define COLOR_GOLD    Colors::gold
#define COLOR_NONE    Colors::none

// defining common entitys
#define AIR_ENTITY    new Entity(AIR_ID,   ".", NO_STATS,COLOR_BLUE,    COLOR_WHITE,  PASSABLE,   VISABLE)
#define GRASS_ENTITY  new Entity(GRASS_ID, " ", NO_STATS,COLOR_BLACK,   COLOR_GREEN, PASSABLE,   VISABLE)
#define DIRT_ENTITY   new Entity(DIRT_ID,  "#", NO_STATS,COLOR_BROWN,   COLOR_BROWN, INPASSABLE, VISABLE)
#define TREE_ENTITY   new Entity(TREE_ID,  "T", NO_STATS,COLOR_GREEN,   COLOR_NONE,  INPASSABLE,   VISABLE)
#define SILT_ENTITY   new Entity(SILT_ID,  "#", NO_STATS,COLOR_SILVER,  COLOR_BROWN, INPASSABLE, VISABLE)
#define IRON_ENTITY   new Entity(IRON_ID,  "#", NO_STATS,COLOR_DARKRED, COLOR_BROWN, INPASSABLE, VISABLE)
