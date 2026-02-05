//
// Created by ACER on 22/01/2026.
//

#ifndef E09_COLLISIONBOXGENERATOR_HPP
#define E09_COLLISIONBOXGENERATOR_HPP

#include <vector>
#include "CollisionBox.hpp"
#include "UtilsStructs.hpp"

using UElement  = UtilsStructs::Element;
using UInstance = UtilsStructs::Instance;

//Generates collision boxes from Elements

class CollisionBoxGenerator {

public:
    static std::vector<CollisionObject> collisions;
    static UInstance collisionInstance;
    static int collisionBoxVisualCount;

    static void fillCollisionsBoxes(const std::vector<UElement>& elements); // Start creation of collision objects for each element
    static CollisionObject createCollisionObject(const UElement& element); // Recognizes element and creates corresponding collision object

    static UElement createCollisionObjectVisual(const CollisionBox& collision); // Creates visual representation of a collision box
    static void fillCollisionsBoxesVisual(); // Start creation of visual representations for all collision boxes
};

#endif // E09_COLLISIONBOXGENERATOR_HPP
