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
#include "TeleporterList.hpp"

using IMElement = UtilsStructs::Element;

class InteriorManager{
    constexpr static const int housePerType[13] = {0, 6, 6, 6, 6, 6, 6, 6, 1, 6, 6, 6, 0};
public:
    enum HouseTemplate{
        ExternalEntrance,
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
        HighLShapedSecondFloor,
        SecretBasement,
        Count
    };

    struct SpawnPosition{
        glm::vec3 position;
        glm::vec2 rotation;
    };

    static std::map<HouseTemplate, std::vector<SpawnPosition>> spawnPositions; //{template, position w.r.t the center, camera rotation(Yaw, Pitch)}

    static glm::vec3 offset;

    static int instanceNumber;

    static int AddRoom(HouseTemplate aTemplate);

    static void AddTeleporter(glm::vec3 spawnPos, glm::vec2 spawnDir, TeleporterList::TeleportUse tpUse, int roomId);

    //House Template
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

        std::vector<IMElement> layoutElements = CreateBaseHouseLayout(center);

        elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

        int id = AddRoom(Base);

        AddTeleporter(center + spawnPositions.at(Base)[0].position, spawnPositions.at(Base)[0].rotation, TeleporterList::TeleportUse::BaseEntrance, id);

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

            std::vector<IMElement> layoutElements = CreateHighHouseFirstFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(HighBaseFirstFloor);

            AddTeleporter(center + spawnPositions.at(HighBaseFirstFloor)[0].position, spawnPositions.at(HighBaseFirstFloor)[0].rotation, TeleporterList::TeleportUse::HighBaseEntrance, id);
            AddTeleporter(center + spawnPositions.at(HighBaseFirstFloor)[1].position, spawnPositions.at(HighBaseFirstFloor)[1].rotation, TeleporterList::TeleportUse::HighBaseStairsUp, id);

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

            std::vector<IMElement> layoutElements = CreateHighHouseSecondFloorLayout(center);
            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(HighBaseSecondFloor);

            AddTeleporter(center + spawnPositions.at(HighBaseSecondFloor)[0].position, spawnPositions.at(HighBaseSecondFloor)[0].rotation, TeleporterList::TeleportUse::HighBaseStairsDown, id);

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

        std::vector<IMElement> layoutElements = CreateDoubleFirstFloorLayout(center);

        elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

        int id = AddRoom(DoubleFirstFloorLeft);

        AddTeleporter(center + spawnPositions.at(DoubleFirstFloorLeft)[0].position, spawnPositions.at(DoubleFirstFloorLeft)[0].rotation, TeleporterList::TeleportUse::DoubleEntranceLeft, id);

        AddTeleporter(center + spawnPositions.at(DoubleFirstFloorLeft)[1].position, spawnPositions.at(DoubleFirstFloorLeft)[1].rotation, TeleporterList::TeleportUse::DoubleStairsUpLeft, id);


        return elements;
    }

    static std::vector<IMElement> CreateDoubleFirstFloorRightTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x - 5.5f, center.y, center.z + 0.6f}, {0,90,0}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x + 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 4, center.y + 1.5f, center.z + 3.8f}, {0,0,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z + 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",{"forniture","pnois"},{center.x - 5.5f, center.y + 1.5f, center.z - 2}, {0,270,0}, {0.5,0.5,1}));  instanceNumber++;

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
            //elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3.5f, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x - 4.0f, center.y + 3, center.z + 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x, center.y + 3, center.z - 4.0f}, {180,0,0})); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y + 3, center.z - 4.0f},{180,0,0})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",{"tex_medieval_atlas","pnois"},{center.x + 4.0f, center.y +  3.0f, center.z + 6.0f},{180,0,0}, {1,1,2})); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",{"tex_nature_atlas_1","pnois"},{center.x, center.y + 3.1f, center.z},{270,0,0}, {10, 1, 10})); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",{"forniture","pnois"},{center.x + 4.0f, center.y, center.z +1},{0,0,0}, {2, 1.5, 1.5f})); instanceNumber++;

            std::vector<IMElement> layoutElements = CreateDoubleFirstFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(DoubleFirstFloorRight);

            AddTeleporter(center + spawnPositions.at(DoubleFirstFloorRight)[0].position, spawnPositions.at(DoubleFirstFloorRight)[0].rotation, TeleporterList::TeleportUse::DoubleEntranceRight, id);

            AddTeleporter(center + spawnPositions.at(DoubleFirstFloorRight)[1].position, spawnPositions.at(DoubleFirstFloorRight)[1].rotation, TeleporterList::TeleportUse::DoubleStairsUpRight, id);


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

            std::vector<IMElement> layoutElements = CreateDoubleSecondFloorLeftLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(DoubleSecondFloorLeft);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorLeft)[0].position, spawnPositions.at(DoubleSecondFloorLeft)[0].rotation, TeleporterList::TeleportUse::DoubleStairsDownLeft, id);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorLeft)[1].position, spawnPositions.at(DoubleSecondFloorLeft)[1].rotation, TeleporterList::TeleportUse::DoubleBridgeFromLeft, id);


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

            std::vector<IMElement> layoutElements = CreateDoubleSecondFloorRightLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(DoubleSecondFloorRight);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorRight)[0].position, spawnPositions.at(DoubleSecondFloorRight)[0].rotation, TeleporterList::TeleportUse::DoubleStairsDownRight, id);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorRight)[1].position, spawnPositions.at(DoubleSecondFloorRight)[1].rotation, TeleporterList::TeleportUse::DoubleBridgeFromRight, id);


        return elements;
        }

    static std::vector<IMElement> ConnectingBridge(glm::vec3 center){

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

        int id = AddRoom(DoubleConnection);

        AddTeleporter(center + spawnPositions.at(DoubleConnection)[0].position, spawnPositions.at(DoubleConnection)[0].rotation, TeleporterList::TeleportUse::ConnectingBridgeRight, id);

        AddTeleporter(center + spawnPositions.at(DoubleConnection)[1].position, spawnPositions.at(DoubleConnection)[1].rotation, TeleporterList::TeleportUse::ConnectingBridgeLeft, id);


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

            std::vector<IMElement> layoutElements = CreateLShapedLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(LShaped);

            AddTeleporter(center + spawnPositions.at(LShaped)[0].position, spawnPositions.at(LShaped)[0].rotation, TeleporterList::TeleportUse::LShapedEntrance, id);

        return elements;
        }

    static std::vector<IMElement> CreateHighLShapedFirstFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",{"forniture","pnois"},{center.x + 11.5f, center.y, center.z + 7.7f}));  instanceNumber++;

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

            std::vector<IMElement> layoutElements = CreateHighLShapedFirstFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(HighLShapedFirstFloor);

            AddTeleporter(center + spawnPositions.at(HighLShapedFirstFloor)[0].position, spawnPositions.at(HighLShapedFirstFloor)[0].rotation, TeleporterList::TeleportUse::HighLShapedEntrance, id);

            AddTeleporter(center + spawnPositions.at(HighLShapedFirstFloor)[1].position, spawnPositions.at(HighLShapedFirstFloor)[1].rotation, TeleporterList::TeleportUse::HighLShapedStairsUp, id);

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

            std::vector<IMElement> layoutElements = CreateHighLShapedSecondFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());


            int id = AddRoom(HighLShapedSecondFloor);

            AddTeleporter(center + spawnPositions.at(HighLShapedSecondFloor)[0].position, spawnPositions.at(HighLShapedSecondFloor)[0].rotation, TeleporterList::TeleportUse::HighLShapedStairsDown, id);

            return elements;
        }

    //House Layout
    static IMElement CreateWallDeco(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 scale = {1,1,1} ){
        IMElement element;
        int rand_int = UtilsStructs::rand_int(1,3);
        glm::vec3 pictureOffset;
        if (rot.y == 0)
            pictureOffset = glm::vec3(0,0,-0.21);
        if (rot.y == 180)
            pictureOffset = glm::vec3(0,0,0.21);
        if (rot.y == 90)
            pictureOffset = glm::vec3(-0.21,0,0);
        if (rot.y == 270)
            pictureOffset = glm::vec3(0.21,0,0);

        if (rand_int == 1){
            element = UtilsStructs::createElement("sword_frame_" + std::to_string(instanceNumber),"sword_frame",{"dungeon","pnois"},{pos.x, pos.y , pos.z}, {rot.x,rot.y,rot.z}, {scale.x,scale.y,scale.z}); instanceNumber++;
        }
        if (rand_int == 2){
            element = UtilsStructs::createElement("picture_" + std::to_string(instanceNumber),"picture1",{"forniture","pnois"},{pos.x + pictureOffset.x, pos.y + pictureOffset.y , pos.z + pictureOffset.z}, {rot.x,rot.y,rot.z}, {scale.x,scale.y,scale.z}); instanceNumber++;
        }
        if(rand_int == 3) {
            element = UtilsStructs::createElement("picture_" + std::to_string(instanceNumber), "picture2",
                                                  {"forniture", "pnois"}, {pos.x + pictureOffset.x, pos.y + pictureOffset.y, pos.z + pictureOffset.z}, {rot.x, rot.y, rot.z},
                                                  {scale.x, scale.y, scale.z});
            instanceNumber++;
        }
        return element;
    }

    static std::vector<IMElement> CreateStudyTableWithChair(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 tableScale = {1,1,1}){
        std::vector<IMElement> elements;
        
        // Study table (table2)
        elements.emplace_back(UtilsStructs::createElement("study_table_" + std::to_string(instanceNumber), "table2", {"dungeon","pnois"}, {pos.x, pos.y + 0.7f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        
        // Single chair positioned based on table rotation
        float chairOffset = 1.0f;
        glm::vec3 chairPos;
        float chairRot;
        
        if (rot.y == 0) {
            chairPos = {pos.x, pos.y + 0.5f, pos.z + chairOffset};
            chairRot = 180;
        } else if (rot.y == 180) {
            chairPos = {pos.x, pos.y + 0.5f, pos.z - chairOffset};
            chairRot = 0;
        } else if (rot.y == 90) {
            chairPos = {pos.x + chairOffset, pos.y + 0.5f, pos.z};
            chairRot = 270;
        } else {
            chairPos = {pos.x - chairOffset, pos.y + 0.5f, pos.z};
            chairRot = 90;
        }
        
        elements.emplace_back(UtilsStructs::createElement("chair_" + std::to_string(instanceNumber), "dungeon_chair3", {"dungeon","pnois"}, {chairPos.x, chairPos.y, chairPos.z}, {0, chairRot, 0}, {1,1,1})); instanceNumber++;
        
        return elements;
    }

    static std::vector<IMElement> CreateTableWithChairs(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 tableScale = {2,2,2}, int numChairs = 2){
        std::vector<IMElement> elements;
        
        // First element: random table
        int rand_table = UtilsStructs::rand_int(1,2);
        int rand_deco = UtilsStructs::rand_int(1,7);
        float tableYOffset = 0.0f;
        glm::vec3 realTableScale = tableScale;
        if (rand_table == 2) {
            realTableScale /= 2;
            realTableScale.y += 0.3f;
            tableYOffset += 0.5;
        }
        std::string tableModel = (rand_table == 1) ? "coffee_table" : "table1";
        elements.emplace_back(UtilsStructs::createElement("table_" + std::to_string(instanceNumber), tableModel, {"dungeon","pnois"}, {pos.x, pos.y + tableYOffset, pos.z}, {rot.x, rot.y, rot.z}, {realTableScale.x, realTableScale.y, realTableScale.z})); instanceNumber++;
        
        // Add chairs around the table based on rotation
        float chairOffset = 1.5f;
        
        if (numChairs >= 1) {
            // Chair in front (relative to table rotation)
            glm::vec3 chair1Pos;
            float chair1Rot = rot.y;
            if (rot.y == 0) {
                chair1Pos = {pos.x, pos.y + 0.5f, pos.z + chairOffset};
                chair1Rot = 180;
            } else if (rot.y == 180) {
                chair1Pos = {pos.x, pos.y + 0.5f, pos.z - chairOffset};
                chair1Rot = 0;
            } else if (rot.y == 90) {
                chair1Pos = {pos.x + chairOffset, pos.y + 0.5f, pos.z};
                chair1Rot = 270;
            } else {
                chair1Pos = {pos.x - chairOffset, pos.y + 0.5f, pos.z};
                chair1Rot = 90;
            }
            elements.emplace_back(UtilsStructs::createElement("chair_" + std::to_string(instanceNumber), "dungeon_chair3", {"dungeon","pnois"}, {chair1Pos.x, chair1Pos.y, chair1Pos.z}, {0, chair1Rot, 0}, {1,1,1})); instanceNumber++;
        }
        
        if (numChairs >= 2) {
            // Chair behind (opposite side)
            glm::vec3 chair2Pos;
            float chair2Rot = rot.y;
            if (rot.y == 0) {
                chair2Pos = {pos.x, pos.y + 0.5f, pos.z - chairOffset};
                chair2Rot = 0;
            } else if (rot.y == 180) {
                chair2Pos = {pos.x, pos.y + 0.5f, pos.z + chairOffset};
                chair2Rot = 180;
            } else if (rot.y == 90) {
                chair2Pos = {pos.x - chairOffset, pos.y + 0.5f, pos.z};
                chair2Rot = 90;
            } else {
                chair2Pos = {pos.x + chairOffset, pos.y + 0.5f, pos.z};
                chair2Rot = 270;
            }
            elements.emplace_back(UtilsStructs::createElement("chair_" + std::to_string(instanceNumber), "dungeon_chair3", {"dungeon","pnois"}, {chair2Pos.x, chair2Pos.y, chair2Pos.z}, {0, chair2Rot, 0}, {1,1,1})); instanceNumber++;
        }

        if(rand_deco == 1){
            elements.emplace_back(UtilsStructs::createElement("bottle_" + std::to_string(instanceNumber), "bottle", {"dungeon","pnois"}, {pos.x, pos.y + 1.3f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 2){
            glm::vec3 plate1Pos;
            glm::vec3 plate2Pos;
            float plateOffset = 0.3;
            float plateOffsetY = 1.05f;
            if (rot.y == 0) {
                plate1Pos = {pos.x, pos.y + plateOffsetY, pos.z - plateOffset};
                plate2Pos = {pos.x, pos.y + plateOffsetY + 0.05f, pos.z + plateOffset};
            } else if (rot.y == 180) {
                plate1Pos = {pos.x, pos.y + plateOffsetY, pos.z + plateOffset};
                plate2Pos = {pos.x, pos.y + plateOffsetY + 0.05f, pos.z - plateOffset};
            } else if (rot.y == 90) {
                plate1Pos = {pos.x + plateOffset, pos.y + plateOffsetY, pos.z};
                plate2Pos = {pos.x - plateOffset, pos.y + plateOffsetY + 0.05f, pos.z};
            } else {
                plate1Pos = {pos.x - plateOffset, pos.y + plateOffsetY, pos.z};
                plate2Pos = {pos.x + plateOffset, pos.y + plateOffsetY + 0.05f, pos.z};
            }
            elements.emplace_back(UtilsStructs::createElement("plate_" + std::to_string(instanceNumber), "empty_plate", {"dungeon","pnois"},{plate1Pos.x,plate1Pos.y,plate1Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("plate_" + std::to_string(instanceNumber), "full_plate", {"dungeon","pnois"}, {plate2Pos.x,plate2Pos.y,plate2Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 3){
            elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light4", {"dungeon","pnois"}, {pos.x, pos.y + 1.3f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 4){
            elements.emplace_back(UtilsStructs::createElement("flower_" + std::to_string(instanceNumber), "flower1", {"dungeon","pnois"}, {pos.x, pos.y + 1.0f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 5){
            elements.emplace_back(UtilsStructs::createElement("flower_" + std::to_string(instanceNumber), "flower2", {"dungeon","pnois"}, {pos.x, pos.y + 1.0f, pos.z}, {rot.x, rot.y, rot.z})); instanceNumber++;
        }
        if(rand_deco == 6){
            elements.emplace_back(UtilsStructs::createElement("flower_" + std::to_string(instanceNumber), "flower3", {"dungeon","pnois"}, {pos.x, pos.y + 0.99f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 7){
            glm::vec3 coins1Pos;
            glm::vec3 coins2Pos;
            glm::vec3 coins3Pos;
            float coinsOffset = 0.43;
            float coinsOffsetY = 1.05f;
            if (rot.y == 0) {
                coins1Pos = {pos.x, pos.y + coinsOffsetY, pos.z - coinsOffset};
                coins3Pos = {pos.x, pos.y + coinsOffsetY + 0.1f, pos.z + coinsOffset};
            } else if (rot.y == 180) {
                coins1Pos = {pos.x, pos.y + coinsOffsetY, pos.z + coinsOffset};
                coins3Pos = {pos.x, pos.y + coinsOffsetY + 0.1f, pos.z - coinsOffset};
            } else if (rot.y == 90) {
                coins1Pos = {pos.x + coinsOffset, pos.y + coinsOffsetY, pos.z};
                coins3Pos = {pos.x - coinsOffset, pos.y + coinsOffsetY + 0.1f, pos.z};
            } else {
                coins1Pos = {pos.x - coinsOffset, pos.y + coinsOffsetY, pos.z};
                coins3Pos = {pos.x + coinsOffset, pos.y + coinsOffsetY + 0.1f, pos.z};
            }
            coins2Pos = {pos.x, pos.y + coinsOffsetY, pos.z};
            elements.emplace_back(UtilsStructs::createElement("coins_" + std::to_string(instanceNumber), "coins1", {"dungeon","pnois"}, {coins1Pos.x, coins1Pos.y, coins1Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("coins_" + std::to_string(instanceNumber), "coins2", {"dungeon","pnois"}, {coins2Pos.x, coins2Pos.y, coins2Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("coins_" + std::to_string(instanceNumber), "coins3", {"dungeon","pnois"}, {coins3Pos.x, coins3Pos.y, coins3Pos.z}, {rot.x, rot.y + 180, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        return elements;
    }

    static std::vector<IMElement> CreateGroundedDeco(glm::vec3 pos, glm::vec3 rot = {0,0,0}){
        std::vector<IMElement> elements;
        int rand_int = UtilsStructs::rand_int(1,4);
        if (rand_int == 1){
            elements = CreateStudyTableWithChair(pos, rot + glm::vec3(0,90,0));
        }
        else elements = CreateTableWithChairs(pos);
        return elements;
    }

    static IMElement CreateRandomBox(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 scale = {1,1,1}){
        int rand_int = UtilsStructs::rand_int(1,3);
        if (rand_int == 1){
            return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box6",{"dungeon","pnois"},{pos.x , pos.y + 0.4f , pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 2){
            return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box8",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 3){
            return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box10",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box6",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});

    }
    static IMElement CreateRandomLibrary(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 scale = {1,1,1}){
        int rand_int = UtilsStructs::rand_int(1,4);
        if (rand_int == 1){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library3",{"dungeon","pnois"},{pos.x , pos.y + 0.4f , pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 2){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library4",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 3){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library5",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 4){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library6",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library1",{"dungeon","pnois"},{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});

    }

    static std::vector<IMElement> CreateBaseHouseLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 4.0f, center.y + 2, center.z - 3.8f})); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x - 3.7f, center.y, center.z - 2.5f}, {0,0,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x - 3.7f, center.y, center.z - 0.5f}));

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 3.5f, center.y, center.z});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }

    static std::vector<IMElement> CreateHighHouseFirstFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 4.0f, center.y + 2, center.z - 3.5f})); instanceNumber++;

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 3.5f, center.y, center.z});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }

    static std::vector<IMElement> CreateHighHouseSecondFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateRandomLibrary({center.x, center.y - 0.5f , center.z + 3.8f}, {0,180,0})); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 3.7f, center.y, center.z - 0.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 3.7f, center.y, center.z + 0.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 2, center.y, center.z}, {0,270,0}));


        return elements;
    }

    static std::vector<IMElement> CreateDoubleFirstFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x, center.y + 2, center.z + 3.5f}, {0,180,0})); instanceNumber++;

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x, center.y, center.z + 2}, {0,90,0});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }

    static std::vector<IMElement> CreateDoubleSecondFloorRightLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x, center.y + 2.0f, center.z + 3.5f}, {0,180,0})); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 3.7f, center.y, center.z - 0.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 3.7f, center.y, center.z + 0.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 2, center.y, center.z}, {0,270,0}));


        return elements;
    }
    static std::vector<IMElement> CreateDoubleSecondFloorLeftLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x, center.y + 2.0f, center.z - 3.5f}, {0,0,0})); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 3.7f, center.y, center.z - 0.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 3.7f, center.y, center.z + 0.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 2, center.y, center.z}, {0,270,0}));


        return elements;
    }

    static std::vector<IMElement> CreateLShapedLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 8.0f, center.y + 2.0f, center.z + 0.5f})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 0.5f, center.y + 2.0f, center.z + 2}, {0,90,0})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 14}, {0,90,0})); instanceNumber++;
        elements.emplace_back(CreateWallDeco({center.x + 14, center.y + 2, center.z + 0.6f})); instanceNumber++;
        elements.emplace_back(CreateRandomLibrary({center.x + 0.2f, center.y - 0.5f , center.z + 8}, {0,90,0})); instanceNumber++;


        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 6.5f, center.y, center.z + 13.5f}, {0,180,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 6.5f, center.y, center.z + 11.5f}, {0,180,0}));

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 8, center.y, center.z + 2.5}, {0,90,0});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    static std::vector<IMElement> CreateHighLShapedFirstFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 8.0f, center.y + 2.0f, center.z + 0.5f})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 0.5f, center.y + 2.0f, center.z + 2}, {0,90,0})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 7.5f, center.y + 2.0f, center.z + 14}, {0,270,0})); instanceNumber++;


        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 14}, {0,90,0})); instanceNumber++;
        elements.emplace_back(CreateWallDeco({center.x + 14, center.y + 2, center.z + 0.6f})); instanceNumber++;

        //Bed
        elements.emplace_back(CreateRandomBox({center.x + 0.6f, center.y, center.z + 14}, {0,90,0})); instanceNumber++;

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 8, center.y, center.z + 2.5}, {0,90,0});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    static std::vector<IMElement> CreateHighLShapedSecondFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 14.0f, center.y + 2.0f, center.z + 0.5f})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", {"dungeon","pnois"}, {center.x + 0.5f, center.y + 2.0f, center.z + 8}, {0,90,0})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 14}, {0,90,0})); instanceNumber++;
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 2},{0,90,0})); instanceNumber++;
        elements.emplace_back(CreateRandomLibrary({center.x + 8.0f, center.y - 0.5f , center.z + 0.2}, {0,0,0})); instanceNumber++;


        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 13.5f, center.y, center.z + 4.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",{"forniture","pnois"},{center.x + 13.5f, center.y, center.z + 3.5f}, {0,270,0}, {1.2,1.2,1.2})); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 11.5, center.y, center.z + 4}, {0, 270, 0}));

        return elements;
    }
    static std::vector<IMElement> CreateHouseInteriors(glm:: vec3 origin, float distance = 20.0f);

    static std::vector<IMElement> CreateHouse(HouseTemplate tmp, glm::vec3 center);

};

#endif //E09_INTERIORMANAGER_HPP
