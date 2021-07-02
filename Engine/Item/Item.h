#ifndef ITEM_H
#define ITEM_H
#include "Equipment.h"
#include <SFML/Graphics.hpp>
class Item
{
public:
    std::string item_category;
    std::string item_type;
    std::vector<int> order_id;
    std::string item_name;
    std::string item_description;
    std::string icon_path;
	int priority;
    std::string spritesheet = "none";
    int spritesheet_id = -1;
    Equipment* equip; // This isn't good but it's the best I've got rn
};

#endif // ITEM_H
