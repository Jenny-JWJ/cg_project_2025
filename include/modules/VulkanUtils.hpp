//
// Created by ACER on 29/09/2025.
//

#ifndef E09_VULKANUTILS_HPP
#define E09_VULKANUTILS_HPP

#endif //E09_VULKANUTILS_HPP

#pragma once
#include <vulkan/vulkan.h>

void printVulkanDeviceInfo(VkPhysicalDevice device);
void printSupportedExtensions(VkPhysicalDevice device);
void printSwapchainFormat(VkPhysicalDevice device, VkSurfaceKHR surface);