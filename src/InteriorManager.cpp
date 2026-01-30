//
// Created by ACER on 24/01/2026.
//

#include "InteriorManager.hpp"
#include "RoomManager.hpp"

std::map<InteriorManager::HouseTemplate, std::vector<InteriorManager::SpawnPosition>> InteriorManager::spawnPositions = {
        {Base,                   {{{0,    0, 3.1},  {0,    0}}}},
        {HighBaseFirstFloor,     {{{0,    0, 3.1},  {0,    0}}, {{-4,0,1}, {3,0.5}}}},
        {HighBaseSecondFloor,    {{{-1.7, 0, -2.8}, {-1.6, -0.5}}}},
        {DoubleFirstFloorRight,  {{{-4.8, 0, 0},    {-1.6, 0}}, {{4,0,-1}, {0,0.5}}}},
        {DoubleSecondFloorRight, {{{-1.4, 0, 3.2},  {-1.6, -0.5}}, {{0,0,-3}, {3,0}}}},
        {DoubleFirstFloorLeft,   {{{4.8,  0, 0},    {1.5,  0}}, {{-4,0,1}, {3,0.5}}}},
        {DoubleSecondFloorLeft,  {{{-1.4, 0, -3.2}, {4.6,  -0.5}}, {{0,0,3}, {0,0}}}},
        {DoubleConnection,       {{{0,    0, -1.8}, {3,    0}}, {{0,0,1.8}, {0,0}}}},
        {LShaped,                {{{10,   0, 6.5},  {0,    0}}}},
        {HighLShapedFirstFloor,  {{{12,   0, 6.5},  {0,    0}},{{2,0,6}, {0,0.5}}}},
        {HighLShapedSecondFloor, {{{2,    0, 12.5}, {3,    -0.5}}}},
        {SecretBasement,         {{{0,    0, 0},    {0,    0}}}},
};

int InteriorManager::instanceNumber = 0;

int InteriorManager::AddRoom(InteriorManager::HouseTemplate tmp) {
    return RoomManager::AddRoom(tmp);
}

void InteriorManager::AddTeleporter(glm::vec3 spawnPos, glm::vec2 spawnDir,TeleporterList::TeleportUse tpUse, int roomId){
    TeleporterList::addTeleporter(spawnPos,{1,1,1},spawnDir + glm::vec2(3,0),spawnPos,spawnDir, tpUse, roomId);
}

std::vector<IMElement>
InteriorManager::CreateHouseInteriors(glm::vec3 origin, float distance) {
    std::vector<IMElement> elements;
    glm::vec3 offset = {0,0,0};
    for (int i = 0; i < static_cast<int>(HouseTemplate::Count); ++i) {
        for (int j = 0; j <= housePerType; j++) {
            HouseTemplate value = static_cast<HouseTemplate>(i);
            auto newElements = CreateHouse(value, origin + offset);
            elements.insert(elements.end(),  newElements.begin(), newElements.end());
            offset.x += distance;
        }
        offset.z += distance;
    }
    return elements;
}

std::vector<IMElement> InteriorManager::CreateHouse(HouseTemplate tmp, glm::vec3 center){
    switch (tmp) {
        case ExternalEntrance:  return {};
        case Base: return CreateBaseHouseTemplate(center);
        case HighBaseFirstFloor: return CreateHighBaseHouseFirstFloorTemplate(center);
        case HighBaseSecondFloor: return CreateHighBaseHouseSecondFloorTemplate(center);
        case DoubleFirstFloorLeft: return CreateDoubleFirstFloorLeftTemplate(center);
        case DoubleFirstFloorRight: return CreateDoubleFirstFloorRightTemplate(center);
        case DoubleSecondFloorLeft: return CreateDoubleSecondFloorLeftTemplate(center);
        case DoubleSecondFloorRight: return CreateDoubleSecondFloorRightTemplate(center);
        case DoubleConnection: return ConnectingBridge(center);
        case LShaped: return CreateLShapedTemplate(center);
        case HighLShapedFirstFloor: return CreateHighLShapedFirstFloorTemplate(center);
        case HighLShapedSecondFloor: return CreateHighLShapedSecondFloorTemplate(center);
    }
    return {};
}
