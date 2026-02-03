//
// Created by ACER on 03/02/2026.
//

#include "DrunkEffectManager.hpp"

float DrunkEffectManager::timer = 0.0f;
bool DrunkEffectManager::isDrunk = false;
std::vector<glm::vec3> DrunkEffectManager::bottles{};