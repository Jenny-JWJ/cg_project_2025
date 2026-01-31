//
// Created by ACER on 15/11/2025.
//

#ifndef E09_MAPMANAGER_HPP
#define E09_MAPMANAGER_HPP
#endif //E09_MAPMANAGER_HPP

#include <string>
#include <fstream>
#include <vector>
#include <map>        // Required for std::map
#include <cmath>      // Required for fabs()
#include <random>
#include <algorithm>  // Required for std::max
#include <glm/vec3.hpp>
#include <json.hpp>
#include "CollisionBoxGenerator.hpp"
#include "UtilsStructs.hpp"
#include "InteriorManager.hpp"
#include "TeleporterList.hpp"
#include "RoomManager.hpp"

using json = nlohmann::json;

using MMFormat = UtilsStructs::Format;
using MMTechnique = UtilsStructs::Technique;
using MMAssetFile = UtilsStructs::AssetFile;
using MMModel = UtilsStructs::Model;
using MMTexture = UtilsStructs::Texture;
using MMElement = UtilsStructs::Element;
using MMInstance = UtilsStructs::Instance;

class MapManager {
public:
    float gridsize = 20.0f;

    static bool debug;

    static std::map<std::string, std::string> modelsPaths;

    static std::map<std::string, std::string> texturePaths;

    static std::string jsonPath;

    static std::mt19937_64 gen;

    static std::string getExtension(const std::string &path) {
        // Trova l'ultima occorrenza del punto
        size_t dotPos = path.find_last_of('.');
        if (dotPos == std::string::npos) {
            return ""; // Nessun punto → nessuna estensione
        }

        // Trova l'ultima slash per evitare errori tipo "/path.to/file"
        size_t slashPos = path.find_last_of("/\\");
        if (slashPos != std::string::npos && dotPos < slashPos) {
            return ""; // Il punto è in una cartella, non è un'estensione
        }

        return path.substr(dotPos); // Include il punto
    }


    static MMModel makeModel(std::pair<std::string, std::string> modelPath) {
        std::string extension = getExtension(modelPath.first);
        MMFormat format;
        if (extension == ".obj")
            format = UtilsStructs::OBJ;
        if (extension == ".mgcg")
            format = UtilsStructs::MGCG;
        if (extension == ".gltf" || extension == ".glb")
            format = UtilsStructs::GLTF;
        return UtilsStructs::createModel(modelPath.second, "VDsimp", modelPath.first, format);
    }

    static MMTexture makeTexture(std::pair<std::string, std::string> texturePath) {
        return UtilsStructs::createTexture(texturePath.second, texturePath.first, UtilsStructs::C);
    }

    static std::vector<MMModel> makeModels() {
        std::vector<MMModel> models;
        for (const auto &model: modelsPaths) {
            models.emplace_back(makeModel(model));
        }
        return models;
    }

    static std::vector<MMTexture> makeTextures() {
        std::vector<MMTexture> textures;
        printf("\n--- [DEBUG] STARTING TEXTURE LOADING ---\n");

        for (const auto &texPair: texturePaths) {
            // Check 1: Does the file actually exist?
            std::ifstream file(texPair.first.c_str());
            if (!file.good()) {
                printf("[!!! FATAL ERROR !!!] FILE NOT FOUND: %s\n", texPair.first.c_str());
                printf("Double check the path and ensure ID '%s' is correct.\n", texPair.second.c_str());
            } else {
                printf("[OK] File found: %s -> ID: %s\n", texPair.first.c_str(), texPair.second.c_str());
            }

            // Check 2: Missing ID check
            if (texPair.second.empty()) {
                printf("[WARNING] Texture ID for %s is EMPTY!\n", texPair.first.c_str());
            }

            textures.emplace_back(makeTexture(texPair));
        }

        printf("--- [DEBUG] TEXTURE LOADING FINISHED ---\n\n");
        return textures;
    }

    // -------------------------------------------------------
    // ENUM → STRING conversion
    // -------------------------------------------------------

    static std::string formatToString(MMFormat f) {
        switch (f) {
            case UtilsStructs::GLTF: return "GLTF";
            case UtilsStructs::MGCG: return "MGCG";
            case UtilsStructs::ASSET: return "ASSET";
            case UtilsStructs::OBJ: return "OBJ";
            case UtilsStructs::D: return "D";
            case UtilsStructs::C: return "C";
        }
        return "";
    }

    static std::string techniqueToString(MMTechnique t) {
        switch (t) {
            case UtilsStructs::CookTorranceChar: return "CookTorranceChar";
            case UtilsStructs::CookTorranceNoiseSimp: return "CookTorranceNoiseSimp";
            case UtilsStructs::SkyBox: return "SkyBox";
            //case UtilsStructs::PBR: return "PBR";
            case UtilsStructs::Vegetation: return "Vegetation";
            case UtilsStructs::CBoxDebug: return "DebugCollisionBoxes";
        }
        return "";
    }

    // -------------------------------------------------------
    // SERIALIZATION FUNCTIONS
    // -------------------------------------------------------

    static json writeAssetFile(const MMAssetFile &a) {
        json j;
        j["id"] = a.id;
        j["file"] = a.file;
        j["format"] = formatToString(a.format);
        return j;
    }

    static json writeModel(const MMModel &m) {
        json j;
        j["id"] = m.id;
        j["VD"] = m.VD;
        j["model"] = m.model;

        if (!m.node.empty()) j["node"] = m.node;
        if (m.meshId >= 0) j["meshId"] = m.meshId;
        if (!m.asset.empty()) j["asset"] = m.asset;

        j["format"] = formatToString(m.format);
        return j;
    }

    static json writeTexture(const MMTexture &t) {
        json j;
        j["id"] = t.id;
        j["texture"] = t.texture;
        j["format"] = formatToString(t.format);
        return j;
    }

    static json writeElement(const MMElement &e) {
        json j;
        j["id"] = e.id;
        j["model"] = e.model;

        json texArr = json::array();
        for (int i = 0; i < 4; i++) {
            if (!e.texture[i].empty())
                texArr.push_back(e.texture[i]);
        }
        j["texture"] = texArr;

        j["translate"] = {e.translate[0], e.translate[1], e.translate[2]};
        j["eulerAngles"] = {e.eulerAngles[0], e.eulerAngles[1], e.eulerAngles[2]};
        j["scale"] = {e.scale[0], e.scale[1], e.scale[2]};

        return j;
    }

    static json writeInstance(const MMInstance &inst) {
        json j;
        j["technique"] = techniqueToString(inst.technique);

        json arr = json::array();
        for (const auto &e: inst.elements) {
            if (!e.id.empty())
                arr.push_back(writeElement(e));
        }

        j["elements"] = arr;
        return j;
    }


    static std::vector<MMElement> placeGlobalEnvironment(const std::vector<MMElement> &riverTiles,
                                                         const std::vector<MMElement> &buildings) {
        std::vector<MMElement> env;

        // Grid settings for distribution
        float step = 6.0f; // Density: lower is more dense
        float mapLimit = 400.0f;
        float castleBoundary = 220.0f; // Threshold between City and Castle zones

        for (float x = -mapLimit; x <= mapLimit; x += step) {
            for (float z = -mapLimit; z <= mapLimit; z += step) {
                // 1. CHECK RIVER (Avoid the hole)
                if (isRiverZone(x, z, riverTiles)) continue;

                // 2. CHECK ROADS (Avoid X=0 and Z=0 main roads)
                if (std::abs(x) < 12.0f || std::abs(z) < 12.0f) continue;

                // 3. CHECK BUILDINGS (Avoid houses and castle)
                bool hitBuilding = false;
                for (const auto &b: buildings) {
                    float dx = x - b.translate[0];
                    float dz = z - b.translate[2];
                    if ((dx * dx + dz * dz) < 100.0f) {
                        // 10 units safety radius
                        hitBuilding = true;
                        break;
                    }
                }
                if (hitBuilding) continue;

                // 4. ZONE LOGIC
                // Randomized offset to avoid perfect grid alignment (looks more natural)
                float offsetX = ((float) rand() / RAND_MAX - 0.5f) * 4.0f;
                float offsetZ = ((float) rand() / RAND_MAX - 0.5f) * 4.0f;

                if (x > castleBoundary) {
                    // --- CASTLE ZONE: Only Vegetation (Trees/Plants) ---
                    std::string model = (rand() % 2 == 0) ? "tree1" : "tree2";
                    env.emplace_back(UtilsStructs::createElement(
                        "castle_veg_" + std::to_string(rand()), model,
                        {"tex_veg_atlas", "pnois"}, {x + offsetX, 0, z + offsetZ},
                        {0, (float) (rand() % 360), 0}, {0.5f, 0.5f, 0.5f}
                    ));
                } else {
                    // --- CITY ZONE: Only Grass Tufts ---
                    env.emplace_back(UtilsStructs::createElement(
                        "city_grass_" + std::to_string(rand()), "grass_tuft",
                        {"tex_nature_atlas_1", "pnois"}, {x + offsetX, 0, z + offsetZ},
                        {90, (float) (rand() % 360), 0}, {1.0f, 1.0f, 1.0f}
                    ));
                }
            }
        }
        return env;
    }

    // --- CIRCULAR LIGHTS (Geometric ring around the castle) ---
    static std::vector<MMElement> createCircularLights() {
        std::vector<MMElement> elements;
        float centerX = 330.0f;
        float centerZ = 0.0f;
        float radius = 48.0f; // Positioned between the barrels and the tents
        int numLights = 10; // Number of lamps in the ring

        for (int i = 0; i < numLights; i++) {
            float angle = i * (2.0f * 3.14159f / numLights);
            float posX = centerX + radius * cos(angle);
            float posZ = centerZ + radius * sin(angle);

            // Lamps face the center to light up the courtyard
            float rotY = -glm::degrees(angle) + 90.0f;

            elements.emplace_back(UtilsStructs::createElement(
                "castle_lamp_" + std::to_string(i),
                "lamp1",
                {"tex_medieval_atlas", "pnois"},
                {posX, 0.0f, posZ},
                {90, rotY, 0},
                {1.0f, 1.0f, 1.0f}
            ));
        }
        return elements;
    }

    // --- CIRCULAR CAMP GENERATION (Tents in a ring) ---
    static std::vector<MMElement> createCircularCamp() {
        std::vector<MMElement> elements;
        float centerX = 330.0f; // Castle X center
        float centerZ = 0.0f; // Castle Z center
        float radius = 55.0f; // Distance from the castle
        int numTents = 8; // Total number of tents in the circle

        for (int i = 0; i < numTents; i++) {
            // Calculate the angle for each tent (360 degrees / numTents)
            float angle = i * (2.0f * 3.14159f / numTents);
            float posX = centerX + radius * cos(angle);
            float posZ = centerZ + radius * sin(angle);

            // Rotation: orient tents to face the center (castle)
            // We take the angle, convert to degrees, and adjust for the model's forward axis
            float rotY = -glm::degrees(angle) + 90.0f;

            // Alternate models and separate textures for visual variety
            std::string modelId = (i % 2 == 0) ? "tent1" : "tent2";
            std::string texId = (i % 2 == 0) ? "tent1_texture" : "tent2_texture";

            elements.emplace_back(UtilsStructs::createElement(
                "tent_circ_" + std::to_string(i),
                modelId,
                {texId, "pnois"},
                {posX, 0.0f, posZ},
                {90, rotY, 0},
                {1.3f, 1.3f, 1.3f} // Scale: Tents should be slightly bigger than the player
            ));
        }
        return elements;
    }

    // --- CIRCULAR BARRELS (All standing upright on the ground) ---
    static std::vector<MMElement> createCircularBarrels() {
        std::vector<MMElement> elements;
        float centerX = 330.0f;
        float centerZ = 0.0f;
        float radius = 42.0f; // Inner ring near the castle walls
        int numGroups = 6;

        for (int i = 0; i < numGroups; i++) {
            float angle = (i * (2.0f * 3.14159f / numGroups)) + 0.5f;
            float posX = centerX + radius * cos(angle);
            float posZ = centerZ + radius * sin(angle);

            // Group of 3 barrels, all standing (Rotation 90,0,0) and on the ground (Y=0)
            // Barrel 1
            elements.emplace_back(UtilsStructs::createElement("bar_a_" + std::to_string(i), "barrel",
                                                              {"tex_medieval_atlas", "pnois"}, {posX, 0, posZ},
                                                              {90, 0, 0}, {0.7f, 0.7f, 0.7f}));
            // Barrel 2 - Slightly offset
            elements.emplace_back(UtilsStructs::createElement("bar_b_" + std::to_string(i), "barrel",
                                                              {"tex_medieval_atlas", "pnois"},
                                                              {posX + 1.2f, 0, posZ + 0.8f}, {90, 0, 0},
                                                              {0.7f, 0.7f, 0.7f}));
            // Barrel 3 - Now standing upright next to the others instead of being on top
            elements.emplace_back(UtilsStructs::createElement("bar_c_" + std::to_string(i), "barrel",
                                                              {"tex_medieval_atlas", "pnois"},
                                                              {posX - 0.8f, 0, posZ + 1.2f}, {90, 0, 0},
                                                              {0.7f, 0.7f, 0.7f}));
        }
        return elements;
    }

    // --- CIRCULAR GRASS FILLER (Detailing the camp ground) ---
    static std::vector<MMElement> createGrassTufts(int count = 50) {
        std::vector<MMElement> tufts;
        // Distribute tufts randomly within the ring area (between radius 35 and 65)
        std::uniform_real_distribution<float> distRadius(35.0f, 65.0f);
        std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * 3.14159f);

        for (int i = 0; i < count; i++) {
            float r = distRadius(gen);
            float a = distAngle(gen);
            float posX = 330.0f + r * cos(a);
            float posZ = 0.0f + r * sin(a);

            // Uses Nature Atlas 1 for detailed grass/bush textures
            tufts.emplace_back(UtilsStructs::createElement("tuft_circ_" + std::to_string(i), "grass_tuft",
                                                           {"tex_nature_atlas_1", "pnois"}, {posX, 0.0f, posZ},
                                                           {90, distAngle(gen) * 50.0f, 0}, {1.0f, 1.0f, 1.0f}));
        }
        return tufts;
    }

    static std::vector<MMElement> createCastle() {
        std::vector<MMElement> castles;
        castles.emplace_back(UtilsStructs::createElement(
            "the_big_castle",
            "castle_model",
            {"tex_medieval_atlas", "pnois"},
            {330.0f, 0.0f, 0.0f},
            {90.0f, -90.0f, 0.0f},
            {1.0f, 1.0f, 1.0f}
        ));

        return castles;
    }

    static std::vector<MMElement> createBridge() {
        std::vector<MMElement> bridges;
        bridges.emplace_back(UtilsStructs::createElement(
            "main_bridge",
            "bridge",
            {"tex_medieval_atlas", "pnois"},
            {240.0f, -5.0f, 0.0f},
            {90.0f, 90.0f, 0.0f},
            {5.0f, 5.0f, 1.2f}
        ));

        return bridges;
    }

    // Generates perfectly straight ramps: two for the Z-river and one for the X-river
    static std::vector<MMElement> createRiverRamps() {
        std::vector<MMElement> ramps;
        float angle = 12.0f;
        float midHeight = -2.485f;

        // Left Ramp
        ramps.emplace_back(UtilsStructs::createElement("ramp_v_left", "ground",
                                                       {"tex_nature_atlas_2", "pnois"},
                                                       {221.71f, midHeight, 0.0f},
                                                       {90.0f + angle, 90.0f, 0.0f},
                                                       {100.0f, 1.2f, 4.0f}));

        // Right Ramp
        ramps.emplace_back(UtilsStructs::createElement("ramp_v_right", "ground",
                                                       {"tex_nature_atlas_2", "pnois"},
                                                       {258.3f, midHeight, 0.0f},
                                                       {90.0f - angle, 90.0f, 0.0f},
                                                       {100.0f, 1.2f, 4.0f}));
        return ramps;
    }

    // Generates a simple L-shaped river path turning towards positive X
    static std::vector<MMElement> createRiverPath() {
        std::vector<MMElement> river;
        float startX = 240.0f;
        float startZ = -250.0f;
        float depth = -2.3f;
        float step = 20.0f;

        for (int i = 0; i < 25; i++) {
            float currentZ = startZ + (i * step);
            river.emplace_back(UtilsStructs::createElement("river_v_" + std::to_string(i), "river_mid",
                                                           {"tex_medieval_atlas", "pnois"}, {startX, depth, currentZ},
                                                           {90, 90, 0}));
        }
        return river;
    }

    // -------------------------------------------------------
    // WATER LAYER: generate water tiles on top of river bed
    // -------------------------------------------------------
    static std::vector<MMElement>
    createRiverWaterFromBed(const std::vector<MMElement>& riverBed) {

        std::vector<MMElement> water;
        float waterOffsetY = 0.15f; // avoid z-fighting
        float widthScale = 2.25f;

        for (const auto& bed : riverBed) {

            water.emplace_back(UtilsStructs::createElement(
                    bed.id + "_water",
                    "river_water",
                    {"water_river_texture", "pnois"},
                    {
                            bed.translate[0],
                            bed.translate[1] + waterOffsetY,
                            bed.translate[2]
                    },
                    {
                            bed.eulerAngles[0],
                            bed.eulerAngles[1],
                            bed.eulerAngles[2]
                    },
                    {
                            bed.scale[0],
                            bed.scale[1]* widthScale,
                            bed.scale[2]* widthScale
                    }
            ));
        }
        return water;
    }



    static bool isRiverZone(float x, float z, const std::vector<MMElement> &riverTiles) {
        // 1. Scava lungo tutto il percorso del fiume (X=240)
        for (const auto &river: riverTiles) {
            if (std::abs(x - river.translate[0]) < 30.0f &&
                std::abs(z - river.translate[2]) < 30.0f) {
                return true;
            }
        }
        // 2. Scava il buco dove poggiano le rampe laterali
        if (std::abs(z - 0.0f) < 25.0f && (std::abs(x - 220.0f) < 15.0f || std::abs(x - 260.0f) < 15.0f)) {
            return true;
        }
        return false;
    }

    static std::vector<MMElement> createGraveyard(glm::vec3 center){
        std::vector<MMElement> elements;
        
        // Grid configuration
        int gridSize = 5; // 5x5 graves per grid
        float spacing = 4.0f; // Distance between graves
        float roadWidth = 8.0f; // Distance between grids (like a road)
        
        // Calculate offsets for each quadrant
        // Each grid is 5 graves * 2 spacing = 10 units wide/tall (0 to 8)
        float gridExtent = (gridSize - 1) * spacing; // 8 units
        float halfRoad = roadWidth / 2.0f;
        
        // Four grid positions relative to center
        std::vector<std::pair<float, float>> gridOffsets = {
            {-(gridExtent + halfRoad), (halfRoad)},           // Top-left
            {(halfRoad), (halfRoad)},                         // Top-right
            {-(gridExtent + halfRoad), -(gridExtent + halfRoad)}, // Bottom-left
            {(halfRoad), -(gridExtent + halfRoad)}            // Bottom-right
        };
        
        int idNumber = 0;
        
        // Create 4 grids of graves
        for (int grid = 0; grid < 4; grid++) {
            float baseX = center.x + gridOffsets[grid].first;
            float baseZ = center.z + gridOffsets[grid].second;
            
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                    // Random grave selection (1 to 21)
                    int graveNumber = rand_int(1, 21);
                    
                    float posX = baseX + (j * spacing);
                    float posZ = baseZ + (i * spacing);
                    
                    // Random rotation for variety
                    float rotY = rand_int(0, 3) * 90.0f;
                    
                    idNumber++;
                    elements.emplace_back(UtilsStructs::createElement(
                        "grave_" + std::to_string(grid) + "_" + std::to_string(idNumber),
                        "grave" + std::to_string(graveNumber),
                        {"dungeon", "pnois"},
                        {posX, 0.5f, posZ},
                        {0.0f, rotY, 0.0f},
                        {1.0f, 1.0f, 1.0f}
                    ));
                }
            }
        }
        
        // Add statue at the center
        elements.emplace_back(UtilsStructs::createElement(
            "cemetery_statue",
            "statue",
            {"dungeon", "pnois"},
            {center.x, 0.0f, center.z},
            {0.0f, 0.0f, 0.0f},
            {1.5f, 1.5f, 1.5f} // Slightly larger for prominence
        ));
        
        return elements;
    }

    // Modified ground generation to prevent tiles from overlapping and covering the river
    static std::vector<MMElement> placeGrassGround(const std::vector<MMElement> &riverTiles,
                                                   float hight = 800.0f, float lenght = 800.0f,
                                                   float x_offset = 400.0f, float z_offset = 400.0f,
                                                   float scale = 20.0f) {
        std::vector<MMElement> elements;
        int count_x = hight / scale;
        int count_z = lenght / scale;
        int idNumber = 0;
        std::string idName = "grass_ground";

        for (int i = 0; i < count_z; i++) {
            for (int j = 0; j < count_x; j++) {
                float posX = j * scale - x_offset;
                float posZ = i * scale - z_offset;

                if (isRiverZone(posX, posZ, riverTiles)) {
                    continue;
                }

                idNumber++;
                elements.emplace_back(UtilsStructs::createElement(idName + std::to_string(idNumber), "ground",
                                                                  {"tex_nature_atlas_2", "pnois"}, {
                                                                      j * scale - x_offset, 0, i * scale - z_offset
                                                                  }, {90, 0, 0}, {1, 1, 1}));
            }
        }
        return elements;
    }

    static std::vector<MMElement> createPaths(std::vector<float> starting_pos, std::vector<float> ending_pos,
                                              float x_pass, float z_pass, std::vector<float> scale = {1, 0.5, 1},
                                              int idNumber = 0) {
        std::vector<MMElement> elements;
        float diff_x = fabs(starting_pos[0] - ending_pos[0]);
        float diff_z = fabs(starting_pos[2] - ending_pos[2]);
        int x_step = x_pass != 0 ? diff_x / x_pass : 0;
        int z_step = z_pass != 0 ? diff_z / z_pass : 0;
        int steps = std::max(x_step, z_step);

        std::string idName = "path_ground";
        float posx = starting_pos[0];
        float posz = starting_pos[2];

        for (int i = 0; i < steps; i++) {
            idNumber++;
            elements.emplace_back(UtilsStructs::createElement(
                idName + std::to_string(idNumber),
                "ground",
                {"tex_medieval_atlas", "pnois"},
                {posx, 0.01f, posz},
                {90, 0, 0},
                {scale[0], scale[1], scale[2]}
            ));

            if (i < x_step)
                posx += x_pass;
            if (i < z_step)
                posz += z_pass;
        }
        return elements;
    }

    static int rand_int(int lo, int hi) {
        std::uniform_int_distribution<int> dist(lo, hi);
        return dist(gen);
    }

    static std::vector<int> CreatePathVector(int modelNumber, int thisIdNumber = 0);

    static glm::vec3 getTeleporterPos(glm::vec3 housePos, float houseRotY, int modelNumber);

    static void AddTeleporter(glm::vec3 housePos, int modelNumber){
        if(modelNumber == 3)
            AddTeleporter(housePos, 6);
        float houseRotY;
        glm::vec2 lookDir;
        if(housePos.z <= 0){
            lookDir = {0,0};
            houseRotY = 180;
        }
        if(housePos.z > 0){
            lookDir = {3.0, 0};
            houseRotY = 0;
        }
        glm::vec2 spawnLookDir;
        if(housePos.z <= 0)
            spawnLookDir = {3.0,0};
        if(housePos.z > 0)
            spawnLookDir = {0, 0};
        glm::vec3 teleporterPos = getTeleporterPos(housePos, houseRotY,modelNumber);
        glm::vec3 halfSize = {1,1,1};

        int id = RoomManager::AddRoom(InteriorManager::ExternalEntrance);
        int tpId = TeleporterList::addTeleporter(teleporterPos,halfSize,lookDir,teleporterPos,spawnLookDir,TeleporterList::TeleportUse::ExternalHouse, id);
        TeleporterList::teleporters.at(tpId).teleporter->SetTeleportPath(CreatePathVector(modelNumber, id));
    }

    static std::vector<MMElement> placeHouses(float hight = 200.0, float lenght = 200.0, float x_offset = 50.0,
                                              float z_offset = 50.0, float scale = 20.0, int idNumber = 0,
                                              std::vector<float> rotation = {90, 0, 0}) {
        std::vector<MMElement> elements;
        int count_x = hight / scale;
        int count_z = lenght / scale;
        std::string idName = "house";

        for (int i = 0; i < count_z; i++) {
            for (int j = 0; j < count_x; j++) {
                std::string model_number = std::to_string(rand_int(1, 5));
                idNumber++;
                elements.emplace_back(UtilsStructs::createElement(
                    idName + model_number + "_" + std::to_string(idNumber), "bldg" + model_number,
                    {"tex_medieval_atlas", "pnois"}, {j * scale - x_offset, 0, i * scale - z_offset}, rotation,
                    {1, 1, 1}));
                AddTeleporter({j * scale - x_offset, 0, i * scale - z_offset}, std::strtol(model_number.c_str(), nullptr, 10));
            }
        }
        return elements;
    }

    static std::vector<MMElement> placeVegetationInGrid(float height = 200.0, float length = 200.0,
                                                        float x_offset = 50.0, float z_offset = 50.0,
                                                        float minDistance = 2.5f,
                                                        std::vector<std::string> modelIds = {"tree"},
                                                        std::string textureId = "tex_veg_atlas",
                                                        const std::vector<MMElement> &obstacles = {}) {
        std::vector<MMElement> elements;

        int targetCount = (int) ((height * length) / (minDistance * minDistance)) * 0.1;

        if (targetCount > 1000) targetCount = 1000;

        int idNumber = 0;
        std::uniform_real_distribution<float> randomX(0.0f, height);
        std::uniform_real_distribution<float> randomZ(0.0f, length);
        std::uniform_real_distribution<float> scaleDist(0.3f, 0.7f);
        std::uniform_real_distribution<float> rotDist(0.0f, 360.0f);
        std::uniform_int_distribution<int> modelSelector(0, modelIds.size() - 1);
        float obstacleSafeRadius = 11.0f;

        for (int i = 0; i < targetCount; i++) {
            float plantX = randomX(gen) - x_offset;
            float plantZ = randomZ(gen) - z_offset;
            float roadSafeZone = 12.0f;
            if (std::abs(plantX) < roadSafeZone || std::abs(plantZ) < roadSafeZone) continue;

            bool hitObstacle = false;
            for (const auto &obs: obstacles) {
                float dx = plantX - obs.translate[0];
                float dz = plantZ - obs.translate[2];
                float distSq = dx * dx + dz * dz;
                if (distSq < (obstacleSafeRadius * obstacleSafeRadius)) {
                    hitObstacle = true;
                    break;
                }
            }
            if (hitObstacle) continue;

            bool tooClose = false;
            for (const auto &el: elements) {
                float dx = plantX - el.translate[0];
                float dz = plantZ - el.translate[2];
                float distSq = dx * dx + dz * dz;
                if (distSq < (minDistance * minDistance)) {
                    tooClose = true;
                    break;
                }
            }
            if (tooClose) continue;

            idNumber++;
            int selectedIndex = modelSelector(gen);
            elements.emplace_back(UtilsStructs::createElement(
                "veg_" + std::to_string(idNumber) + "_" + std::to_string(rand()),
                modelIds[selectedIndex], {textureId, "pnois"},
                {plantX, 0.0f, plantZ}, {0.0f, rotDist(gen), 0.0f},
                {scaleDist(gen), scaleDist(gen), scaleDist(gen)}
            ));
        }
        return elements;
    }

    // -------------------------------------------------------
    // HELPER FUNCTION: Place rocks STRICTLY ON THE ROAD (Randomized & Tiny)
    // -------------------------------------------------------
    static std::vector<MMElement> placeRocksOnRoad(int count = 40,
                                                   float mapLimit = 200.0f,
                                                   std::vector<std::string> modelIds = {"rocks1"},
                                                   std::string textureId = "tex_veg_atlas") {
        std::vector<MMElement> elements;

        // Random Generators

        // 1. Position along the road length (Longitudinal)
        std::uniform_real_distribution<float> randomPos(-mapLimit, mapLimit);

        // 2. Position across the road width (Lateral)
        // Keep strictly centered (-1.5 to +1.5) to ensure they stay on the pavement
        std::uniform_real_distribution<float> randomWidth(-1.5f, 1.5f);

        // 3. Scale: Tiny pebbles/debris
        // Range 0.08 - 0.20 makes them look like small stones
        std::uniform_real_distribution<float> scaleDist(0.08f, 0.2f);

        // 4. Random Rotation
        std::uniform_real_distribution<float> rotDist(0.0f, 360.0f);

        // 5. MMModel Selector (Picks a random index)
        std::uniform_int_distribution<int> modelSelector(0, modelIds.size() - 1);

        for (int i = 0; i < count; i++) {
            float rockX, rockZ;
            int direction = rand() % 2;

            if (direction == 0) {
                // Horizontal Road
                rockX = randomPos(gen);
                rockZ = randomWidth(gen);
            } else {
                // Vertical Road
                rockX = randomWidth(gen);
                rockZ = randomPos(gen);
            }

            // Lower Height (Y)
            // 0.05f ensures tiny rocks sit on the ground and don't float
            float rockY = 0.05f;

            // Overlap check
            bool tooClose = false;
            for (const auto &el: elements) {
                float dx = rockX - el.translate[0];
                float dz = rockZ - el.translate[2];
                // Distance threshold 0.3 because rocks are small
                if ((dx * dx + dz * dz) < 0.3f) {
                    tooClose = true;
                    break;
                }
            }
            if (tooClose) {
                i--;
                continue;
            }

            // Pick Random MMModel
            int selectedIndex = modelSelector(gen);
            std::string currentModel = modelIds[selectedIndex];

            // Create MMElement
            elements.emplace_back(UtilsStructs::createElement(
                "rock_" + std::to_string(i) + "_" + std::to_string(rand()),
                currentModel,
                {textureId, "pnois"},
                {rockX, rockY, rockZ},
                {0.0f, rotDist(gen), 0.0f},
                {scaleDist(gen), scaleDist(gen), scaleDist(gen)}
            ));
        }
        return elements;
    }

    // -------------------------------------------------------
    // HELPER FUNCTION: Place Street Lights (EXACTLY ON ROAD EDGE)
    // -------------------------------------------------------
    static std::vector<MMElement> placeStreetLights(float mapLimit = 200.0f,
                                                    int axis = 0,
                                                    float spacing = 25.0f,
                                                    std::string modelId = "lamp1",
                                                    std::string textureId = "tex_medieval_atlas") {
        std::vector<MMElement> elements;

        float start = -mapLimit;
        float end = mapLimit;
        int count = (int) ((end - start) / spacing);

        float offsetFromCenter = 6.0f;

        for (int i = 0; i <= count; i++) {
            float currentPos = start + (i * spacing);

            // Skip intersection
            if (std::abs(currentPos) < 15.0f) continue;

            glm::vec3 posLeft, posRight;
            glm::vec3 rotLeft, rotRight;

            float xRot = 90.0f;

            if (axis == 0) {
                // Horizontal Road
                posLeft = {currentPos, 0.0f, offsetFromCenter};
                rotLeft = {xRot, 180.0f, 0.0f};

                posRight = {currentPos, 0.0f, -offsetFromCenter};
                rotRight = {xRot, 0.0f, 0.0f};
            } else {
                // Vertical Road
                posLeft = {offsetFromCenter, 0.0f, currentPos};
                rotLeft = {xRot, 90.0f, 0.0f};

                posRight = {-offsetFromCenter, 0.0f, currentPos};
                rotRight = {xRot, -90.0f, 0.0f};
            }

            std::vector<float> scaleVec = {1.0f, 1.0f, 1.0f};

            // Left Lamp
            elements.emplace_back(UtilsStructs::createElement(
                "lamp_" + std::to_string(axis) + "_L_" + std::to_string(i),
                modelId, {textureId, "pnois"},
                {posLeft.x, posLeft.y, posLeft.z},
                {rotLeft.x, rotLeft.y, rotLeft.z},
                scaleVec
            ));

            // Right Lamp
            elements.emplace_back(UtilsStructs::createElement(
                "lamp_" + std::to_string(axis) + "_R_" + std::to_string(i),
                modelId, {textureId, "pnois"},
                {posRight.x, posRight.y, posRight.z},
                {rotRight.x, rotRight.y, rotRight.z},
                scaleVec
            ));
        }
        return elements;
    }

    // -------------------------------------------------------
    // BUILD JSON DOCUMENT
    // -------------------------------------------------------

    static json buildJson(std::vector<MMAssetFile> &assets,
                          std::vector<MMModel> &models,
                          std::vector<MMTexture> &textures,
                          std::vector<MMInstance> &instances) {
        json doc;

        doc["assetfiles"] = json::array();
        for (auto &a: assets)
            doc["assetfiles"].push_back(writeAssetFile(a));

        doc["models"] = json::array();
        for (auto &m: models)
            doc["models"].push_back(writeModel(m));

        doc["textures"] = json::array();
        for (auto &t: textures)
            doc["textures"].push_back(writeTexture(t));

        doc["instances"] = json::array();
        for (auto &inst: instances)
            doc["instances"].push_back(writeInstance(inst));

        return doc;
    }

    // -------------------------------------------------------
    // SAVE JSON TO FILE
    // -------------------------------------------------------

    static void saveJson(const json &j, const std::string &path) {
        std::ofstream file(path);
        if (!file.is_open())
            throw std::runtime_error("Impossibile aprire il file JSON");

        file << j.dump(4); // indent = 4
    }

    static void Initialize() {
        modelsPaths = {
            {"assets/models/Castle/SPW_Medieval_Bldg_01.mgcg", "bldg1"},
            {"assets/models/Castle/SPW_Medieval_Bldg_02.mgcg", "bldg2"},
            {"assets/models/Castle/SPW_Medieval_Bldg_03.mgcg", "bldg3"},
            {"assets/models/Castle/SPW_Medieval_Bldg_04.mgcg", "bldg4"},
            {"assets/models/Castle/SPW_Medieval_Bldg_06.mgcg", "bldg5"},
            {"assets/models/Castle/SPW_Medieval_Boat.mgcg", "boat"},
            {"assets/models/Castle/SPW_Medieval_Box_01.mgcg", "box1"},
            {"assets/models/Castle/SPW_Medieval_Box_02.mgcg", "box2"},
            {"assets/models/Castle/SPW_Medieval_Box_03.mgcg", "box3"},
            {"assets/models/Castle/SPW_Medieval_Props_01.mgcg", "well"},
            {"assets/models/Castle/SPW_Terrain_Grass_Flat.mgcg", "ground"},
            {"assets/models/Vegetation/vegetation.016.mgcg", "tree1"},
            {"assets/models/Vegetation/vegetation.025.mgcg", "tree2"},
            {"assets/models/Vegetation/vegetation.028.mgcg", "tree3"},
            {"assets/models/Vegetation/vegetation.029.mgcg", "tree4"},
            {"assets/models/Vegetation/vegetation.051.mgcg", "rocks1"},
            {"assets/models/Vegetation/vegetation.052.mgcg", "rocks2"},
            {"assets/models/Vegetation/vegetation.053.mgcg", "rocks3"},
            {"assets/models/Castle/SPW_Medieval_Light.mgcg", "lamp1"},
            {"assets/models/Interiors/door_005_Mesh.119.mgcg", "door"},
            {"assets/models/Interiors/door_026_Mesh.6709.mgcg", "door_frame"},
            {"assets/models/Interiors/tunnel.031_Mesh.7927.mgcg", "wall"},
            {"assets/models/Interiors/SPW_Natures_Wood.mgcg", "wall_pillar"},
            {"assets/models/Interiors/floor_001_Mesh.640.mgcg", "house_floor"},
            {"assets/models/Interiors/Stairs_013_Mesh.674.mgcg", "stairs"},
            {"assets/models/Interiors/window_004_Mesh.432.mgcg", "window"},
            {"assets/models/Interiors/tunnel.024_Mesh.6126.mgcg", "tunnel"},
            {"assets/models/CollisionBoxes/cube.obj", "cube"},
            {"assets/models/CollisionBoxes/sphere.obj", "sphere"},
            {"assets/models/CollisionBoxes/cylinder.obj", "cylinder"},
            {"assets/models/River/SPW_Terrain_River_Corner.mgcg", "river_corner"},
            {"assets/models/River/SPW_Terrain_River_Intersection.mgcg", "river_fork"},
            {"assets/models/River/SPW_Terrain_River_Mid.mgcg", "river_mid"},
            {"assets/models/Castle/SPW_Medieval_Props_Stand_01.mgcg", "bridge"},
            {"assets/models/Castle/SPW_Medieval_Castle_01.mgcg", "castle_model"},
            {"assets/models/Castle/SPW_Medieval_Barrel.mgcg", "barrel"},
            {"assets/models/Castle/SPW_Medieval_Tent_01.mgcg", "tent1"},
            {"assets/models/Castle/SPW_Medieval_Tent_03.mgcg", "tent2"},
            {"assets/models/Castle/SPW_Natures_Bush_01.mgcg", "grass_tuft"},
            {"assets/models/Dungeon/prop.001_Mesh.900.mgcg", "bucket"},
            {"assets/models/River/SPW_Terrain_Water.mgcg", "river_water"},
            {"assets/models/Cemetery/grave.002_Mesh.7917.mgcg", "grave1"},
            {"assets/models/Cemetery/grave.003_Mesh.7906.mgcg", "grave2"},
            {"assets/models/Cemetery/grave.004_Mesh.7750.mgcg", "grave3"},
            {"assets/models/Cemetery/grave.005_Mesh.4386.mgcg", "grave4"},
            {"assets/models/Cemetery/grave.006_Mesh.5495.mgcg", "grave5"},
            {"assets/models/Cemetery/grave.007_Mesh.5383.mgcg", "grave6"},
            {"assets/models/Cemetery/grave.008_Mesh.5380.mgcg", "grave7"},
            {"assets/models/Cemetery/grave.009_Mesh.909.mgcg", "grave8"},
            {"assets/models/Cemetery/grave.010_Mesh.908.mgcg", "grave9"},
            {"assets/models/Cemetery/grave.012_Mesh.4385.mgcg", "grave10"},
            {"assets/models/Cemetery/grave.013_Mesh.6740.mgcg", "grave11"},
            {"assets/models/Cemetery/grave.015_Mesh.7919.mgcg", "grave12"},
            {"assets/models/Cemetery/grave.018_Mesh.7873.mgcg", "grave13"},
            {"assets/models/Cemetery/grave.019_Mesh.4590.mgcg", "grave14"},
            {"assets/models/Cemetery/grave.020_Mesh.895.mgcg", "grave15"},
            {"assets/models/Cemetery/grave.022_Mesh.6139.mgcg", "grave16"},
            {"assets/models/Cemetery/grave.030_Mesh.7845.mgcg", "grave17"},
            {"assets/models/Cemetery/grave.031_Mesh.5496.mgcg", "grave18"},
            {"assets/models/Cemetery/grave.039_Mesh.897.mgcg", "grave19"},
            {"assets/models/Cemetery/grave.041_Mesh.898.mgcg", "grave20"},
            {"assets/models/Cemetery/grave.045_Mesh.6263.mgcg", "grave21"},
            {"assets/models/Cemetery/coffin_Mesh.7527.mgcg", "coffin1"},
            {"assets/models/Cemetery/coffin.002_Mesh.7922.mgcg", "coffin2"},
            {"assets/models/Cemetery/coffin.003_Mesh.7918.mgcg", "coffin3"},
            {"assets/models/Cemetery/coffin.004_Mesh.7920.mgcg", "coffin4"},
            {"assets/models/Cemetery/bones.022_Mesh.6372.mgcg", "bones1"},
            {"assets/models/Cemetery/bones.025_Mesh.7708.mgcg", "bones2"},
            {"assets/models/Cemetery/bones.029_Mesh.5843.mgcg", "bones3"},
            {"assets/models/Cemetery/bones.030_Mesh.5848.mgcg", "bones4"},
            {"assets/models/Cemetery/cast_Mesh.6268.mgcg", "cast1"},
            {"assets/models/Cemetery/cast.001_Mesh.8090.mgcg", "cast2"},
            {"assets/models/Cemetery/cast.002_Mesh.6272.mgcg", "cast3"},
            {"assets/models/Cemetery/fence.001_Mesh.5505.mgcg", "fence1"},
            {"assets/models/Cemetery/fence.002_Mesh.5501.mgcg", "fence2"},
            {"assets/models/Cemetery/fence.003_Mesh.5500.mgcg", "fence3"},
            {"assets/models/Cemetery/fence.023_Mesh.4424.mgcg", "fence4"},
            {"assets/models/Cemetery/decoration.017_Mesh.299.mgcg", "statue"},
        };

        texturePaths = {
            {"assets/textures/Castle_Textures/SPW_Medieval.png", "tex_medieval_atlas"},
            {"assets/textures/Castle_Textures/SPW_Natures_01.png", "tex_nature_atlas_1"},
            {"assets/textures/Castle_Textures/SPW_Natures_02.png", "tex_nature_atlas_2"},
            {"assets/textures/Vegetation/Textures_Vegetation.png", "tex_veg_atlas"},
            {"assets/textures/FornitureTextures.png", "forniture"},
            {"assets/textures/DungeonTextures.png", "dungeon"},
            {"assets/textures/Perlin_noise.png", "pnois"},
            {"assets/textures/day_sky.png", "skybox"},
            {"assets/textures/Black.png", "black"},
            {"assets/textures/brown.png", "brown"},
            {"assets/textures/translucent_lightblue_texture.png", "colBox_texture"},
            {"assets/textures/Castle_Textures/SPW_Medieval_Tent_01_Color01.png", "tent1_texture"},
            {"assets/textures/Castle_Textures/SPW_Medieval_Tent_03_Color02.png", "tent2_texture"},
            {"assets/textures/fillerwell.png", "tex_well_depth"},
            {"assets/textures/water.png","water_well_texture"},
            {"assets/textures/Castle_Textures/SPW_Medieval_Tent_03_Color02.png", "tent2_texture"},
            {"assets/textures/water_river.png", "water_river_texture"},

        };
    }

    // -------------------------------------------------------
    // MAIN FUNCTION: Generate the scene.json file
    // -------------------------------------------------------
    static void makeJson() {
        Initialize();
        jsonPath = "assets/models/scene.json";

        // --- A. ASSETS & MODELS ---
        std::vector<MMAssetFile> assetFiles = {
            UtilsStructs::createAssetFile("hm", "assets/models/uomo.gltf", UtilsStructs::GLTF),
            UtilsStructs::createAssetFile("a1", "assets/models/running.gltf", UtilsStructs::GLTF),
            UtilsStructs::createAssetFile("a2", "assets/models/idle.gltf", UtilsStructs::GLTF),
            UtilsStructs::createAssetFile("a3", "assets/models/pointing.gltf", UtilsStructs::GLTF),
            UtilsStructs::createAssetFile("a4", "assets/models/waving.gltf", UtilsStructs::GLTF),
            UtilsStructs::createAssetFile("ct", "assets/models/MainSceneEnvOnly.gltf", UtilsStructs::GLTF)
        };

        std::vector<MMModel> models = makeModels();
        models.emplace_back(
            UtilsStructs::createModel("hm0", "VDchar", "Mesh", UtilsStructs::ASSET, "Ch01_Body", 0, "hm"));
        models.emplace_back(
            UtilsStructs::createModel("hm1", "VDchar", "Mesh", UtilsStructs::ASSET, "Ch01_Body", 1, "hm"));
        models.emplace_back(
            UtilsStructs::createModel("skybox", "VDskybox", "assets/models/SkyBoxCube.obj", UtilsStructs::OBJ));

        std::vector<MMTexture> textures = makeTextures();
        textures.emplace_back(
            UtilsStructs::createTexture("st", "assets/textures/uomo/Ch01_1001_Diffuse.png", UtilsStructs::C));

        // --- B. CHARACTER ELEMENTS ---
        std::vector<MMElement> charElements = {
            UtilsStructs::createElement("hm0", "hm0", {"st"}),
            UtilsStructs::createElement("hm1", "hm1", {"st"}),
        };

        // --- C. RIVER & INFRASTRUCTURE ---
        // 1. Create the river tiles
        std::vector<MMElement> riverTiles = createRiverPath();

        // 3. Create the river water
        std::vector<MMElement> riverWater = createRiverWaterFromBed(riverTiles);

        // 3. Create the river ramps
        std::vector<MMElement> ramps = createRiverRamps();

        // 4. Create the bridge (Il Pontos)
        std::vector<MMElement> bridgeElements = createBridge();

        // 5. Create the castle
        std::vector<MMElement> castleElements = createCastle();

        auto campTents = createCircularCamp();
        auto campBarrels = createCircularBarrels();
        auto campTufts = createGrassTufts(60); // Higher count for better density
        auto campLights = createCircularLights();

        // --- D. GROUND GENERATION ---
        std::vector<MMElement> simpElements = placeGrassGround(riverTiles);

        simpElements.insert(simpElements.end(), riverTiles.begin(), riverTiles.end());
        simpElements.insert(simpElements.end(), riverWater.begin(), riverWater.end());
        simpElements.insert(simpElements.end(), ramps.begin(), ramps.end());
        simpElements.insert(simpElements.end(), bridgeElements.begin(), bridgeElements.end());
        simpElements.insert(simpElements.end(), castleElements.begin(), castleElements.end());
        simpElements.insert(simpElements.end(), campTents.begin(), campTents.end());
        simpElements.insert(simpElements.end(), campBarrels.begin(), campBarrels.end());
        simpElements.insert(simpElements.end(), campTufts.begin(), campTufts.end());
        simpElements.insert(simpElements.end(), campLights.begin(), campLights.end());

        // --- E. ROADS & PATHS ---
        float widthH = 0.4f;
        float widthV = 0.4f;


        auto paths1 = createPaths({-200, 0, 0}, {210, 0, 0}, 20, 0, {2.1f, widthH, 1.0f}, 0);
        simpElements.insert(simpElements.end(), paths1.begin(), paths1.end());

        // Vertical Road
        auto paths2 = createPaths({0, 0, -200}, {0, 0, 200}, 0, 20, {widthV, 2.1f, 1.0f}, 20);
        simpElements.insert(simpElements.end(), paths2.begin(), paths2.end());

        // --- F. PROPS (Rocks & Lights) ---
        std::vector<std::string> rockModels = {"rocks1", "rocks2", "rocks3"};
        std::vector<MMElement> roadRocks = placeRocksOnRoad(40, 200.0f, rockModels, "tex_veg_atlas");
        simpElements.insert(simpElements.end(), roadRocks.begin(), roadRocks.end());

        std::vector<MMElement> lightsH = placeStreetLights(200.0f, 0, 25.0f, "lamp1", "tex_medieval_atlas");
        simpElements.insert(simpElements.end(), lightsH.begin(), lightsH.end());

        std::vector<MMElement> lightsV = placeStreetLights(200.0f, 1, 25.0f, "lamp1", "tex_medieval_atlas");
        simpElements.insert(simpElements.end(), lightsV.begin(), lightsV.end());

        std::vector<MMElement> interior = InteriorManager::CreateHouseInteriors({900, 0, 900});
        simpElements.insert(simpElements.end(), interior.begin(), interior.end());

        // --- G. GRAVEYARD ---
        glm::vec3 graveyardCenter = {350.0f, 0.0f, -110.0f};
        std::vector<MMElement> graveYard = createGraveyard(graveyardCenter);
        simpElements.insert(simpElements.end(), graveYard.begin(), graveYard.end());
        
        // Graveyard paths - Cross roads and perimeter
        // Parameters from createGraveyard: spacing=4, roadWidth=8, gridSize=5
        float graveyardExtent = 20.0f; // Cross roads through center
        float perimeterExtent = 24.0f; // Perimeter paths further out
        float pathInset = 1.5f; // Inset to prevent overlap at corners
        float pathScale = 0.24f; // Width scale (0.8x narrower)
        
        // Horizontal cross path (through center)
        auto gravePath1 = createPaths(
            {graveyardCenter.x - graveyardExtent + 2.5f, 0, graveyardCenter.z},
            {graveyardCenter.x + graveyardExtent, 0, graveyardCenter.z}, 
            2.0f, 0, {0.8f, pathScale, 1.0f}, 1000);
        simpElements.insert(simpElements.end(), gravePath1.begin(), gravePath1.end());
        
        // Vertical cross path (through center)
        auto gravePath2 = createPaths(
            {graveyardCenter.x, 0, graveyardCenter.z - graveyardExtent + 2.5f},
            {graveyardCenter.x, 0, graveyardCenter.z + graveyardExtent}, 
            0, 2.0f, {pathScale, 0.8f, 1.0f}, 2000);
        simpElements.insert(simpElements.end(), gravePath2.begin(), gravePath2.end());
        
        // Perimeter square - Top side
        auto gravePath3 = createPaths(
            {graveyardCenter.x - perimeterExtent + pathInset + 4.1f, 0, graveyardCenter.z + perimeterExtent},
            {graveyardCenter.x + perimeterExtent - pathInset -2.0f, 0, graveyardCenter.z + perimeterExtent},
            2.0f, 0, {0.8f, pathScale, 1.0f}, 3000);
        simpElements.insert(simpElements.end(), gravePath3.begin(), gravePath3.end());
        
        // Perimeter square - Bottom side
        auto gravePath4 = createPaths(
            {graveyardCenter.x - perimeterExtent + pathInset + 4.1f, 0, graveyardCenter.z - perimeterExtent},
            {graveyardCenter.x + perimeterExtent - pathInset -2.0f, 0, graveyardCenter.z - perimeterExtent},
            2.0f, 0, {0.8f, pathScale, 1.0f}, 4000);
        simpElements.insert(simpElements.end(), gravePath4.begin(), gravePath4.end());
        
        // Perimeter square - Left side
        auto gravePath5 = createPaths(
            {graveyardCenter.x - perimeterExtent, 0, graveyardCenter.z - perimeterExtent + pathInset + 5},
            {graveyardCenter.x - perimeterExtent, 0, graveyardCenter.z + perimeterExtent - pathInset - 2.2f},
            0, 2.0f, {pathScale, 0.8f, 1.0f}, 5000);
        simpElements.insert(simpElements.end(), gravePath5.begin(), gravePath5.end());
        
        // Perimeter square - Right side
        auto gravePath6 = createPaths(
            {graveyardCenter.x + perimeterExtent, 0, graveyardCenter.z - perimeterExtent + pathInset + 4.1f},
            {graveyardCenter.x + perimeterExtent, 0, graveyardCenter.z + perimeterExtent - pathInset - 0.9f},
            0, 2.0f, {pathScale, 0.8f, 1.0f}, 6000);
        gravePath6.emplace_back(UtilsStructs::createElement("pathAdditive", "ground",{"tex_medieval_atlas", "pnois"}, {graveyardCenter.x + perimeterExtent, 0.01f, graveyardCenter.z + perimeterExtent - pathInset - 4.1f}, {90, 0, 0},{pathScale, 0.8f, 1.0f}));
        simpElements.insert(simpElements.end(), gravePath6.begin(), gravePath6.end());

        float areaW = 150.0f;
        float areaL = 150.0f;
        float gridSize = 30.0f;
        std::vector<MMElement> h1 = placeHouses(areaW, areaL, -20, -20, gridSize, 0, {90, 180, 0});
        std::vector<MMElement> h2 = placeHouses(areaW, areaL, -20, 140, gridSize, 25);
        std::vector<MMElement> h3 = placeHouses(areaW, areaL, 140, -20, gridSize, 50, {90, 180, 0});
        std::vector<MMElement> h4 = placeHouses(areaW, areaL, 140, 140, gridSize, 75);

        std::vector<MMElement> extras;
        extras.emplace_back(UtilsStructs::createElement("ww1", "well", {"tex_medieval_atlas", "pnois"}, {0, 0, 0},
                                                        {90, 0, 0}, {1, 1, 1}));

        // --- Inside makeJson() -> extras section ---
        for (int i = 0; i < 8; i++) {
            // Randomize position slightly around the center
            float angle = i * (2.0f * 3.14159f / 8.0f);
            float dist = 0.05f + (rand() % 100 / 1000.0f); // Random radius between 0.05 and 0.15
            float posX = cos(angle) * dist;
            float posZ = sin(angle) * dist;

            extras.emplace_back(UtilsStructs::createElement(
                "well_splash_" + std::to_string(i),
                "cube",
                {"water_well_texture", "pnois"},
                {posX, 0.08, posZ}, // Fixed at water level initially
                {0, 0, 0},
                {0.04f, 0.04f, 0.04f} // Keep them tiny
            ));
        }

        //Basic rope
        extras.emplace_back(UtilsStructs::createElement(
            "well_rope_wire",
            "cylinder",
            {"brown", "pnois"},
            {0.0f, 1.38f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.025f, 0.6f, 0.025f}
        ));

        //Bucket surface filler
        extras.emplace_back(UtilsStructs::createElement(
            "well_mask",
            "cylinder",
            {"tex_well_depth", "pnois"},
            {0.0f, 1.2f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.36f, 0.01f, 0.36f}
        ));

        //Basic bucket
        extras.emplace_back(UtilsStructs::createElement(
            "well_bucket",
            "bucket",
            {"dungeon", "pnois"},
            {0.0f, 1.14f, 0.0f},
            {0, 0, 0},
            {1.0f, 1.0f, 1.0f}
        ));

        //Spawned bucket
        extras.emplace_back(UtilsStructs::createElement(
            "spawned_bucket",
            "bucket",
            {"dungeon", "pnois"},
            {2.5f, -100.0f, 2.5f},
            {0, 0, 0},
            {1.0f, 1.0f, 1.0f}
        ));

        std::vector<MMElement> allObstacles;
        allObstacles.insert(allObstacles.end(), h1.begin(), h1.end());
        allObstacles.insert(allObstacles.end(), h2.begin(), h2.end());
        allObstacles.insert(allObstacles.end(), h3.begin(), h3.end());
        allObstacles.insert(allObstacles.end(), h4.begin(), h4.end());
        allObstacles.insert(allObstacles.end(), extras.begin(), extras.end());

        // --- H. VEGETATION ---
        std::vector<std::string> treeModels = {"tree1", "tree2", "tree3", "tree4"};
        float treeSpacing = 5.0f;
        std::vector<MMElement> vegElements = placeVegetationInGrid(areaW, areaL, -20, -20, treeSpacing, treeModels,
                                                                   "tex_veg_atlas", allObstacles);
        auto v2 = placeVegetationInGrid(areaW, areaL, -20, 140, treeSpacing, treeModels, "tex_veg_atlas", allObstacles);
        auto v3 = placeVegetationInGrid(areaW, areaL, 140, -20, treeSpacing, treeModels, "tex_veg_atlas", allObstacles);
        auto v4 = placeVegetationInGrid(areaW, areaL, 140, 140, treeSpacing, treeModels, "tex_veg_atlas", allObstacles);
        vegElements.insert(vegElements.end(), v2.begin(), v2.end());
        vegElements.insert(vegElements.end(), v3.begin(), v3.end());
        vegElements.insert(vegElements.end(), v4.begin(), v4.end());

        simpElements.insert(simpElements.end(), allObstacles.begin(), allObstacles.end());

        // --- I. FINALIZING INSTANCES ---
        std::vector<MMElement> skyboxElements = {UtilsStructs::createElement("skybox", "skybox", {"skybox"})};

        CollisionBoxGenerator::fillCollisionsBoxes(simpElements);
        CollisionBoxGenerator::fillCollisionsBoxes(vegElements);

        MMInstance debugBox;
        if (debug) {
            CollisionBoxGenerator::fillCollisionsBoxesVisual();
            debugBox = CollisionBoxGenerator::collisionInstance;
        }

        std::vector<MMInstance> istances;
        if (!debug && debugBox.elements.empty())
            istances = {
                UtilsStructs::createInstance(UtilsStructs::CookTorranceChar, charElements),
                UtilsStructs::createInstance(UtilsStructs::CookTorranceNoiseSimp, simpElements),
                UtilsStructs::createInstance(UtilsStructs::SkyBox, skyboxElements),
                UtilsStructs::createInstance(UtilsStructs::Vegetation, vegElements)
            };
        else {
            istances = {
                UtilsStructs::createInstance(UtilsStructs::CookTorranceChar, charElements),
                UtilsStructs::createInstance(UtilsStructs::CookTorranceNoiseSimp, simpElements),
                UtilsStructs::createInstance(UtilsStructs::SkyBox, skyboxElements),
                UtilsStructs::createInstance(UtilsStructs::Vegetation, vegElements),
                debugBox
            };
        }

        json jsonobj = buildJson(assetFiles, models, textures, istances);
        saveJson(jsonobj, jsonPath);
    }
};
