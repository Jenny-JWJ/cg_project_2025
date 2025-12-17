#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include <glm/glm.hpp>
#include <vector>

// --------------------------------------------------
// Single Axis-Aligned Bounding Box (AABB)
// --------------------------------------------------
struct CollisionBox {
    glm::vec3 center;     // world-space center
    glm::vec3 halfSize;   // half extents (size * 0.5)

    CollisionBox() = default;
    CollisionBox(const glm::vec3& c, const glm::vec3& size);

    bool intersects(const CollisionBox& other) const;
};

// --------------------------------------------------
// A collision object composed of multiple boxes
// (for L-shaped buildings, etc.)
// --------------------------------------------------
class CollisionObject {
public:
    std::vector<CollisionBox> boxes;

    void addBox(const glm::vec3& center, const glm::vec3& size);
    bool collidesWith(const CollisionObject& other) const;
};

#endif // COLLISION_BOX_HPP
