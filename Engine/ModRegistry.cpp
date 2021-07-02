#include "ModRegistry.h"
#include "Item/Item.h"
#include "V4Core.h"
#include <algorithm>
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
                    Mod new_mod;
                    new_mod.path = folder;

                    json mod_info;
                    mod_file >> mod_info;

                    try
                    {
                        new_mod.name = mod_info["name"];
                    } catch (const std::exception& e)
                    {
                        new_mod.name = "No Data";
                    }
                    try
                    {
                        new_mod.author = mod_info["author"];
                    } catch (const std::exception& e)
                    {
                        new_mod.author = "No Data";
                    }
                    try
                    {
                        new_mod.version = mod_info["version"];
                    } catch (const std::exception& e)
                    {
                        new_mod.version = "1.0.0";
                    }

					std::vector<std::string> langs;
					std::ifstream mod_lang_data(folder + "/lang/lang.json", std::ios::in);
					if (mod_lang_data.good())
					{
						json lang_data;
						mod_lang_data >> lang_data;

						for (const auto& lang_name : lang_data)
						{
							langs.push_back(lang_name);
						}
					}

					if(!langs.empty())
					{
						std::unordered_map<std::string, std::wstring> string_map;
						std::string desired_lang = std::string(config->GetLanguageName().begin(), config->GetLanguageName().end());

						if(auto i = find(langs.begin(), langs.end(), desired_lang); i != langs.end())
						{
							std::string lang_name = langs[i - langs.begin()];
							
							std::ifstream lang_data(folder + "/lang/" + lang_name + ".json");
							if (lang_data.good())
							{
								json strings;

								lang_data >> strings;

								for(auto it = strings.begin(); it != strings.end(); ++it)
								{
									std::string key = it.key();
									std::string val = it.value();
									std::wstring value = std::wstring(val.begin(), val.end());
									string_map.insert(std::pair(key, value));
								}

								new_mod.string_map = string_map;
							} else
							{
								spdlog::error("Could not load lang file.");
							}
						}
						
					}

                    std::ifstream mod_worldmap_data(folder + "/missions/worldmap.dat", std::ios::in);
                    if (mod_worldmap_data.good())
                    {
                        json worldmap_data;
                        mod_worldmap_data >> worldmap_data;

                        new_mod.worldmap_data = worldmap_data;
                    }

                    std::ifstream mod_item_data(folder + "/data/item_data.json", std::ios::in);
                    if (mod_item_data.good())
                    {
                        json item_data;
                        mod_item_data >> item_data;

                        new_mod.item_data = item_data;
                    }

                    spdlog::info("Loaded mod: {} by {}, version {}", new_mod.name, new_mod.author, new_mod.version);

                    mods.push_back(new_mod);
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
            for (auto it = category.begin(); it != category.end(); ++it) // do this to get key (i.e. what type the items are)
            {
				const auto& type = it.value();

				if(type == "details") // Whoops
				{
					continue;
				}

                for (const auto& item : type)
                {
                    if (item.is_object())
                    {
                        Item* new_item = new Item();

						std::string item_category = "nodata";
                        bool isEquipment = false;

						if (auto i = category.find("details"); i != category.end())
						{
							if (auto o = category["details"].find("category"); o != category["details"].end())
							{
								item_category = category["details"]["category"];
							}
							if (auto o = category["details"].find("equipment"); o != category["details"].end())
							{
								isEquipment = category["details"]["equipment"];
							}
						}
						new_item->item_category = item_category;

						new_item->item_type = it.key();

						std::string item_name = "item_stone";
						if (auto i = item.find("name"); i != item.end())
						{
							item_name = item["name"];
						}
						new_item->item_name = item_name;

						std::string item_desc = "desc_stone";
						if (auto i = item.find("desc"); i != item.end())
						{
							item_desc = item["desc"];
						}
						new_item->item_description = item_desc;

						std::string icon_path = "stone";
						if (auto i = item.find("icon"); i != item.end())
						{
							icon_path = item["icon"];
						}
						new_item->icon_path = icon_path;

						std::string spritesheet = "main";
						if (auto i = item.find("item_group"); i != item.end())
						{
							spritesheet = item["item_group"];
						}
						new_item->spritesheet = spritesheet;

						int spritesheet_id = 1;
						if (auto i = item.find("item_id"); i != item.end())
						{
							spritesheet_id = item["item_id"];
						}
						new_item->spritesheet_id = spritesheet_id;

						int priority = 1;
						if (auto i = item.find("priority"); i != item.end())
						{
							priority = item["priority"];
						}
						new_item->priority = priority;

                        if (isEquipment)
                        {
                            new_item->equip = new Equipment();

							int hp = 0;
							if (auto i = item.find("hp"); i != item.end())
							{
								hp = item["hp"];
							}
							new_item->equip->hp = hp;

							int min_dmg = 0;
							if (auto i = item.find("min_dmg"); i != item.end())
							{
								min_dmg = item["min_dmg"];
							}
							new_item->equip->min_dmg = min_dmg;

							int max_dmg = 0;
							if (auto i = item.find("max_dmg"); i != item.end())
							{
								max_dmg = item["max_dmg"];
							}
							new_item->equip->max_dmg = max_dmg;

							int crit = 0;
							if (auto i = item.find("crit"); i != item.end())
							{
								crit = item["crit"];
							}
							new_item->equip->crit = crit;

							float attack_speed = 0.0F;
							if (auto i = item.find("attack_speed"); i != item.end())
							{
								attack_speed = item["attack_speed"];
							}
							new_item->equip->attack_speed = attack_speed;
                        }

                        spdlog::info("Added modded item: {}", new_item->item_name);

                        items.push_back(new_item);
                    }
                }
            }
        }
    }
}