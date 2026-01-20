#version 450

// Global Uniforms: Light, Camera, and Time
layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec3 lightDir;
    vec4 lightColor;
    vec3 eyePos;
    float time; // Required for wind animation
} gubo;

// Local Uniforms: Transformation Matrices
layout(set = 1, binding = 0) uniform UniformBufferObject {
    mat4 mvpMat;
    mat4 mMat;
    mat4 nMat;
} ubo;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragUV;

void main() {
    vec3 pos = inPos;

    // --- WIND ANIMATION ---
    // Calculate weight: Top of the plant moves (UV.y=0), bottom stays fixed (UV.y=1)
    float windWeight = (1.0 - inUV.y);

    // Sway calculation using sine wave based on time and position
    float swaySpeed = 2.0;
    float swayAmount = 0.1;

    // Use position to desynchronize movement between different plants
    float localTime = gubo.time * swaySpeed + pos.x;

    // Apply movement to X and Z axes
    pos.x += sin(localTime) * swayAmount * windWeight;
    pos.z += cos(localTime * 0.7) * swayAmount * windWeight;

    // Standard Matrix Transformations
    gl_Position = ubo.mvpMat * vec4(pos, 1.0);
    fragPos = (ubo.mMat * vec4(pos, 1.0)).xyz;
    fragNorm = mat3(ubo.nMat) * inNorm;
    fragUV = inUV;
}