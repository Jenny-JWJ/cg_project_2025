//
// Created by ACER on 22/01/2026.
//

#ifndef E09_COLLISIONBOXGENERATOR_HPP
#define E09_COLLISIONBOXGENERATOR_HPP

#endif //E09_COLLISIONBOXGENERATOR_HPP

#include "stdlib.h"
#include "CollisionBox.hpp"
#include "UtilsStructs.hpp"

using Element = UtilsStructs::Element;
using UInstance = UtilsStructs::Instance;

class CollisionBoxGenerator{

public:
    static std::vector<CollisionObject> collisions;
    static UInstance collisionInstance;
    static int collisionBoxVisualCount;

    static void fillCollisionsBoxes(std::vector<Element> elements){
        for (auto element : elements){
            collisions.emplace_back(createCollisionObject(element));
        }
    }

    static CollisionObject createCollisionObject(Element element){
        std::string id = element.id;
        CollisionObject col;
        glm::vec3 pos = glm::vec3 (element.translate[0], element.translate[1], element.translate[2]);
        glm::vec3 ang = glm::vec3 (element.eulerAngles[0], element.eulerAngles[1], element.eulerAngles[2]);

        if (element.id == "house1") {
            col.addBox(pos + glm::vec3(0.0f, 2.5f, 0.0f),
                       glm::vec3(12.0f, 5.0f, 8.0f),
                       CollisionBox::Shape::cube);
        }
        else if (element.id == "house2") {
            double a = 3.0f;
            double b = 12.0f;
            double c = 8.0f;

            col.addBox(pos + glm::vec3(a, 2.5f, 0.0f),
                       glm::vec3(b, 5.0f, c),
                       CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 2.5f, a),
                       glm::vec3(c, 5.0f, b),
                       CollisionBox::Shape::cube);
        }
        else if (element.id == "house3") {
            double a = 5.0f;
            double b = 8.0f;
            double c = 8.0f;

            col.addBox(pos + glm::vec3(0.0f, 2.5f, a),
                       glm::vec3(b, 5.0f, c),
                       CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 2.5f, -a),
                       glm::vec3(b, 5.0f, c),
                       CollisionBox::Shape::cube);
        }
        else if (element.id == "house4") {
            col.addBox(pos + glm::vec3(0.0f, 3.5f, 0.0f),
                       glm::vec3(12.0f, 7.0f, 8.0f),
                       CollisionBox::Shape::cube);
        }
        else if (element.id == "house5") {
            double a = 3.0f;
            double b = 12.0f;
            double c = 8.0f;

            col.addBox(pos + glm::vec3(a, 3.5f, 0.0f),
                       glm::vec3(b, 7.0f, c),
                       CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 3.5f, a),
                       glm::vec3(c, 7.0f, b),
                       CollisionBox::Shape::cube);
        }
        else if (element.id == "ww") {
            col.addBox(pos + glm::vec3(0.0f, 1.0f, 0.0f),
                       glm::vec3(1.0f, 1.0f, 1.0f),
                       CollisionBox::Shape::cylinder);
        }
        return col;
    }

    static Element createCollisionObjectVisual(CollisionBox collision){
        Element element;

        element.id = "colBox_" + std::to_string(collision.shape) + "_" + std::to_string(collisionBoxVisualCount);

        element.translate[0] = collision.center.x; element.translate[1] = collision.center.y; element.translate[2] = collision.center.z;

        glm::vec3 baseSize = {1.0, 1.0, 1.0};

        glm::vec3 sizeMult = {collision.halfSize.x*2/baseSize.x, collision.halfSize.y*2/baseSize.y, collision.halfSize.z*2/baseSize.z};
        element.scale[0] = sizeMult.x; element.scale[1] = sizeMult.y; element.scale[2] = sizeMult.z;

        element.model = std::to_string(collision.shape);

        element.texture[0] = "colBox_texture";

        element.eulerAngles[0] = 0.0f; element.eulerAngles[1] = 0.0f; element.eulerAngles[2] = 0.0f;

        return element;
    }

    static void fillCollisionsBoxesVisual(){
        std::vector<Element> elements;
        for (auto colObj : collisions){
            for (auto col : colObj.boxes){
                elements.emplace_back(createCollisionObjectVisual(col));
            }
        }
        collisionInstance.technique = UtilsStructs::CBoxDebug;
        collisionInstance.elements = elements;
    }
};