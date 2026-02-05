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
#include "DrunkEffectManager.hpp"
#include "CandleManager.hpp"

using IMElement = UtilsStructs::Element;

class InteriorManager{
    // Number of houses per type to generate
    constexpr static const int housePerType[13] = {0, 6, 6, 3, 6, 3, 6, 3, 1, 6, 6, 2, 0};
public:
    // House templates, represents the different structures of interiors needed to represent all possible "rooms" of houses
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

    static std::map<HouseTemplate, std::vector<SpawnPosition>> spawnPositions; //{template, {{spawn position w.r.t the center, camera spawn rotation(Yaw, Pitch)}, ...}}

    static glm::vec3 offset;

    static int instanceNumber;

    // Reusable texture arrays
    inline static const std::vector<std::string> texForniture = {"forniture", "pnois"};
    inline static const std::vector<std::string> texDungeon = {"dungeon", "pnois"};
    inline static const std::vector<std::string> texMedieval = {"tex_medieval_atlas", "pnois"};
    inline static const std::vector<std::string> texNature = {"tex_nature_atlas_1", "pnois"};
    inline static const std::vector<std::string> texBlack = {"black", "pnois"};

    // Reusable scales
    inline static const std::vector<float> scaleDefault = {1.0f, 1.0f, 1.0f};
    inline static const std::vector<float> scaleWindow = {0.5f, 0.5f, 1.0f};
    inline static const std::vector<float> scaleWall = {1.0f, 1.5f, 1.0f};
    inline static const std::vector<float> scaleGround = {10.0f, 1.0f, 10.0f};
    inline static const std::vector<float> scaleBed = {1.2f, 1.2f, 1.2f};
    inline static const std::vector<float> scaleTable = {2.0f, 2.0f, 2.0f};
    inline static const std::vector<float> scaleHole = {1.0f, 1.0f, 2.0f};

    // Reusable rotations
    inline static const std::vector<float> rot0 = {0.0f, 0.0f, 0.0f};
    inline static const std::vector<float> rot90 = {0.0f, 90.0f, 0.0f};
    inline static const std::vector<float> rot180 = {0.0f, 180.0f, 0.0f};
    inline static const std::vector<float> rot270 = {0.0f, 270.0f, 0.0f};
    inline static const std::vector<float> rot90X = {90.0f, 0.0f, 0.0f};
    inline static const std::vector<float> rot180X = {180.0f, 0.0f, 0.0f};
    inline static const std::vector<float> rot270X = {270.0f, 0.0f, 0.0f};
    inline static const std::vector<float> rot90_180 = {90.0f, 180.0f, 0.0f};
    inline static const std::vector<float> rot90_90 = {90.0f, 90.0f, 0.0f};
    inline static const std::vector<float> rot90_270 = {90.0f, 270.0f, 0.0f};

    // Add a new room to the RoomManager and return its ID
    static int AddRoom(HouseTemplate aTemplate);

    // Add a teleporter at specified position and rotation, linked to a room ID
    static void AddTeleporter(glm::vec3 spawnPos, glm::vec2 spawnDir, TeleporterList::TeleportUse tpUse, int roomId);

    //House Template
    //Base, rectangular house with one floor
    static std::vector<IMElement> CreateBaseHouseTemplate(glm::vec3 center){

        std::vector<IMElement> elements;
        elements.reserve(50);

        //Door
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

        //Windows
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 5.5f, center.y + 1.5f, center.z + 2}, rot90, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z - 2}, rot270, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 5.5f, center.y + 1.5f, center.z - 2}, rot90, scaleWindow));  instanceNumber++;

        //Walls
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

        //Pillars
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 6.0f, center.y, center.z}, rot90_270)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

        //Floor
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z - 4.0f}, rot0)); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y - 0.1f, center.z}, rot90X, scaleGround)); instanceNumber++;

        //Roof
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z}, rot270X, scaleGround)); instanceNumber++;

        // Add interior layout
        std::vector<IMElement> layoutElements = CreateBaseHouseLayout(center);

        elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

        int id = AddRoom(Base);

        AddTeleporter(center + spawnPositions.at(Base)[0].position, spawnPositions.at(Base)[0].rotation, TeleporterList::TeleportUse::BaseEntrance, id);

        return elements;
        }
    //High Base House, rectangular house with two floors, first floor
    static std::vector<IMElement> CreateHighBaseHouseFirstFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;
            elements.reserve(52);

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 5.5f, center.y + 1.5f, center.z + 2}, rot90, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z - 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 5.5f, center.y + 1.5f, center.z - 2}, rot90, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

            //Pillars
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 6.0f, center.y, center.z}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y - 0.1f, center.z},rot90X, scaleGround)); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texBlack,{center.x - 4.0f, center.y + 3.05f, center.z},rot270X, scaleHole)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texBlack,{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},rot270X, scaleHole)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x - 4.0f, center.y, center.z + 1},rot0, {2, 1.5, 1.5f})); instanceNumber++;
            
            // Add interior layout
            std::vector<IMElement> layoutElements = CreateHighHouseFirstFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(HighBaseFirstFloor);

            AddTeleporter(center + spawnPositions.at(HighBaseFirstFloor)[0].position, spawnPositions.at(HighBaseFirstFloor)[0].rotation, TeleporterList::TeleportUse::HighBaseEntrance, id);
            AddTeleporter(center + spawnPositions.at(HighBaseFirstFloor)[1].position, spawnPositions.at(HighBaseFirstFloor)[1].rotation, TeleporterList::TeleportUse::HighBaseStairsUp, id);

        return elements;
        }

    //High Base House, rectangular house with two floors, second floor
    static std::vector<IMElement> CreateHighBaseHouseSecondFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;
            elements.reserve(50);

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

            //Pillars
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 6.0f, center.y, center.z}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texBlack,{center.x, center.y - 5, center.z},rot90X, {50, 50, 50})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3.05f, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},rot180X)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x - 4.0f, center.y - 3, center.z + 0.5f},rot0, {2.5, 1.5, 1.5f})); instanceNumber++;

            // Add interior layout
            std::vector<IMElement> layoutElements = CreateHighHouseSecondFloorLayout(center);
            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(HighBaseSecondFloor);

            AddTeleporter(center + spawnPositions.at(HighBaseSecondFloor)[0].position, spawnPositions.at(HighBaseSecondFloor)[0].rotation, TeleporterList::TeleportUse::HighBaseStairsDown, id);

            return elements;
        }

    //Double House, two rectangular houses joined, first floor, left side
    static std::vector<IMElement> CreateDoubleFirstFloorLeftTemplate(glm::vec3 center){

        std::vector<IMElement> elements;
        elements.reserve(82);

        //Door
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x + 5.5f, center.y, center.z + 0.6f}, rot90));  instanceNumber++;

        //Windows
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z - 2}, rot270, scaleWindow));  instanceNumber++;

        //Walls
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

        //Pillars
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

        //Floor
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z},rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z},rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y - 0.1f, center.z},rot90X, scaleGround)); instanceNumber++;

        //Roof
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z},rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texBlack,{center.x - 4.0f, center.y + 3.05f, center.z},rot270X, scaleHole)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f},rot180X)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texBlack,{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},rot270X, scaleHole)); instanceNumber++;

        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z},rot270X, scaleGround)); instanceNumber++;

        //Stairs
        elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x - 4.0f, center.y, center.z + 1},rot0, {2, 1.5, 1.5f})); instanceNumber++;

        // Add interior layout
        std::vector<IMElement> layoutElements = CreateDoubleFirstFloorLayout(center);

        elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

        int id = AddRoom(DoubleFirstFloorLeft);

        AddTeleporter(center + spawnPositions.at(DoubleFirstFloorLeft)[0].position, spawnPositions.at(DoubleFirstFloorLeft)[0].rotation, TeleporterList::TeleportUse::DoubleEntranceLeft, id);

        AddTeleporter(center + spawnPositions.at(DoubleFirstFloorLeft)[1].position, spawnPositions.at(DoubleFirstFloorLeft)[1].rotation, TeleporterList::TeleportUse::DoubleStairsUpLeft, id);


        return elements;
        }
    //Double House, two rectangular houses joined, first floor, right side
    static std::vector<IMElement> CreateDoubleFirstFloorRightTemplate(glm::vec3 center){

            std::vector<IMElement> elements;
            elements.reserve(83);

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 5.5f, center.y, center.z + 0.6f}, rot90));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 4, center.y + 1.5f, center.z + 3.8f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 5.5f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x - 5.5f, center.y + 1.5f, center.z - 2}, rot270, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

            //Pillars
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 6.0f, center.y, center.z}, rot90_270)); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y - 0.1f, center.z},rot90X, scaleGround)); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z -4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texBlack,{center.x + 4.0f, center.y + 3.05f, center.z},rot270X, scaleHole)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3.5f, center.z - 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y +  3.0f, center.z + 6.0f},rot180X, scaleHole)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x + 4.0f, center.y, center.z +1},rot0, {2, 1.5, 1.5f})); instanceNumber++;
            
            // Add interior layout
            std::vector<IMElement> layoutElements = CreateDoubleFirstFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(DoubleFirstFloorRight);

            AddTeleporter(center + spawnPositions.at(DoubleFirstFloorRight)[0].position, spawnPositions.at(DoubleFirstFloorRight)[0].rotation, TeleporterList::TeleportUse::DoubleEntranceRight, id);

            AddTeleporter(center + spawnPositions.at(DoubleFirstFloorRight)[1].position, spawnPositions.at(DoubleFirstFloorRight)[1].rotation, TeleporterList::TeleportUse::DoubleStairsUpRight, id);


        return elements;
        }

    //Double House, two rectangular houses joined, second floor, left side
    static std::vector<IMElement> CreateDoubleSecondFloorLeftTemplate(glm::vec3 center){

            std::vector<IMElement> elements;
            elements.reserve(77);

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 0.5f, center.y, center.z + 3.8f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z - 2}, rot270, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

            //Pillars
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texBlack,{center.x, center.y - 5, center.z},rot90X, {50, 50, 50})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3.05f, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},rot180X)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x - 4.0f, center.y - 3, center.z + 0.5f},rot0, {2.5, 1.5, 1.5f})); instanceNumber++;

            // Add interior layout
            std::vector<IMElement> layoutElements = CreateDoubleSecondFloorLeftLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(DoubleSecondFloorLeft);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorLeft)[0].position, spawnPositions.at(DoubleSecondFloorLeft)[0].rotation, TeleporterList::TeleportUse::DoubleStairsDownLeft, id);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorLeft)[1].position, spawnPositions.at(DoubleSecondFloorLeft)[1].rotation, TeleporterList::TeleportUse::DoubleBridgeFromLeft, id);


        return elements;
        }
    
    //Double House, two rectangular houses joined, second floor, right side
    static std::vector<IMElement> CreateDoubleSecondFloorRightTemplate(glm::vec3 center){

            std::vector<IMElement> elements;
            elements.reserve(110);

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 0.5f, center.y, center.z - 3.8f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 5.5f, center.y + 1.5f, center.z - 2}, rot270, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z + 4.2f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 4.0f, center.y, center.z - 4.2f}, rot0,  {1,1.5f,1})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z + 4.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 4.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 6.0f, center.y, center.z - 4.0f}, rot90, scaleWall)); instanceNumber++;

            //Pillars
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z + 4.2f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 2.0f, center.y, center.z - 4.2f}, rot90X)); instanceNumber++;
            //elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 6.0f, center.y, center.z}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 6.0f, center.y, center.z}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z + 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z + 3.9f}, rot90_90)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 5.9f, center.y, center.z - 3.9f}, rot90_270)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x - 5.9f, center.y, center.z - 3.9f}, rot90_90)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z + 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z + 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y, center.z - 4.0f}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y, center.z - 4.0f},rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texBlack,{center.x, center.y - 5, center.z},rot90X, {50, 50, 50})); instanceNumber++;

            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3.05f, center.z},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z + 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y + 3, center.z + 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 3, center.z - 4.0f}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 4.0f, center.y + 3, center.z - 4.0f},rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x - 4.0f, center.y +  3.05f, center.z - 4.0f},rot180X)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 3.1f, center.z},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x - 4.0f, center.y - 3, center.z - 0.5f},rot180, {2.5, 1.5, 1.5f})); instanceNumber++;
            
            // Add interior layout
            std::vector<IMElement> layoutElements = CreateDoubleSecondFloorRightLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(DoubleSecondFloorRight);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorRight)[0].position, spawnPositions.at(DoubleSecondFloorRight)[0].rotation, TeleporterList::TeleportUse::DoubleStairsDownRight, id);

            AddTeleporter(center + spawnPositions.at(DoubleSecondFloorRight)[1].position, spawnPositions.at(DoubleSecondFloorRight)[1].rotation, TeleporterList::TeleportUse::DoubleBridgeFromRight, id);


        return elements;
        }

    //Connecting Bridge between two double houses
    static std::vector<IMElement> ConnectingBridge(glm::vec3 center){

        std::vector<IMElement> elements;

        //Door
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 0.5f, center.y, center.z + 2.5f}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x - 0.5f, center.y, center.z - 2.5f}));  instanceNumber++;


        //Windows
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 0.9f, center.y + 1.5f, center.z + 1}, rot90, {0.5,0.5,0.3}));  instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 0.9f, center.y + 1.5f, center.z - 1}, rot90, {0.5,0.5,0.3}));  instanceNumber++;

        //Floor and walls
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"tunnel",texDungeon,{center.x, center.y, center.z}, rot0, {1,1.5f,1.5})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z - 3}, rot0, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x, center.y, center.z + 3}, rot180, scaleWall)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y - 0.1f, center.z},rot90X, scaleGround)); instanceNumber++;

        //Roof
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x, center.y + 2.5f, center.z}, rot180X, {1,1,1.5})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("house_roof_" + std::to_string(instanceNumber),"ground",texNature,{center.x, center.y + 2.6f, center.z},rot270X, scaleGround)); instanceNumber++;

        int id = AddRoom(DoubleConnection);

        AddTeleporter(center + spawnPositions.at(DoubleConnection)[0].position, spawnPositions.at(DoubleConnection)[0].rotation, TeleporterList::TeleportUse::ConnectingBridgeRight, id);

        AddTeleporter(center + spawnPositions.at(DoubleConnection)[1].position, spawnPositions.at(DoubleConnection)[1].rotation, TeleporterList::TeleportUse::ConnectingBridgeLeft, id);


        return elements;
        }
    //L-Shaped House, one floor
    static std::vector<IMElement> CreateLShapedTemplate(glm::vec3 center){

            std::vector<IMElement> elements;

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x + 9.5f, center.y, center.z + 7.7f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 14, center.y + 1.5f, center.z + 7.7f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 15.6f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 15.6f, center.y + 1.5f, center.z + 6}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 7.6f, center.y + 1.5f, center.z + 10}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 7.6f, center.y + 1.5f, center.z + 14}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 2, center.y + 1.5f, center.z + 15.7f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 6, center.y + 1.5f, center.z + 15.7f}, rot0, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 2.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 10.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 14.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 2.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 6.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 10.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 14.0f}, rot90, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 10.0f, center.y, center.z + 8.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 14.0f, center.y, center.z + 8.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 16.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 2.0f, center.y, center.z + 16.1f}, rot180, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 8.1f, center.y, center.z + 10.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 8.1f, center.y, center.z + 14.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 16.1f, center.y, center.z + 6.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 16.1f, center.y, center.z + 2.0f}, rot270, scaleWall)); instanceNumber++;

            //Pillars

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 0.1f, center.y, center.z + 0.1f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 4, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 12, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 15.9f, center.y, center.z + 0.1f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x  + 16, center.y, center.z + 4.0f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 15.9f, center.y, center.z + 7.9f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 8.3f, center.y, center.z + 8.3f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x , center.y, center.z + 4}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x , center.y, center.z + 12}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 0.1f, center.y, center.z + 15.9f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x  + 4, center.y, center.z + 16.0f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 7.9f, center.y, center.z + 15.9f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 8, center.y, center.z + 12.0f}, rot90_180)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 10}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 14}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 10}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 14}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y, center.z + 6}, rot0)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x + 10, center.y - 0.1f, center.z + 10},rot90X, scaleGround)); instanceNumber++;


            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 10}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 14}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 10}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 14}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x + 10, center.y + 3.1f, center.z + 10},rot270X, scaleGround)); instanceNumber++;

            // Add interior layout
            std::vector<IMElement> layoutElements = CreateLShapedLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(LShaped);

            AddTeleporter(center + spawnPositions.at(LShaped)[0].position, spawnPositions.at(LShaped)[0].rotation, TeleporterList::TeleportUse::LShapedEntrance, id);

        return elements;
        }

    //High L-Shaped House, two floor, first floor
    static std::vector<IMElement> CreateHighLShapedFirstFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;
            elements.reserve(101);

            //Door
            elements.emplace_back(UtilsStructs::createElement("door_"+ std::to_string(instanceNumber),"door",texForniture,{center.x + 11.5f, center.y, center.z + 7.7f}));  instanceNumber++;

            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 7.6f, center.y + 1.5f, center.z + 10}, rot270, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 2.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 10.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 14.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 2.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 6.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 10.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 14.0f}, rot90, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 10.0f, center.y, center.z + 8.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 14.0f, center.y, center.z + 8.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 16.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 2.0f, center.y, center.z + 16.1f}, rot180, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 8.1f, center.y, center.z + 10.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 8.1f, center.y, center.z + 14.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 16.1f, center.y, center.z + 6.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 16.1f, center.y, center.z + 2.0f}, rot270, scaleWall)); instanceNumber++;

            //Pillars

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 0.1f, center.y, center.z + 0.1f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 4, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 12, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 15.9f, center.y, center.z + 0.1f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x  + 16, center.y, center.z + 4.0f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 15.9f, center.y, center.z + 7.9f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 8.3f, center.y, center.z + 8.3f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x , center.y, center.z + 4}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x , center.y, center.z + 12}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 0.1f, center.y, center.z + 15.9f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x  + 4, center.y, center.z + 16.0f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 7.9f, center.y, center.z + 15.9f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 8, center.y, center.z + 12.0f}, rot90_180)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 10}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 14}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 10}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 14}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y, center.z + 6}, rot0)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x + 10, center.y - 0.1f, center.z + 10},rot90X, scaleGround)); instanceNumber++;


            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texBlack,{center.x + 2, center.y + 3.1f, center.z + 6}, rot270X, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texBlack,{center.x + 2, center.y + 3.1f, center.z + 10}, rot270X, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 14}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 10}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 14}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x + 10, center.y + 3.2f, center.z + 10},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x + 2, center.y, center.z + 6.05f},rot180, {2.5, 1.5, 2.0f})); instanceNumber++;

            // Add interior layout
            std::vector<IMElement> layoutElements = CreateHighLShapedFirstFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());

            int id = AddRoom(HighLShapedFirstFloor);

            AddTeleporter(center + spawnPositions.at(HighLShapedFirstFloor)[0].position, spawnPositions.at(HighLShapedFirstFloor)[0].rotation, TeleporterList::TeleportUse::HighLShapedEntrance, id);

            AddTeleporter(center + spawnPositions.at(HighLShapedFirstFloor)[1].position, spawnPositions.at(HighLShapedFirstFloor)[1].rotation, TeleporterList::TeleportUse::HighLShapedStairsUp, id);

        return elements;
        }
    //High L-Shaped House, two floor, second floor
    static std::vector<IMElement> CreateHighLShapedSecondFloorTemplate(glm::vec3 center){

            std::vector<IMElement> elements;


            //Windows
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 14, center.y + 1.5f, center.z + 7.7f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 15.6f, center.y + 1.5f, center.z + 2}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 15.6f, center.y + 1.5f, center.z + 6}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 7.6f, center.y + 1.5f, center.z + 10}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 7.6f, center.y + 1.5f, center.z + 14}, rot270, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 2, center.y + 1.5f, center.z + 15.7f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 6, center.y + 1.5f, center.z + 15.7f}, rot0, scaleWindow));  instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("window_"+ std::to_string(instanceNumber),"window",texForniture,{center.x + 10, center.y + 1.5f, center.z + 7.7f}, rot0, scaleWindow));  instanceNumber++;

            //Walls
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 2.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 10.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 14.0f, center.y, center.z - 0.1f}, rot0, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 2.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 6.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 10.0f}, rot90, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x - 0.1f, center.y, center.z + 14.0f}, rot90, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 10.0f, center.y, center.z + 8.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 14.0f, center.y, center.z + 8.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 6.0f, center.y, center.z + 16.1f}, rot180, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 2.0f, center.y, center.z + 16.1f}, rot180, scaleWall)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 8.1f, center.y, center.z + 10.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 8.1f, center.y, center.z + 14.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 16.1f, center.y, center.z + 6.0f}, rot270, scaleWall)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("wall_" + std::to_string(instanceNumber),"wall",texDungeon,{center.x + 16.1f, center.y, center.z + 2.0f}, rot270, scaleWall)); instanceNumber++;

            //Pillars

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 0.1f, center.y, center.z + 0.1f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 4, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 12, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 15.9f, center.y, center.z + 0.1f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x  + 16, center.y, center.z + 4.0f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 15.9f, center.y, center.z + 7.9f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 8.3f, center.y, center.z + 8.3f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x, center.y, center.z}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x , center.y, center.z + 4}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x , center.y, center.z + 12}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 0.1f, center.y, center.z + 15.9f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x  + 4, center.y, center.z + 16.0f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 7.9f, center.y, center.z + 15.9f}, rot90_180)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 8, center.y, center.z + 12.0f}, rot90_180)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("pillar_" + std::to_string(instanceNumber),"wall_pillar",texNature,{center.x + 12, center.y, center.z + 8}, rot90_180)); instanceNumber++;

            //Floor
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y, center.z + 14}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y, center.z + 2}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 10}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y, center.z + 14}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y, center.z + 6}, rot0)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y, center.z + 6}, rot0)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texBlack,{center.x + 10, center.y - 5, center.z + 10},rot90X, {50, 50, 50})); instanceNumber++;


            //Roof
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3.1f, center.z + 6}, rot0, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3.1f, center.z + 10}, rot0, {0.5,0.5,0.5})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 2, center.y + 3, center.z + 14}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y + 3, center.z + 2}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 10}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 6, center.y + 3, center.z + 14}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 10, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"house_floor",texMedieval,{center.x + 14, center.y + 3, center.z + 6}, rot180X)); instanceNumber++;

            elements.emplace_back(UtilsStructs::createElement("house_floor_" + std::to_string(instanceNumber),"ground",texNature,{center.x + 10, center.y + 3.2f, center.z + 10},rot270X, scaleGround)); instanceNumber++;

            //Stairs
            elements.emplace_back(UtilsStructs::createElement("stairs" + std::to_string(instanceNumber),"stairs",texForniture,{center.x + 2, center.y - 3, center.z + 6.05f},rot180, {2.5, 1.5, 2.0f})); instanceNumber++;

            // Add interior layout
            std::vector<IMElement> layoutElements = CreateHighLShapedSecondFloorLayout(center);

            elements.insert(elements.end(), layoutElements.begin(), layoutElements.end());


            int id = AddRoom(HighLShapedSecondFloor);

            AddTeleporter(center + spawnPositions.at(HighLShapedSecondFloor)[0].position, spawnPositions.at(HighLShapedSecondFloor)[0].rotation, TeleporterList::TeleportUse::HighLShapedStairsDown, id);

            return elements;
        }

    
    
    //House Layout
    //Wall decorations
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
            element = UtilsStructs::createElement("sword_frame_" + std::to_string(instanceNumber),"sword_frame",texDungeon,{pos.x, pos.y , pos.z}, {rot.x,rot.y,rot.z}, {scale.x,scale.y,scale.z}); instanceNumber++;
        }
        if (rand_int == 2){
            element = UtilsStructs::createElement("picture_" + std::to_string(instanceNumber),"picture1",texForniture,{pos.x + pictureOffset.x, pos.y + pictureOffset.y , pos.z + pictureOffset.z}, {rot.x,rot.y,rot.z}, {scale.x,scale.y,scale.z}); instanceNumber++;
        }
        if(rand_int == 3) {
            element = UtilsStructs::createElement("picture_" + std::to_string(instanceNumber), "picture2",
                                                  {"forniture", "pnois"}, {pos.x + pictureOffset.x, pos.y + pictureOffset.y, pos.z + pictureOffset.z}, {rot.x, rot.y, rot.z},
                                                  {scale.x, scale.y, scale.z});
            instanceNumber++;
        }
        return element;
    }
    // Study table with single chair
    static std::vector<IMElement> CreateStudyTableWithChair(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 tableScale = {1,1,1}){
        std::vector<IMElement> elements;
        elements.reserve(2);
        
        // Study table (table2)
        elements.emplace_back(UtilsStructs::createElement("study_table_" + std::to_string(instanceNumber), "table2", texDungeon, {pos.x, pos.y + 0.7f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        
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
        
        elements.emplace_back(UtilsStructs::createElement("chair_" + std::to_string(instanceNumber), "dungeon_chair3", texDungeon, {chairPos.x, chairPos.y, chairPos.z}, {0, chairRot, 0}, {1,1,1})); instanceNumber++;
        
        return elements;
    }
    // Dining table with chairs
    static std::vector<IMElement> CreateTableWithChairs(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 tableScale = {2,2,2}, int numChairs = 2){
        std::vector<IMElement> elements;
        elements.reserve(5);
        
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
        elements.emplace_back(UtilsStructs::createElement("table_" + std::to_string(instanceNumber), tableModel, texDungeon, {pos.x, pos.y + tableYOffset, pos.z}, {rot.x, rot.y, rot.z}, {realTableScale.x, realTableScale.y, realTableScale.z})); instanceNumber++;
        
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
            elements.emplace_back(UtilsStructs::createElement("chair_" + std::to_string(instanceNumber), "dungeon_chair3", texDungeon, {chair1Pos.x, chair1Pos.y, chair1Pos.z}, {0, chair1Rot, 0}, {1,1,1})); instanceNumber++;
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
            elements.emplace_back(UtilsStructs::createElement("chair_" + std::to_string(instanceNumber), "dungeon_chair3", texDungeon, {chair2Pos.x, chair2Pos.y, chair2Pos.z}, {0, chair2Rot, 0}, {1,1,1})); instanceNumber++;
        }

        if(rand_deco == 1){
            elements.emplace_back(UtilsStructs::createElement("bottle_" + std::to_string(instanceNumber), "bottle", texDungeon, {pos.x, pos.y + 1.3f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            DrunkEffectManager::bottles.emplace_back(glm::vec3(pos.x, pos.y + 1.3f, pos.z));
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
            elements.emplace_back(UtilsStructs::createElement("plate_" + std::to_string(instanceNumber), "empty_plate", texDungeon,{plate1Pos.x,plate1Pos.y,plate1Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("plate_" + std::to_string(instanceNumber), "full_plate", texDungeon, {plate2Pos.x,plate2Pos.y,plate2Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 3){
            elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light4", texDungeon, {pos.x, pos.y + 1.3f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z}));
            CandleManager::candlePositions["candle_" + std::to_string(instanceNumber)] = glm::vec3(pos.x, pos.y + 1.3f, pos.z);
            instanceNumber++;
        }
        if(rand_deco == 4){
            elements.emplace_back(UtilsStructs::createElement("flower_" + std::to_string(instanceNumber), "flower1", texDungeon, {pos.x, pos.y + 1.0f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        if(rand_deco == 5){
            elements.emplace_back(UtilsStructs::createElement("flower_" + std::to_string(instanceNumber), "flower2", texDungeon, {pos.x, pos.y + 1.0f, pos.z}, {rot.x, rot.y, rot.z})); instanceNumber++;
        }
        if(rand_deco == 6){
            elements.emplace_back(UtilsStructs::createElement("flower_" + std::to_string(instanceNumber), "flower3", texDungeon, {pos.x, pos.y + 0.99f, pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
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
            elements.emplace_back(UtilsStructs::createElement("coins_" + std::to_string(instanceNumber), "coins1", texDungeon, {coins1Pos.x, coins1Pos.y, coins1Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("coins_" + std::to_string(instanceNumber), "coins2", texDungeon, {coins2Pos.x, coins2Pos.y, coins2Pos.z}, {rot.x, rot.y, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
            elements.emplace_back(UtilsStructs::createElement("coins_" + std::to_string(instanceNumber), "coins3", texDungeon, {coins3Pos.x, coins3Pos.y, coins3Pos.z}, {rot.x, rot.y + 180, rot.z}, {tableScale.x, tableScale.y, tableScale.z})); instanceNumber++;
        }
        return elements;
    }
    //Decoration placed on the ground (tables and chairs)
    static std::vector<IMElement> CreateGroundedDeco(glm::vec3 pos, glm::vec3 rot = {0,0,0}){
        std::vector<IMElement> elements;
        elements.reserve(10);
        int rand_int = UtilsStructs::rand_int(1,5);
        if (rand_int == 1){
            elements = CreateStudyTableWithChair(pos, rot + glm::vec3(0,90,0));
        }
        else elements = CreateTableWithChairs(pos);
        return elements;
    }
    //Random Boxes
    static IMElement CreateRandomBox(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 scale = {1,1,1}){
        int rand_int = UtilsStructs::rand_int(1,3);
        if (rand_int == 1){
            return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box6",texDungeon,{pos.x , pos.y + 0.4f , pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 2){
            return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box8",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 3){
            return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box10",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        return UtilsStructs::createElement("chest_" + std::to_string(instanceNumber),"dungeon_box6",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});

    }
    //Random Libraries
    static IMElement CreateRandomLibrary(glm::vec3 pos, glm::vec3 rot = {0,0,0}, glm::vec3 scale = {1,1,1}){
        int rand_int = UtilsStructs::rand_int(1,4);
        if (rand_int == 1){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library3",texDungeon,{pos.x , pos.y + 0.4f , pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 2){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library4",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 3){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library5",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        if (rand_int == 4){
            return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library6",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});
        }
        return UtilsStructs::createElement("library_" + std::to_string(instanceNumber),"dungeon_library1",texDungeon,{pos.x , pos.y + 0.4f, pos.z}, {rot.x , rot.y, rot.z}, {scale.x , scale.y, scale.z});

    }
    // Layout of a Base House
    static std::vector<IMElement> CreateBaseHouseLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(10);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 4.0f, center.y + 2, center.z - 3.8f})); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x - 3.7f, center.y, center.z - 2.5f}, rot0, scaleBed)); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x - 3.7f, center.y, center.z - 0.5f}));

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 3.5f, center.y, center.z});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    // Layout of a High House, first floor
    static std::vector<IMElement> CreateHighHouseFirstFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(10);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 4.0f, center.y + 2, center.z - 3.5f})); instanceNumber++;

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 3.5f, center.y, center.z});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    // Layout of a High House, second floor
    static std::vector<IMElement> CreateHighHouseSecondFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(10);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateRandomLibrary({center.x, center.y - 0.5f , center.z + 3.8f}, {rot180[0],rot180[1],rot180[2]})); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 3.7f, center.y, center.z - 0.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 3.7f, center.y, center.z + 0.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 2, center.y, center.z}, {rot270[0], rot270[1], rot270[2]}));


        return elements;
    }
    // Layout of a Double House, first floor (left and right are the same)
    static std::vector<IMElement> CreateDoubleFirstFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(15);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x, center.y + 2.0f, center.z - 3.5f})); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x, center.y + 2, center.z + 3.5f}, {0,180,0})); instanceNumber++;

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x, center.y, center.z + 2}, {0,90,0});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    // Layout of a Double House, second floor right side
    static std::vector<IMElement> CreateDoubleSecondFloorRightLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(10);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x, center.y + 2.0f, center.z + 3.5f}, rot180)); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 3.7f, center.y, center.z - 0.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 3.7f, center.y, center.z + 0.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 2, center.y, center.z}, {0,270,0}));


        return elements;
    }
    // Layout of a Double House, second floor left side
    static std::vector<IMElement> CreateDoubleSecondFloorLeftLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(10);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x, center.y + 2.0f, center.z - 3.5f}, rot0)); instanceNumber++;

        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 3.7f, center.y, center.z - 0.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 3.7f, center.y, center.z + 0.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 2, center.y, center.z}, {rot270[0], rot270[1], rot270[2]}));


        return elements;
    }
    // Layout of a L-Shaped House
    static std::vector<IMElement> CreateLShapedLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(15);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 8.0f, center.y + 2.0f, center.z + 0.5f})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 0.5f, center.y + 2.0f, center.z + 2}, rot90)); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 14}, {rot90[0], rot90[1], rot90[2]})); instanceNumber++;
        elements.emplace_back(CreateWallDeco({center.x + 14, center.y + 2, center.z + 0.6f})); instanceNumber++;
        elements.emplace_back(CreateRandomLibrary({center.x + 0.2f, center.y - 0.5f , center.z + 8}, {rot90[0], rot90[1], rot90[2]})); instanceNumber++;


        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 6.5f, center.y, center.z + 13.5f}, rot180, scaleBed)); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 6.5f, center.y, center.z + 11.5f}, {0,180,0}));

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 8, center.y, center.z + 2.5}, {rot90[0], rot90[1], rot90[2]});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    // Layout of a High L-Shaped House, first floor
    static std::vector<IMElement> CreateHighLShapedFirstFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(15);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 8.0f, center.y + 2.0f, center.z + 0.5f})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 0.5f, center.y + 2.0f, center.z + 2}, rot90)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 7.5f, center.y + 2.0f, center.z + 14}, rot270)); instanceNumber++;


        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 14}, {rot90[0], rot90[1], rot90[2]})); instanceNumber++;
        elements.emplace_back(CreateWallDeco({center.x + 14, center.y + 2, center.z + 0.6f})); instanceNumber++;

        //Bed
        elements.emplace_back(CreateRandomBox({center.x + 0.6f, center.y, center.z + 14}, {0,90,0})); instanceNumber++;

        //GroundedDeco
        std::vector<IMElement> groundElements = CreateGroundedDeco({center.x + 8, center.y, center.z + 2.5}, {rot90[0], rot90[1], rot90[2]});
        elements.insert(elements.end(), groundElements.begin(), groundElements.end());

        return elements;
    }
    // Layout of a High L-Shaped House, second floor
    static std::vector<IMElement> CreateHighLShapedSecondFloorLayout(glm::vec3 center){
        std::vector<IMElement> elements;
        elements.reserve(10);
        //Fixed Lights
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 14.0f, center.y + 2.0f, center.z + 0.5f})); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("candle_" + std::to_string(instanceNumber), "dungeon_light3", texDungeon, {center.x + 0.5f, center.y + 2.0f, center.z + 8}, rot90)); instanceNumber++;

        //WallDeco
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 14}, {0,90,0})); instanceNumber++;
        elements.emplace_back(CreateWallDeco({center.x + 0.6f, center.y + 2, center.z + 2},{0,90,0})); instanceNumber++;
        elements.emplace_back(CreateRandomLibrary({center.x + 8.0f, center.y - 0.5f , center.z + 0.2}, {rot0[0], rot0[1], rot0[2]})); instanceNumber++;


        //Bed
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 13.5f, center.y, center.z + 4.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(UtilsStructs::createElement("bed_" + std::to_string(instanceNumber),"bed",texForniture,{center.x + 13.5f, center.y, center.z + 3.5f}, rot270, scaleBed)); instanceNumber++;
        elements.emplace_back(CreateRandomBox({center.x + 11.5, center.y, center.z + 4}, {0, 270, 0}));

        return elements;
    }
    static std::vector<IMElement> CreateHouseInteriors(glm:: vec3 origin, float distance = 20.0f);

    static std::vector<IMElement> CreateHouse(HouseTemplate tmp, glm::vec3 center);

};

#endif //E09_INTERIORMANAGER_HPP



