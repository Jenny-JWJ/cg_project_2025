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
    static std::map<int,InteriorManager::HouseTemplate> rooms; // All the rooms in the map, with their id and type

    static int GetRoomId();

    static int AddRoom(InteriorManager::HouseTemplate tmp); // Adds a room to the map and returns its id

    static std::vector<int> GetRoomsByType(InteriorManager::HouseTemplate type); // Returns a vector of all the rooms of a certain type, with their id
};



#endif //E09_ROOMMANAGER_HPP
