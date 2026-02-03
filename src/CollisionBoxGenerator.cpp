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

    glm::vec3 rot = glm::vec3(
            element.eulerAngles[0],
            element.eulerAngles[1],
            element.eulerAngles[2]
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
                glm::vec3(0.4f, 1.0f, 0.4f),
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
    else if (element.model.find("castle_model") != std::string::npos) {
        col.addBox(
                pos,
                glm::vec3(14, 20.0f, 14),
                CollisionBox::Shape::cube
        );
        col.addBox(
                pos + glm::vec3(7.0f, 12, 7.0f),
                glm::vec3(6, 24.0f, 6),
                CollisionBox::Shape::cylinder
        );
        col.addBox(
                pos + glm::vec3(-7.0f, 12, 7.0f),
                glm::vec3(6, 24.0f, 6),
                CollisionBox::Shape::cylinder
        );
        col.addBox(
                pos + glm::vec3(7.0f, 12, -7.0f),
                glm::vec3(6, 24.0f, 6),
                CollisionBox::Shape::cylinder
        );
        col.addBox(
                pos + glm::vec3(-7.0f, 12, -7.0f),
                glm::vec3(6, 24.0f, 6),
                CollisionBox::Shape::cylinder
        );
        col.addBox(
                pos + glm::vec3(-9.0f, 2, 0.0f),
                glm::vec3(3.5f, 4.0f, 3.5f),
                CollisionBox::Shape::cube
        );
    }
    else if (element.model == "wall") {
        col.addBox(
                pos + glm::vec3(0.0f, 2.5f, 0.0f),
                glm::vec3(4.0f, 5.0f, 0.9f),
                rot,
                CollisionBox::Shape::cube
        );
    }
    else if (element.model == "tunnel") {
        col.addBox(
                pos + glm::vec3(1.3f, 2.5f, 0.0f),
                glm::vec3(0.9f, 5.0f, 6.0f),
                rot,
                CollisionBox::Shape::cube
        );
        col.addBox(
                pos + glm::vec3(-1.3f, 2.5f, 0.0f),
                glm::vec3(0.9f, 5.0f, 6.0f),
                rot,
                CollisionBox::Shape::cube
        );
    }
    else if (element.model == "stairs") {
        float xmult = element.scale[0]/2;
        float ymult = element.scale[1]/1.5;
        float zmult = element.scale[2]/1.5;
        if (rot.y == 0){
            col.addBox(
                    pos + glm::vec3(xmult*0.0f, ymult*2.0f, -2*zmult),
                    glm::vec3(xmult*3, ymult*4.0f, 2.5*zmult),
                    CollisionBox::Shape::cube
            );
            col.addBox(
                    pos + glm::vec3(xmult*0.0f, ymult*5.0f, -1*zmult),
                    glm::vec3(xmult*3, ymult*4.0f, 6*zmult),
                    CollisionBox::Shape::cube
            );
        }

        if (rot.y == 180){
            col.addBox(
                    pos + glm::vec3(xmult*0.0f, ymult*2.0f, 2*zmult),
                    glm::vec3(xmult*3, ymult*4.0f, 2.5*zmult),
                    CollisionBox::Shape::cube
            );
            col.addBox(
                    pos + glm::vec3(xmult*0.0f, ymult*5.0f, 1*zmult),
                    glm::vec3(xmult*3, ymult*4.0f, 6*zmult),
                    CollisionBox::Shape::cube
            );
        }
    }
    /*else if (element.model.find("tent1") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(0.0f, 1, 1.0f),
                glm::vec3(2.0f, 2.0f, 0.1f),
                CollisionBox::Shape::cube
        );
        col.addBox(
                pos + glm::vec3(0.0f, 1, -1.0f),
                glm::vec3(2.0f, 2.0f, 0.1f),
                CollisionBox::Shape::cube
        );
        col.addBox(
                pos + glm::vec3(2.0f, 1, 0.0f),
                glm::vec3(0.1f, 2.0f, 2.0f),
                CollisionBox::Shape::cube
        );
    }
    else if (element.model.find("tent2") != std::string::npos) {
        col.addBox(
                pos + glm::vec3(4.0f, 1, 2.0f),
                glm::vec3(0.1f, 2.0f, 12),
                rot + glm::vec3(-90, 0, 0),
                CollisionBox::Shape::cube
        );
        col.addBox(
                pos + glm::vec3(-4.0f, 1, -2.0f),
                glm::vec3(0.1f, 2.0f, 12),
                rot + glm::vec3(-90, 0, 0),
                CollisionBox::Shape::cube
        );
        col.addBox(
                pos + glm::vec3(-3.0f, 1, 6.0f),
                glm::vec3(8.0f, 2.0f, 0.1f),
                rot + glm::vec3(-90, 0, 0),
                CollisionBox::Shape::cube
        );
    }*/
    else if(element.model.find("statue") != std::string::npos){
        col.addBox(
                pos,
                glm::vec3(1.5f,2,1.5f),
                CollisionBox::Shape::cube
                );
    }
    else if(element.model.find("fence1") != std::string::npos){
        col.addBox(
                pos,
                glm::vec3(3,6,0.1),
                rot,
                CollisionBox::Shape::cube
        );
    }
    else if(element.model.find("fence2") != std::string::npos){
        col.addBox(
                pos,
                glm::vec3(3,6,0.1),
                rot,
                CollisionBox::Shape::cube
        );
    }
    else if(element.model.find("fence3") != std::string::npos){
        col.addBox(
                pos,
                glm::vec3(3,12,3),
                CollisionBox::Shape::cube
        );
    }
    else if(element.model == "grave1" || element.model == "grave2" || element.model == "grave3" || element.model == "grave13" || element.model == "grave14" || element.model == "grave15" || element.model == "grave16"){
        col.addBox(
                pos,
                glm::vec3(1,1,2.5),
                rot,
                CollisionBox::Shape::cube
        );
    }
    else if(element.model == "grave4" || element.model == "grave5" || element.model == "grave6" || element.model == "grave7" || element.model == "grave8" || element.model == "grave9" || element.model == "grave10" || element.model == "grave11" || element.model == "grave12"){
        col.addBox(
                pos,
                glm::vec3(1,1,0.4),
                rot,
                CollisionBox::Shape::cube
        );
    }
    else if(element.model == "grave17" || element.model == "grave18" || element.model == "grave19" || element.model == "grave20" || element.model == "grave21"){
        col.addBox(
                pos,
                glm::vec3(1,1,0.2),
                rot,
                CollisionBox::Shape::cube
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

    // For rotated boxes, position at center. For non-rotated, offset to base if models have origin at bottom
    bool isRotatedY = (collision.eulerAngles.x != 0.0f || collision.eulerAngles.z != 0.0f);
    
    element.translate[0] = collision.center.x;
    element.translate[1] = isRotatedY ? collision.center.y : (collision.center.y - collision.halfSize.y);
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

    element.eulerAngles[0] = collision.eulerAngles.x;
    element.eulerAngles[1] = collision.eulerAngles.y;
    element.eulerAngles[2] = collision.eulerAngles.z;

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
