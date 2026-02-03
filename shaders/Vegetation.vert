#version 450

// GLOBAL UNIFORMS (Set 0)
layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec4 lightDir;
    vec4 lightColor;
    vec4 eyePos;
    float time; // Total elapsed time since application start
} gubo;

// LOCAL UNIFORMS (Set 1)
layout(set = 1, binding = 0) uniform UniformBufferObject {
    mat4 mvpMat; // Model-View-Projection
    mat4 mMat;   // Model Matrix (World position)
    mat4 nMat;   // Normal Matrix (Lighting)
} ubo;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragUV;

void main() {
    vec3 pos = inPos;

    // --- WIND WEIGHTING ---
    // We use UV.y to determine height.
    // In most models, UV.y = 1.0 is the bottom (static) and 0.0 is the top (moving).
    // Trunk weight: Uses a cubic gradient so the base stays firmly on the ground.
    float windWeight = pow(1.0 - inUV.y, 3.0);

    // Tip weight: High power (6.0) ensures only the very edges of leaves flutter.
    float tipWeight = pow(1.0 - inUV.y, 6.0);

    // --- PRIMARY SWAY (TRUNK ROTATION) ---
    // Extract world position to give each plant a unique phase (so they don't sway in sync).
    float worldX = ubo.mMat[3][0];
    float worldZ = ubo.mMat[3][2];
    float slowTime = gubo.time * 1.2 + (worldX * 0.5);

    // Calculate subtle tilt angles using Sine and Cosine
    float maxTilt = 0.04; // Maximum angular displacement
    float angleX = sin(slowTime) * maxTilt * windWeight;
    float angleZ = cos(slowTime * 0.7) * (maxTilt * 0.4) * windWeight;

    // Procedural Rotation Matrices (Pivot around the base)
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

    // Apply rotations to both position and normal vectors to keep lighting accurate
    pos = rotZ * rotX * pos;
    vec3 animatedNorm = rotZ * rotX * inNorm;

    // --- MICRO-FLUTTER (LEAF SHIVER) ---
    // Fast, high-frequency oscillation for the leaves.
    float fastTime = gubo.time * 6.0 + (worldX + worldZ);
    float flutterScale = 0.005; // 5 millimeters max displacement

    pos.x += sin(fastTime) * flutterScale * tipWeight;
    pos.z += cos(fastTime * 1.5) * flutterScale * tipWeight;

    // --- FINAL TRANSFORMATIONS ---
    gl_Position = ubo.mvpMat * vec4(pos, 1.0); // Projection for the GPU
    fragPos = (ubo.mMat * vec4(pos, 1.0)).xyz; // World position for lighting
    fragNorm = mat3(ubo.nMat) * animatedNorm;  // Transformed normals
    fragUV = inUV;
}