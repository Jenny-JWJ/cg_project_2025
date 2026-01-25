//
// Created by ACER on 24/01/2026.
//

#ifndef E09_INTERIORMANAGER_HPP
#define E09_INTERIORMANAGER_HPP

#include <stdlib.h>
#include <vector>
#include <iostream>
#include "modules/GlobalGML.hpp"
#include "UtilsStructs.hpp"

using IMElement = UtilsStructs::Element;

class InteriorManager{
public:
    enum HouseTemplate{
        Base,
        HighBaseFirstFloor,
        HighBaseSecondFloor,
        DoubleFirstFloorRight,
        DoubleSecondFloorRight,
        DoubleFirstFloorLeft,
        DoubleSecondFloorLeft,
        DoubleConnection,
        LShaped,
        HighLShapedFirstFloor,
        HighLshapedSecondFloor,
        SecretBasement
    };

    static glm::vec3 offset;
    static int instanceNumber;

static std::vector<IMElement> CreateBaseHouseTemplate(glm::vec3 center){

    std::vector<IMElement> elements;

    //Door
    elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

    //Walls
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x, center.y, center.z + 4.2f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 4.0f, center.y, center.z + 4.2f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 4.0f, center.y, center.z + 4.2f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x, center.y, center.z - 4.2f}, {0,0,0},  {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 4.0f, center.y, center.z - 4.2f}, {0,0,0},  {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 4.0f, center.y, center.z - 4.2f}, {0,0,0},  {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 6.0f, center.y, center.z}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z + 4.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 6.0f, center.y, center.z + 4.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z - 4.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 6.0f, center.y, center.z - 4.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;

    //Pillars
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"medieval_nature1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

    //Floor
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x - 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x - 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;

    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"medieval_nature1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

    //Roof
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x - 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"medieval_buildings","pnois"},{center.x - 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;

    elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"medieval_nature1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;


    return elements;
}

};

#endif //E09_INTERIORMANAGER_HPP
