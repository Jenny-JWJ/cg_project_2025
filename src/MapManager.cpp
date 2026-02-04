//
// Created by ACER on 15/11/2025.
//

#include "MapManager.hpp"

std::map<std::string,std::string> MapManager::modelsPaths = {};
std::map<std::string,std::string> MapManager::texturePaths = {};
std::string MapManager::jsonPath = "";
std::mt19937_64 MapManager::gen(999999);
std::mt19937_64 UtilsStructs::gen(999999);

std::vector<int> MapManager::CreatePathVector(int modelNumber, int thisIdNumber) {
    std::vector<int> path;
    std::vector<int> candidate;
    
    // Reserve space based on model complexity
    if (modelNumber == 3 || modelNumber == 6) {
        path.reserve(6);  // Double houses: 5 rooms + 1 ID
    } else if (modelNumber == 4 || modelNumber == 5) {
        path.reserve(2);  // High houses: 2 floors
    } else {
        path.reserve(1);  // Simple houses: 1 room
    }
    
    if(modelNumber == 1){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::Base);
        int x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 2){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::LShaped);
        int x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 3){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorRight);
        int x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorRight);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleConnection);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorLeft);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorLeft);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        path.emplace_back(thisIdNumber - 1);
    }
    else if (modelNumber == 4){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighBaseFirstFloor);
        int x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighBaseSecondFloor);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 5){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighLShapedFirstFloor);
        int x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighLShapedSecondFloor);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 6){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorLeft);
        int x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorLeft);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleConnection);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorRight);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorRight);
        x = UtilsStructs::rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        path.emplace_back(thisIdNumber + 1);
    }
    return path;
}

glm::vec3 MapManager::getTeleporterPos(glm::vec3 housePos,float houseRotY, int modelNumber) {
    glm::vec3 tpPos;
    float sign = (houseRotY == 180) ? 1.0f : -1.0f;

    if (modelNumber == 1) {
        tpPos = housePos + glm::vec3(0.0f, 0.0f, 5.2f * sign);
    } else if (modelNumber == 2) {
        tpPos = housePos + glm::vec3(5.5f * sign, 0.0f, 5.7f * sign);
    } else if (modelNumber == 3) {
        tpPos = housePos + glm::vec3(8.5f * sign, 0.0f, 7.7f * sign);
    } else if (modelNumber == 4) {
        tpPos = housePos + glm::vec3(0.0f, 0.0f, 5.2f * sign);
    } else if (modelNumber == 5) {
        tpPos = housePos + glm::vec3(5.5f * sign, 0.0f, 4.7f * sign);
    } else if (modelNumber == 6) {
        tpPos = housePos + glm::vec3(-8.5f * sign, 0.0f, 7.7f * sign);
    }
    return tpPos;
}

bool MapManager::debug;
