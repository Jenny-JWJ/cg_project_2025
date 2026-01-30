#include "Teleporter.hpp"
#include "TeleporterList.hpp"
#include <cmath>
#include <iostream>

Teleporter::Teleporter(int id,
                       const glm::vec3& c,
                       const glm::vec3& size,
                       const glm::vec2& ld,
                       const glm::vec3& sPoint,
                       const glm::vec2& sLookDir)
        : id(id),
          center(c),
          halfSize(size),
          lookDir(ld),
          spawnPoint(sPoint),
          spawnLookDir(sLookDir)
{}

bool Teleporter::CanTeleport(const glm::vec3& pos,
                             const glm::vec2& viewDir) const
{
    constexpr float PERIOD = 6.0f;

    auto normalize = [&](float a) {
        a = std::fmod(a, PERIOD);
        if (a < 0.0f) a += PERIOD;
        return a;
    };

    auto angDist = [&](float a, float b) {
        float d = std::abs(a - b);
        return std::min(d, PERIOD - d);
    };

    float viewYaw = normalize(viewDir.x);
    float tpYaw   = normalize(lookDir.x);

    bool isInArea =  std::abs(center.x - pos.x) <= halfSize.x &&
                     std::abs(center.y - pos.y) <= halfSize.y &&
                     std::abs(center.z - pos.z) <= halfSize.z;

    bool looksInRightDirection = angDist(viewYaw, tpYaw) <= lookTol &&
                                 std::abs(viewDir.y - lookDir.y) <= lookTol;

    return isInArea && looksInRightDirection;
}

void Teleporter::Teleport(glm::vec3& pos,
                          float& yaw,
                          float& pitch) const
{
    const Teleporter* target = TeleporterList::getTeleporter(targetTpId);
    if (!target) return;

    pos   = target->spawnPoint;
    yaw   = target->spawnLookDir.x;
    pitch = target->spawnLookDir.y;
}

void Teleporter::SetTeleportPath(const std::vector<int>& path)
{
    pathVector = path;
}
