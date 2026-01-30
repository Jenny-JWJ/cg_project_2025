//
// Created by ACER on 15/11/2025.
//

#include "MapManager.hpp"

std::map<std::string,std::string> MapManager::modelsPaths = {};
std::map<std::string,std::string> MapManager::texturePaths = {};
std::string MapManager::jsonPath = "";
std::mt19937_64 MapManager::gen(123456);

std::vector<int> MapManager::CreatePathVector(int modelNumber, int thisIdNumber) {
    std::vector<int> path = {};
    std::vector<int> candidate;
    std::cout<<"Model Number: " + std::to_string(modelNumber) + "\n";
    if(modelNumber == 1){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::Base);
        int x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 2){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::LShaped);
        int x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 3){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorRight);
        int x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorRight);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleConnection);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorLeft);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorLeft);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        path.emplace_back(thisIdNumber - 1);
    }
    else if (modelNumber == 4){
        std::cout <<"in\n";
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighBaseFirstFloor);
        std::cout <<"candidate selected\n";
        int x = rand_int(0, candidate.size()-1);
        std::cout <<"random int selected\n";
        path.emplace_back(candidate[x]);
        std::cout <<"path point inserted\n";
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighBaseSecondFloor);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 5){
        std::cout <<"in\n";
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighLShapedFirstFloor);
        std::cout <<"candidate selected\n";
        int x = rand_int(0, candidate.size()-1);
        std::cout <<"random int selected\n";
        path.emplace_back(candidate[x]);
        std::cout <<"path point inserted\n";
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::HighLShapedSecondFloor);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
    }
    else if (modelNumber == 6){
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorLeft);
        int x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorLeft);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleConnection);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleSecondFloorRight);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        candidate = RoomManager::GetRoomsByType(InteriorManager::HouseTemplate::DoubleFirstFloorRight);
        x = rand_int(0, candidate.size()-1);
        path.emplace_back(candidate[x]);
        path.emplace_back(thisIdNumber + 1);
    }
    return path;
}

glm::vec3 MapManager::getTeleporterPos(glm::vec3 housePos,float houseRotY, int modelNumber) {
    glm::vec3 tpPos;
    if (modelNumber == 1){
        if(houseRotY == 180)
            tpPos = housePos + glm::vec3(0,0,5.2);
        else if (houseRotY == 0){
            tpPos = housePos + glm::vec3(0,0,-5.2);
        }
    }
    if (modelNumber == 2){
        if(houseRotY == 180)
            tpPos = housePos + glm::vec3(5.5,0,5.7);
        else if (houseRotY == 0){
            tpPos = housePos + glm::vec3(-5.5,0,-5.7);
        }
    }
    if (modelNumber == 3){
        if(houseRotY == 180)
            tpPos = housePos + glm::vec3(8.5,0,7.7);
        else if (houseRotY == 0){
            tpPos = housePos + glm::vec3(-8.5,0,-7.7);
        }
    }
    if (modelNumber == 4){
        if(houseRotY == 180)
            tpPos = housePos + glm::vec3(0,0,5.2);
        else if (houseRotY == 0){
            tpPos = housePos + glm::vec3(0,0,-5.2);
        }
    }
    if (modelNumber == 5){
        if(houseRotY == 180)
            tpPos = housePos + glm::vec3(5.5,0,4.7);
        else if (houseRotY == 0){
            tpPos = housePos + glm::vec3(-5.5,0,-4.7);
        }
    }
    if (modelNumber == 6){
        if(houseRotY == 180)
            tpPos = housePos + glm::vec3(-8.5,0,7.7);
        else if (houseRotY == 0){
            tpPos = housePos + glm::vec3(8.5,0,-7.7);
        }
    }
    return tpPos;
}

bool MapManager::debug;
