#ifndef MODREGISTRY_H
#define MODREGISTRY_H

#include "Item/Item.h"
#include <filesystem>
#include <nlohmann/json.hpp>

class Config;
class ModRegistry
{
public:
    struct Mod {
        std::filesystem::path path;
        std::string name;
        std::string author;
        std::string version;
		std::string prefix;
        nlohmann::json item_data;
        nlohmann::json worldmap_data;
		std::vector<std::filesystem::path> resources;
		std::unordered_map<std::string, std::wstring> string_map;
    };

    std::vector<Mod> mods;

    ModRegistry();
    ~ModRegistry();
	void init(Config* thisConfig);
    nlohmann::json addModMissions(nlohmann::json worldData);
	std::filesystem::path getOverwritten(std::filesystem::path);
    void addItems(std::vector<Item*>& items);

private:
    Config* config;

    std::string modsPath = "mods";

    void loadMods();
};


#endif // MODREGISTRY_H