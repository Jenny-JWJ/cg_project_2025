//
// Created by ACER on 23/01/2026.
//
#include "CollisionBoxGenerator.hpp"

#include <string>
#include <glm/vec3.hpp>
#include <iostream>

// === STATIC MEMBERS ===
std::vector<CollisionObject> CollisionBoxGenerator::collisions = {};
UInstance CollisionBoxGenerator::collisionInstance;
int CollisionBoxGenerator::collisionBoxVisualCount = 0;

// === FUNCTIONS ===

void CollisionBoxGenerator::fillCollisionsBoxes(const std::vector<UElement>& elements) {
    std::cout <<"Starting to fill the collisions";
    for (const auto& element : elements) {
        collisions.emplace_back(createCollisionObject(element));
    }
    std::cout <<"Collisions created: " << collisions.size();
}

CollisionObject CollisionBoxGenerator::createCollisionObject(const UElement& element) {
    CollisionObject col;

    glm::vec3 pos = glm::vec3(
            element.translate[0],
            element.translate[1],
            element.translate[2]
    );




    if (element.id.find("house1") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 2.5f, 0.0f),
                glm::vec3(12.0f, 5.0f, 8.0f),
                CollisionBox::Shape::cube
        );
    }
    else if (element.id.find("house2") != std::string::npos) {

        if (element.eulerAngles[1] == 180.0f)
        {
            double a = -4.0, b = 8, c = 15.5;

            col.addBox(pos + glm::vec3(b/2, 2.5f, a),
                   glm::vec3(b, 5.0f, c),
                   CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 2.5f, 0.0f),
                       glm::vec3(c, 5.0f, b),
                       CollisionBox::Shape::cube);
        }
        else if (element.eulerAngles[1] == 0.0f)
        {
            double a = 4.0, b = 8, c = 15.5;

            col.addBox(pos + glm::vec3(-b/2, 2.5f, a),
                       glm::vec3(b, 5.0f, c),
                       CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 2.5f, 0.0f),
                       glm::vec3(c, 5.0f, b),
                       CollisionBox::Shape::cube);
        }
    }
    else if (element.id.find("house3") != std::string::npos) {
        double a = 8.5, b = 8.0, c = 12.0;

        col.addBox(pos + glm::vec3(a, 3.5f, 0.0f),
                   glm::vec3(b, 7.0f, c),
                   CollisionBox::Shape::cube);

        col.addBox(pos + glm::vec3(-a, 3.5f, 0.0f),
                   glm::vec3(b, 7.0f, c),
                   CollisionBox::Shape::cube);
    }
    else if (element.id.find("house4") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 3.5f, 0.0f),
                glm::vec3(12.0f, 7.0f, 8.0f),
                CollisionBox::Shape::cube
        );
    }
    else if (element.id.find("house5") != std::string::npos) {
        if (element.eulerAngles[1] == 180.0f)
        {
            double a = -4.0, b = 8, c = 15.5;

            col.addBox(pos + glm::vec3(b/2, 3.5f, a),
                       glm::vec3(b, 7.0f, c),
                       CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 3.5f, 0.0f),
                       glm::vec3(c, 7.0f, b),
                       CollisionBox::Shape::cube);
        }
        else if (element.eulerAngles[1] == 0.0f)
        {
            double a = 4.0, b = 8, c = 15.5;

            col.addBox(pos + glm::vec3(-b/2, 3.5f, a),
                       glm::vec3(b, 7.0f, c),
                       CollisionBox::Shape::cube);

            col.addBox(pos + glm::vec3(0.0f, 3.5f, 0.0f),
                       glm::vec3(c, 7.0f, b),
                       CollisionBox::Shape::cube);
        }
    }
    else if (element.id.find("ww") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 0.5f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                CollisionBox::Shape::cylinder
        );
    }
    else if (element.model.find("tree1") != std::string::npos || element.model.find("tree2") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 2.5f, 0.0f),
                glm::vec3(0.2f, 5.0f, 0.2f),
                CollisionBox::Shape::cylinder
        );
    }
    else if (element.model.find("tree3") != std::string::npos || element.model.find("tree4") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                CollisionBox::Shape::sphere
        );
    }
    else if (element.model.find("barrel") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 0.5f, 0.0f),
                glm::vec3(1.0f, 1.0f, 0.5f),
                CollisionBox::Shape::cylinder
        );
    }
    else if (element.model.find("lamp1") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 2.5f, 0.0f),
                glm::vec3(0.1f, 5.0f, 0.1f),
                CollisionBox::Shape::cylinder
        );
    }

    return col;
}

UElement CollisionBoxGenerator::createCollisionObjectVisual(const CollisionBox& collision) {
    UElement element;

    element.id =
            "colBox_" +
            std::to_string(static_cast<int>(collision.shape)) +
            "_" +
            std::to_string(collisionBoxVisualCount++);

    element.translate[0] = collision.center.x;
    element.translate[1] = collision.center.y - collision.halfSize.y;
    element.translate[2] = collision.center.z;



    if(collision.shape == CollisionBox::cube){
        element.model = "cube";
        element.scale[0] = collision.halfSize.x * 2.0f;
        element.scale[1] = collision.halfSize.y * 2.0f;
        element.scale[2] = collision.halfSize.z * 2.0f;
    }

    if(collision.shape == CollisionBox::sphere){
        element.model = "sphere";
        element.scale[0] = collision.halfSize.x * 2.0f * 2.0f;
        element.scale[1] = collision.halfSize.y * 2.0f * 2.0f;
        element.scale[2] = collision.halfSize.z * 2.0f * 2.0f;
    }

    if(collision.shape == CollisionBox::cylinder){
        element.model = "cylinder";
        element.scale[0] = collision.halfSize.x * 2.0f * 2.0f;
        element.scale[1] = collision.halfSize.y * 2.0f;
        element.scale[2] = collision.halfSize.z * 2.0f * 2.0f;
        //element.translate[1] = collision.center.y - collision.halfSize.y * 2.0f;
    }


    element.texture[0] = "colBox_texture";
    element.texture[1] = "pnois";

    element.eulerAngles[0] = 0.0f;
    element.eulerAngles[1] = 0.0f;
    element.eulerAngles[2] = 0.0f;

    return element;
}

void CollisionBoxGenerator::fillCollisionsBoxesVisual() {
    std::vector<UElement> elements;

    for (const auto& colObj : collisions) {
        for (const auto& col : colObj.boxes) {
            elements.emplace_back(createCollisionObjectVisual(col));
        }
    }

    collisionInstance.technique = UtilsStructs::CBoxDebug;
    collisionInstance.elements = elements;
}
