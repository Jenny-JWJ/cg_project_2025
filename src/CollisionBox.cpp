#include "CollisionBox.hpp"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

// ---------------- CollisionBox ----------------

CollisionBox::CollisionBox(const glm::vec3& c, const glm::vec3& size, Shape s)
        : center(c), halfSize(size * 0.5f), eulerAngles(0.0f), shape(s) {}

CollisionBox::CollisionBox(const glm::vec3& c, const glm::vec3& size, const glm::vec3& angles, Shape s)
        : center(c), halfSize(size * 0.5f), eulerAngles(angles), shape(s) {}

glm::mat3 CollisionBox::getRotationMatrix() const {
    // Convert euler angles (degrees) to rotation matrix
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, glm::radians(eulerAngles.x), glm::vec3(1, 0, 0)); // pitch
    rotation = glm::rotate(rotation, glm::radians(eulerAngles.y), glm::vec3(0, 1, 0)); // yaw
    rotation = glm::rotate(rotation, glm::radians(eulerAngles.z), glm::vec3(0, 0, 1)); // roll
    return glm::mat3(rotation);
}

float clamp(float v, float min, float max) {
    return std::max(min, std::min(v, max));
}


bool cubeCube(const CollisionBox& a, const CollisionBox& b) {
    // Fast path: if both boxes have no rotation, use AABB test (backwards compatible)
    if (a.eulerAngles == glm::vec3(0.0f) && b.eulerAngles == glm::vec3(0.0f)) {
        return (std::abs(a.center.x - b.center.x) <= (a.halfSize.x + b.halfSize.x)) &&
               (std::abs(a.center.y - b.center.y) <= (a.halfSize.y + b.halfSize.y)) &&
               (std::abs(a.center.z - b.center.z) <= (a.halfSize.z + b.halfSize.z));
    }
    
    // OBB collision using Separating Axis Theorem (SAT)
    glm::mat3 Ra = a.getRotationMatrix();
    glm::mat3 Rb = b.getRotationMatrix();
    
    glm::vec3 T = b.center - a.center;
    
    // Compute rotation matrix expressing b in a's coordinate frame
    glm::mat3 R = glm::transpose(Ra) * Rb;
    glm::mat3 AbsR;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            AbsR[i][j] = std::abs(R[i][j]) + 1e-6f; // epsilon for floating point errors
    
    // Transform T into a's coordinate frame
    glm::vec3 t = glm::transpose(Ra) * T;
    
    // Test axes L = A0, A1, A2 (a's local axes)
    for (int i = 0; i < 3; i++) {
        float ra = a.halfSize[i];
        float rb = b.halfSize[0] * AbsR[i][0] + b.halfSize[1] * AbsR[i][1] + b.halfSize[2] * AbsR[i][2];
        if (std::abs(t[i]) > ra + rb) return false;
    }
    
    // Test axes L = B0, B1, B2 (b's local axes)
    for (int i = 0; i < 3; i++) {
        float ra = a.halfSize[0] * AbsR[0][i] + a.halfSize[1] * AbsR[1][i] + a.halfSize[2] * AbsR[2][i];
        float rb = b.halfSize[i];
        float proj = t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // Test cross products of edges
    // L = A0 x B0
    {
        float ra = a.halfSize[1] * AbsR[2][0] + a.halfSize[2] * AbsR[1][0];
        float rb = b.halfSize[1] * AbsR[0][2] + b.halfSize[2] * AbsR[0][1];
        float proj = t[2] * R[1][0] - t[1] * R[2][0];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A0 x B1
    {
        float ra = a.halfSize[1] * AbsR[2][1] + a.halfSize[2] * AbsR[1][1];
        float rb = b.halfSize[0] * AbsR[0][2] + b.halfSize[2] * AbsR[0][0];
        float proj = t[2] * R[1][1] - t[1] * R[2][1];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A0 x B2
    {
        float ra = a.halfSize[1] * AbsR[2][2] + a.halfSize[2] * AbsR[1][2];
        float rb = b.halfSize[0] * AbsR[0][1] + b.halfSize[1] * AbsR[0][0];
        float proj = t[2] * R[1][2] - t[1] * R[2][2];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A1 x B0
    {
        float ra = a.halfSize[0] * AbsR[2][0] + a.halfSize[2] * AbsR[0][0];
        float rb = b.halfSize[1] * AbsR[1][2] + b.halfSize[2] * AbsR[1][1];
        float proj = t[0] * R[2][0] - t[2] * R[0][0];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A1 x B1
    {
        float ra = a.halfSize[0] * AbsR[2][1] + a.halfSize[2] * AbsR[0][1];
        float rb = b.halfSize[0] * AbsR[1][2] + b.halfSize[2] * AbsR[1][0];
        float proj = t[0] * R[2][1] - t[2] * R[0][1];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A1 x B2
    {
        float ra = a.halfSize[0] * AbsR[2][2] + a.halfSize[2] * AbsR[0][2];
        float rb = b.halfSize[0] * AbsR[1][1] + b.halfSize[1] * AbsR[1][0];
        float proj = t[0] * R[2][2] - t[2] * R[0][2];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A2 x B0
    {
        float ra = a.halfSize[0] * AbsR[1][0] + a.halfSize[1] * AbsR[0][0];
        float rb = b.halfSize[1] * AbsR[2][2] + b.halfSize[2] * AbsR[2][1];
        float proj = t[1] * R[0][0] - t[0] * R[1][0];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A2 x B1
    {
        float ra = a.halfSize[0] * AbsR[1][1] + a.halfSize[1] * AbsR[0][1];
        float rb = b.halfSize[0] * AbsR[2][2] + b.halfSize[2] * AbsR[2][0];
        float proj = t[1] * R[0][1] - t[0] * R[1][1];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // L = A2 x B2
    {
        float ra = a.halfSize[0] * AbsR[1][2] + a.halfSize[1] * AbsR[0][2];
        float rb = b.halfSize[0] * AbsR[2][1] + b.halfSize[1] * AbsR[2][0];
        float proj = t[1] * R[0][2] - t[0] * R[1][2];
        if (std::abs(proj) > ra + rb) return false;
    }
    
    // No separating axis found, boxes must be intersecting
    return true;
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
    // Fast path for non-rotated cube
    if (cube.eulerAngles == glm::vec3(0.0f)) {
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
    
    // For rotated cube, transform sphere center to cube's local space
    glm::mat3 R = cube.getRotationMatrix();
    glm::vec3 localSphereCenter = glm::transpose(R) * (sphere.center - cube.center);
    
    // Find closest point on cube in local space
    glm::vec3 closest;
    closest.x = clamp(localSphereCenter.x, -cube.halfSize.x, cube.halfSize.x);
    closest.y = clamp(localSphereCenter.y, -cube.halfSize.y, cube.halfSize.y);
    closest.z = clamp(localSphereCenter.z, -cube.halfSize.z, cube.halfSize.z);
    
    // Check distance in local space
    glm::vec3 d = closest - localSphereCenter;
    return glm::dot(d, d) <= sphere.halfSize.x * sphere.halfSize.x;
}

bool cubeCylinder(const CollisionBox& cube, const CollisionBox& cyl) {
    // Fast path for non-rotated cube (assumes cylinder is axis-aligned)
    if (cube.eulerAngles == glm::vec3(0.0f) && cyl.eulerAngles == glm::vec3(0.0f)) {
        float cubeMinY = cube.center.y - cube.halfSize.y;
        float cubeMaxY = cube.center.y + cube.halfSize.y;
        float cylMinY  = cyl.center.y - cyl.halfSize.y;
        float cylMaxY  = cyl.center.y + cyl.halfSize.y;

        if (cubeMaxY < cylMinY || cylMaxY < cubeMinY)
            return false;

        float x = clamp(cyl.center.x,
                        cube.center.x - cube.halfSize.x,
                        cube.center.x + cube.halfSize.x);

        float z = clamp(cyl.center.z,
                        cube.center.z - cube.halfSize.z,
                        cube.center.z + cube.halfSize.z);

        glm::vec2 d(cyl.center.x - x, cyl.center.z - z);
        return glm::dot(d, d) <= cyl.halfSize.x * cyl.halfSize.x;
    }
    
    // For rotated cube, transform cylinder to cube's local space
    glm::mat3 R = cube.getRotationMatrix();
    glm::vec3 localCylCenter = glm::transpose(R) * (cyl.center - cube.center);
    
    // Check Y overlap in local space
    float cylMinY = localCylCenter.y - cyl.halfSize.y;
    float cylMaxY = localCylCenter.y + cyl.halfSize.y;
    if (cylMaxY < -cube.halfSize.y || cylMinY > cube.halfSize.y)
        return false;
    
    // Clamp on X-Z plane in local space
    float x = clamp(localCylCenter.x, -cube.halfSize.x, cube.halfSize.x);
    float z = clamp(localCylCenter.z, -cube.halfSize.z, cube.halfSize.z);
    
    glm::vec2 d(localCylCenter.x - x, localCylCenter.z - z);
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

    if (shape == cube && o.shape == cylinder)
        return cubeCylinder(*this, o);

    if (shape == cylinder && o.shape == sphere)
        return sphereCylinder(o, *this);

    if (shape == sphere && o.shape == cylinder)
        return sphereCylinder(*this, o);

}

// ---------------- CollisionObject ----------------

void CollisionObject::addBox(const glm::vec3& center, const glm::vec3& size, CollisionBox::Shape shape) {
    boxes.emplace_back(center, size, shape);
}

void CollisionObject::addBox(const glm::vec3& center, const glm::vec3& size, const glm::vec3& eulerAngles, CollisionBox::Shape shape) {
    boxes.emplace_back(center, size, eulerAngles, shape);
}

bool CollisionObject::collidesWith(const CollisionObject& other) const {
    for (const auto& a : boxes)
        for (const auto& b : other.boxes)
            if (a.intersects(b))
                return true;
    return false;
}
