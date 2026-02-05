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

    /**
 * CIRCULAR LIGHTS GENERATION
 * Places a ring of street lamps around the castle courtyard.
 * Each lamp is automatically rotated to face the center (330, 0).
 */
    static std::vector<MMElement> createCircularLights() {
        std::vector<MMElement> elements;
        elements.reserve(10);  // Pre-allocate to avoid reallocations
        
        // Constants
        const float centerX = 330.0f;
        const float centerZ = 0.0f;
        const float radius = 48.0f;
        const int numLights = 10;
        
        // Reusable constant arrays (created once, reused 10 times)
        static const std::vector<std::string> textures = {"tex_medieval_atlas", "pnois"};
        static const std::vector<float> baseScale = {1.0f, 1.0f, 1.0f};

        for (int i = 0; i < numLights; i++) {
            // Distribute lamps evenly (2 * PI = 360 degrees)
            float angle = i * (2.0f * 3.14159f / numLights);
            float posX = centerX + radius * cos(angle);
            float posZ = centerZ + radius * sin(angle);

            // Calculate rotation so lamps face inward (-angle converted to deg + offset)
            float rotY = -glm::degrees(angle) + 90.0f;

            elements.emplace_back(UtilsStructs::createElement(
                "castle_lamp_" + std::to_string(i),
                "lamp1",
                textures,
                {posX, 0.0f, posZ},
                {90.0f, rotY, 0.0f},
                baseScale
            ));
        }
        return elements;
    }

    /**
 * CIRCULAR CAMP GENERATION
 * Spawns a ring of tents facing the castle.
 * Alternates between two different tent models for visual variety.
 */
    static std::vector<MMElement> createCircularCamp() {
        std::vector<MMElement> elements;
        elements.reserve(8);  // Pre-allocate
        
        // Constants
        const float centerX = 330.0f;
        const float centerZ = 0.0f;
        const float radius = 55.0f;
        const int numTents = 8;
        
        // Reusable constants (created once, referenced 8 times)
        static const std::vector<float> tentScale = {1.3f, 1.3f, 1.3f};
        static const std::string modelIds[2] = {"tent1", "tent2"};
        static const std::string texIds[2] = {"tent1_texture", "tent2_texture"};
        static const std::string pnois = "pnois";

        for (int i = 0; i < numTents; i++) {
            // Calculate the angle for each tent (360 degrees / numTents)
            float angle = i * (2.0f * 3.14159f / numTents);
            float posX = centerX + radius * cos(angle);
            float posZ = centerZ + radius * sin(angle);

            // Rotation: orient tents to face the center (castle)
            float rotY = -glm::degrees(angle) + 90.0f;

            // Variety logic: select model and texture based on parity
            int variant = i % 2;

            elements.emplace_back(UtilsStructs::createElement(
                "tent_circ_" + std::to_string(i),
                modelIds[variant],
                {texIds[variant], pnois},
                {posX, 0.0f, posZ},
                {90.0f, rotY, 0.0f},
                tentScale
            ));
        }
        return elements;
    }

    /**
 * CIRCULAR BARRELS
 * Place circular barrels inside the camp.
 */
    static std::vector<MMElement> createCircularBarrels() {
        std::vector<MMElement> elements;
        elements.reserve(18);  // 6 groups × 3 barrels = 18
        
        // Constants
        const float centerX = 330.0f;
        const float centerZ = 0.0f;
        const float radius = 42.0f;
        const int numGroups = 6;
        
        // Reusable constants (created once, reused 18 times)
        static const std::vector<std::string> textures = {"tex_medieval_atlas", "pnois"};
        static const std::vector<float> rotation = {90.0f, 0.0f, 0.0f};
        static const std::vector<float> barrelScale = {0.7f, 0.7f, 0.7f};
        static const std::string barrelModel = "barrel";
        static const std::string prefixes[3] = {"bar_a_", "bar_b_", "bar_c_"};

        for (int i = 0; i < numGroups; i++) {
            float angle = (i * (2.0f * 3.14159f / numGroups)) + 0.5f;
            float posX = centerX + radius * cos(angle);
            float posZ = centerZ + radius * sin(angle);

            // Barrel 1 - Base position
            elements.emplace_back(UtilsStructs::createElement(prefixes[0] + std::to_string(i), barrelModel,
                                                              textures, {posX, 0.0f, posZ},
                                                              rotation, barrelScale));
            // Barrel 2 - Offset position
            elements.emplace_back(UtilsStructs::createElement(prefixes[1] + std::to_string(i), barrelModel,
                                                              textures, {posX + 1.2f, 0.0f, posZ + 0.8f},
                                                              rotation, barrelScale));
            // Barrel 3 - Offset position
            elements.emplace_back(UtilsStructs::createElement(prefixes[2] + std::to_string(i), barrelModel,
                                                              textures, {posX - 0.8f, 0.0f, posZ + 1.2f},
                                                              rotation, barrelScale));
        }
        return elements;
    }

    /**
 * Grass Tufts generation
 * Place grass tufts near the castle inside the castle.
 */
    static std::vector<MMElement> createGrassTufts(int count = 50) {
        std::vector<MMElement> tufts;
        tufts.reserve(count);  // Pre-allocate
        
        // Constants
        const float centerX = 330.0f;
        const float centerZ = 0.0f;
        
        // Reusable constants (created once, reused 50+ times)
        static const std::vector<std::string> textures = {"tex_nature_atlas_1", "pnois"};
        static const std::vector<float> baseScale = {1.0f, 1.0f, 1.0f};
        static const std::string tuftModel = "grass_tuft";
        
        // Random distributions (moved outside loop)
        std::uniform_real_distribution<float> distRadius(35.0f, 65.0f);
        std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * 3.14159f);

        for (int i = 0; i < count; i++) {
            float r = distRadius(gen);
            float a = distAngle(gen);
            float posX = centerX + r * cos(a);
            float posZ = centerZ + r * sin(a);
            float rotY = distAngle(gen) * 50.0f;

            tufts.emplace_back(UtilsStructs::createElement("tuft_circ_" + std::to_string(i), tuftModel,
                                                           textures, {posX, 0.0f, posZ},
                                                           {90.0f, rotY, 0.0f}, baseScale));
        }
        return tufts;
    }

    /**
 * CASTLE GENERATION
 * Place castle.
 */
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

    /**
     * BRIDGE GENERATION
     * Place bridge.
     */
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

    /**
 * RIVER RAMPS GENERATION
 * Creates two inclined ground meshes to allow player access to the river bed.
 * Angle is adjusted on the X-axis (90 + angle) to create the slope.
 */
    static std::vector<MMElement> createRiverRamps() {
        std::vector<MMElement> ramps;
        float angle = 12.0f; // Slant angle of the ramp
        float midHeight = -2.485f; // Middle pivot for height alignment

        // Left Ramp: Positioned on one side of the river bed
        ramps.emplace_back(UtilsStructs::createElement("ramp_v_left", "ground",
                                                       {"tex_nature_atlas_2", "pnois"},
                                                       {221.71f, midHeight, 0.0f},
                                                       {90.0f + angle, 90.0f, 0.0f},
                                                       {100.0f, 1.2f, 4.0f}));

        // Right Ramp: Mirrored on the opposite side
        ramps.emplace_back(UtilsStructs::createElement("ramp_v_right", "ground",
                                                       {"tex_nature_atlas_2", "pnois"},
                                                       {258.3f, midHeight, 0.0f},
                                                       {90.0f - angle, 90.0f, 0.0f},
                                                       {100.0f, 1.2f, 4.0f}));
        return ramps;
    }


    /**
 * RIVER PATH GENERATION
 * Loops through a linear path to spawn "river_mid" segments.
 */
    // Optimized: 1 large river piece instead of 25 small tiles
    static std::vector<MMElement> createRiverPath() {
        std::vector<MMElement> river;
        float centerX = 240.0f;
        float centerZ = 0.0f;  // Center of Z range [-250, 250]
        float depth = -2.3f;
        float riverLength = 500.0f;  // Covers -250 to 250
        
        // Single large river bed piece, scaled to cover entire length
        river.emplace_back(UtilsStructs::createElement(
            "river_main",
            "river_mid",
            {"tex_medieval_atlas", "pnois"},
            {centerX, depth, centerZ},
            {90, 90, 0},
            {riverLength / 20.0f, 1.0f, 1.0f}  // Scale X to cover full length (base is 20 units)
        ));
        
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

    /**
 * RIVER ZONE DETECTION
 * Returns true if the given (x, z) coordinates are part of the river bed or the ramp area.
 * Used to prevent spawning grass or obstacles where the terrain should be sunken.
 */
    static bool isRiverZone(float x, float z, const std::vector<MMElement> &riverTiles) {
        // MAIN RIVER BED CHECK
        // Iterate through all placed river segments (usually aligned along X=240)
        for (const auto &river: riverTiles) {
            // Create a 60x60 units exclusion zone (30 units radius) around each tile center
            if (std::abs(x - river.translate[0]) < 30.0f &&
                std::abs(z - river.translate[2]) < 30.0f) {
                return true; // Point is inside the main river flow
            }
        }
        // LATERAL RAMP EXCAVATION
        // Check if the coordinates fall within the two specific areas where ramps provide access.
        // This handles the "cut" into the river banks at Z=0.
        // Left Bank: Near X=220 | Right Bank: Near X=260
        if (std::abs(z - 0.0f) < 25.0f && (std::abs(x - 220.0f) < 15.0f || std::abs(x - 260.0f) < 15.0f)) {
            return true; // Point is inside a ramp transition zone
        }
        return false; // Point is safe to use for standard ground generation
    }

    static std::vector<MMElement> createGraveyard(glm::vec3 center){
        std::vector<MMElement> elements;
        elements.reserve(150);  // 100 graves + ~40 fences + 6 extras
        
        // Reusable constants (created once, reused 140+ times!)
        static const std::vector<std::string> dungeonTextures = {"dungeon", "pnois"};
        static const std::vector<float> graveScale = {1.0f, 1.0f, 1.0f};
        static const std::vector<float> fenceScale = {1.0f, 1.5f, 1.0f};
        static const std::vector<float> postScale = {4.0f, 4.0f, 4.0f};
        static const std::vector<float> statueScale = {1.5f, 1.5f, 1.5f};
        static const std::vector<float> rot180 = {0.0f, 180.0f, 0.0f};
        static const std::vector<float> rot90 = {0.0f, 90.0f, 0.0f};
        static const std::vector<float> rot0 = {0.0f, 0.0f, 0.0f};
        
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
                    int graveNumber = UtilsStructs::rand_int(1, 21);
                    
                    float posX = baseX + (j * spacing);
                    float posZ = baseZ + (i * spacing);
                    
                    // Random rotation for variety
                    float rotY = UtilsStructs::rand_int(0, 3) * 90.0f;
                    
                    idNumber++;
                    elements.emplace_back(UtilsStructs::createElement(
                        "grave_" + std::to_string(grid) + "_" + std::to_string(idNumber),
                        "grave" + std::to_string(graveNumber),
                        dungeonTextures,
                        {posX, 0.5f, posZ},
                        {0.0f, rotY, 0.0f},
                        graveScale
                    ));
                }
            }
        }

        float graveYardWidth = gridSize*spacing + 7.0f;

        // Create fence perimeter using fence2 model
        float fenceSpacing = 3.0f; // Distance between fence segments
        int fenceSegmentsPerSide = (int)((2.0f * graveYardWidth) / fenceSpacing);
        
        // Top side (Z = graveYardWidth) - with entrance in the middle
        for (int i = 0; i <= fenceSegmentsPerSide; i++) {
            if (i == 0 || i == fenceSegmentsPerSide) continue; // Skip corners
            if (i == fenceSegmentsPerSide / 2) continue; // Skip middle segment for entrance
            float posX = center.x - graveYardWidth + (i * fenceSpacing);
            
            // Use fence1 for the segment to the left of the entrance
            std::string fenceModel = (i == fenceSegmentsPerSide / 2 - 1) ? "fence1" : "fence2";
            
            elements.emplace_back(UtilsStructs::createElement(
                "graveFence_top_" + std::to_string(i),
                fenceModel,
                dungeonTextures,
                {posX, 2.25f, center.z + graveYardWidth},
                rot180,
                fenceScale
            ));
        }
        
        // Bottom side (Z = -graveYardWidth)
        for (int i = 0; i <= fenceSegmentsPerSide; i++) {
            if (i == 0 || i == fenceSegmentsPerSide) continue; // Skip corners
            float posX = center.x - graveYardWidth + (i * fenceSpacing);
            elements.emplace_back(UtilsStructs::createElement(
                "graveFence_bottom_" + std::to_string(i),
                "fence2",
                dungeonTextures,
                {posX, 2.25f, center.z - graveYardWidth},
                rot180,
                fenceScale
            ));
        }
        
        // Left side (X = -graveYardWidth)
        for (int i = 0; i <= fenceSegmentsPerSide; i++) {
            if (i == 0 || i == fenceSegmentsPerSide) continue; // Skip corners
            float posZ = center.z - graveYardWidth + (i * fenceSpacing);
            elements.emplace_back(UtilsStructs::createElement(
                "graveFence_left_" + std::to_string(i),
                "fence2",
                dungeonTextures,
                {center.x - graveYardWidth, 2.25f, posZ},
                rot90,
                fenceScale
            ));
        }
        
        // Right side (X = graveYardWidth)
        for (int i = 0; i <= fenceSegmentsPerSide; i++) {
            if (i == 0 || i == fenceSegmentsPerSide) continue; // Skip corners
            float posZ = center.z - graveYardWidth + (i * fenceSpacing);
            elements.emplace_back(UtilsStructs::createElement(
                "graveFence_right_" + std::to_string(i),
                "fence2",
                dungeonTextures,
                {center.x + graveYardWidth, 2.25f, posZ},
                rot90,
                fenceScale
            ));
        }

        // Add corner fence3 posts
        elements.emplace_back(UtilsStructs::createElement("graveWall1", "fence3", dungeonTextures, {center.x + graveYardWidth, 6, center.z + graveYardWidth}, rot0, postScale));
        elements.emplace_back(UtilsStructs::createElement("graveWall2", "fence3", dungeonTextures, {center.x - graveYardWidth, 6, center.z + graveYardWidth}, rot0, postScale));
        elements.emplace_back(UtilsStructs::createElement("graveWall3", "fence3", dungeonTextures, {center.x + graveYardWidth, 6, center.z - graveYardWidth}, rot0, postScale));
        elements.emplace_back(UtilsStructs::createElement("graveWall4", "fence3", dungeonTextures, {center.x - graveYardWidth, 6, center.z - graveYardWidth}, rot0, postScale));

        // Add statue at the center
        elements.emplace_back(UtilsStructs::createElement(
            "cemetery_statue",
            "statue",
            dungeonTextures,
            {center.x, 0.0f, center.z},
            rot0,
            statueScale
        ));
        
        // Add cast3 under the statue (will animate upward)
        elements.emplace_back(UtilsStructs::createElement(
            "cemetery_cast3",
            "cast3",
            dungeonTextures,
            {center.x, -4.0f, center.z},
            rot0,
            graveScale
        ));
        
        return elements;
    }

    // Optimized ground generation: Creates only 2 large ground pieces instead of 1600+ small tiles
    // Left piece: X[-250, 220], Right piece: X[260, 450], both covering Z[-250, 250]
    static std::vector<MMElement> placeGrassGround(const std::vector<MMElement> &riverTiles) {
        std::vector<MMElement> elements;
        elements.reserve(2);  // Only 2 ground pieces
        
        // Reusable constants
        static const std::vector<std::string> grassTextures = {"tex_nature_atlas_2", "pnois"};
        static const std::vector<float> groundRotation = {90.0f, 0.0f, 0.0f};
        static const std::string groundModel = "ground";
        
        // River is at X ≈ 240, width ≈ 60 units (200 to 280)
        float riverCenterX = 240.0f;
        float riverHalfWidth = 30.0f;  // Increased to prevent ground invasion
        
        // World bounds
        float minX = -250.0f;
        float maxX = 450.0f;
        float minZ = -250.0f;
        float maxZ = 250.0f;
        
        // Calculate dimensions for each ground piece
        float leftWidth = (riverCenterX - riverHalfWidth) - minX;  // ~470 units
        float rightWidth = maxX - (riverCenterX + riverHalfWidth); // ~190 units
        float depth = maxZ - minZ;                                  // 500 units
        
        // LEFT GROUND PIECE (west of river)
        // Center it between minX and river left edge
        float leftCenterX = minX + leftWidth / 2.0f;
        float leftCenterZ = (minZ + maxZ) / 2.0f;
        
        elements.emplace_back(UtilsStructs::createElement(
            "grass_ground_left",
            groundModel,
            grassTextures,
            {leftCenterX, 0.0f, leftCenterZ},
            groundRotation,
            {leftWidth / 20.0f, depth / 20.0f, 1.0f}  // Scale to cover the area (base ground is 20x20)
        ));
        
        // RIGHT GROUND PIECE (east of river)
        // Center it between river right edge and maxX
        float rightCenterX = (riverCenterX + riverHalfWidth) + rightWidth / 2.0f;
        float rightCenterZ = (minZ + maxZ) / 2.0f;
        
        elements.emplace_back(UtilsStructs::createElement(
            "grass_ground_right",
            groundModel,
            grassTextures,
            {rightCenterX, 0.0f, rightCenterZ},
            groundRotation,
            {rightWidth / 20.0f, depth / 20.0f, 1.0f}  // Scale to cover the area
        ));
        
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
        
        elements.reserve(steps);  // Pre-allocate based on calculated steps
        
        // Reusable constants
        static const std::vector<std::string> pathTextures = {"tex_medieval_atlas", "pnois"};
        static const std::vector<float> pathRotation = {90.0f, 0.0f, 0.0f};
        static const std::string groundModel = "ground";
        std::vector<float> scaleVec = {scale[0], scale[1], scale[2]};  // Created once

        std::string idName = "path_ground";
        float posx = starting_pos[0];
        float posz = starting_pos[2];

        for (int i = 0; i < steps; i++) {
            idNumber++;
            elements.emplace_back(UtilsStructs::createElement(
                idName + std::to_string(idNumber),
                groundModel,
                pathTextures,
                {posx, 0.01f, posz},
                pathRotation,
                scaleVec
            ));

            if (i < x_step)
                posx += x_pass;
            if (i < z_step)
                posz += z_pass;
        }
        return elements;
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
        int totalHouses = count_x * count_z;
        
        elements.reserve(totalHouses);  // Pre-allocate
        
        // Reusable constants (created once, reused 100+ times)
        static const std::vector<std::string> medievalTextures = {"tex_medieval_atlas", "pnois"};
        static const std::vector<float> defaultScale = {1.0f, 1.0f, 1.0f};
        static const std::string idName = "house";

        for (int i = 0; i < count_z; i++) {
            for (int j = 0; j < count_x; j++) {
                int modelNum = UtilsStructs::rand_int(1, 5);
                idNumber++;
                
                float posX = j * scale - x_offset;
                float posZ = i * scale - z_offset;
                
                elements.emplace_back(UtilsStructs::createElement(
                    idName + std::to_string(modelNum) + "_" + std::to_string(idNumber), 
                    "bldg" + std::to_string(modelNum),
                    medievalTextures, 
                    {posX, 0.0f, posZ}, 
                    rotation,
                    defaultScale));
                
                AddTeleporter({posX, 0.0f, posZ}, modelNum);
            }
        }
        return elements;
    }

    /**
 * PROCEDURAL VEGETATION PLACEMENT
 * Generates a randomized list of vegetation elements (trees, bushes) within a defined area.
 * It automatically avoids obstacles (houses), roads, and overlapping with other plants.
 */
    static std::vector<MMElement> placeVegetationInGrid(float height = 200.0, float length = 200.0,
                                                        float x_offset = 50.0, float z_offset = 50.0,
                                                        float minDistance = 2.5f,
                                                        std::vector<std::string> modelIds = {"tree"},
                                                        std::string textureId = "tex_veg_atlas",
                                                        const std::vector<MMElement> &obstacles = {}) {
        std::vector<MMElement> elements;

        // DENSITY CALCULATION
        // Calculate target count based on area, filling roughly 10% of the available slots.
        int targetCount = (int) ((height * length) / (minDistance * minDistance)) * 0.1;

        if (targetCount > 1000) targetCount = 1000; // Hardware safety cap
        
        elements.reserve(targetCount);  // Pre-allocate for target count
        
        // Reusable constants
        static const std::string pnois = "pnois";

        // RANDOM DISTRIBUTION SETUP
        int idNumber = 0;
        std::uniform_real_distribution<float> randomX(0.0f, height);
        std::uniform_real_distribution<float> randomZ(0.0f, length);
        std::uniform_real_distribution<float> scaleDist(0.3f, 0.7f); // Variation in size
        std::uniform_real_distribution<float> rotDist(0.0f, 360.0f); // Variation in orientation
        std::uniform_int_distribution<int> modelSelector(0, modelIds.size() - 1);

        float obstacleSafeRadius = 11.0f; // Distance to keep away from houses/props

        for (int i = 0; i < targetCount; i++) {
            // Generate potential coordinates
            float plantX = randomX(gen) - x_offset;
            float plantZ = randomZ(gen) - z_offset;

            // ROAD EXCLUSION ZONE
            // Prevents trees from spawning in the center of the world (roads/paths)
            float roadSafeZone = 12.0f;
            if (std::abs(plantX) < roadSafeZone || std::abs(plantZ) < roadSafeZone) continue;

            // OBSTACLE COLLISION CHECK
            // Verify the point is not too close to any house or man-made structure
            bool hitObstacle = false;
            for (const auto &obs: obstacles) {
                float dx = plantX - obs.translate[0];
                float dz = plantZ - obs.translate[2];
                // Using squared distance for performance (avoids expensive sqrt() calls)
                float distSq = dx * dx + dz * dz;
                if (distSq < (obstacleSafeRadius * obstacleSafeRadius)) {
                    hitObstacle = true;
                    break;
                }
            }
            if (hitObstacle) continue;

            // PROXIMITY CHECK (Self-Collision)
            // Ensure this new plant isn't on top of a previously placed plant
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

            // ELEMENT CREATION
            // All checks passed! Add the instance to the list with randomized scale and rotation
            idNumber++;
            int selectedIndex = modelSelector(gen);
            float rotY = rotDist(gen);
            float scale = scaleDist(gen);
            
            elements.emplace_back(UtilsStructs::createElement(
                "veg_" + std::to_string(idNumber) + "_" + std::to_string(rand()),
                modelIds[selectedIndex], 
                {textureId, pnois},
                {plantX, 0.0f, plantZ}, 
                {0.0f, rotY, 0.0f},
                {scale, scale, scale}
            ));
        }
        return elements;
    }

    // -------------------------------------------------------
// PERIMETER TREES WITH RIVER GAP
// Dense forest border, leaving an opening for the river
// -------------------------------------------------------
    static std::vector<MMElement> placePerimeterForest(
            float minX, float maxX,
            float minZ, float maxZ,
            float riverMinX, float riverMaxX,
            int rows = 10,
            float spacing = 6.0f,
            float rowDepth = 4.0f,
            float scaleMul = 1.0f,
            const std::vector<std::string>& modelIds = {"tree1"},
            const std::string& textureId = "tex_veg_atlas"
    ) {
        std::vector<MMElement> elements;
        
        // Estimate tree count: perimeter * rows, accounting for river gap
        int xPositions = (int)((maxX - minX) / spacing) + 1;
        int zPositions = (int)((maxZ - minZ) / spacing) + 1;
        int riverGapCount = (int)((riverMaxX - riverMinX) / spacing);
        int estimatedCount = 2 * rows * (xPositions + zPositions - riverGapCount);
        elements.reserve(estimatedCount);
        
        static const std::string pnois = "pnois";

        std::uniform_real_distribution<float> rotDist(0.0f, 360.0f);
        std::uniform_real_distribution<float> scaleJitter(0.85f, 1.15f);
        std::uniform_real_distribution<float> offsetJitter(-1.0f, 1.0f);
        std::uniform_int_distribution<int> modelSelector(0, modelIds.size() - 1);

        int id = 0;

        auto spawnTree = [&](float x, float z, float depthOffsetX, float depthOffsetZ) {
            float scale = scaleMul * scaleJitter(gen);
            int modelIdx = modelSelector(gen);

            elements.emplace_back(UtilsStructs::createElement(
                    "perimeter_tree_" + std::to_string(id++),
                    modelIds[modelIdx],
                    {textureId, pnois},
                    {
                            x + depthOffsetX + offsetJitter(gen),
                            0.0f,
                            z + depthOffsetZ + offsetJitter(gen)
                    },
                    {0.0f, rotDist(gen), 0.0f},
                    {scale, scale, scale}
            ));
        };

        // -------------------------
        // TOP & BOTTOM borders
        // -------------------------
        for (int r = 0; r < rows; r++) {
            float dz = r * rowDepth;

            for (float x = minX; x <= maxX; x += spacing) {
                if (x > riverMinX && x < riverMaxX) continue;

                spawnTree(x, minZ - dz, 0.0f, 0.0f); // top
                spawnTree(x, maxZ + dz, 0.0f, 0.0f); // bottom
            }
        }

        // -------------------------
        // LEFT & RIGHT borders
        // -------------------------
        for (int r = 0; r < rows; r++) {
            float dx = r * rowDepth;

            for (float z = minZ; z <= maxZ; z += spacing) {
                spawnTree(minX - dx, z, 0.0f, 0.0f); // left
                spawnTree(maxX + dx, z, 0.0f, 0.0f); // right
            }
        }

        return elements;
    }

    /**
 * ROAD DEBRIS GENERATOR (Rocks/Pebbles)
 * Scatters small, randomized rocks strictly along the road centerlines.
 */
    static std::vector<MMElement> placeRocksOnRoad(int count = 40,
                                                   float mapLimit = 200.0f,
                                                   std::vector<std::string> modelIds = {"rocks1"},
                                                   std::string textureId = "tex_veg_atlas") {
        std::vector<MMElement> elements;
        elements.reserve(count);  // Pre-allocate for target count
        
        // Reusable constants
        static const std::string pnois = "pnois";

        // RANDOMIZATION PARAMETERS
        std::uniform_real_distribution<float> randomPos(-mapLimit, mapLimit); // Along road length
        std::uniform_real_distribution<float> randomWidth(-1.5f, 1.5f); // Strict road width constraint
        std::uniform_real_distribution<float> scaleDist(0.08f, 0.2f); // Tiny scale for pebbles
        std::uniform_real_distribution<float> rotDist(0.0f, 360.0f); // Random orientation
        std::uniform_int_distribution<int> modelSelector(0, modelIds.size() - 1);

        for (int i = 0; i < count; i++) {
            float rockX, rockZ;
            int direction = rand() % 2; // 0 for Horizontal, 1 for Vertical road

            if (direction == 0) {
                // Horizontal alignment (Z is narrow, X is long)
                rockX = randomPos(gen);
                rockZ = randomWidth(gen);
            } else {
                // Vertical alignment (X is narrow, Z is long)
                rockX = randomWidth(gen);
                rockZ = randomPos(gen);
            }

            // Set Y height slightly above 0 to prevent "Z-fighting" with the road texture
            float rockY = 0.05f;

            // PROXIMITY CHECK
            bool tooClose = false;
            for (const auto &el: elements) {
                float dx = rockX - el.translate[0];
                float dz = rockZ - el.translate[2];
                // Threshold of 0.3 for small debris overlap detection
                if ((dx * dx + dz * dz) < 0.3f) {
                    tooClose = true;
                    break;
                }
            }
            if (tooClose) {
                // Retry if overlap detected
                i--;
                continue;
            }

            // ELEMENT INSTANTIATION
            int selectedIndex = modelSelector(gen);
            std::string currentModel = modelIds[selectedIndex];
            float rotY = rotDist(gen);
            float scale = scaleDist(gen);
            
            elements.emplace_back(UtilsStructs::createElement(
                "rock_" + std::to_string(i) + "_" + std::to_string(rand()),
                currentModel,
                {textureId, pnois},
                {rockX, rockY, rockZ},
                {0.0f, rotY, 0.0f},
                {scale, scale, scale}
            ));
        }
        return elements;
    }

    /**
 * SYMMETRICAL STREET LIGHT PLACEMENT
 * Places lamps along the edges of the road at regular intervals.
 */
    static std::vector<MMElement> placeStreetLights(float mapLimit = 200.0f,
                                                    int axis = 0,
                                                    float spacing = 25.0f,
                                                    std::string modelId = "lamp1",
                                                    std::string textureId = "tex_medieval_atlas") {
        std::vector<MMElement> elements;

        float start = -mapLimit;
        float end = mapLimit;
        int count = (int) ((end - start) / spacing);
        
        elements.reserve(count * 2);  // 2 lamps per position (left + right)
        
        // Reusable constants
        static const std::string pnois = "pnois";
        static const std::vector<float> lampScale = {1.0f, 1.0f, 1.0f};

        // Distance from the road centerline (road width is roughly 12 units)
        float offsetFromCenter = 6.0f;

        for (int i = 0; i <= count; i++) {
            float currentPos = start + (i * spacing);

            // INTERSECTION CLEARANCE
            // Do not place lamps in the center of the crossroad (0,0)
            if (std::abs(currentPos) < 15.0f) continue;

            glm::vec3 posLeft, posRight;
            glm::vec3 rotLeft, rotRight;
            float xRot = 90.0f; // Standard X-axis fix for engine coordinates

            // AXIS-BASED ORIENTATION
            if (axis == 0) {
                // Horizontal Road (Lamps placed on North/South edges)
                posLeft = {currentPos, 0.0f, offsetFromCenter};
                rotLeft = {xRot, 180.0f, 0.0f}; // Face South

                posRight = {currentPos, 0.0f, -offsetFromCenter};
                rotRight = {xRot, 0.0f, 0.0f}; // Face North
            } else {
                // Vertical Road (Lamps placed on East/West edges)
                posLeft = {offsetFromCenter, 0.0f, currentPos};
                rotLeft = {xRot, 90.0f, 0.0f}; // Face West

                posRight = {-offsetFromCenter, 0.0f, currentPos};
                rotRight = {xRot, -90.0f, 0.0f}; // Face East
            }

            // Left Lamp
            elements.emplace_back(UtilsStructs::createElement(
                "lamp_" + std::to_string(axis) + "_L_" + std::to_string(i),
                modelId, 
                {textureId, pnois},
                {posLeft.x, posLeft.y, posLeft.z},
                {rotLeft.x, rotLeft.y, rotLeft.z},
                lampScale
            ));

            // Right Lamp
            elements.emplace_back(UtilsStructs::createElement(
                "lamp_" + std::to_string(axis) + "_R_" + std::to_string(i),
                modelId, 
                {textureId, pnois},
                {posRight.x, posRight.y, posRight.z},
                {rotRight.x, rotRight.y, rotRight.z},
                lampScale
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
            {"assets/models/Interiors/bed_003_Mesh.262.mgcg", "bed"},
            {"assets/models/Interiors/closet_008_Mesh.550.mgcg", "closet1"},
            {"assets/models/Interiors/closet_026_Mesh.6415.mgcg", "closet2"},
            {"assets/models/Interiors/coffee_table_003_Mesh.260.mgcg", "coffee_table"},
            {"assets/models/Interiors/flower_004_Mesh.016.mgcg", "flower1"},
            {"assets/models/Interiors/flower_014_Mesh.360.mgcg", "flower2"},
            {"assets/models/Interiors/flower_018_Mesh.581.mgcg", "flower3"},
            {"assets/models/Interiors/library.003_Mesh.6514.mgcg", "library"},
            {"assets/models/Interiors/musical_instrument_001_Mesh.6623.mgcg", "piano"},
            {"assets/models/Interiors/picture_057_Mesh.6502.mgcg", "picture1"},
            {"assets/models/Interiors/picture_058_Mesh.6503.mgcg", "picture2"},
            {"assets/models/Interiors/prop.012_Mesh.215.mgcg", "sword_frame"},
            {"assets/models/Interiors/prop.019_Mesh.6652.mgcg", "empty_plate"},
            {"assets/models/Interiors/prop.020_Mesh.7012.mgcg", "bottle"},
            {"assets/models/Interiors/prop.023_Mesh.6584.mgcg", "cup"},
            {"assets/models/Interiors/prop.024_Mesh.7009.mgcg", "coins1"},
            {"assets/models/Interiors/prop.025_Mesh.6303.mgcg", "full_plate"},
            {"assets/models/Interiors/prop.040_Mesh.6497.mgcg", "coins2"},
            {"assets/models/Interiors/prop.041_Mesh.6255.mgcg", "coins3"},
            {"assets/models/Interiors/table.002_Mesh.6854.mgcg", "table1"},
            {"assets/models/Interiors/table.004_Mesh.6586.mgcg", "table2"},
            {"assets/models/Interiors/Walls_006_Plane.mgcg", "wall_plane"},
            {"assets/models/Interiors/Walls_062_Mesh.667.mgcg", "wall_mesh"},
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
            {"assets/models/Dungeon/barrel.001_Mesh.4453.mgcg", "dungeon_barrel1"},
            {"assets/models/Dungeon/barrel.002_Mesh.4450.mgcg", "dungeon_barrel2"},
            {"assets/models/Dungeon/barrel.003_Mesh.6792.mgcg", "dungeon_barrel3"},
            {"assets/models/Dungeon/barrel.012_Mesh.7843.mgcg", "dungeon_barrel4"},
            {"assets/models/Dungeon/bones.005_Mesh.375.mgcg", "bones5"},
            {"assets/models/Dungeon/bones.006_Mesh.6266.mgcg", "bones6"},
            {"assets/models/Dungeon/bones.007_Mesh.371.mgcg", "bones7"},
            {"assets/models/Dungeon/bones.008_Mesh.7359.mgcg", "bones8"},
            {"assets/models/Dungeon/bones.009_Mesh.372.mgcg", "bones9"},
            {"assets/models/Dungeon/bones.010_Mesh.6129.mgcg", "bones10"},
            {"assets/models/Dungeon/bones.011_Mesh.368.mgcg", "bones11"},
            {"assets/models/Dungeon/bones.012_Mesh.365.mgcg", "bones12"},
            {"assets/models/Dungeon/bones.013_Mesh.7822.mgcg", "bones13"},
            {"assets/models/Dungeon/bones.014_Mesh.373.mgcg", "bones14"},
            {"assets/models/Dungeon/bones.015_Mesh.374.mgcg", "bones15"},
            {"assets/models/Dungeon/bones.016_Mesh.222.mgcg", "bones16"},
            {"assets/models/Dungeon/bones.017_Mesh.218.mgcg", "bones17"},
            {"assets/models/Dungeon/bones.018_Mesh.7746.mgcg", "bones18"},
            {"assets/models/Dungeon/bones.019_Mesh.7745.mgcg", "bones19"},
            {"assets/models/Dungeon/bones.020_Mesh.7741.mgcg", "bones20"},
            {"assets/models/Dungeon/bones.021_Mesh.7748.mgcg", "bones21"},
            {"assets/models/Dungeon/bones.022_Mesh.6372.mgcg", "bones22"},
            {"assets/models/Dungeon/bones.023_Mesh.366.mgcg", "bones23"},
            {"assets/models/Dungeon/bones.024_Mesh.7711.mgcg", "bones24"},
            {"assets/models/Dungeon/bones.025_Mesh.7708.mgcg", "bones25"},
            {"assets/models/Dungeon/bones.026_Mesh.7710.mgcg", "bones26"},
            {"assets/models/Dungeon/bones.027_Mesh.5847.mgcg", "bones27"},
            {"assets/models/Dungeon/bones.028_Mesh.5846.mgcg", "bones28"},
            {"assets/models/Dungeon/bones.029_Mesh.5843.mgcg", "bones29"},
            {"assets/models/Dungeon/bones.030_Mesh.5848.mgcg", "bones30"},
            {"assets/models/Dungeon/bones.031_Mesh.5845.mgcg", "bones31"},
            {"assets/models/Dungeon/bones.032_Mesh.7778.mgcg", "bones32"},
            {"assets/models/Dungeon/bones.033_Mesh.700.mgcg", "bones33"},
            {"assets/models/Dungeon/bones.034_Mesh.5238.mgcg", "bones34"},
            {"assets/models/Dungeon/box.001_Mesh.962.mgcg", "dungeon_box1"},
            {"assets/models/Dungeon/box.002_Mesh.899.mgcg", "dungeon_box2"},
            {"assets/models/Dungeon/box.003_Mesh.904.mgcg", "dungeon_box3"},
            {"assets/models/Dungeon/box.004_Mesh.901.mgcg", "dungeon_box4"},
            {"assets/models/Dungeon/box.005_Mesh.4454.mgcg", "dungeon_box5"},
            {"assets/models/Dungeon/box.006_Mesh.216.mgcg", "dungeon_box6"},
            {"assets/models/Dungeon/box.007_Mesh.964.mgcg", "dungeon_box7"},
            {"assets/models/Dungeon/box.008_Mesh.7152.mgcg", "dungeon_box8"},
            {"assets/models/Dungeon/box.009_Mesh.6858.mgcg", "dungeon_box9"},
            {"assets/models/Dungeon/box.010_Mesh.6720.mgcg", "dungeon_box10"},
            {"assets/models/Dungeon/box.024_Mesh.6794.mgcg", "dungeon_box11"},
            {"assets/models/Dungeon/chair.001_Mesh.7776.mgcg", "dungeon_chair1"},
            {"assets/models/Dungeon/chair.002_Mesh.6849.mgcg", "dungeon_chair2"},
            {"assets/models/Dungeon/chair.003_Mesh.6582.mgcg", "dungeon_chair3"},
            {"assets/models/Dungeon/chair.004_Mesh.6118.mgcg", "dungeon_chair4"},
            {"assets/models/Dungeon/chair.005_Mesh.7153.mgcg", "dungeon_chair5"},
            {"assets/models/Dungeon/chair.006_Mesh.7892.mgcg", "dungeon_chair6"},
            {"assets/models/Dungeon/chair.013_Mesh.6796.mgcg", "dungeon_chair7"},
            {"assets/models/Dungeon/coffin.005_Mesh.7872.mgcg", "coffin5"},
            {"assets/models/Dungeon/coffin_Mesh.7527.mgcg", "coffin6"},
            {"assets/models/Dungeon/crow.001_Mesh.5389.mgcg", "crow1"},
            {"assets/models/Dungeon/crow.002_Mesh.5917.mgcg", "crow2"},
            {"assets/models/Dungeon/crow_Mesh.5912.mgcg", "crow3"},
            {"assets/models/Dungeon/cube_Mesh.7712.mgcg", "dungeon_cube"},
            {"assets/models/Dungeon/cupboard.001_Mesh.6553.mgcg", "cupboard1"},
            {"assets/models/Dungeon/cupboard.002_Mesh.6115.mgcg", "cupboard2"},
            {"assets/models/Dungeon/cupboard.003_Mesh.4441.mgcg", "cupboard3"},
            {"assets/models/Dungeon/decoration.001_Mesh.7073.mgcg", "dungeon_decoration1"},
            {"assets/models/Dungeon/decoration.002_Mesh.7105.mgcg", "dungeon_decoration2"},
            {"assets/models/Dungeon/decoration.003_Mesh.6176.mgcg", "dungeon_decoration3"},
            {"assets/models/Dungeon/decoration.004_Mesh.4720.mgcg", "dungeon_decoration4"},
            {"assets/models/Dungeon/decoration.005_Mesh.6547.mgcg", "dungeon_decoration5"},
            {"assets/models/Dungeon/decoration.006_Mesh.4745.mgcg", "dungeon_decoration6"},
            {"assets/models/Dungeon/decoration.007_Mesh.6499.mgcg", "dungeon_decoration7"},
            {"assets/models/Dungeon/decoration.008_Mesh.6494.mgcg", "dungeon_decoration8"},
            {"assets/models/Dungeon/decoration.009_Mesh.6496.mgcg", "dungeon_decoration9"},
            {"assets/models/Dungeon/decoration.010_Mesh.6724.mgcg", "dungeon_decoration10"},
            {"assets/models/Dungeon/decoration.011_Mesh.7123.mgcg", "dungeon_decoration11"},
            {"assets/models/Dungeon/decoration.012_Mesh.4442.mgcg", "dungeon_decoration12"},
            {"assets/models/Dungeon/decoration.013_Mesh.4440.mgcg", "dungeon_decoration13"},
            {"assets/models/Dungeon/decoration.014_Mesh.4915.mgcg", "dungeon_decoration14"},
            {"assets/models/Dungeon/decoration.015_Mesh.6804.mgcg", "dungeon_decoration15"},
            {"assets/models/Dungeon/decoration.016_Mesh.4737.mgcg", "dungeon_decoration16"},
            {"assets/models/Dungeon/decoration.017_Mesh.299.mgcg", "dungeon_decoration17"},
            {"assets/models/Dungeon/decoration.018_Mesh.6190.mgcg", "dungeon_decoration18"},
            {"assets/models/Dungeon/decoration.019_Mesh.4909.mgcg", "dungeon_decoration19"},
            {"assets/models/Dungeon/decoration.020_Mesh.4906.mgcg", "dungeon_decoration20"},
            {"assets/models/Dungeon/decoration.021_Mesh.268.mgcg", "dungeon_decoration21"},
            {"assets/models/Dungeon/decoration.022_Mesh.468.mgcg", "dungeon_decoration22"},
            {"assets/models/Dungeon/decoration.023_Mesh.5634.mgcg", "dungeon_decoration23"},
            {"assets/models/Dungeon/decoration.024_Mesh.4921.mgcg", "dungeon_decoration24"},
            {"assets/models/Dungeon/decoration.025_Mesh.5810.mgcg", "dungeon_decoration25"},
            {"assets/models/Dungeon/decoration.026_Mesh.6000.mgcg", "dungeon_decoration26"},
            {"assets/models/Dungeon/decoration.027_Mesh.6199.mgcg", "dungeon_decoration27"},
            {"assets/models/Dungeon/decoration_Mesh.6383.mgcg", "dungeon_decoration28"},
            {"assets/models/Dungeon/door.001_Mesh.6202.mgcg", "dungeon_door1"},
            {"assets/models/Dungeon/door.002_Mesh.7405.mgcg", "dungeon_door2"},
            {"assets/models/Dungeon/door.003_Mesh.7402.mgcg", "dungeon_door3"},
            {"assets/models/Dungeon/door.004_Mesh.4799.mgcg", "dungeon_door4"},
            {"assets/models/Dungeon/fence.005_Mesh.5497.mgcg", "fence5"},
            {"assets/models/Dungeon/fence.006_Mesh.5502.mgcg", "fence6"},
            {"assets/models/Dungeon/fence.007_Mesh.5499.mgcg", "fence7"},
            {"assets/models/Dungeon/fence.008_Mesh.355.mgcg", "fence8"},
            {"assets/models/Dungeon/fence.009_Mesh.361.mgcg", "fence9"},
            {"assets/models/Dungeon/fence.010_Mesh.6149.mgcg", "fence10"},
            {"assets/models/Dungeon/fence.011_Mesh.359.mgcg", "fence11"},
            {"assets/models/Dungeon/fence.012_Mesh.354.mgcg", "fence12"},
            {"assets/models/Dungeon/fence.013_Mesh.353.mgcg", "fence13"},
            {"assets/models/Dungeon/fence.014_Mesh.349.mgcg", "fence14"},
            {"assets/models/Dungeon/fence.015_Mesh.350.mgcg", "fence15"},
            {"assets/models/Dungeon/fence.016_Mesh.351.mgcg", "fence16"},
            {"assets/models/Dungeon/fence.017_Mesh.352.mgcg", "fence17"},
            {"assets/models/Dungeon/fence.018_Mesh.7753.mgcg", "fence18"},
            {"assets/models/Dungeon/fence.019_Mesh.7752.mgcg", "fence19"},
            {"assets/models/Dungeon/fence.020_Mesh.7747.mgcg", "fence20"},
            {"assets/models/Dungeon/fence.021_Mesh.6946.mgcg", "fence21"},
            {"assets/models/Dungeon/fence.022_Mesh.7531.mgcg", "fence22"},
            {"assets/models/Dungeon/fence.023_Mesh.4424.mgcg", "fence23"},
            {"assets/models/Dungeon/fence.024_Mesh.7749.mgcg", "fence24"},
            {"assets/models/Dungeon/fence.034_Mesh.6603.mgcg", "fence25"},
            {"assets/models/Dungeon/floor.001_Mesh.6812.mgcg", "dungeon_floor1"},
            {"assets/models/Dungeon/floor_Mesh.7127.mgcg", "dungeon_floor2"},
            {"assets/models/Dungeon/grave.001_Mesh.8105.mgcg", "dungeon_grave1"},
            {"assets/models/Dungeon/grave.002_Mesh.7917.mgcg", "dungeon_grave2"},
            {"assets/models/Dungeon/grave.003_Mesh.7906.mgcg", "dungeon_grave3"},
            {"assets/models/Dungeon/grave.004_Mesh.7750.mgcg", "dungeon_grave4"},
            {"assets/models/Dungeon/grave.005_Mesh.4386.mgcg", "dungeon_grave5"},
            {"assets/models/Dungeon/grave.006_Mesh.5495.mgcg", "dungeon_grave6"},
            {"assets/models/Dungeon/grave.007_Mesh.5383.mgcg", "dungeon_grave7"},
            {"assets/models/Dungeon/grave.008_Mesh.5380.mgcg", "dungeon_grave8"},
            {"assets/models/Dungeon/grave.009_Mesh.909.mgcg", "dungeon_grave9"},
            {"assets/models/Dungeon/grave.010_Mesh.908.mgcg", "dungeon_grave10"},
            {"assets/models/Dungeon/grave.011_Mesh.905.mgcg", "dungeon_grave11"},
            {"assets/models/Dungeon/grave.012_Mesh.4385.mgcg", "dungeon_grave12"},
            {"assets/models/Dungeon/grave.013_Mesh.6740.mgcg", "dungeon_grave13"},
            {"assets/models/Dungeon/grave.014_Mesh.5113.mgcg", "dungeon_grave14"},
            {"assets/models/Dungeon/grave.015_Mesh.7919.mgcg", "dungeon_grave15"},
            {"assets/models/Dungeon/grave.016_Mesh.7916.mgcg", "dungeon_grave16"},
            {"assets/models/Dungeon/grave.017_Mesh.8099.mgcg", "dungeon_grave17"},
            {"assets/models/Dungeon/grave.018_Mesh.7873.mgcg", "dungeon_grave18"},
            {"assets/models/Dungeon/grave.019_Mesh.4590.mgcg", "dungeon_grave19"},
            {"assets/models/Dungeon/grave.020_Mesh.895.mgcg", "dungeon_grave20"},
            {"assets/models/Dungeon/grave.021_Mesh.6262.mgcg", "dungeon_grave21"},
            {"assets/models/Dungeon/grave.022_Mesh.6139.mgcg", "dungeon_grave22"},
            {"assets/models/Dungeon/grave.023_Mesh.6265.mgcg", "dungeon_grave23"},
            {"assets/models/Dungeon/grave.024_Mesh.6261.mgcg", "dungeon_grave24"},
            {"assets/models/Dungeon/grave.025_Mesh.5498.mgcg", "dungeon_grave25"},
            {"assets/models/Dungeon/grave.026_Mesh.4383.mgcg", "dungeon_grave26"},
            {"assets/models/Dungeon/grave.027_Mesh.5494.mgcg", "dungeon_grave27"},
            {"assets/models/Dungeon/grave.028_Mesh.5116.mgcg", "dungeon_grave28"},
            {"assets/models/Dungeon/grave.029_Mesh.6471.mgcg", "dungeon_grave29"},
            {"assets/models/Dungeon/grave.030_Mesh.7845.mgcg", "dungeon_grave30"},
            {"assets/models/Dungeon/grave.031_Mesh.5496.mgcg", "dungeon_grave31"},
            {"assets/models/Dungeon/grave.032_Mesh.6429.mgcg", "dungeon_grave32"},
            {"assets/models/Dungeon/grave.033_Mesh.7915.mgcg", "dungeon_grave33"},
            {"assets/models/Dungeon/grave.034_Mesh.7913.mgcg", "dungeon_grave34"},
            {"assets/models/Dungeon/grave.035_Mesh.7908.mgcg", "dungeon_grave35"},
            {"assets/models/Dungeon/grave.036_Mesh.6456.mgcg", "dungeon_grave36"},
            {"assets/models/Dungeon/grave.037_Mesh.7904.mgcg", "dungeon_grave37"},
            {"assets/models/Dungeon/grave.038_Mesh.7934.mgcg", "dungeon_grave38"},
            {"assets/models/Dungeon/grave.039_Mesh.897.mgcg", "dungeon_grave39"},
            {"assets/models/Dungeon/grave.040_Mesh.896.mgcg", "dungeon_grave40"},
            {"assets/models/Dungeon/grave.041_Mesh.898.mgcg", "dungeon_grave41"},
            {"assets/models/Dungeon/grave.042_Mesh.894.mgcg", "dungeon_grave42"},
            {"assets/models/Dungeon/grave.043_Mesh.6274.mgcg", "dungeon_grave43"},
            {"assets/models/Dungeon/grave.044_Mesh.6270.mgcg", "dungeon_grave44"},
            {"assets/models/Dungeon/grave.045_Mesh.6263.mgcg", "dungeon_grave45"},
            {"assets/models/Dungeon/grave.046_Mesh.7529.mgcg", "dungeon_grave46"},
            {"assets/models/Dungeon/grave.047_Mesh.7224.mgcg", "dungeon_grave47"},
            {"assets/models/Dungeon/grave.048_Mesh.7844.mgcg", "dungeon_grave48"},
            {"assets/models/Dungeon/grave.049_Mesh.6366.mgcg", "dungeon_grave49"},
            {"assets/models/Dungeon/grave.050_Mesh.7517.mgcg", "dungeon_grave50"},
            {"assets/models/Dungeon/grave_Mesh.5998.mgcg", "dungeon_grave51"},
            {"assets/models/Dungeon/jug.001_Mesh.5244.mgcg", "jug1"},
            {"assets/models/Dungeon/jug.002_Mesh.961.mgcg", "jug2"},
            {"assets/models/Dungeon/jug.003_Mesh.902.mgcg", "jug3"},
            {"assets/models/Dungeon/jug.004_Mesh.4451.mgcg", "jug4"},
            {"assets/models/Dungeon/jug.005_Mesh.4447.mgcg", "jug5"},
            {"assets/models/Dungeon/jug.006_Mesh.7360.mgcg", "jug6"},
            {"assets/models/Dungeon/jug.007_Mesh.7357.mgcg", "jug7"},
            {"assets/models/Dungeon/jug.008_Mesh.217.mgcg", "jug8"},
            {"assets/models/Dungeon/jug.009_Mesh.220.mgcg", "jug9"},
            {"assets/models/Dungeon/jug.010_Mesh.214.mgcg", "jug10"},
            {"assets/models/Dungeon/jug.011_Mesh.219.mgcg", "jug11"},
            {"assets/models/Dungeon/ladder.001_Mesh.6585.mgcg", "ladder1"},
            {"assets/models/Dungeon/ladder.002_Mesh.7128.mgcg", "ladder2"},
            {"assets/models/Dungeon/library.001_Mesh.8060.mgcg", "dungeon_library1"},
            {"assets/models/Dungeon/library.002_Mesh.463.mgcg", "dungeon_library2"},
            {"assets/models/Dungeon/library.003_Mesh.6514.mgcg", "dungeon_library3"},
            {"assets/models/Dungeon/library.004_Mesh.6513.mgcg", "dungeon_library4"},
            {"assets/models/Dungeon/library.005_Mesh.6511.mgcg", "dungeon_library5"},
            {"assets/models/Dungeon/library_Mesh.198.mgcg", "dungeon_library6"},
            {"assets/models/Dungeon/light.001_Mesh.5388.mgcg", "dungeon_light1"},
            {"assets/models/Dungeon/light.002_Mesh.6811.mgcg", "dungeon_light2"},
            {"assets/models/Dungeon/light.003_Mesh.7870.mgcg", "dungeon_light3"},
            {"assets/models/Dungeon/light.004_Mesh.6798.mgcg", "dungeon_light4"},
            {"assets/models/Dungeon/light.005_Mesh.7787.mgcg", "dungeon_light5"},
            {"assets/models/Dungeon/light.006_Mesh.7788.mgcg", "dungeon_light6"},
            {"assets/models/Dungeon/light.007_Mesh.6852.mgcg", "dungeon_light7"},
            {"assets/models/Dungeon/light.008_Mesh.4718.mgcg", "dungeon_light8"},
            {"assets/models/Dungeon/light.009_Mesh.6851.mgcg", "dungeon_light9"},
            {"assets/models/Dungeon/light.010_Mesh.6200.mgcg", "dungeon_light10"},
            {"assets/models/Dungeon/light.011_Mesh.4797.mgcg", "dungeon_light11"},
            {"assets/models/Dungeon/light.012_Mesh.4744.mgcg", "dungeon_light12"},
            {"assets/models/Dungeon/light.013_Mesh.7136.mgcg", "dungeon_light13"},
            {"assets/models/Dungeon/light.014_Mesh.6549.mgcg", "dungeon_light14"},
            {"assets/models/Dungeon/light.015_Mesh.6776.mgcg", "dungeon_light15"},
            {"assets/models/Dungeon/light.016_Mesh.5815.mgcg", "dungeon_light16"},
            {"assets/models/Dungeon/light.017_Mesh.470.mgcg", "dungeon_light17"},
            {"assets/models/Dungeon/log.001_Mesh.5247.mgcg", "log1"},
            {"assets/models/Dungeon/log.002_Mesh.8018.mgcg", "log2"},
            {"assets/models/Dungeon/log.003_Mesh.966.mgcg", "log3"},
            {"assets/models/Dungeon/log_Mesh.965.mgcg", "log4"},
            {"assets/models/Dungeon/plane_Mesh.367.mgcg", "dungeon_plane"},
            {"assets/models/Dungeon/prop.002_Mesh.7100.mgcg", "dungeon_prop2"},
            {"assets/models/Dungeon/prop.003_Mesh.6907.mgcg", "dungeon_prop3"},
            {"assets/models/Dungeon/prop.004_Mesh.7103.mgcg", "dungeon_prop4"},
            {"assets/models/Dungeon/prop.005_Mesh.6904.mgcg", "dungeon_prop5"},
            {"assets/models/Dungeon/prop.006_Mesh.308.mgcg", "dungeon_prop6"},
            {"assets/models/Dungeon/prop.007_Mesh.305.mgcg", "dungeon_prop7"},
            {"assets/models/Dungeon/prop.008_Mesh.306.mgcg", "dungeon_prop8"},
            {"assets/models/Dungeon/prop.009_Mesh.970.mgcg", "dungeon_prop9"},
            {"assets/models/Dungeon/prop.010_Mesh.967.mgcg", "dungeon_prop10"},
            {"assets/models/Dungeon/prop.011_Mesh.6795.mgcg", "dungeon_prop11"},
            {"assets/models/Dungeon/prop.012_Mesh.215.mgcg", "dungeon_prop12"},
            {"assets/models/Dungeon/prop.013_Mesh.211.mgcg", "dungeon_prop13"},
            {"assets/models/Dungeon/prop.014_Mesh.7789.mgcg", "dungeon_prop14"},
            {"assets/models/Dungeon/prop.015_Mesh.7791.mgcg", "dungeon_prop15"},
            {"assets/models/Dungeon/prop.016_Mesh.6779.mgcg", "dungeon_prop16"},
            {"assets/models/Dungeon/prop.017_Mesh.6189.mgcg", "dungeon_prop17"},
            {"assets/models/Dungeon/prop.018_Mesh.6588.mgcg", "dungeon_prop18"},
            {"assets/models/Dungeon/prop.019_Mesh.6652.mgcg", "dungeon_prop19"},
            {"assets/models/Dungeon/prop.020_Mesh.7012.mgcg", "dungeon_prop20"},
            {"assets/models/Dungeon/prop.021_Mesh.6229.mgcg", "dungeon_prop21"},
            {"assets/models/Dungeon/prop.022_Mesh.7259.mgcg", "dungeon_prop22"},
            {"assets/models/Dungeon/prop.023_Mesh.6584.mgcg", "dungeon_prop23"},
            {"assets/models/Dungeon/prop.024_Mesh.7009.mgcg", "dungeon_prop24"},
            {"assets/models/Dungeon/prop.025_Mesh.6303.mgcg", "dungeon_prop25"},
            {"assets/models/Dungeon/prop.026_Mesh.7074.mgcg", "dungeon_prop26"},
            {"assets/models/Dungeon/prop.027_Mesh.7071.mgcg", "dungeon_prop27"},
            {"assets/models/Dungeon/prop.028_Mesh.6817.mgcg", "dungeon_prop28"},
            {"assets/models/Dungeon/prop.029_Mesh.6819.mgcg", "dungeon_prop29"},
            {"assets/models/Dungeon/prop.030_Mesh.7394.mgcg", "dungeon_prop30"},
            {"assets/models/Dungeon/prop.031_Mesh.7155.mgcg", "dungeon_prop31"},
            {"assets/models/Dungeon/prop.032_Mesh.7038.mgcg", "dungeon_prop32"},
            {"assets/models/Dungeon/prop.033_Mesh.7035.mgcg", "dungeon_prop33"},
            {"assets/models/Dungeon/prop.034_Mesh.7986.mgcg", "dungeon_prop34"},
            {"assets/models/Dungeon/prop.035_Mesh.6860.mgcg", "dungeon_prop35"},
            {"assets/models/Dungeon/prop.036_Mesh.4743.mgcg", "dungeon_prop36"},
            {"assets/models/Dungeon/prop.037_Mesh.4747.mgcg", "dungeon_prop37"},
            {"assets/models/Dungeon/prop.038_Mesh.4746.mgcg", "dungeon_prop38"},
            {"assets/models/Dungeon/prop.039_Mesh.6493.mgcg", "dungeon_prop39"},
            {"assets/models/Dungeon/prop.040_Mesh.6497.mgcg", "dungeon_prop40"},
            {"assets/models/Dungeon/prop.041_Mesh.6255.mgcg", "dungeon_prop41"},
            {"assets/models/Dungeon/prop.042_Mesh.7896.mgcg", "dungeon_prop42"},
            {"assets/models/Dungeon/prop.043_Mesh.4444.mgcg", "dungeon_prop43"},
            {"assets/models/Dungeon/prop.044_Mesh.6555.mgcg", "dungeon_prop44"},
            {"assets/models/Dungeon/prop.045_Mesh.6552.mgcg", "dungeon_prop45"},
            {"assets/models/Dungeon/prop.046_Mesh.6551.mgcg", "dungeon_prop46"},
            {"assets/models/Dungeon/prop.047_Mesh.6548.mgcg", "dungeon_prop47"},
            {"assets/models/Dungeon/prop.048_Mesh.4553.mgcg", "dungeon_prop48"},
            {"assets/models/Dungeon/prop.049_Mesh.7303.mgcg", "dungeon_prop49"},
            {"assets/models/Dungeon/prop.050_Mesh.7300.mgcg", "dungeon_prop50"},
            {"assets/models/Dungeon/prop.051_Mesh.4546.mgcg", "dungeon_prop51"},
            {"assets/models/Dungeon/prop.052_Mesh.7306.mgcg", "dungeon_prop52"},
            {"assets/models/Dungeon/prop.053_Mesh.7302.mgcg", "dungeon_prop53"},
            {"assets/models/Dungeon/prop.054_Mesh.5249.mgcg", "dungeon_prop54"},
            {"assets/models/Dungeon/prop.055_Mesh.7011.mgcg", "dungeon_prop55"},
            {"assets/models/Dungeon/prop.056_Mesh.4938.mgcg", "dungeon_prop56"},
            {"assets/models/Dungeon/prop.057_Mesh.5818.mgcg", "dungeon_prop57"},
            {"assets/models/Dungeon/prop_Mesh.8089.mgcg", "dungeon_prop58"},
            {"assets/models/Dungeon/pumpkin.001_Mesh.297.mgcg", "pumpkin1"},
            {"assets/models/Dungeon/pumpkin.002_Mesh.295.mgcg", "pumpkin2"},
            {"assets/models/Dungeon/pumpkin.003_Mesh.7755.mgcg", "pumpkin3"},
            {"assets/models/Dungeon/pumpkin.004_Mesh.7754.mgcg", "pumpkin4"},
            {"assets/models/Dungeon/pumpkin.005_Mesh.248.mgcg", "pumpkin5"},
            {"assets/models/Dungeon/pumpkin.006_Mesh.245.mgcg", "pumpkin6"},
            {"assets/models/Dungeon/pumpkin.007_Mesh.5391.mgcg", "pumpkin7"},
            {"assets/models/Dungeon/pumpkin.008_Mesh.483.mgcg", "pumpkin8"},
            {"assets/models/Dungeon/pumpkin.009_Mesh.7751.mgcg", "pumpkin9"},
            {"assets/models/Dungeon/pumpkin.010_Mesh.4592.mgcg", "pumpkin10"},
            {"assets/models/Dungeon/pumpkin_Mesh.192.mgcg", "pumpkin11"},
            {"assets/models/Dungeon/stone.001_Mesh.7905.mgcg", "dungeon_stone1"},
            {"assets/models/Dungeon/stone.002_Mesh.5119.mgcg", "dungeon_stone2"},
            {"assets/models/Dungeon/stone.003_Mesh.7901.mgcg", "dungeon_stone3"},
            {"assets/models/Dungeon/stone.004_Mesh.5118.mgcg", "dungeon_stone4"},
            {"assets/models/Dungeon/stone.005_Mesh.5115.mgcg", "dungeon_stone5"},
            {"assets/models/Dungeon/stone.006_Mesh.7903.mgcg", "dungeon_stone6"},
            {"assets/models/Dungeon/stone.007_Mesh.7902.mgcg", "dungeon_stone7"},
            {"assets/models/Dungeon/stone.008_Mesh.7900.mgcg", "dungeon_stone8"},
            {"assets/models/Dungeon/stone.009_Mesh.7899.mgcg", "dungeon_stone9"},
            {"assets/models/Dungeon/stone.010_Mesh.7898.mgcg", "dungeon_stone10"},
            {"assets/models/Dungeon/stone.011_Mesh.6783.mgcg", "dungeon_stone11"},
            {"assets/models/Dungeon/stone.012_Mesh.6786.mgcg", "dungeon_stone12"},
            {"assets/models/Dungeon/stone.013_Mesh.6781.mgcg", "dungeon_stone13"},
            {"assets/models/Dungeon/stone.014_Mesh.6785.mgcg", "dungeon_stone14"},
            {"assets/models/Dungeon/stone.015_Mesh.6782.mgcg", "dungeon_stone15"},
            {"assets/models/Dungeon/stone.016_Mesh.6813.mgcg", "dungeon_stone16"},
            {"assets/models/Dungeon/stone.017_Mesh.6815.mgcg", "dungeon_stone17"},
            {"assets/models/Dungeon/stone_Mesh.7869.mgcg", "dungeon_stone18"},
            {"assets/models/Dungeon/sword.001_Mesh.6186.mgcg", "sword1"},
            {"assets/models/Dungeon/sword.002_Mesh.6192.mgcg", "sword2"},
            {"assets/models/Dungeon/sword_Mesh.7528.mgcg", "sword3"},
            {"assets/models/Dungeon/table.001_Mesh.7007.mgcg", "dungeon_table1"},
            {"assets/models/Dungeon/table.002_Mesh.6854.mgcg", "dungeon_table2"},
            {"assets/models/Dungeon/table.003_Mesh.6823.mgcg", "dungeon_table3"},
            {"assets/models/Dungeon/table.004_Mesh.6586.mgcg", "dungeon_table4"},
            {"assets/models/Dungeon/table.005_Mesh.7403.mgcg", "dungeon_table5"},
            {"assets/models/Dungeon/table.006_Mesh.6116.mgcg", "dungeon_table6"},
            {"assets/models/Dungeon/table.007_Mesh.4796.mgcg", "dungeon_table7"},
            {"assets/models/Dungeon/table.008_Mesh.6304.mgcg", "dungeon_table8"},
            {"assets/models/Dungeon/table.009_Mesh.4795.mgcg", "dungeon_table9"},
            {"assets/models/Dungeon/table.010_Mesh.6861.mgcg", "dungeon_table10"},
            {"assets/models/Dungeon/table.011_Mesh.7895.mgcg", "dungeon_table11"},
            {"assets/models/Dungeon/table.012_Mesh.6780.mgcg", "dungeon_table12"},
            {"assets/models/Dungeon/table.013_Mesh.6820.mgcg", "dungeon_table13"},
            {"assets/models/Dungeon/table.014_Mesh.6113.mgcg", "dungeon_table14"},
            {"assets/models/Dungeon/table.015_Mesh.7354.mgcg", "dungeon_table15"},
            {"assets/models/Dungeon/table_Mesh.968.mgcg", "dungeon_table16"},
            {"assets/models/Dungeon/torture.001_Mesh.4345.mgcg", "torture1"},
            {"assets/models/Dungeon/torture.002_Mesh.4920.mgcg", "torture2"},
            {"assets/models/Dungeon/torture.003_Mesh.5819.mgcg", "torture3"},
            {"assets/models/Dungeon/torture.004_Mesh.5240.mgcg", "torture4"},
            {"assets/models/Dungeon/torture.005_Mesh.7794.mgcg", "torture5"},
            {"assets/models/Dungeon/torture.006_Mesh.5036.mgcg", "torture6"},
            {"assets/models/Dungeon/torture.007_Mesh.5184.mgcg", "torture7"},
            {"assets/models/Dungeon/torture.008_Mesh.5234.mgcg", "torture8"},
            {"assets/models/Dungeon/torture.009_Mesh.5239.mgcg", "torture9"},
            {"assets/models/Dungeon/torture.010_Mesh.7090.mgcg", "torture10"},
            {"assets/models/Dungeon/torture.011_Mesh.7087.mgcg", "torture11"},
            {"assets/models/Dungeon/torture.012_Mesh.7092.mgcg", "torture12"},
            {"assets/models/Dungeon/torture_Mesh.6153.mgcg", "torture13"},
            {"assets/models/Dungeon/tunnel.001_Mesh.4490.mgcg", "dungeon_tunnel1"},
            {"assets/models/Dungeon/tunnel.002_Mesh.7094.mgcg", "dungeon_tunnel2"},
            {"assets/models/Dungeon/tunnel.003_Mesh.4991.mgcg", "dungeon_tunnel3"},
            {"assets/models/Dungeon/tunnel.004_Mesh.7758.mgcg", "dungeon_tunnel4"},
            {"assets/models/Dungeon/tunnel.005_Mesh.7961.mgcg", "dungeon_tunnel5"},
            {"assets/models/Dungeon/tunnel.006_Mesh.7960.mgcg", "dungeon_tunnel6"},
            {"assets/models/Dungeon/tunnel.007_Mesh.6510.mgcg", "dungeon_tunnel7"},
            {"assets/models/Dungeon/tunnel.008_Mesh.7207.mgcg", "dungeon_tunnel8"},
            {"assets/models/Dungeon/tunnel.009_Mesh.5778.mgcg", "dungeon_tunnel9"},
            {"assets/models/Dungeon/tunnel.010_Mesh.7713.mgcg", "dungeon_tunnel10"},
            {"assets/models/Dungeon/tunnel.011_Mesh.4671.mgcg", "dungeon_tunnel11"},
            {"assets/models/Dungeon/tunnel.012_Mesh.6449.mgcg", "dungeon_tunnel12"},
            {"assets/models/Dungeon/tunnel.013_Mesh.7204.mgcg", "dungeon_tunnel13"},
            {"assets/models/Dungeon/tunnel.014_Mesh.7957.mgcg", "dungeon_tunnel14"},
            {"assets/models/Dungeon/tunnel.015_Mesh.6443.mgcg", "dungeon_tunnel15"},
            {"assets/models/Dungeon/tunnel.016_Mesh.8017.mgcg", "dungeon_tunnel16"},
            {"assets/models/Dungeon/tunnel.017_Mesh.6462.mgcg", "dungeon_tunnel17"},
            {"assets/models/Dungeon/tunnel.018_Mesh.4676.mgcg", "dungeon_tunnel18"},
            {"assets/models/Dungeon/tunnel.019_Mesh.5760.mgcg", "dungeon_tunnel19"},
            {"assets/models/Dungeon/tunnel.020_Mesh.8016.mgcg", "dungeon_tunnel20"},
            {"assets/models/Dungeon/tunnel.021_Mesh.196.mgcg", "dungeon_tunnel21"},
            {"assets/models/Dungeon/tunnel.022_Mesh.4400.mgcg", "dungeon_tunnel22"},
            {"assets/models/Dungeon/tunnel.023_Mesh.6412.mgcg", "dungeon_tunnel23"},
            {"assets/models/Dungeon/tunnel.024_Mesh.6126.mgcg", "dungeon_tunnel24"},
            {"assets/models/Dungeon/tunnel.025_Mesh.4668.mgcg", "dungeon_tunnel25"},
            {"assets/models/Dungeon/tunnel.026_Mesh.6140.mgcg", "dungeon_tunnel26"},
            {"assets/models/Dungeon/tunnel.027_Mesh.6404.mgcg", "dungeon_tunnel27"},
            {"assets/models/Dungeon/tunnel.028_Mesh.7989.mgcg", "dungeon_tunnel28"},
            {"assets/models/Dungeon/tunnel.029_Mesh.6128.mgcg", "dungeon_tunnel29"},
            {"assets/models/Dungeon/tunnel.030_Mesh.7968.mgcg", "dungeon_tunnel30"},
            {"assets/models/Dungeon/tunnel.031_Mesh.7927.mgcg", "dungeon_tunnel31"},
            {"assets/models/Dungeon/tunnel.032_Mesh.7959.mgcg", "dungeon_tunnel32"},
            {"assets/models/Dungeon/tunnel.033_Mesh.6508.mgcg", "dungeon_tunnel33"},
            {"assets/models/Dungeon/tunnel_Mesh.4672.mgcg", "dungeon_tunnel34"},
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

        simpElements.emplace_back(UtilsStructs::createElement("held_candle","dungeon_light4",{"dungeon","pnois"}, {0,0,0}));
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

        // --- PERIMETER TREE WALL ---
        auto perimeterForest = placePerimeterForest(
                -205.0f, 400.0f,     // map X limits
                -205.0f, 205.0f,     // map Z limits
                205.0f, 275.0f,      // river gap
                10,                   // FIVE rows
                6.0f,                // spacing between trees
                4.0f,                // distance between rows
                1,                // tall trees
                {"tree1"},  // pine-like trees
                "tex_veg_atlas"
        );


        vegElements.insert(
                vegElements.end(),
                perimeterForest.begin(),
                perimeterForest.end()
        );


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
