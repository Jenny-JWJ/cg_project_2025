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

class CollisionBoxGenerator {

public:
    static std::vector<CollisionObject> collisions;
    static UInstance collisionInstance;
    static int collisionBoxVisualCount;

    static void fillCollisionsBoxes(const std::vector<UElement>& elements);
    static CollisionObject createCollisionObject(const UElement& element);

    static UElement createCollisionObjectVisual(const CollisionBox& collision);
    static void fillCollisionsBoxesVisual();
};

#endif // E09_COLLISIONBOXGENERATOR_HPP
