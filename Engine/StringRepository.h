#ifndef STRINGREPOSITORY_H
#define STRINGREPOSITORY_H

#include "ModRegistry.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
class StringRepository
{
public:
    std::vector<std::string> langNames;
    std::vector<std::string> langFonts;
    std::unordered_map<std::string, std::wstring> stringMap;
    int configDebugID = 0;
    StringRepository();
    void LoadLanguageFiles(int langNum, ModRegistry* modReg);
    void LoadLanguageFile(std::ifstream* conf, ModRegistry* modReg);
	void LoadLanguages();
    std::wstring GetUnicodeString(std::wstring key);
    std::wstring GetUnicodeString(std::string key);
    std::string GetString(std::wstring key);
    std::string GetString(std::string key);
private:
    std::map<std::string, std::string> stringMap;
    std::vector<std::string> langFiles;

    void LoadLanguageFile(std::ifstream* conf);
};

#endif // STRINGREPOSITORY_H
