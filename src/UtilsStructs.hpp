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
};


#endif //E09_UTILSSTRUCTS_HPP
