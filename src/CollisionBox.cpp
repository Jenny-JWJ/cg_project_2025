#include "CollisionBox.hpp"
#include <cmath>

// ---------------- CollisionBox ----------------

CollisionBox::CollisionBox(const glm::vec3& c, const glm::vec3& size)
        : center(c), halfSize(size * 0.5f) {}

bool CollisionBox::intersects(const CollisionBox& o) const {
    return (std::abs(center.x - o.center.x) <= (halfSize.x + o.halfSize.x)) &&
           (std::abs(center.y - o.center.y) <= (halfSize.y + o.halfSize.y)) &&
           (std::abs(center.z - o.center.z) <= (halfSize.z + o.halfSize.z));
}

// ---------------- CollisionObject ----------------

void CollisionObject::addBox(const glm::vec3& center, const glm::vec3& size) {
    boxes.emplace_back(center, size);
}

bool CollisionObject::collidesWith(const CollisionObject& other) const {
    for (const auto& a : boxes)
        for (const auto& b : other.boxes)
            if (a.intersects(b))
                return true;
    return false;
}
