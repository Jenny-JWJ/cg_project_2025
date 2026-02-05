#ifndef E09_TELEPORTERLIST_HPP
#define E09_TELEPORTERLIST_HPP

#include <map>
#include <memory>
#include <deque>
#include "Teleporter.hpp"

class TeleporterList {
public:
    // Enum defining the different uses of teleporters, which determines how they are connected to other teleporters to create paths between rooms
    enum class TeleportUse {
        ExternalHouse,
        BaseEntrance,
        HighBaseEntrance,
        HighBaseStairsUp,
        HighBaseStairsDown,
        DoubleEntranceLeft,
        DoubleStairsUpLeft,
        DoubleStairsDownLeft,
        DoubleBridgeFromLeft,
        ConnectingBridgeLeft,
        DoubleEntranceRight,
        DoubleStairsUpRight,
        DoubleStairsDownRight,
        DoubleBridgeFromRight,
        ConnectingBridgeRight,
        LShapedEntrance,
        HighLShapedEntrance,
        HighLShapedStairsUp,
        HighLShapedStairsDown
    };

    struct TeleportInfo {
        std::unique_ptr<Teleporter> teleporter;
        TeleportUse use;
        int roomId;
    };

    static int addTeleporter(const glm::vec3& center,
                             const glm::vec3& size,
                             const glm::vec2& lookDir,
                             const glm::vec3& spawnPoint,
                             const glm::vec2& spawnLookDir,
                             TeleportUse teleportUse,
                             int roomId);

    static Teleporter* getTeleporter(int id);
    static std::map<int, TeleportInfo> teleporters;

    static void SetupTeleportPath(Teleporter *pTeleporter, const std::deque<int>& deque1); // Sets up the teleport path for a given teleporter using a deque of teleporter IDs

private:

    static int nextId;
};

#endif // E09_TELEPORTERLIST_HPP
