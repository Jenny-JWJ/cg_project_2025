//
// Created by ACER on 15/11/2025.
//

#ifndef E09_MAPMANAGER_HPP
#define E09_MAPMANAGER_HPP

#include <string>
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

class MapManager {
public:

    float gridsize = 20.0f;

    std::string filePathsBuildings[20] = {
            "assets/models/Castle/SPW_Medieval_Bldg_01.mgcg",
            "assets/models/Castle/SPW_Medieval_Bldg_02.mgcg",
            "assets/models/Castle/SPW_Medieval_Bldg_03.mgcg",
            "assets/models/Castle/SPW_Medieval_Bldg_04.mgcg",
            "assets/models/Castle/SPW_Medieval_Bldg_05.mgcg",
            "assets/models/Castle/SPW_Medieval_Bldg_06.mgcg",
            "assets/models/Castle/SPW_Medieval_Bldg_07.mgcg"
    };

    std::string filePathsDeco[20] = {
            "assets/models/Castle/SPW_Medieval_Boat.mgcg",
            "assets/models/Castle/SPW_Medieval_Box_01.mgcg",
            "assets/models/Castle/SPW_Medieval_Box_02.mgcg",
            "assets/models/Castle/SPW_Medieval_Box_03.mgcg",
            "assets/models/Castle/SPW_Medieval_Barrel>.mgcg",
            "assets/models/Castle/SPW_Medieval_Props_01.mgcg"
    };

    static std::string jsonPath;

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
        Element elements[100];
    };

    // -------------------------------------------------------
// STRUCT CREATION FUNCTIONS
// -------------------------------------------------------

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

        int count = std::min((int)elems.size(), 100);
        for (int i = 0; i < count; i++)
            inst.elements[i] = elems[i];

        return inst;
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

    static void makeJson(){
        jsonPath = "assets/models/scene.json";
        std::vector<AssetFile> assetFiles = {
                createAssetFile("hm", "assets/models/uomo.gltf", GLTF),
                createAssetFile("a1", "assets/models/running.gltf", GLTF),
                createAssetFile("a2", "assets/models/idle.gltf", GLTF),
                createAssetFile("a3", "assets/models/pointing.gltf", GLTF),
                createAssetFile("a4", "assets/models/waving.gltf", GLTF),
                createAssetFile("ct", "assets/models/MainSceneEnvOnly.gltf", GLTF)
        };
        std::vector<Model> models = {
                createModel("hm0","VDchar", "Mesh", ASSET, "Ch01_Body", 0, "hm"),
                createModel("hm1","VDchar", "Mesh", ASSET, "Ch01_Body", 1, "hm"),
                createModel("skybox","VDskybox", "assets/models/SkyBoxCube.obj", OBJ),
                createModel("water_well","VDsimp", "assets/models/Castle/SPW_Medieval_Props_01.mgcg", MGCG),
                createModel("ground","VDsimp", "assets/models/Castle/SPW_Terrain_Grass_Flat.mgcg", MGCG),
        };

        std::vector<Texture> textures = {
                createTexture("st", "assets/textures/uomo/Ch01_1001_Diffuse.png", C),
                createTexture("castle_builds", "assets/textures/Castle_Textures/SPW_Medieval.png", C),
                createTexture("castle_nature2", "assets/textures/Castle_Textures/SPW_Natures_02.png", C),
                createTexture("pnois", "assets/textures/Perlin_noise.png", C),
                createTexture("skybox", "assets/textures/sky_23_2k.png", C),
        };

        std::vector<Element> charElements = {
                createElement("hm0", "hm0", {"st"}),
                createElement("hm1", "hm1", {"st"}),
        };
        std::vector<Element> simpElements = {
                createElement("grass", "ground", {"castle_nature2", "pnois"}, {0,0,0}, {90,0,0}, {1,1,1}),
                createElement("ww1", "water_well", {"castle_builds", "pnois"}, {0,0,0}, {90,0,0}, {1,1,1})
        };
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
