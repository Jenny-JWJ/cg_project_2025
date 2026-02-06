#ifndef COLLISION_BOX_HPP
#define COLLISION_BOX_HPP

#include <glm/glm.hpp>
#include <vector>

// Collision box representing cube, sphere, or cylinder
struct CollisionBox {

    enum Shape{
        cube,
        sphere,
        cylinder
    };

    glm::vec3 center;     // world-space center
    glm::vec3 halfSize; // half extents (size * 0.5), for sphere halfSize.x = halfSize.y = halfSize.z = radius, for cylinder halfSize.x = halfsize.y = base radius
    glm::vec3 eulerAngles; // rotation in degrees (pitch, yaw, roll) - (0,0,0) = no rotation
    Shape shape;

    CollisionBox() : eulerAngles(0.0f) {}
    CollisionBox(const glm::vec3& c, const glm::vec3& size, Shape shape = cube);
    CollisionBox(const glm::vec3& c, const glm::vec3& size, const glm::vec3& angles, Shape shape = cube);

    glm::mat3 getRotationMatrix() const; // Helper to convert euler angles to rotation matrix
    bool intersects(const CollisionBox& other) const;
};


// A collision object composed of multiple boxes
// (for L-shaped buildings, etc.)
class CollisionObject {
public:
    std::vector<CollisionBox> boxes;
    CollisionObject();

    void addBox(const glm::vec3& center, const glm::vec3& size, CollisionBox::Shape shape = CollisionBox::Shape::cube);
    void addBox(const glm::vec3& center, const glm::vec3& size, const glm::vec3& eulerAngles, CollisionBox::Shape shape = CollisionBox::Shape::cube);
    bool collidesWith(const CollisionObject& other) const;
};

#endif // COLLISION_BOX_HPP
