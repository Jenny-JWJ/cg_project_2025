#ifndef E09_TELEPORTER_HPP
#define E09_TELEPORTER_HPP

#include <vector>
#include "modules/GlobalGML.hpp"

class Teleporter {
public:
    int id;
    int targetTpId = -1;

    std::vector<int> pathVector;

    glm::vec3 center;
    glm::vec3 halfSize;
    glm::vec2 lookDir;
    const float lookTol = 0.5f;

    glm::vec3 spawnPoint;
    glm::vec2 spawnLookDir;

    Teleporter(int id,
               const glm::vec3& c,
               const glm::vec3& size,
               const glm::vec2& ld,
               const glm::vec3& sPoint,
               const glm::vec2& sLookDir);

    bool CanTeleport(const glm::vec3& pos,
                     const glm::vec2& viewDir) const;

    void Teleport(glm::vec3& pos,
                  float& yaw,
                  float& pitch) const;

    void SetTeleportPath(const std::vector<int>& path);
};

#endif // E09_TELEPORTER_HPP
