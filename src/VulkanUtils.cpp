#include "modules/VulkanUtils.hpp"
#include <iostream>
#include <vector>

void printVulkanDeviceInfo(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(device, &properties);

    std::cout << "GPU Name: " << properties.deviceName << std::endl;
    std::cout << "Driver Version: " << properties.driverVersion << std::endl;
    std::cout << "API Version: " << properties.apiVersion << std::endl;
    std::cout << "Vendor ID: " << properties.vendorID << std::endl;
    std::cout << "Device ID: " << properties.deviceID << std::endl;
    std::cout << "Device Type: " << properties.deviceType << std::endl;
}

void printSupportedExtensions(VkPhysicalDevice device) {
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());

    std::cout << "Supported Extensions:" << std::endl;
    for (const auto& ext : extensions) {
        std::cout << "  " << ext.extensionName << std::endl;
    }
}

void printSwapchainFormat(VkPhysicalDevice device, VkSurfaceKHR surface) {
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data());

    std::cout << "Available Swapchain Formats:" << std::endl;
    for (const auto& format : formats) {
        std::cout << "  Format: " << format.format << ", ColorSpace: " << format.colorSpace << std::endl;
    }
}
