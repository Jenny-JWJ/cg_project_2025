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
    //Insert door
    elements.emplace_back(UtilsStructs::createElement("door_"+ instanceNumber,"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;
    //elements.emplace_back(UtilsStructs::createElement("door_frame_"+ instanceNumber,"door_frame",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 3.8f})); instanceNumber++;
    //InsertWalls
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x, center.y, center.z + 4.2f}, {0,180,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x + 4.0f, center.y, center.z + 4.2f}, {0,180,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x - 4.0f, center.y, center.z + 4.2f}, {0,180,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x, center.y, center.z - 4.2f})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x + 4.0f, center.y, center.z - 4.2f})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x - 4.0f, center.y, center.z - 4.2f})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z}, {0,270,0})); instanceNumber++;
    elements.emplace_back(UtilsStructs::createElement("wall_" + instanceNumber,"wall",{"dungeon","pnois"},{center.x - 6.0f, center.y, center.z}, {0,90,0})); instanceNumber++;
    //elements.emplace_back(UtilsStructs::createElement("house_" + instanceNumber,"bldg1",{"dungeon","pnois"},{center.x , center.y, center.z}, {90,0,0})); instanceNumber++;

    return elements;
}

};

#endif //E09_INTERIORMANAGER_HPP
