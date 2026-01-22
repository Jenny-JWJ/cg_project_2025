#include "CollisionBox.hpp"
#include <cmath>

// ---------------- CollisionBox ----------------

CollisionBox::CollisionBox(const glm::vec3& c, const glm::vec3& size, Shape s)
        : center(c), halfSize(size * 0.5f), shape(s) {}

float clamp(float v, float min, float max) {
    return std::max(min, std::min(v, max));
}


bool cubeCube(const CollisionBox& a, const CollisionBox& b) {
    return (std::abs(a.center.x - b.center.x) <= (a.halfSize.x + b.halfSize.x)) &&
           (std::abs(a.center.y - b.center.y) <= (a.halfSize.y + b.halfSize.y)) &&
           (std::abs(a.center.z - b.center.z) <= (a.halfSize.z + b.halfSize.z));
}

bool sphereSphere(const CollisionBox& a, const CollisionBox& b) {
    glm::vec3 d = a.center - b.center;
    float r = a.halfSize.x + b.halfSize.y;
    return glm::dot(d, d) <= r * r;
}

bool cylinderCylinder(const CollisionBox& a, const CollisionBox& b) {
    // Overlap verticale (asse Y)
    float aMinY = a.center.y - a.halfSize.y;
    float aMaxY = a.center.y + a.halfSize.y;
    float bMinY = b.center.y - b.halfSize.y;
    float bMaxY = b.center.y + b.halfSize.y;

    if (aMaxY < bMinY || bMaxY < aMinY)
        return false;

    // Distanza sul piano orizzontale (X-Z)
    glm::vec2 d(a.center.x - b.center.x,
                a.center.z - b.center.z);

    float r = a.halfSize.x + b.halfSize.x;
    return glm::dot(d, d) <= r * r;
}


bool cubeSphere(const CollisionBox& cube, const CollisionBox& sphere) {
    glm::vec3 closest;

    closest.x = clamp(sphere.center.x,
                      cube.center.x - cube.halfSize.x,
                      cube.center.x + cube.halfSize.x);

    closest.y = clamp(sphere.center.y,
                      cube.center.y - cube.halfSize.y,
                      cube.center.y + cube.halfSize.y);

    closest.z = clamp(sphere.center.z,
                      cube.center.z - cube.halfSize.z,
                      cube.center.z + cube.halfSize.z);

    glm::vec3 d = closest - sphere.center;
    return glm::dot(d, d) <= sphere.halfSize.x * sphere.halfSize.x;
}

bool cubeCylinder(const CollisionBox& cube, const CollisionBox& cyl) {
    // Overlap verticale (Y)
    float cubeMinY = cube.center.y - cube.halfSize.y;
    float cubeMaxY = cube.center.y + cube.halfSize.y;
    float cylMinY  = cyl.center.y - cyl.halfSize.y;
    float cylMaxY  = cyl.center.y + cyl.halfSize.y;

    if (cubeMaxY < cylMinY || cylMaxY < cubeMinY)
        return false;

    // Clamp sul piano X-Z
    float x = clamp(cyl.center.x,
                    cube.center.x - cube.halfSize.x,
                    cube.center.x + cube.halfSize.x);

    float z = clamp(cyl.center.z,
                    cube.center.z - cube.halfSize.z,
                    cube.center.z + cube.halfSize.z);

    glm::vec2 d(cyl.center.x - x,
                cyl.center.z - z);

    return glm::dot(d, d) <= cyl.halfSize.x * cyl.halfSize.x;
}

bool sphereCylinder(const CollisionBox& sphere, const CollisionBox& cyl) {
    // Clamp verticale
    float cylMinY = cyl.center.y - cyl.halfSize.y;
    float cylMaxY = cyl.center.y + cyl.halfSize.y;

    float y = clamp(sphere.center.y, cylMinY, cylMaxY);

    // Distanza orizzontale (X-Z)
    glm::vec2 d(sphere.center.x - cyl.center.x,
                sphere.center.z - cyl.center.z);

    float r = sphere.halfSize.x + cyl.halfSize.x;

    return glm::dot(d, d) <= r * r &&
           std::abs(sphere.center.y - y) <= sphere.halfSize.x;
}


bool CollisionBox::intersects(const CollisionBox& o) const {
    if (shape == cube && o.shape == cube)
        return cubeCube(*this, o);

    if (shape == sphere && o.shape == sphere)
        return sphereSphere(*this, o);

    if (shape == cylinder && o.shape == cylinder)
        return cylinderCylinder(*this, o);

    if (shape == sphere && o.shape == cube)
        return cubeSphere(o, *this);

    if (shape == cube && o.shape == sphere)
        return cubeSphere(*this, o);

    if (shape == cube && o.shape == cylinder)
        return cubeCylinder(*this, o);

    if (shape == cylinder && o.shape == cube)
        return cubeCylinder(o, *this);

}

// ---------------- CollisionObject ----------------

void CollisionObject::addBox(const glm::vec3& center, const glm::vec3& size, CollisionBox::Shape shape) {
    boxes.emplace_back(center, size, shape);
}

bool CollisionObject::collidesWith(const CollisionObject& other) const {
    for (const auto& a : boxes)
        for (const auto& b : other.boxes)
            if (a.intersects(b))
                return true;
    return false;
}
