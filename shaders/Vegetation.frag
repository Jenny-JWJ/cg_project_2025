#version 450

// GLOBAL UNIFORMS (Set 0)
layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec4 lightDir;
    vec4 lightColor; // This color shifts from white to orange to blue
    vec4 eyePos;
    float time;
} gubo;

// TEXTURE SAMPLER (Set 1)
layout(set = 1, binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

void main() {
    // --- TEXTURE SAMPLING ---
    // Extract the RGBA color from the texture map at the current UV coordinate.
    vec4 baseColor = texture(texSampler, fragUV);

    // --- ALPHA CLIPPING (DISCARD) ---
    // Foliage is often made of square planes (quads). We use the alpha channel
    // to "cut out" the shape of the leaf.
    // 'discard' prevents the GPU from writing to the Depth Buffer for transparent pixels.
    if(baseColor.a < 0.5) {
        discard;
    }

    // --- DIFFUSE LIGHTING (LAMBERT) ---
    // Standard N·L calculation to determine how much the surface faces the sun.
    vec3 N = normalize(fragNorm);
    vec3 L = normalize(gubo.lightDir.xyz);
    float lambert = max(dot(N, L), 0.0);

    // --- DYNAMIC AMBIENT LIGHT ---
    // We derive ambient light from the global light color (0.18 multiplier).
    // This ensures that during the night, the trees aren't pitch black,
    // but take on the deep blue tint of the sky.
    vec3 ambient = gubo.lightColor.rgb * 0.18;

    // --- COLOR COMPOSITION ---
    // Multiply the base texture color by the sum of direct sunlight and ambient light.
    // This keeps the foliage integrated with the sunset/sunrise colors.
    vec3 finalRGB = baseColor.rgb * (gubo.lightColor.rgb * lambert + ambient);

    // --- FINAL OUTPUT ---
    // Alpha is set to 1.0 because transparent pixels were already 'discarded'.
    outColor = vec4(finalRGB, 1.0);
}