//
// Created by ACER on 15/11/2025.
//

#ifndef E09_MAPMANAGER_HPP
#define E09_MAPMANAGER_HPP

#include <string>
#include <fstream>
#include <json.hpp>
#include <random>
#include <iostream>


using json = nlohmann::json;

class MapManager {
public:

    float gridsize = 20.0f;

    static std::map<std::string,std::string> modelsPaths;

    static std::map<std::string,std::string> texturePaths;

    static std::string jsonPath;

    static std::mt19937_64 gen;

    // -------------------------------------------------------
    // ENUM
    // -------------------------------------------------------

    enum Format {
        GLTF,
        MGCG,
        ASSET,
        OBJ,
        D,
        C
    };

    enum Technique {
        CookTorranceChar,
        CookTorranceNoiseSimp,
        SkyBox,
        PBR
    };

    // -------------------------------------------------------
    // DATA STRUCTURES
    // -------------------------------------------------------

    struct AssetFile {
        std::string id;
        std::string file;
        Format format;
    };

    struct Model {
        std::string id;
        std::string VD;
        std::string model;
        std::string node;
        int meshId = -1;
        std::string asset;
        Format format;
    };

    struct Texture {
        std::string id;
        std::string texture;
        Format format;
    };

    struct Element {
        std::string id;
        std::string model;
        std::string texture[4] = {};
        float translate[3] = {0, 0, 0};
        float eulerAngles[3] = {0, 0, 0};
        float scale[3] = {1, 1, 1};
    };

    struct Istance {
        Technique technique;
        std::vector<Element> elements;
    };

    // -------------------------------------------------------
// STRUCT CREATION FUNCTIONS
// -------------------------------------------------------

   static std::string getExtension(const std::string& path) {
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

    static AssetFile createAssetFile(const std::string& id,
                              const std::string& file,
                              Format format)
    {
        AssetFile a;
        a.id = id;
        a.file = file;
        a.format = format;
        return a;
    }

    static Model createModel(const std::string& id,
                      const std::string& VD,
                      const std::string& modelPath,
                      Format format,
                      const std::string& node = "",
                      int meshId = -1,
                      const std::string& asset = "")
    {
        Model m;
        m.id = id;
        m.VD = VD;
        m.model = modelPath;
        m.format = format;
        m.node = node;
        m.meshId = meshId;
        m.asset = asset;
        return m;
    }

    static Texture createTexture(const std::string& id,
                          const std::string& path,
                          Format format)
    {
        Texture t;
        t.id = id;
        t.texture = path;
        t.format = format;
        return t;
    }

    static Element createElement(const std::string& id,
                          const std::string& model,
                          const std::vector<std::string>& textures,
                          const std::vector<float>& translate = {0,0,0},
                          const std::vector<float>& eulerAngles = {0,0,0},
                          const std::vector<float>& scale = {1,1,1})
    {
        Element e;
        e.id = id;
        e.model = model;

        // Copy textures safely
        for (int i = 0; i < 4; i++)
            e.texture[i] = (i < (int)textures.size()) ? textures[i] : "";

        // Copy transform values
        for (int i = 0; i < 3; i++) {
            e.translate[i]    = i < (int)translate.size()    ? translate[i]    : 0;
            e.eulerAngles[i]  = i < (int)eulerAngles.size()  ? eulerAngles[i]  : 0;
            e.scale[i]        = i < (int)scale.size()        ? scale[i]        : 1;
        }

        return e;
    }

    static Istance createInstance(Technique technique,
                           const std::vector<Element>& elems)
    {
        Istance inst;
        inst.technique = technique;
        inst.elements = elems;

        return inst;
    }

    static Model makeModel(std::pair<std::string,std::string> modelPath){
        std::string extension = getExtension(modelPath.first);
        Format format;
        if (extension == ".obj")
            format = OBJ;
        if (extension == ".mgcg")
            format = MGCG;
        if (extension == ".gltf")
            format = GLTF;
        return createModel(modelPath.second,"VDsimp",modelPath.first,format);
    }

    static Texture makeTexture(std::pair<std::string,std::string> texturePath){
        return createTexture(texturePath.second, texturePath.first, C);
    }

 static std::vector<Model> makeModels(){
        std::vector<Model> models;
        for (const auto& model : modelsPaths){
            models.emplace_back(makeModel(model));
        }
     return models;
   }

 static std::vector<Texture> makeTextures(){
     std::vector<Texture> textures;
     for (const auto& texture : texturePaths){
         printf("%s : ", texture.second.c_str());
         textures.emplace_back(makeTexture(texture));
         printf("%s\n", makeTexture(texture).id.c_str());
     }
     return textures;
   }

    // -------------------------------------------------------
    // ENUM → STRING conversion
    // -------------------------------------------------------

    static std::string formatToString(Format f) {
        switch (f) {
            case GLTF:  return "GLTF";
            case MGCG:  return "MGCG";
            case ASSET: return "ASSET";
            case OBJ:   return "OBJ";
            case D:     return "D";
            case C:     return "C";
        }
        return "";
    }

    static std::string techniqueToString(Technique t) {
        switch (t) {
            case CookTorranceChar:      return "CookTorranceChar";
            case CookTorranceNoiseSimp: return "CookTorranceNoiseSimp";
            case SkyBox:                return "SkyBox";
            case PBR:                   return "PBR";
        }
        return "";
    }

    // -------------------------------------------------------
    // SERIALIZATION FUNCTIONS
    // -------------------------------------------------------

    static json writeAssetFile(const AssetFile& a) {
        json j;
        j["id"] = a.id;
        j["file"] = a.file;
        j["format"] = formatToString(a.format);
        return j;
    }

    static json writeModel(const Model& m) {
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

    static json writeTexture(const Texture& t) {
        json j;
        j["id"] = t.id;
        j["texture"] = t.texture;
        j["format"] = formatToString(t.format);
        return j;
    }

    static json writeElement(const Element& e) {
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

    static json writeInstance(const Istance& inst) {
        json j;
        j["technique"] = techniqueToString(inst.technique);

        json arr = json::array();
        for (const auto& e : inst.elements) {
            if (!e.id.empty())
                arr.push_back(writeElement(e));
        }

        j["elements"] = arr;
        return j;
    }

    static std::vector<Element> placeGrassGround(float hight = 100.0, float lenght = 200.0, float x_offset = 50.0, float z_offset = 50.0, float scale = 20.0){
       std::vector<Element> elements;
       int count_x = hight/scale;
       int count_z = lenght/scale;
       int idNumber = 0;
       std::string idName = "grass_ground";

       for (int i = 0; i < count_z; i++){
           for (int j = 0; j < count_x; j++){
               idNumber++;
               elements.emplace_back(createElement(idName + std::to_string(idNumber), "ground", {"medieval_nature2", "pnois"},{j*scale-x_offset,0,i*scale-z_offset},{90,0,0},{4,1,4}));
           }
       }
        return elements;
   }

    static std::vector<Element> createPaths(std::vector<float> starting_pos, std::vector<float> ending_pos, float x_pass, float z_pass, std::vector<float> scale = {1,0.5,1}, int idNumber = 0){
        std::vector<Element> elements;
        float diff_x = fabs(starting_pos[0] - ending_pos[0]);
        float diff_z = fabs(starting_pos[2] - ending_pos[2]);
        int x_step = x_pass!=0? diff_x/x_pass : 0;
        int z_step = z_pass!=0? diff_z/z_pass : 0;
        int steps = std::max(x_step, z_step);
        std::string idName = "path_ground";
        float posx = starting_pos[0];
        float posz = starting_pos[2];
        for (int i = 0; i < steps; i++){
                idNumber++;
                elements.emplace_back(createElement(idName + std::to_string(idNumber), "ground", {"medieval_nature1", "pnois"},{posx,0.1,posz},{90,0,0},{scale[0],scale[1],scale[2]}));
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

    static std::vector<Element> placeHouses(float hight = 200.0, float lenght = 200.0, float x_offset = 50.0, float z_offset = 50.0, float scale = 20.0, int idNumber = 0){
        std::vector<Element> elements;
        int count_x = hight/scale;
        int count_z = lenght/scale;
        std::string idName = "house";

        for (int i = 0; i < count_z; i++){
            for (int j = 0; j < count_x; j++){
                idNumber++;
                elements.emplace_back(createElement(idName + std::to_string(idNumber), "bldg" + std::to_string(rand_int(1,7)), {"medieval_buildings", "pnois"},{j*scale-x_offset,0,i*scale-z_offset},{90,0,0},{1,1,1}));
            }
        }
        return elements;
    }

    // -------------------------------------------------------
    // BUILD JSON DOCUMENT
    // -------------------------------------------------------

    static json buildJson(std::vector<AssetFile>& assets,
                   std::vector<Model>& models,
                   std::vector<Texture>& textures,
                   std::vector<Istance>& instances)
    {
        json doc;

        doc["assetfiles"] = json::array();
        for (auto& a : assets)
            doc["assetfiles"].push_back(writeAssetFile(a));

        doc["models"] = json::array();
        for (auto& m : models)
            doc["models"].push_back(writeModel(m));

        doc["textures"] = json::array();
        for (auto& t : textures)
            doc["textures"].push_back(writeTexture(t));

        doc["instances"] = json::array();
        for (auto& inst : instances)
            doc["instances"].push_back(writeInstance(inst));

        return doc;
    }

    // -------------------------------------------------------
    // SAVE JSON TO FILE
    // -------------------------------------------------------

    static void saveJson(const json& j, const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open())
            throw std::runtime_error("Impossibile aprire il file JSON");

        file << j.dump(4); // indent = 4
    }

     static void Initialize(){
         modelsPaths = {
                 {"assets/models/Castle/SPW_Medieval_Bldg_01.mgcg", "bldg1"},
                 {"assets/models/Castle/SPW_Medieval_Bldg_02.mgcg", "bldg2"},
                 {"assets/models/Castle/SPW_Medieval_Bldg_03.mgcg", "bldg3"},
                 {"assets/models/Castle/SPW_Medieval_Bldg_04.mgcg", "bldg4"},
                 {"assets/models/Castle/SPW_Medieval_Bldg_05.mgcg", "bldg5"},
                 {"assets/models/Castle/SPW_Medieval_Bldg_06.mgcg", "bldg6"},
                 {"assets/models/Castle/SPW_Medieval_Bldg_07.mgcg", "bldg7"},
                 {"assets/models/Castle/SPW_Medieval_Boat.mgcg", "boat"},
                 {"assets/models/Castle/SPW_Medieval_Box_01.mgcg", "box1"},
                 {"assets/models/Castle/SPW_Medieval_Box_02.mgcg", "box2"},
                 {"assets/models/Castle/SPW_Medieval_Box_03.mgcg", "box3"},
                 {"assets/models/Castle/SPW_Medieval_Barrel.mgcg", "barrel"},
                 {"assets/models/Castle/SPW_Medieval_Props_01.mgcg", "well"},
                 {"assets/models/Castle/SPW_Terrain_Grass_Flat.mgcg", "ground"}
         };

         texturePaths = {
                 {"assets/textures/Castle_Textures/SPW_Medieval.png", "medieval_buildings"},
                 {"assets/textures/Castle_Textures/SPW_Natures_01.png", "medieval_nature1"},
                 {"assets/textures/Castle_Textures/SPW_Natures_02.png", "medieval_nature2"},
                 {"assets/textures/Perlin_noise.png", "pnois"},
                 {"assets/textures/sky_23_2k.png", "skybox"}
         };
    }

    static void makeJson(){
        Initialize();
        jsonPath = "assets/models/scene.json";
        std::vector<AssetFile> assetFiles = {
                createAssetFile("hm", "assets/models/uomo.gltf", GLTF),
                createAssetFile("a1", "assets/models/running.gltf", GLTF),
                createAssetFile("a2", "assets/models/idle.gltf", GLTF),
                createAssetFile("a3", "assets/models/pointing.gltf", GLTF),
                createAssetFile("a4", "assets/models/waving.gltf", GLTF),
                createAssetFile("ct", "assets/models/MainSceneEnvOnly.gltf", GLTF)
        };
        std::vector<Model> models = makeModels();
        std::vector<Model> modelsToAdd = {
                createModel("hm0","VDchar", "Mesh", ASSET, "Ch01_Body", 0, "hm"),
                createModel("hm1","VDchar", "Mesh", ASSET, "Ch01_Body", 1, "hm"),
                createModel("skybox","VDskybox", "assets/models/SkyBoxCube.obj", OBJ),
        };

        for (const auto& model : modelsToAdd){
            models.emplace_back(model);
        }

        std::vector<Texture> textures = makeTextures();

        std::vector<Texture> texturesToAdd = {
                createTexture("st", "assets/textures/uomo/Ch01_1001_Diffuse.png", C),
        };

        for (const auto& texture : texturesToAdd){
            textures.emplace_back(texture);
        }

        std::vector<Element> charElements = {
                createElement("hm0", "hm0", {"st"}),
                createElement("hm1", "hm1", {"st"}),
        };
        std::vector<Element> simpElements = placeGrassGround();

        for (const auto& simpElement : createPaths({-200, 0, 0},{200,0,0},20,0)){
            simpElements.emplace_back(simpElement);
        }

        std::vector<Element> simpElementsHouses = placeHouses(150,150,-200, -200,30);

        for (const auto& simpElement : placeHouses(150,150,-200, 50,30, 25)){
            simpElementsHouses.emplace_back(simpElement);
        }

        for (const auto& simpElement : placeHouses(150,150,50, 50,30, 50)){
            simpElementsHouses.emplace_back(simpElement);
        }

        for (const auto& simpElement : placeHouses(150,150,50, -200,30, 75)){
            simpElementsHouses.emplace_back(simpElement);
        }


        std::vector<Element> simpElementsToAdd{
                createElement("ww1", "well", {"medieval_buildings", "pnois"}, {0,0,0}, {90,0,0}, {1,1,1})
        };

        for (const auto& simpElement : simpElementsToAdd){
            simpElementsHouses.emplace_back(simpElement);
        }

        for (const auto& simpElement : simpElementsHouses){
            simpElements.emplace_back(simpElement);
        }

        std::vector<Element> skyboxElements = {
                createElement("skybox", "skybox", {"skybox"})
        };
        std::vector<Istance> istances = {
                createInstance(CookTorranceChar,charElements),
                createInstance(CookTorranceNoiseSimp, simpElements),
                createInstance(SkyBox, skyboxElements)
        };


        json jsonobj = buildJson(assetFiles,models,textures,istances);
        saveJson(jsonobj, jsonPath);
    }
};

#endif //E09_MAPMANAGER_HPP
