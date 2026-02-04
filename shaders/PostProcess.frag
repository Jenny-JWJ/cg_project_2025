#version 450

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D sceneTexture;

layout(binding = 1) uniform PostProcessUBO {
    float drunkIntensity;  // 0.0 = sober, 1.0 = max drunk
    float time;            // For animated distortion
} ubo;

void main() {
    vec2 uv = fragTexCoord;
    
    if (ubo.drunkIntensity > 0.0) {
        // Wave distortion effect
        float waveStrength = ubo.drunkIntensity * 0.02;
        float waveSpeed = ubo.time * 2.0;
        
        // Multiple wave frequencies for chaotic drunk effect
        uv.x += sin(uv.y * 10.0 + waveSpeed) * waveStrength;
        uv.y += cos(uv.x * 10.0 + waveSpeed * 0.8) * waveStrength;
        
        // Radial distortion from center
        vec2 center = vec2(0.5, 0.5);
        vec2 offset = uv - center;
        float dist = length(offset);
        float radialStrength = ubo.drunkIntensity * 0.1;
        uv += offset * sin(dist * 10.0 - waveSpeed) * radialStrength;
        
        // Clamp UV to prevent wrapping (pacman effect)
        uv = clamp(uv, 0.0, 1.0);
        
        // Chromatic aberration (color separation)
        float aberration = ubo.drunkIntensity * 0.005;
        vec3 color;
        color.r = texture(sceneTexture, clamp(uv + vec2(aberration, 0.0), 0.0, 1.0)).r;
        color.g = texture(sceneTexture, uv).g;
        color.b = texture(sceneTexture, clamp(uv - vec2(aberration, 0.0), 0.0, 1.0)).b;
        
        // Vignette effect (darken edges)
        float vignette = 1.0 - dist * ubo.drunkIntensity * 0.5;
        vignette = smoothstep(0.3, 1.0, vignette);
        
        outColor = vec4(color * vignette, 1.0);
    } else {
        // No effect, just pass through
        outColor = texture(sceneTexture, uv);
    }
}
