#version 450

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec4 lightDir;
    vec4 lightColor;
    vec4 eyePos;
    float time;
} gubo;

layout(set = 1, binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

void main() {
    // 1. Sample Albedo Texture
    vec4 baseColor = texture(texSampler, fragUV);

    // 2. Alpha Clipping (Standard for vegetation quads)
    if(baseColor.a < 0.5) {
        discard;
    }

    // 3. Basic Diffuse Lighting (Lambert)
    vec3 N = normalize(fragNorm);
    vec3 L = normalize(gubo.lightDir.xyz);
    float lambert = max(dot(N, L), 0.0);

    // 4. Dynamic Ambient Light
    // Derived from global light color to ensure consistency at night/sunset
    vec3 ambient = gubo.lightColor.rgb * 0.18;

    // 5. Final Color Composition
    vec3 finalRGB = baseColor.rgb * (gubo.lightColor.rgb * lambert + ambient);

    // Output with full opacity since we already performed alpha testing
    outColor = vec4(finalRGB, 1.0);
}