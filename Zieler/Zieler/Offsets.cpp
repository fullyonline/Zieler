#include "Offsets.h"
#include "json/json.h"
#include <string>
#include <Windows.h>

Offsets::Offsets() {
	// Get the location from the config.json in a windows envirement
	DWORD buffer = MAX_PATH;
	char currentDir[MAX_PATH];	
	GetCurrentDirectory(buffer, currentDir);
	//path = std::filesystem::path(currentDir += "offsetConfig.json");
	// std::string path(currentDir);
	// path += "\\Config"; // config.json from https://github.com/frk1/hazedumper
	/*
	Json::Value json;

	if (std::ifstream in{ path / "offsetConfig.json" }; in.good()) {

	}
	*/
}