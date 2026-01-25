//
// Created by ACER on 22/01/2026.
//

#ifndef E09_UTILSSTRUCTS_HPP
#define E09_UTILSSTRUCTS_HPP

#include <string>
#include <fstream>
#include <vector>
class UtilsStructs{
public:
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
        PBR,
        Vegetation,
        CBoxDebug
    };

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

    struct Instance {
        Technique technique;
        std::vector<Element> elements;
    };

    static AssetFile createAssetFile(const std::string &id,
                                       const std::string &file,
                                       Format format) {
        AssetFile a;
        a.id = id;
        a.file = file;
        a.format = format;
        return a;
    }

    static Model createModel(const std::string &id,
                               const std::string &VD,
                               const std::string &modelPath,
                               Format format,
                               const std::string &node = "",
                               int meshId = -1,
                               const std::string &asset = "") {
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

    static Texture createTexture(const std::string &id,
                                   const std::string &path,
                                   Format format) {
        Texture t;
        t.id = id;
        t.texture = path;
        t.format = format;
        return t;
    }

    static Element createElement(const std::string &id,
                                   const std::string &model,
                                   const std::vector<std::string> &textures,
                                   const std::vector<float> &translate = {0, 0, 0},
                                   const std::vector<float> &eulerAngles = {0, 0, 0},
                                   const std::vector<float> &scale = {1, 1, 1}) {
        Element e;
        e.id = id;
        e.model = model;

        // Copy textures safely
        for (int i = 0; i < 4; i++)
            e.texture[i] = (i < (int) textures.size()) ? textures[i] : "";

        // Copy transform values
        for (int i = 0; i < 3; i++) {
            e.translate[i] = i < (int) translate.size() ? translate[i] : 0;
            e.eulerAngles[i] = i < (int) eulerAngles.size() ? eulerAngles[i] : 0;
            e.scale[i] = i < (int) scale.size() ? scale[i] : 1;
        }

        return e;
    }

    static Instance createInstance(Technique technique,
                                     const std::vector<Element> &elems) {
        Instance inst;
        inst.technique = technique;
        inst.elements = elems;

        return inst;
    }
};


#endif //E09_UTILSSTRUCTS_HPP
