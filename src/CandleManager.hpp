//
// Created by ACER on 03/02/2026.
//



#ifndef E09_CANDLEMANAGER_HPP
#define E09_CANDLEMANAGER_HPP

#include <map>
#include <string>
#include "modules/GlobalGML.hpp"

class CandleManager{
public:
    static std::map<std::string, glm::vec3> candlePositions;
    static bool isHoldingCandle;
    static std::string pickableCandle;
    static std::string droppedCandle;
    static std::string heldCandleId; // "" if not holding any candle
    constexpr static const float distTolerance = 3.5f;
    
    // Offset from player position (right hand position)
    static constexpr glm::vec3 candleOffset = glm::vec3(0.15f, 1.3f, 0.7f);
    
    static bool canPickupCandle(glm::vec3 pos, glm::vec3 forwardDir);
    static bool canDropCandle(glm::vec3 pos, glm::vec3 forwardDir);
    static void pickupCandle();
    static void dropCandle();
    
    // Calculate world position of held candle relative to player
    static glm::vec3 getCandleWorldPosition(glm::vec3 playerPos, float characterRotation, bool isFirstPerson);
    
    // Get the light position (slightly above the candle flame)
    static glm::vec3 getCandleLightPosition(glm::vec3 playerPos, float characterRotation, bool isFirstPerson);
};

#endif //E09_CANDLEMANAGER_HPP
