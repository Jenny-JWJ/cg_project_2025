//
// Created by ACER on 03/02/2026.
//

#include <vector>
#include "modules/GlobalGML.hpp"

#ifndef E09_DRUNKEFFECTMANAGER_HPP
#define E09_DRUNKEFFECTMANAGER_HPP
class DrunkEffectManager{
public:
    static std::vector<glm::vec3> bottles;
    constexpr static const float drunkTime = 50.0f;
    static float intensity;
    static float timer;
    static bool isDrunk;
    constexpr static const float distTollerance = 3.5f;

    static bool canDrink(const glm::vec3& pos, const glm::vec3& forwardDir){
        if (isDrunk) return false;
        for (const auto& bottle : bottles){
            // Check distance
            float distance = glm::length(bottle - pos);
            if (distance > distTollerance) continue;
            
            // Calculate direction to bottle
            glm::vec3 toBottle = glm::normalize(bottle - pos);
            
            // Check if looking at bottle (dot product > 0.6 means within ~53 degree cone)
            if (glm::dot(forwardDir, toBottle) > 0.6f){
                return true;
            }
        }
        return false;
    }

    static void drink(){
        isDrunk = true;
    }

    static void drunkEffect(glm::vec3& m,
                            float& yaw,
                            float& pitch,
                            float& roll,
                            float deltaT){
        if (!isDrunk) return;
        if(timer >= drunkTime){
            isDrunk = false;
            timer = 0.0f;
            return;
        }
        
        // Add oscillations to camera rotation for drunk effect
        intensity = 1.0f - (timer / drunkTime); // Fade effect over time
        
        // Yaw oscillation (side to side) - slow wave
        yaw += sin(timer * 1.5f) * 0.08f * intensity;
        
        // Pitch oscillation (up and down) - slightly faster
        pitch += cos(timer * 2.0f) * 0.05f * intensity;
        
        // Roll oscillation (head tilt) - different frequency
        roll += sin(timer * 1.2f) * 0.15f * intensity;
        
        // Position wobble
        m.x += sin(timer * 1.8f) * 0.02f * intensity;
        m.z += cos(timer * 1.6f) * 0.02f * intensity;

        timer += deltaT;
    }

    static float getDrunkIntensity(){
        return intensity;
    }
};
#endif //E09_DRUNKEFFECTMANAGER_HPP
