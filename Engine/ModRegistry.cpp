#include "ModRegistry.h"
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
