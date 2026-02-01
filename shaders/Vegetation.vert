#version 450

// --- GLOBAL UNIFORMS (Set 0) ---
layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec4 lightDir;
    vec4 lightColor;
    vec4 eyePos;
    float time;
} gubo;

// --- LOCAL UNIFORMS (Set 1) ---
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

    // 1. Weights
    // Trunk weight (Smooth gradient)
    float windWeight = pow(1.0 - inUV.y, 3.0);
    // Tip weight (Extremely selective - only the very ends of the leaves)
    float tipWeight = pow(1.0 - inUV.y, 6.0);

    // 2. Main Trunk Sway (Rotation-based)
    float worldX = ubo.mMat[3][0];
    float worldZ = ubo.mMat[3][2];
    float slowTime = gubo.time * 1.2 + (worldX * 0.5);

    // Very subtle tilt to keep the structure solid
    float maxTilt = 0.04;
    float angleX = sin(slowTime) * maxTilt * windWeight;
    float angleZ = cos(slowTime * 0.7) * (maxTilt * 0.4) * windWeight;

    // Rotation matrices for the pivot
    mat3 rotZ = mat3(
        cos(angleX), -sin(angleX), 0,
        sin(angleX),  cos(angleX), 0,
        0,            0,           1
    );
    mat3 rotX = mat3(
        1, 0,           0,
        0, cos(angleZ), -sin(angleZ),
        0, sin(angleZ),  cos(angleZ)
    );

    // Apply primary rotation
    pos = rotZ * rotX * pos;
    vec3 animatedNorm = rotZ * rotX * inNorm;

    // 3. Micro-Flutter (Tiny displacement only for the absolute tips)
    float fastTime = gubo.time * 6.0 + (worldX + worldZ);
    float flutterScale = 0.005; // 5 millimeters max displacement

    pos.x += sin(fastTime) * flutterScale * tipWeight;
    pos.z += cos(fastTime * 1.5) * flutterScale * tipWeight;

    // 4. Final Transformations
    gl_Position = ubo.mvpMat * vec4(pos, 1.0);
    fragPos = (ubo.mMat * vec4(pos, 1.0)).xyz;
    fragNorm = mat3(ubo.nMat) * animatedNorm;
    fragUV = inUV;
}