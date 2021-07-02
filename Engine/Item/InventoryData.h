#ifndef INVENTORY_DATA_H
#define INVENTORY_DATA_H
#include "Item.h"
#include "ItemRegistry.h"
#include <SFML/Graphics.hpp>

class SaveReader;

class InventoryData
{
public:
    SaveReader* saveReader;
    ItemRegistry* itemReg;

    struct InventoryItem {
        Item* item;
        //string item_ench;
        //int item_level;
        int item_count;
    };
    std::vector<InventoryItem> items;
    void init(ItemRegistry* itemReg);
    Item* getItemByItemID(std::vector<int> inv_id);
    int getItemCountByID(std::vector<int> item_id);
    int getItemCountByInvID(int item_inv_id);
    int countItemsByType(std::string type);
    int getInvID(std::vector<int> item_id);
    int getInvID(std::string item_name);
    bool checkItemObtained(std::vector<int> item_id);
    bool checkItemObtained(std::string item_name);
    void addItem(std::string item_name, int count = 1);
    InventoryData();
    ~InventoryData();

    /*struct Enchantment // This should be somewhere else, like in barracks.h, here just a `string name` should be listed
    {
        int hp = 0;
        int min_dmg = 0;
        int max_dmg = 0;
        int attack_speed = 0;
        int crit = 0;
    };*/
};

#endif // INVENTORY_DATA_H
