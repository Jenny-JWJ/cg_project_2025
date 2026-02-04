//
// Created by ACER on 03/02/2026.
//

#include "CandleManager.hpp"
#include <iostream>

// Static member initialization
std::map<std::string, glm::vec3> CandleManager::candlePositions;
bool CandleManager::isHoldingCandle = false;
std::string CandleManager::pickableCandle = "";
std::string CandleManager::droppedCandle = "";
std::string CandleManager::heldCandleId = "";

bool CandleManager::canPickupCandle(glm::vec3 pos, glm::vec3 forwardDir){
    if (isHoldingCandle) return false; // Already holding a candle
    
    for (const auto& [candleId, candlePos] : candlePositions){
        // Check distance
        float distance = glm::length(candlePos - pos);
        if (distance > distTolerance) continue;
        
        // Calculate direction to candle
        glm::vec3 toCandle = glm::normalize(candlePos - pos);
        
        // Check if looking at candle (dot product > 0.6 means within ~53 degree cone)
        if (glm::dot(forwardDir, toCandle) > 0.6f){
            pickableCandle = candleId;
            return true;
        }
    }
    pickableCandle = "";
    return false;
}

bool CandleManager::canDropCandle(glm::vec3 pos, glm::vec3 forwardDir){
    if (!isHoldingCandle) return false; // Not holding a candle
    
    // Get the original position of the held candle
    auto it = candlePositions.find(heldCandleId);
    if (it == candlePositions.end()) return false; // Invalid candle ID
    
    glm::vec3 candlePos = it->second;
    
    // Check distance
    float distance = glm::length(candlePos - pos);
    if (distance > distTolerance) return false;
    
    // Calculate direction to candle's original position
    glm::vec3 toCandle = glm::normalize(candlePos - pos);
    
    // Check if looking at the drop position
    if (glm::dot(forwardDir, toCandle) > 0.6f){
        return true;
    }
    
    return false;
}

void CandleManager::pickupCandle(){
    isHoldingCandle = true;
    heldCandleId = pickableCandle;
}

void CandleManager::dropCandle(){
    droppedCandle = heldCandleId;
    isHoldingCandle = false;
    heldCandleId = "";
}

glm::vec3 CandleManager::getCandleWorldPosition(glm::vec3 playerPos, float characterRotation, bool isFirstPerson){
    // Use the same rotation approach as the character model (rotate around Y-axis in world space)
    // When in first person, we need opposite rotation to keep candle visible
    float rotation = isFirstPerson ? characterRotation : -characterRotation;
    
    // Calculate forward and right vectors by rotating base vectors around Y-axis
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 forward = glm::vec3(rotMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
    glm::vec3 right = glm::vec3(rotMat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Adjust offsets based on camera mode
    glm::vec3 offset;
    if (isFirstPerson) {
        // First person: candle to the right and forward
        offset = right * candleOffset.x + up * candleOffset.y + forward * candleOffset.z;
    } else {
        // Third person: candle behind and to the right of character (visible from camera)
        offset = right * (candleOffset.x - 0.5f) + up * candleOffset.y + forward * (-candleOffset.z +0.4f);
    }
    
    // Calculate candle position in world space
    glm::vec3 candleWorldPos = playerPos + offset;
    
    return candleWorldPos;
}

glm::vec3 CandleManager::getCandleLightPosition(glm::vec3 playerPos, float characterRotation, bool isFirstPerson){
    glm::vec3 candlePos = getCandleWorldPosition(playerPos, characterRotation, isFirstPerson);
    return candlePos + glm::vec3(0.0f, 0.3f, 0.0f); // Flame is 0.3 units above candle
}
