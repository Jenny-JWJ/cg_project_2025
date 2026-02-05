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
                     const glm::vec2& viewDir) const; // Checks if the player can teleport by checking if they are in the teleporter area and looking in the right direction

    void Teleport(glm::vec3& pos,
                  float& yaw,
                  float& pitch) const; // Teleports the player to the target teleporter's spawn point and sets their look direction to the target teleporter's spawn look direction

    void SetTeleportPath(const std::vector<int>& path); // Sets the path vector for this teleporter. The path vector is used, upon using a teleporter to enter a house, to create the path of rooms connected by teleporters
};

#endif // E09_TELEPORTER_HPP
