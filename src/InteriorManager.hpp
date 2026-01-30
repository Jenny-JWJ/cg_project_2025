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
    static const int housePerType = 3;
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

            int id = AddRoom(LShaped);

            AddTeleporter(center + spawnPositions.at(LShaped)[0].position, spawnPositions.at(LShaped)[0].rotation, TeleporterList::TeleportUse::LShapedEntrance, id);

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

        int id = AddRoom(HighLShapedSecondFloor);

        AddTeleporter(center + spawnPositions.at(HighLShapedSecondFloor)[0].position, spawnPositions.at(HighLShapedSecondFloor)[0].rotation, TeleporterList::TeleportUse::HighLShapedStairsDown, id);

            return elements;
        }

    static std::vector<IMElement> CreateHouseInteriors(glm:: vec3 origin, float distance = 20.0f);

    static std::vector<IMElement> CreateHouse(HouseTemplate tmp, glm::vec3 center);

};

#endif //E09_INTERIORMANAGER_HPP
