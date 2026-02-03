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

glm::vec3 CandleManager::getCandleWorldPosition(glm::vec3 playerPos, float playerYaw){
    // Calculate right and forward vectors from player's yaw
    glm::vec3 forward = glm::vec3(sin(playerYaw), 0.0f, cos(playerYaw));
    glm::vec3 right = glm::vec3(cos(playerYaw), 0.0f, -sin(playerYaw));
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Calculate candle position in world space
    glm::vec3 candleWorldPos = playerPos 
        + right * candleOffset.x 
        + up * candleOffset.y 
        + forward * candleOffset.z;
    
    return candleWorldPos;
}

glm::vec3 CandleManager::getCandleLightPosition(glm::vec3 playerPos, float playerYaw){
    glm::vec3 candlePos = getCandleWorldPosition(playerPos, playerYaw);
    return candlePos + glm::vec3(0.0f, 0.3f, 0.0f); // Flame is 0.3 units above candle
}
