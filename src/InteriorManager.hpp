//
// Created by ACER on 24/01/2026.
//

#ifndef E09_INTERIORMANAGER_HPP
#define E09_INTERIORMANAGER_HPP

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <map>
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
        DoubleConnectionFromRight,
        DoubleConnectionFromLeft,
        LShaped,
        HighLShapedFirstFloor,
        HighLshapedSecondFloor,
        SecretBasement
    };

    struct SpawnPosition{
        glm::vec3 position;
        glm::vec2 rotation;
    };

    static std::map<HouseTemplate, SpawnPosition> spawnPositions; //{template, position w.r.t the center, camera rotation(Yaw, Pitch)}

    static glm::vec3 offset;

    static int instanceNumber;

    static std::vector<IMElement> CreateBaseHouseTemplate(glm::vec3 center){

        std::vector<IMElement> elements;

        //Door
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

        //Windows
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z + 2}, {0,90,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z - 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z - 2}, {0,90,0}, {0.5,0.5,1}));  instanceNumber++;

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
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

        //Floor
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

        //Roof
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;


        return elements;
    }

    static std::vector<IMElement> CreateHighBaseHouseFirstFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z + 2}, {0,90,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z - 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z - 2}, {0,90,0}, {0.5,0.5,1}));  instanceNumber++;

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
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x - 4.0f, center.y + 3.05f, center.z},{270,0,0}, {1,1,2})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},{270,0,0}, {1,1,2})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x - 4.0f, center.y, center.z + 1},{0,0,0}, {2, 1.5, 1.5f})); instanceNumber++;

            return elements;
        }

    static std::vector<IMElement> CreateHighBaseHouseSecondFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;

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
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x, center.y - 5, center.z},{90,0,0}, {50, 50, 50})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3.05f, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},{180,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x - 4.0f, center.y - 3, center.z + 0.5f},{0,0,0}, {2.5, 1.5, 1.5f})); instanceNumber++;

            return elements;
        }

    static std::vector<IMElement> CreateDoubleFirstFloorLeftTemplate(glm::vec3 center){

        std::vector<IMElement> elements;

        //Door
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x + 5.5f, center.y, center.z + 0.6f}, {0,90,0}));  instanceNumber++;

        //Windows
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z - 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;

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
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
        //elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

        //Floor
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

        //Roof
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x - 4.0f, center.y + 3.05f, center.z},{270,0,0}, {1,1,2})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},{270,0,0}, {1,1,2})); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

        //Stairs
        elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x - 4.0f, center.y, center.z + 1},{0,0,0}, {2, 1.5, 1.5f})); instanceNumber++;

        return elements;
    }

    static std::vector<IMElement> CreateDoubleFirstFloorRightTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 5.5f, center.y, center.z + 0.6f}, {0,90,0}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 4, center.y + 1.5f, center.z - 3.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 4, center.y + 1.5f, center.z - 3.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z + 2}, {0,90,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z - 2}, {0,90,0}, {0.5,0.5,1}));  instanceNumber++;

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
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z -4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x + 4.0f, center.y + 3.05f, center.z},{270,0,0}, {1,1,2})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x + 4.0f, center.y +  3.05f, center.z + 4.0f},{270,0,0}, {1,1,2})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x + 4.0f, center.y, center.z - 1},{0,180,0}, {2, 1.5, 1.5f})); instanceNumber++;

            return elements;
        }

    static std::vector<IMElement> CreateDoubleSecondFloorLeftTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z - 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;

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
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

        //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x, center.y - 5, center.z},{90,0,0}, {50, 50, 50})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3.05f, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},{180,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x - 4.0f, center.y - 3, center.z + 0.5f},{0,0,0}, {2.5, 1.5, 1.5f})); instanceNumber++;

            return elements;
        }

    static std::vector<IMElement> CreateDoubleSecondFloorRightTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z - 3.8f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 5.5f, center.y + 1.5f, center.z - 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;

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
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z + 4.2f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 2.0f, center.y, center.z - 4.2f}, {90,0,0})); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 6.0f, center.y, center.z}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 6.0f, center.y, center.z}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z + 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z + 3.9f}, {90,90,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 5.9f, center.y, center.z - 3.9f}, {90,270,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x - 5.9f, center.y, center.z - 3.9f}, {90,90,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z + 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z + 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y, center.z - 4.0f}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y, center.z - 4.0f},{0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x, center.y - 5, center.z},{90,0,0}, {50, 50, 50})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3.05f, center.z},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z + 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},{180,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x - 4.0f, center.y - 3, center.z - 0.5f},{0,180,0}, {2.5, 1.5, 1.5f})); instanceNumber++;

            return elements;
        }

    static std::vector<IMElement> ConnectingBridgeFromRight(glm::vec3 center){

        std::vector<IMElement> elements;

        //Door
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 2.5f}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z - 2.5f}));  instanceNumber++;


        //Windows
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 0.9f, center.y + 1.5f, center.z + 1}, {0,90,0}, {0.5,0.5,0.3}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 0.9f, center.y + 1.5f, center.z - 1}, {0,90,0}, {0.5,0.5,0.3}));  instanceNumber++;

        //Floor and walls
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"tunnel",{"dungeon","pnois"},{center.x, center.y, center.z}, {0,0,0}, {1,1.5f,1.5})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x, center.y, center.z - 3}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x, center.y, center.z + 3}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

        //Roof
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 2.5f, center.z}, {180,0,0}, {1,1,1.5})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 2.6f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;
        return elements;
    }

    static std::vector<IMElement> ConnectingBridgeFromLeft(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z + 2.5f}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 0.5f, center.y, center.z - 2.5f}));  instanceNumber++;


            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 0.9f, center.y + 1.5f, center.z + 1}, {0,90,0}, {0.5,0.5,0.3}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 0.9f, center.y + 1.5f, center.z - 1}, {0,90,0}, {0.5,0.5,0.3}));  instanceNumber++;

            //Floor and walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"tunnel",{"dungeon","pnois"},{center.x, center.y, center.z}, {0,0,0}, {1,1.5f,1.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x, center.y, center.z - 3}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x, center.y, center.z + 3}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y - 0.1f, center.z},{90,0,0}, {10, 1, 10})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 2.5f, center.z}, {180,0,0}, {1,1,1.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 2.6f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;
            return elements;
        }

    static std::vector<IMElement> CreateLShapedTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x + 9.5f, center.y, center.z + 7.7f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 14, center.y + 1.5f, center.z + 7.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 15.6f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 15.6f, center.y + 1.5f, center.z + 6}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 7.6f, center.y + 1.5f, center.z + 10}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 7.6f, center.y + 1.5f, center.z + 14}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 2, center.y + 1.5f, center.z + 15.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 6, center.y + 1.5f, center.z + 15.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;

        //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 2.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 10.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 14.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 2.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 6.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 10.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 14.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 10.0f, center.y, center.z + 8.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 14.0f, center.y, center.z + 8.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z + 16.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 2.0f, center.y, center.z + 16.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 8.1f, center.y, center.z + 10.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 8.1f, center.y, center.z + 14.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 16.1f, center.y, center.z + 6.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 16.1f, center.y, center.z + 2.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;

            //Pillars

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 0.1f, center.y, center.z + 0.1f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 4, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 12, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 15.9f, center.y, center.z + 0.1f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x  + 16, center.y, center.z + 4.0f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 15.9f, center.y, center.z + 7.9f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 8.3f, center.y, center.z + 8.3f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x , center.y, center.z + 4}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x , center.y, center.z + 12}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 0.1f, center.y, center.z + 15.9f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x  + 4, center.y, center.z + 16.0f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 7.9f, center.y, center.z + 15.9f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 8, center.y, center.z + 12.0f}, {90,180,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 10}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 14}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 10}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 14}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y, center.z + 6}, {0,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x + 10, center.y - 0.1f, center.z + 10},{90,0,0}, {10, 1, 10})); instanceNumber++;


            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 10}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 14}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 10}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 14}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x + 10, center.y + 3.1f, center.z + 10},{270,0,0}, {10, 1, 10})); instanceNumber++;


        return elements;
        }

    static std::vector<IMElement> CreateHighLShapedFirstFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x + 11.5f, center.y, center.z + 7.7f}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x + 4.5f, center.y, center.z + 15.7f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 7.6f, center.y + 1.5f, center.z + 10}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 2.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 10.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 14.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 2.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 6.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 10.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 14.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 10.0f, center.y, center.z + 8.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 14.0f, center.y, center.z + 8.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z + 16.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 2.0f, center.y, center.z + 16.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 8.1f, center.y, center.z + 10.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 8.1f, center.y, center.z + 14.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 16.1f, center.y, center.z + 6.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 16.1f, center.y, center.z + 2.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;

            //Pillars

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 0.1f, center.y, center.z + 0.1f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 4, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 12, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 15.9f, center.y, center.z + 0.1f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x  + 16, center.y, center.z + 4.0f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 15.9f, center.y, center.z + 7.9f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 8.3f, center.y, center.z + 8.3f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x , center.y, center.z + 4}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x , center.y, center.z + 12}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 0.1f, center.y, center.z + 15.9f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x  + 4, center.y, center.z + 16.0f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 7.9f, center.y, center.z + 15.9f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 8, center.y, center.z + 12.0f}, {90,180,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 10}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 14}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 10}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 14}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y, center.z + 6}, {0,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x + 10, center.y - 0.1f, center.z + 10},{90,0,0}, {10, 1, 10})); instanceNumber++;


            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x + 2, center.y + 3.1f, center.z + 6}, {270,0,0}, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x + 2, center.y + 3.1f, center.z + 10}, {270,0,0}, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 14}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 10}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 14}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x + 10, center.y + 3.2f, center.z + 10},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x + 2, center.y, center.z + 6.05f},{0,180,0}, {2.5, 1.5, 2.0f})); instanceNumber++;


        return elements;
        }

    static std::vector<IMElement> CreateHighLShapedSecondFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;


            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 14, center.y + 1.5f, center.z + 7.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 15.6f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 15.6f, center.y + 1.5f, center.z + 6}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 7.6f, center.y + 1.5f, center.z + 10}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 7.6f, center.y + 1.5f, center.z + 14}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 2, center.y + 1.5f, center.z + 15.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 6, center.y + 1.5f, center.z + 15.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 10, center.y + 1.5f, center.z + 7.7f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 2.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 10.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 14.0f, center.y, center.z - 0.1f}, {0,0,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 2.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 6.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 10.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x - 0.1f, center.y, center.z + 14.0f}, {0,90,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 10.0f, center.y, center.z + 8.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 14.0f, center.y, center.z + 8.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 6.0f, center.y, center.z + 16.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 2.0f, center.y, center.z + 16.1f}, {0,180,0}, {1,1.5f,1})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 8.1f, center.y, center.z + 10.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 8.1f, center.y, center.z + 14.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 16.1f, center.y, center.z + 6.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",{"dungeon","pnois"},{center.x + 16.1f, center.y, center.z + 2.0f}, {0,270,0}, {1,1.5f,1})); instanceNumber++;

            //Pillars

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 0.1f, center.y, center.z + 0.1f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 4, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 12, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 15.9f, center.y, center.z + 0.1f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x  + 16, center.y, center.z + 4.0f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 15.9f, center.y, center.z + 7.9f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 8.3f, center.y, center.z + 8.3f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x, center.y, center.z}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x , center.y, center.z + 4}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x , center.y, center.z + 12}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 0.1f, center.y, center.z + 15.9f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x  + 4, center.y, center.z + 16.0f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 7.9f, center.y, center.z + 15.9f}, {90,180,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 8, center.y, center.z + 12.0f}, {90,180,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",{"tex_nature_atlas_1","pnois"},{center.x + 12, center.y, center.z + 8}, {90,180,0})); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 10}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y, center.z + 14}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y, center.z + 2}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 10}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y, center.z + 14}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y, center.z + 6}, {0,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y, center.z + 6}, {0,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"black","pnois"},{center.x + 10, center.y - 5, center.z + 10},{90,0,0}, {50, 50, 50})); instanceNumber++;


            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3.1f, center.z + 6}, {0,0,0}, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3.1f, center.z + 10}, {0,0,0}, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 2, center.y + 3, center.z + 14}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y + 3, center.z + 2}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 10}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 6, center.y + 3, center.z + 14}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 10, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 14, center.y + 3, center.z + 6}, {180,0,0})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x + 10, center.y + 3.2f, center.z + 10},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x + 2, center.y - 3, center.z + 6.05f},{0,180,0}, {2.5, 1.5, 2.0f})); instanceNumber++;


            return elements;
        }

    static void Initialize(){
        spawnPositions = {
                {Base, {{0,0,3.1}, {0,0}}},
                {HighBaseFirstFloor, {{0,0,3.1}, {0,0}}},
                {HighBaseSecondFloor, {{-1.7,0,-2.8}, {-1.6,0}}},
                {DoubleFirstFloorRight, {{-4.8,0,0}, {-1.6,0}}},
                {DoubleSecondFloorRight, {{-1.4,0,3.2}, {0,0}}},
                {DoubleFirstFloorLeft, {{4.8,0,0}, {1.5,0}}},
                {DoubleSecondFloorLeft, {{-1.4,0,-3.2}, {4.6,0}}},
                {DoubleConnectionFromRight, {{0,0,-2}, {3,0}}},
                {DoubleConnectionFromLeft, {{0,0,-2}, {3,0}}},
                {LShaped, {{10,0,7}, {0,0}}},
                {HighLShapedFirstFloor, {{10,0,7}, {0,0}}},
                {HighLshapedSecondFloor, {{2.1,0,12.5}, {3,0}}},
                {SecretBasement, {{0,0,0}, {0,0}}},
        };
    }
};

#endif //E09_INTERIORMANAGER_HPP
