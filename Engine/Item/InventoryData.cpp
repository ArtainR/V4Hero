#include "InventoryData.h"
#include "../SaveReader.h"
#include "Item.h"
#include "ItemRegistry.h"
#include <iostream>

/** Needs some rework **/

using namespace std;

InventoryData::InventoryData()
{
}

InventoryData::~InventoryData()
{
}

Item* InventoryData::getItemByItemID(vector<int> inv_id)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (inv_id == items[i].item->order_id)
        {
            return items[i].item;
        }
    }
}

int InventoryData::getItemCountByID(vector<int> item_id)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].item->order_id == item_id)
        {
            return items[i].item_count;
        }
    }
}

int InventoryData::getInvID(std::vector<int> item_id)
{
    for (int i = 0; i < items.size(); i++)
    {
        vector<int> cur_id = items[i].item->order_id;

        if (cur_id == item_id)
        {
            return i;
        }

        return 0;
    }
}

int InventoryData::getInvID(std::string item_name)
{
    for (int i = 0; i < items.size(); i++)
    {
        std::string cur_name = items[i].item->item_name;

        if (cur_name == item_name)
        {
            return i;
        }

        return 0;
    }
}

bool InventoryData::checkItemObtained(vector<int> item_id)
{
    for (int i = 0; i < items.size(); i++)
    {
        InventoryData::InventoryItem current_item = items[i];

        if (current_item.item->order_id == item_id)
        {
            return true;
        }
    }

    return false;
}

bool InventoryData::checkItemObtained(string item_name)
{
    for (int i = 0; i < items.size(); i++)
    {
        InventoryData::InventoryItem current_item = items[i];

        if (current_item.item->item_name == item_name)
        {
            return true;
        }
    }

    return false;
}

void InventoryData::addItem(string item_name, int count)
{
    if (checkItemObtained(item_name))
    {
        items[getInvID(item_name)].item_count += count;
    } else
    {
        InventoryData::InventoryItem new_item;
        new_item.item = saveReader->itemReg.getItemByName(item_name);
        new_item.item_count = count;
        items.push_back(new_item);
    }
}
