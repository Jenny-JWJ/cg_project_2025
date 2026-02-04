#include "TeleporterList.hpp"
#include "RoomManager.hpp"

std::map<int, TeleporterList::TeleportInfo> TeleporterList::teleporters;
int TeleporterList::nextId = 0;

int TeleporterList::addTeleporter(const glm::vec3& center,
                                  const glm::vec3& size,
                                  const glm::vec2& lookDir,
                                  const glm::vec3& spawnPoint,
                                  const glm::vec2& spawnLookDir,
                                  TeleportUse teleportUse,
                                  int roomId)
{
    int id = nextId++;

    TeleportInfo info{
            std::make_unique<Teleporter>(
                    id,
                    center,
                    size,
                    lookDir,
                    spawnPoint,
                    spawnLookDir
            ),
            teleportUse,
            roomId
    };

    teleporters.emplace(id, std::move(info));
    return id;
}

Teleporter* TeleporterList::getTeleporter(int id)
{
    auto it = teleporters.find(id);
    if (it == teleporters.end())
        return nullptr;

    return it->second.teleporter.get();
}

void TeleporterList::SetupTeleportPath(Teleporter* pTeleporter,
                                       const std::deque<int>& deque1)
{
    std::map<TeleportUse, Teleporter*> teleporters_use;

    bool isRightEntrance =
            (RoomManager::rooms.at(deque1[0]) == InteriorManager::DoubleFirstFloorRight);

    for (int roomId : deque1) {
        for (const auto& tp : teleporters) {
            if (tp.second.roomId == roomId) {
                teleporters_use.emplace(
                        tp.second.use,
                        tp.second.teleporter.get()
                );
            }
        }
    }

    for (auto& [use, tp] : teleporters_use) {

        if (use == TeleportUse::BaseEntrance ||
            use == TeleportUse::HighBaseEntrance ||
            use == TeleportUse::LShapedEntrance ||
            use == TeleportUse::HighLShapedEntrance)
        {
            pTeleporter->targetTpId = tp->id;
            tp->targetTpId = pTeleporter->id;
        }

        else if (use == TeleportUse::DoubleEntranceRight)
        {
            Teleporter* tpLeft =
                    teleporters_use.at(TeleportUse::DoubleEntranceLeft);
            Teleporter* tpExternal =
                    teleporters_use.at(TeleportUse::ExternalHouse);

            if (isRightEntrance) {
                tp->targetTpId = pTeleporter->id;
                pTeleporter->targetTpId = tp->id;

                tpLeft->targetTpId = tpExternal->id;
                tpExternal->targetTpId = tpLeft->id;
            }
            else {
                tp->targetTpId = tpExternal->id;
                tpExternal->targetTpId = tp->id;

                tpLeft->targetTpId = pTeleporter->id;
                pTeleporter->targetTpId = tpLeft->id;
            }
        }

        else if (use == TeleportUse::HighBaseStairsUp)
        {
            Teleporter* down =
                    teleporters_use.at(TeleportUse::HighBaseStairsDown);

            down->targetTpId = tp->id;
            tp->targetTpId = down->id;
        }

        else if (use == TeleportUse::HighLShapedStairsUp)
        {
            Teleporter* down =
                    teleporters_use.at(TeleportUse::HighLShapedStairsDown);

            down->targetTpId = tp->id;
            tp->targetTpId = down->id;
        }

        else if (use == TeleportUse::DoubleStairsUpLeft)
        {
            Teleporter* down =
                    teleporters_use.at(TeleportUse::DoubleStairsDownLeft);

            down->targetTpId = tp->id;
            tp->targetTpId = down->id;
        }

        else if (use == TeleportUse::DoubleStairsUpRight)
        {
            Teleporter* down =
                    teleporters_use.at(TeleportUse::DoubleStairsDownRight);

            down->targetTpId = tp->id;
            tp->targetTpId = down->id;
        }

        else if (use == TeleportUse::DoubleBridgeFromRight)
        {
            Teleporter* right =
                    teleporters_use.at(TeleportUse::ConnectingBridgeRight);
            Teleporter* left =
                    teleporters_use.at(TeleportUse::ConnectingBridgeLeft);
            Teleporter* fromLeft =
                    teleporters_use.at(TeleportUse::DoubleBridgeFromLeft);

            right->targetTpId = tp->id;
            tp->targetTpId = right->id;

            left->targetTpId = fromLeft->id;
            fromLeft->targetTpId = left->id;
        }
    }
}
