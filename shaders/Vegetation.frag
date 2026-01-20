#version 450

// -----------------------------------------------------------
// GLOBAL UNIFORMS (Set 0)
// Shared data like Light direction, Light color, Camera position, and Time.
// This must match 'GlobalUniformBufferObject' in C++.
// -----------------------------------------------------------
layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec3 lightDir;
    vec4 lightColor;
    vec3 eyePos;
    float time;
} gubo;

// -----------------------------------------------------------
// LOCAL TEXTURES (Set 1)
// -----------------------------------------------------------
// Binding 1: The main texture of the plant (Albedo/Color).
layout(set = 1, binding = 1) uniform sampler2D texSampler;

// Binding 2: Noise texture (mostly used in Vertex shader for wind,
// but defined in the layout, so we declare it here to be safe).
layout(set = 1, binding = 2) uniform sampler2D noiseSampler;

// -----------------------------------------------------------
// INPUTS (From Vertex Shader)
// -----------------------------------------------------------
layout(location = 0) in vec3 fragPos;   // Interpolated World Position
layout(location = 1) in vec3 fragNorm;  // Interpolated Normal
layout(location = 2) in vec2 fragUV;    // Interpolated UV coordinates

// -----------------------------------------------------------
// OUTPUT
// -----------------------------------------------------------
layout(location = 0) out vec4 outColor; // Final pixel color

void main() {
    // 1. Sample the color from the texture using UV coordinates
    vec4 baseColor = texture(texSampler, fragUV);

    // 2. ALPHA CUTOFF / DISCARD (Crucial for Vegetation)
    // Vegetation is often modeled using simple squares (quads).
    // To make them look like leaves, we use a texture with transparency.
    // If the alpha value of the texture pixel is low (transparent),
    // we 'discard' it immediately. This prevents the "black square" artifact.
    if(baseColor.a < 0.5) {
        discard;
    }

    // 3. Lighting Calculations (Standard Lambert Diffuse)
    // We calculate how much light hits the surface.

    vec3 N = normalize(fragNorm);      // Surface Normal
    vec3 L = normalize(gubo.lightDir); // Light Direction

    // Diffuse factor: Dot product between Normal and Light Direction.
    // max(..., 0.0) ensures we don't get negative lighting from behind.
    float lambert = max(dot(N, L), 0.0);

    // Ambient light: Constant light to ensure shadows aren't pitch black.
    vec3 ambient = vec3(0.1);

    // 4. Combine Lighting with Texture Color
    // Formula: TextureColor * (SunLight * Intensity + AmbientLight)
    vec3 finalRGB = baseColor.rgb * (gubo.lightColor.rgb * lambert + ambient);

    // 5. Output Final Color
    // We set Alpha to 1.0 because we already discarded the transparent parts.
    outColor = vec4(finalRGB, 1.0);
}