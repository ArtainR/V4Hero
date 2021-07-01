#ifndef MODREGISTRY_H
#define MODREGISTRY_H

#include "Config.h"
#include <nlohmann/json.hpp>

class ModRegistry
{
	public:
		struct Mod
		{
			std::string path;
			std::string name;
			std::string author;
			std::string version;
			nlohmann::json items;
			nlohmann::json worldmap_data;
		};

		std::vector<Mod> mods;

		ModRegistry();
		~ModRegistry();
		void init(Config* thisConfig);
		nlohmann::json addModMissions(nlohmann::json worldData);

	private:
		Config* config;

		std::string modsPath;

		void loadMods();
};


#endif // MODREGISTRY_H