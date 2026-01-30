//
// Created by ACER on 29/01/2026.
//

#include "RoomManager.hpp"

int RoomManager::nextRoomId = 0;
std::map<int,InteriorManager::HouseTemplate> RoomManager::rooms = {};

int RoomManager::GetRoomId() {
    int id = nextRoomId;
    nextRoomId++;
    return id;
}

int RoomManager::AddRoom(InteriorManager::HouseTemplate tmp) {
    int id = GetRoomId();
    rooms.insert({id, tmp});
    return id;
}

std::vector<int> RoomManager::GetRoomsByType(InteriorManager::HouseTemplate type){
    std::vector<int> rs = {};
    for (auto room : rooms) {
        if (room.second == type)
            rs.emplace_back(room.first);
    }
    return rs;
}


