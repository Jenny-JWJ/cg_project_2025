//
// Created by ACER on 15/11/2025.
//

#include "MapManager.hpp"

std::map<std::string,std::string> MapManager::modelsPaths = {};
std::map<std::string,std::string> MapManager::texturePaths = {};
std::string MapManager::jsonPath = "";
std::mt19937_64 MapManager::gen(123456);
bool MapManager::debug;
