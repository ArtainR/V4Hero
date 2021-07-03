#include "StringRepository.h"
#include "ModRegistry.h"
#include "DebugOut.h"
#include "Func.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <codecvt>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

StringRepository::StringRepository()
{
    configDebugID = 0;
    ///check if config file already exists
    std::ifstream check("config.ini");
    bool exists = check.good();
    check.close();
}
void StringRepository::LoadLanguageFile(std::ifstream* conf, ModRegistry* modReg)
{
    std::vector<std::wstring> keysCheckList;
    std::locale old_locale;
    std::locale utf8_locale(old_locale, new std::codecvt_utf8<wchar_t>);
    conf->imbue(utf8_locale);


    if (conf->good())
    {
		json lang_data;

		*conf >> lang_data;

		for(auto it = lang_data.begin(); it != lang_data.end(); ++it)
		{
			std::string key = it.key();
			std::string val = it.value();
			std::wstring value = std::wstring(val.begin(), val.end());
			stringMap.insert(std::pair(key, value));
		}

		for(const auto& mod : modReg->mods)
		{
			spdlog::debug("Adding {}'s string_map to StringRepository", mod.name);
			stringMap.insert(mod.string_map.begin(), mod.string_map.end()); // Merge didn't wanna work, idk
		}
    } else
    {
		spdlog::error("Could not load lang file.");
    }

    conf->close();
}
void StringRepository::LoadLanguageFiles(int langNum, ModRegistry* modReg)
{

        std::ifstream conf2("resources/lang/" + langFiles[langNum - 1] + ".json");
		spdlog::info("Loading language file: {}", langNames[langNum - 1]);
        LoadLanguageFile(&conf2, modReg);
}

void StringRepository::LoadLanguages()
{
    std::ifstream conf("resources/lang/lang.json");

    if (conf.good())
    {
		json lang_data;

		conf >> lang_data;

		for(const auto& lang : lang_data)
		{
			langFiles.push_back(lang["lang"]);
			langNames.push_back(lang["lang"]);
			langFonts.push_back(lang["font"]);
		}
	}
	else
	{
		langFiles.push_back("English");
		langNames.push_back("English");
		langFonts.push_back("roboto.ttf");
	}
}


std::wstring StringRepository::GetUnicodeString(std::wstring key)
{
    std::string s(key.begin(), key.end());

    if (!stringMap[s].empty())
    {
        return stringMap[s];
    } else
    {
        std::string nodata = s + "__no_data";
        return std::wstring(nodata.begin(), nodata.end());
    }
}

std::wstring StringRepository::GetUnicodeString(std::string key)
{
    if (!stringMap[key].empty())
    {
        return stringMap[key];
    } else
    {
        std::string nodata = key + "__no_data";
        return std::wstring(nodata.begin(), nodata.end());
    }
}

std::string StringRepository::GetString(std::wstring key)
{
    std::string s(key.begin(), key.end());
    std::wstring ws = stringMap[s];
    std::string o(ws.begin(), ws.end());
    return o;
}

std::string StringRepository::GetString(std::string key)
{
    std::wstring ws = stringMap[key];
    std::string s(ws.begin(), ws.end());
    return s;
}
