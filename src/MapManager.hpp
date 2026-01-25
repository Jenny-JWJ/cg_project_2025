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
        for (const auto &texture: texturePaths) {
            printf("%s : ", texture.second.c_str());
            textures.emplace_back(makeTexture(texture));
            printf("%s\n", makeTexture(texture).id.c_str());
        }
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

    static std::vector<MMElement> placeGrassGround(float hight = 100.0, float lenght = 200.0, float x_offset = 50.0,
                                                   float z_offset = 50.0, float scale = 20.0) {
        std::vector<MMElement> elements;
        int count_x = hight / scale;
        int count_z = lenght / scale;
        int idNumber = 0;
        std::string idName = "grass_ground";

        for (int i = 0; i < count_z; i++) {
            for (int j = 0; j < count_x; j++) {
                idNumber++;
                elements.emplace_back(UtilsStructs::createElement(idName + std::to_string(idNumber), "ground",
                                                    {"medieval_nature2", "pnois"}, {
                                                        j * scale - x_offset, 0, i * scale - z_offset
                                                    }, {90, 0, 0}, {4, 1, 4}));
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
                {"medieval_buildings", "pnois"},
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

    static std::vector<MMElement> placeHouses(float hight = 200.0, float lenght = 200.0, float x_offset = 50.0,
                                              float z_offset = 50.0, float scale = 20.0, int idNumber = 0,
                                              std::vector<float> rotation = {90, 0, 0}) {
        std::vector<MMElement> elements;
        int count_x = hight / scale;
        int count_z = lenght / scale;
        std::string idName = "house";

        for (int i = 0; i < count_z; i++){
            for (int j = 0; j < count_x; j++){
                std::string model_number = std::to_string(rand_int(1,6));
                idNumber++;
                elements.emplace_back(UtilsStructs::createElement(idName + model_number + "_" + std::to_string(idNumber), "bldg" + model_number, {"medieval_buildings", "pnois"},{j*scale-x_offset,0,i*scale-z_offset},rotation,{1,1,1}));
            }
        }
        return elements;
    }

    static std::vector<MMElement> placeVegetationInGrid(float height = 200.0, float length = 200.0,
                                                        float x_offset = 50.0, float z_offset = 50.0,
                                                        float minDistance = 2.5f,
                                                        std::vector<std::string> modelIds = {"tree"},
                                                        std::string textureId = "tree_tex",
                                                        const std::vector<MMElement> &obstacles = {}) {
        std::vector<MMElement> elements;

        // --- MODIFICA QUI ---
        // Usa 0.1 (10%) o addirittura 0.05 (5%) se ne vuoi pochissimi.
        // Questo riduce drasticamente il numero totale, ma permette loro di stare vicini.
        int targetCount = (int) ((height * length) / (minDistance * minDistance)) * 0.1;

        if (targetCount > 1000) targetCount = 1000;

        // ... Il resto rimane UGUALE (copialo dal codice precedente) ...
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
                                                   std::string textureId = "medieval_buildings") {
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
            for (const auto& el : elements) {
                float dx = rockX - el.translate[0];
                float dz = rockZ - el.translate[2];
                // Distance threshold 0.3 because rocks are small
                if ((dx*dx + dz*dz) < 0.3f) { tooClose = true; break; }
            }
            if (tooClose) { i--; continue; }

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
                                                    std::string textureId = "lamp_tex") {
        std::vector<MMElement> elements;

        float start = -mapLimit;
        float end = mapLimit;
        int count = (int)((end - start) / spacing);

        // --- FIX DISTANCE: EXACTLY ON EDGE ---
        // Road width is 20 total (-10 to +10).
        // Setting this to 10.0f places the origin of the lamp exactly on the road line.
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
            //{"assets/models/Castle/SPW_Medieval_Barrel.mgcg", "barrel"},
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
            {"assets/models/CollisionBoxes/cube.obj", "cube"},
            {"assets/models/CollisionBoxes/sphere.obj", "sphere"},
            {"assets/models/CollisionBoxes/cylinder.obj", "cylinder"},
        };

        texturePaths = {
            {"assets/textures/Castle_Textures/SPW_Medieval.png", "medieval_buildings"},
            {"assets/textures/Castle_Textures/SPW_Natures_01.png", "medieval_nature1"},
            {"assets/textures/Castle_Textures/SPW_Natures_02.png", "medieval_nature2"},
            {"assets/textures/FornitureTextures.png", "forniture"},
            {"assets/textures/DungeonTextures.png", "dungeon"},
            {"assets/textures/Perlin_noise.png", "pnois"},
            {"assets/textures/day_sky.png", "skybox"},
            {"assets/textures/Vegetation/Textures_Vegetation.png", "tree_tex"},
            {"assets/textures/Vegetation/Textures_Vegetation.png", "rock_tex"},
            {"assets/textures/Castle_Textures/SPW_Natures_01.png", "lamp_tex"},
            {"assets/textures/Black.png", "black"},
            {"assets/textures/translucent_lightblue_texture.png", "colBox_texture"}
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
        models.emplace_back(UtilsStructs::createModel("hm0", "VDchar", "Mesh", UtilsStructs::ASSET, "Ch01_Body", 0, "hm"));
        models.emplace_back(UtilsStructs::createModel("hm1", "VDchar", "Mesh", UtilsStructs::ASSET, "Ch01_Body", 1, "hm"));
        models.emplace_back(UtilsStructs::createModel("skybox", "VDskybox", "assets/models/SkyBoxCube.obj", UtilsStructs::OBJ));

        std::vector<MMTexture> textures = makeTextures();
        textures.emplace_back(UtilsStructs::createTexture("st", "assets/textures/uomo/Ch01_1001_Diffuse.png", UtilsStructs::C));

        // --- B. STATIC ELEMENTS (Ground, Roads, Rocks, Lights) ---
        // MMInstance Index 1: Static objects

        std::vector<MMElement> charElements = {
                UtilsStructs::createElement("hm0", "hm0", {"st"}),
                UtilsStructs::createElement("hm1", "hm1", {"st"}),
        };

        // 1. Grass Ground
        std::vector<MMElement> simpElements = placeGrassGround();

        // 2. Horizontal Road (Gray Color {0.4, 0.4, 0.4})
        float widthH = 0.4f;
        float widthV = 0.4f;

        auto paths1 = createPaths({-200, 0, 0}, {200, 0, 0}, 20, 0, {2.1f, widthH, 1.0f}, 0);
        simpElements.insert(simpElements.end(), paths1.begin(), paths1.end());

        // 3. Vertical Road (Gray Color {0.4, 0.4, 0.4})
        auto paths2 = createPaths({0, 0, -200}, {0, 0, 200}, 0, 20, {widthV, 2.1f, 1.0f}, 20);
        simpElements.insert(simpElements.end(), paths2.begin(), paths2.end());

        // 4. Rocks on Road (Multi-model & Gray MMTexture)
        std::vector<std::string> rockModels = {"rocks1", "rocks2", "rocks3"};
        std::vector<MMElement> roadRocks = placeRocksOnRoad(40, 200.0f, rockModels, "medieval_buildings");
        simpElements.insert(simpElements.end(), roadRocks.begin(), roadRocks.end());

        // 5. STREET LIGHTS GENERATION
        // Generate lights for Horizontal Road (Axis 0)
        // Note: Logic for "Light only at night" must be handled in the Game Loop/Shader,
        // here we only place the physical 3D model.
        std::vector<MMElement> lightsH = placeStreetLights(200.0f, 0, 25.0f, "lamp1", "lamp_tex");
        simpElements.insert(simpElements.end(), lightsH.begin(), lightsH.end());

        // Generate lights for Vertical Road (Axis 1)
        std::vector<MMElement> lightsV = placeStreetLights(200.0f, 1, 25.0f, "lamp1", "lamp_tex");
        simpElements.insert(simpElements.end(), lightsV.begin(), lightsV.end());

        std::vector<MMElement> interior = InteriorManager::CreateDoubleFirstFloorRightTemplate({300, 0, 300});
        simpElements.insert(simpElements.end(), interior.begin(), interior.end());
        // --- C. HOUSES (Obstacles) ---
        float areaW = 150.0f; float areaL = 150.0f; float gridSize = 30.0f;

        std::vector<MMElement> h1 = placeHouses(areaW, areaL, -20, -20, gridSize, 0, {90, 180, 0});
        std::vector<MMElement> h2 = placeHouses(areaW, areaL, -20, 140, gridSize, 25);
        std::vector<MMElement> h3 = placeHouses(areaW, areaL, 140, -20, gridSize, 50, {90, 180, 0});
        std::vector<MMElement> h4 = placeHouses(areaW, areaL, 140, 140, gridSize, 75);

        std::vector<MMElement> extras;
        extras.emplace_back(UtilsStructs::createElement("ww1", "well", {"medieval_buildings", "pnois"}, {0, 0, 0}, {90, 0, 0}, {1, 1, 1}));

        // Master Obstacle List
        std::vector<MMElement> allObstacles;
        allObstacles.insert(allObstacles.end(), h1.begin(), h1.end());
        allObstacles.insert(allObstacles.end(), h2.begin(), h2.end());
        allObstacles.insert(allObstacles.end(), h3.begin(), h3.end());
        allObstacles.insert(allObstacles.end(), h4.begin(), h4.end());
        allObstacles.insert(allObstacles.end(), extras.begin(), extras.end());


        // --- D. VEGETATION ---
        std::vector<std::string> treeModels = {"tree1", "tree2", "tree3", "tree4"};
        float treeSpacing = 5.0f;

        std::vector<MMElement> vegElements = placeVegetationInGrid(areaW, areaL, -20, -20, treeSpacing, treeModels, "tree_tex", allObstacles);
        auto v2 = placeVegetationInGrid(areaW, areaL, -20, 140, treeSpacing, treeModels, "tree_tex", allObstacles);
        vegElements.insert(vegElements.end(), v2.begin(), v2.end());

        auto v3 = placeVegetationInGrid(areaW, areaL, 140, -20, treeSpacing, treeModels, "tree_tex", allObstacles);
        vegElements.insert(vegElements.end(), v3.begin(), v3.end());

        auto v4 = placeVegetationInGrid(areaW, areaL, 140, 140, treeSpacing, treeModels, "tree_tex", allObstacles);
        vegElements.insert(vegElements.end(), v4.begin(), v4.end());


        // --- E. FINALIZE ---
        simpElements.insert(simpElements.end(), allObstacles.begin(), allObstacles.end());


        // --- F. INSTANCES ---
        std::vector<MMElement> skyboxElements = {UtilsStructs::createElement("skybox", "skybox", {"skybox"}) };

        CollisionBoxGenerator::fillCollisionsBoxes(simpElements);
        CollisionBoxGenerator::fillCollisionsBoxes(vegElements);
        MMInstance debugBox;
        if(debug){
            CollisionBoxGenerator::fillCollisionsBoxesVisual();
            debugBox = CollisionBoxGenerator::collisionInstance;
        }
        std::vector<MMInstance> istances;
        if(!debug && debugBox.elements.empty())
            istances = {
                    UtilsStructs::createInstance(UtilsStructs::CookTorranceChar, charElements),       // Idx 0
                    UtilsStructs::createInstance(UtilsStructs::CookTorranceNoiseSimp, simpElements),  // Idx 1 (Includes Lights)
                    UtilsStructs::createInstance(UtilsStructs::SkyBox, skyboxElements),               // Idx 2
                    UtilsStructs::createInstance(UtilsStructs::Vegetation, vegElements)               // Idx 3
            };

        else{
            istances = {
                    UtilsStructs::createInstance(UtilsStructs::CookTorranceChar, charElements),       // Idx 0
                    UtilsStructs::createInstance(UtilsStructs::CookTorranceNoiseSimp, simpElements),  // Idx 1 (Includes Lights)
                    UtilsStructs::createInstance(UtilsStructs::SkyBox, skyboxElements),               // Idx 2
                    UtilsStructs::createInstance(UtilsStructs::Vegetation, vegElements),              // Idx 3
                    debugBox                                                                          // Idx 4
            };
        }

        json jsonobj = buildJson(assetFiles, models, textures, istances);
        saveJson(jsonobj, jsonPath);
    }
};