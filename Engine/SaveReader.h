#ifndef SAVEREADER_H
#define SAVEREADER_H
#include "DebugOut.h"
#include "Item/InventoryData.h"
#include "Item/ItemRegistry.h"
#include "Pon/PonRegistry.h"
#include "StringRepository.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
class SaveReader
{
public:
    ItemRegistry itemReg;
    PonRegistry ponReg;
    InventoryData invData;

    nlohmann::json save_data;

    sf::String kami_name;
    int times_launched;
    bool hero_unlocked = false;

    std::vector<int> missions_unlocked = {1};
    int locations_unlocked = 1;
    std::map<int, int> mission_levels; // Storing the mission level

    std::string save_ver = "2.0";

    SaveReader();
    void LoadSave(Config& tconfig);
    void Flush();
    void CreateBlankSave();
    DebugOut* debugOut;
    Config* thisConfig;
    bool isNewSave;
    void Save();
    bool isMissionUnlocked(int mission);
};

#endif // SAVEREADER_H
