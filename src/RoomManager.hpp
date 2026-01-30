//
// Created by ACER on 29/01/2026.
//

#ifndef E09_ROOMMANAGER_HPP
#define E09_ROOMMANAGER_HPP

#include <vector>
#include <map>
#include "InteriorManager.hpp"
class RoomManager{
    static int nextRoomId;

public:
    static std::map<int,InteriorManager::HouseTemplate> rooms;

    static int GetRoomId();

    static int AddRoom(InteriorManager::HouseTemplate tmp);

    static std::vector<int> GetRoomsByType(InteriorManager::HouseTemplate type);
};



#endif //E09_ROOMMANAGER_HPP
