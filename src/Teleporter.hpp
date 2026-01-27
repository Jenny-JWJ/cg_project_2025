//
// Created by ACER on 27/01/2026.
//

#ifndef E09_TELEPORTER_HPP
#define E09_TELEPORTER_HPP

#include <iostream>
#include "modules/GlobalGML.hpp"

class Teleporter{
    glm::vec3 center;
    glm::vec3 halfSize;
    glm::vec2 lookDir;
    const float lookTol = 0.5f;

    glm::vec3 teleportPoint;
    glm::vec2 teleportLookDir;

public:

    Teleporter() = default;
    Teleporter(const glm::vec3& c, const glm::vec3& size, const glm::vec2 ld, const glm::vec3 tPoint,const glm::vec2 tLookDir);

    bool CanTeleport(glm::vec3 pos, glm::vec2 lookDir){
        return (std::abs(center.x - pos.x) <= (halfSize.x)) &&
               (std::abs(center.y - pos.y) <= (halfSize.y)) &&
               (std::abs(center.z - pos.z) <= (halfSize.z)) &&
                (abs(lookDir.x - this->lookDir.x <= lookTol)) &&
                (abs(lookDir.y - this->lookDir.y <= lookTol));
    }

    void Teleport(glm::vec3& pos, float& yaw, float& pitch) {
        std::cout << "teleport position x: " + std::to_string(teleportPoint.x) + " y: " + std::to_string(teleportPoint.y) + "z: " + std::to_string(teleportPoint.z) + "\n";
        pos = teleportPoint;
        std::cout << "player position x: " + std::to_string(pos.x) + " y: " + std::to_string(pos.y) + "z: " + std::to_string(pos.z) + "\n";
        std::cout << "teleport look at Yaw: " + std::to_string(teleportLookDir.x) + " Pitch: " + std::to_string(teleportLookDir.y) + "\n";
        yaw = teleportLookDir.x;
        pitch = teleportLookDir.y;
        std::cout << "player look at Yaw: " + std::to_string(yaw) + " Pithc: " + std::to_string(pitch) + "\n";
    }



};

#endif //E09_TELEPORTER_HPP
