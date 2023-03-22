#pragma once
#include "View.h"

struct MenuOption{
    MenuOption(std::string desc, void* (*func)(void**)) {
        this->description = desc;
        this->action = func;
    };
    std::string description;
    void *(*action)(void**);
};
typedef struct MenuOption MenuOption;

class Menu :
    public View
{

    std::vector<std::string> textSelectionList;
    std::vector<Entity*> entitySelectionList;

public:

    void Render() override;
};
