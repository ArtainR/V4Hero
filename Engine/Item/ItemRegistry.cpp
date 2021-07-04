#include "ItemRegistry.h"
#include "../Config.h"
#include "../Func.h"
#include "../ModRegistry.h"
#include "../SaveReader.h"
#include "../V4Core.h"
#include "Equipment.h"
#include "Item.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using namespace std;
using json = nlohmann::json; // Convenience recommended by the library

ItemRegistry::ItemRegistry()
{
}

void ItemRegistry::readItemFiles()
{
    items.clear();

    ifstream t("resources/data/item_data.json", std::ios::in);
    t >> item_data;
    for (int i = 0; i < item_data["items"].size(); i++)
    {
        for (int j = 0; j < item_data["items"][i].size(); j++)
        {
            if (item_data["items"][i][0].is_array()) // If it isn't that means the item_data.json file is old
            {
                //type_counts[i]++;
                for (int k = 0; k < item_data["items"][i][j].size(); k++)
                {
                    switch (i)
                    {
                        case 0: ///Key items
                        {
                            Item* new_item = new Item();
                            new_item->item_category = "key_items";
                            new_item->item_type = "key_item";
                            new_item->item_name = item_data["items"][i][j][k]["name"];
                            new_item->item_description = item_data["items"][i][j][k]["desc"];
                            new_item->icon_path = item_data["items"][i][j][k]["icon"];
                            new_item->spritesheet = item_data["items"][i][j][k]["item_group"];
                            new_item->spritesheet_id = item_data["items"][i][j][k]["item_id"];
							new_item->priority = item_data["items"][i][j][k]["priority"];
                            new_item->order_id.push_back(i);
                            new_item->order_id.push_back(j);
                            new_item->order_id.push_back(k);
                            items.push_back(new_item);

                            break;
                        }

                        case 1: /// Materials
                        {
                            Item* new_item = new Item();
                            new_item->item_category = "materials";
                            switch (j)
                            {
                                case 0: {
                                    new_item->item_type = "wood";
                                    break;
                                }

                                case 1: {
                                    new_item->item_type = "meat";
                                    break;
                                }

                                case 2: {
                                    new_item->item_type = "fangs";
                                    break;
                                }

                                case 3: {
                                    new_item->item_type = "bones";
                                    break;
                                }

                                case 4: {
                                    new_item->item_type = "ore";
                                    break;
                                }
                            }
                            new_item->item_name = item_data["items"][i][j][k]["name"];
                            new_item->item_description = item_data["items"][i][j][k]["desc"];
                            new_item->icon_path = item_data["items"][i][j][k]["icon"];
                            new_item->spritesheet = item_data["items"][i][j][k]["item_group"];
                            new_item->spritesheet_id = item_data["items"][i][j][k]["item_id"];
							new_item->priority = item_data["items"][i][j][k]["priority"];
                            new_item->order_id.push_back(i);
                            new_item->order_id.push_back(j);
                            new_item->order_id.push_back(k);
                            items.push_back(new_item);

                            break;
                        }

                        case 2: /// Consumables
                        {
                            Item* new_item = new Item();
                            new_item->item_category = "consumables";
                            switch (j)
                            {
                                case 0: {
                                    new_item->item_type = "potion";
                                    break;
                                }
                            }
                            new_item->item_name = item_data["items"][i][j][k]["name"];
                            new_item->item_description = item_data["items"][i][j][k]["desc"];
                            new_item->icon_path = item_data["items"][i][j][k]["icon"];
                            new_item->spritesheet = item_data["items"][i][j][k]["item_group"];
                            new_item->spritesheet_id = item_data["items"][i][j][k]["item_id"];
							new_item->priority = item_data["items"][i][j][k]["priority"];
                            new_item->order_id.push_back(i);
                            new_item->order_id.push_back(j);
                            new_item->order_id.push_back(k);
                            items.push_back(new_item);

                            break;
                        }

                        case 3: /// Weapons
                        {
                            Item* new_weapon = new Item();
                            new_weapon->item_category = "weapon";
                            switch (j)
                            {
                                case 0: {
                                    new_weapon->item_type = "spear";
                                    break;
                                }

                                case 1: {
                                    new_weapon->item_type = "sword";
                                    break;
                                }
                            }

                            new_weapon->item_name = item_data["items"][i][j][k]["name"];
                            new_weapon->item_description = item_data["items"][i][j][k]["desc"];
                            new_weapon->icon_path = item_data["items"][i][j][k]["icon"];
                            new_weapon->spritesheet = item_data["items"][i][j][k]["item_group"];
                            new_weapon->spritesheet_id = item_data["items"][i][j][k]["item_id"];
							new_weapon->priority = item_data["items"][i][j][k]["priority"];
                            new_weapon->equip = new Equipment();
                            new_weapon->equip->hp = item_data["items"][i][j][k]["hp"];
                            new_weapon->equip->min_dmg = item_data["items"][i][j][k]["min_dmg"];
                            new_weapon->equip->max_dmg = item_data["items"][i][j][k]["max_dmg"];
                            new_weapon->equip->crit = item_data["items"][i][j][k]["crit"];
                            new_weapon->equip->attack_speed = item_data["items"][i][j][k]["attack_speed"];
                            new_weapon->order_id.push_back(i);
                            new_weapon->order_id.push_back(j);
                            new_weapon->order_id.push_back(k);
                            items.push_back(new_weapon);

                            break;
                        }

                        case 4: /// Armour
                        {
                            Item* new_armour = new Item();
                            new_armour->item_category = "armor";
                            switch (j)
                            {
                                case 0: {
                                    new_armour->item_type = "shield";
                                    break;
                                }

                                case 1: {
                                    new_armour->item_type = "helm";
                                    break;
                                }

                                case 2: {
                                    new_armour->item_type = "mask";
                                    break;
                                }
                            }

                            new_armour->item_name = item_data["items"][i][j][k]["name"];
                            new_armour->item_description = item_data["items"][i][j][k]["desc"];
                            new_armour->icon_path = item_data["items"][i][j][k]["icon"];
                            new_armour->spritesheet = item_data["items"][i][j][k]["item_group"];
                            new_armour->spritesheet_id = item_data["items"][i][j][k]["item_id"];
							new_armour->priority = item_data["items"][i][j][k]["priority"];
                            new_armour->equip = new Equipment();
                            new_armour->equip->hp = item_data["items"][i][j][k]["hp"];
                            new_armour->equip->min_dmg = item_data["items"][i][j][k]["min_dmg"];
                            new_armour->equip->max_dmg = item_data["items"][i][j][k]["max_dmg"];
                            new_armour->equip->crit = item_data["items"][i][j][k]["crit"];
                            new_armour->equip->attack_speed = item_data["items"][i][j][k]["attack_speed"];
                            new_armour->order_id.push_back(i);
                            new_armour->order_id.push_back(j);
                            new_armour->order_id.push_back(k);
                            items.push_back(new_armour);

                            break;
                        }
                    }
                    //if(i != 0) // Not sure
                    //{
                    //item_counts[type_counts[i] + j]++;
                    //}
                }
            } else
            {
                spdlog::error("Old item_data.json detected");
            }
        }
    }

    spdlog::info("Vanilla items count: {}", items.size());

    if (!saveReader->thisConfig->thisCore->modReg.mods.empty())
    {
        int oldCount = items.size();
        saveReader->thisConfig->thisCore->modReg.addItems(items);
        spdlog::info("Modded items count: {}", items.size() - oldCount);
    }

    /*
    cout << "Loaded items:" << endl;
    for(int i = 0; i < items.size(); i++)
    {
        cout << "Item: " << items[i]->item_name << endl;
    }
    */
    // Use this to print out all loaded items
    /*
    cout << "Item counts:" << endl;
    for(int i = 0; i < item_counts.size(); i++)
    {
        for(int o = 0; o < item_counts[i].size(); o++)
        {
            cout << "Category:" << i << ", Type:" << o << ", Count:" << item_counts[i][o] << endl;
        }
    }
    */
    // Use this to print out all item counts
}
ItemRegistry::~ItemRegistry()
{
}

Item* ItemRegistry::getItemByID(std::vector<int> id)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->order_id == id)
        {
            return items[i];
        }
    }

    spdlog::error("Item registry failed to find item of id [{}, {}, {}]", id[0], id[1], id[2]);
}

int ItemRegistry::getCategoryIDByString(std::string item_category)
{
    if (item_category == "key_items")
        return Categories::KEY_ITEMS;
    if (item_category == "materials")
        return Categories::MATERIALS;
    if (item_category == "consumables")
        return Categories::CONSUMABLES;
    if (item_category == "weapon")
        return Categories::WEAPONS;
    if (item_category == "armor")
        return Categories::ARMOR;
	return Categories::NO_DATA;
}

Item* ItemRegistry::getItemByName(std::string name, bool lang_specific)
{
    if (lang_specific) // By e.g. Wooden Spear (won't return if comparing between languages)
    {
        string converted_name = Func::ConvertToUtf8String(saveReader->thisConfig->strRepo.GetUnicodeString(name));
        for (const auto& item : items)
        {
            if (Func::ConvertToUtf8String(saveReader->thisConfig->strRepo.GetUnicodeString(item->item_name)) == converted_name)
            {
                return item;
            }
        }
    } else // By e.g. item_wooden_spear
    {
        for (const auto& item : items)
        {
            if (item->item_name == name)
            {
                return item;
            }
        }
    }

    spdlog::error("ItemRegistry failed to find item {}", name);
}
