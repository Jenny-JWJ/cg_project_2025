//
// Created by ACER on 27/01/2026.
//

#include "Teleporter.hpp"

Teleporter::Teleporter(const glm::vec3 &c, const glm::vec3 &size, const glm::vec2 ld, const glm::vec3 tPoint,
                       const glm::vec2 tLookDir) : center(c), halfSize(size), lookDir(ld), teleportPoint(tPoint), teleportLookDir(tLookDir) {}