#include "ModRegistry.h"
#include "Item/Item.h"
#include "V4Core.h"
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

std::vector<std::string> get_directores(const std::string& s) // stolen from https://stackoverflow.com/questions/5043403/listing-only-folders-in-directory
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::recursive_directory_iterator(s))
    {
        if (p.is_directory())
        {
            r.push_back(p.path().string());
        }
    }
    return r;
}


ModRegistry::ModRegistry()
{
}

ModRegistry::~ModRegistry()
{
}

void ModRegistry::init(Config* thisConfig)
{
    config = thisConfig;

    modsPath = std::filesystem::current_path().string() + "/mods";
    spdlog::info("Mods path: {}", modsPath);

    loadMods();
}

void ModRegistry::loadMods()
{
    if (std::filesystem::exists(modsPath))
    {
        for (const auto& folder : get_directores(modsPath))
        {
            if (std::filesystem::exists(folder + "/mod_info.json"))
            {
                std::ifstream mod_file(folder + "/mod_info.json", std ::ios::in);

                if (mod_file.good())
                {
                    Mod tmp;
                    tmp.path = folder;
                    spdlog::info("Mod path: {}", folder);

                    json mod_info;
                    mod_file >> mod_info;

                    try
                    {
                        tmp.name = mod_info["name"];
                    } catch (const std::exception& e)
                    {
                        tmp.name = "No Data";
                    }
                    try
                    {
                        tmp.author = mod_info["author"];
                    } catch (const std::exception& e)
                    {
                        tmp.author = "No Data";
                    }
                    try
                    {
                        tmp.version = mod_info["version"];
                    } catch (const std::exception& e)
                    {
                        tmp.version = "1.0.0";
                    }

                    std::ifstream mod_worldmap_data(folder + "/missions/worldmap.dat", std::ios::in);
                    if (mod_worldmap_data.good())
                    {
                        json worldmap_data;
                        mod_worldmap_data >> worldmap_data;

                        tmp.worldmap_data = worldmap_data;
                    }

                    std::ifstream mod_item_data(folder + "/data/item_data.json", std::ios::in);
                    if (mod_item_data.good())
                    {
                        json item_data;
                        mod_item_data >> item_data;

                        tmp.item_data = item_data;
                    }

                    spdlog::info("Loaded mod: {} by {}, version {}", tmp.name, tmp.author, tmp.version);

                    mods.push_back(tmp);
                }
            }
        }
    } else
    {
        spdlog::info("No mods to load");
    }
}

json ModRegistry::addModMissions(json worldData)
{
    for (auto& mod : mods)
    {
        for (auto& mission : mod.worldmap_data)
        {
            mission["mission_path"] = mod.path + "/missions/";
            worldData.push_back(mission);
        }
    }

    return worldData;
}

void ModRegistry::addItems(std::vector<Item*>& items)
{
    for (const auto& mod : mods)
    {
        for (const auto& category : mod.item_data)
        {
            for (const auto& type : category)
            {
                for (const auto& item : type)
                {
                    if (item.is_object())
                    {
                        Item* tmp = new Item();

                        bool isEquipment;

                        try
                        {
                            tmp->item_category = category[0];
                        } catch (const std::exception& e)
                        {
                            tmp->item_category = "nodata";
                        }
                        try
                        {
                            isEquipment = category[1];
                        } catch (const std::exception& e)
                        {
                            isEquipment = false;
                        }
                        try
                        {
                            tmp->item_type = type[0];
                        } catch (const std::exception& e)
                        {
                            tmp->item_type = "nodata";
                        }

                        try
                        {
                            tmp->item_name = item["name"];
                        } catch (const std::exception& e)
                        {
                            tmp->item_name = "item_stone";
                        }
                        try
                        {
                            tmp->item_description = item["desc"];
                        } catch (const std::exception& e)
                        {
                            tmp->item_description = "desc_stone";
                        }
                        try
                        {
                            tmp->icon_path = item["icon"];
                        } catch (const std::exception& e)
                        {
                            tmp->icon_path = "stone";
                        }
                        try
                        {
                            tmp->spritesheet = item["item_group"];
                        } catch (const std::exception& e)
                        {
                            tmp->spritesheet = "main";
                        }
                        try
                        {
                            tmp->spritesheet_id = item["item_id"];
                        } catch (const std::exception& e)
                        {
                            tmp->spritesheet_id = 1;
                        }

                        if (isEquipment)
                        {
                            tmp->equip = new Equipment();
                            try
                            {
                                tmp->equip->hp = item["hp"];
                            } catch (const std::exception& e)
                            {
                                tmp->equip->hp = 0;
                            }
                            try
                            {
                                tmp->equip->min_dmg = item["min_dmg"];
                            } catch (const std::exception& e)
                            {
                                tmp->equip->min_dmg = 0;
                            }
                            try
                            {
                                tmp->equip->max_dmg = item["max_dmg"];
                            } catch (const std::exception& e)
                            {
                                tmp->equip->max_dmg = 0;
                            }
                            try
                            {
                                tmp->equip->crit = item["crit"];
                            } catch (const std::exception& e)
                            {
                                tmp->equip->crit = 0;
                            }
                            try
                            {
                                tmp->equip->attack_speed = item["attack_speed"];
                            } catch (const std::exception& e)
                            {
                                tmp->equip->attack_speed = 0;
                            }
                        }

                        spdlog::info("Added modded item: {}", tmp->item_name);

                        items.push_back(tmp);
                    }
                }
            }
        }
    }
}