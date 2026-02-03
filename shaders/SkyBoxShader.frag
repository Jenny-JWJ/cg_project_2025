#version 450

layout(location = 0) in vec3 fragTexCoord; // Directions from the vertex shader (cubemap-like)
layout(location = 0) out vec4 outColor;

// SKYBOX UNIFORMS
layout(binding = 0) uniform skyBoxUniformBufferObject {
    mat4 mvpMat;
    vec4 settings; // x = blendFactor: 1.0 (Day), 0.0 (Night)
} ubo;

layout(binding = 1) uniform sampler2D texDay; // The high-resolution day sky texture

// PSEUDO-RANDOM GENERATOR
float hash21(vec2 p) {
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

void main() {
    // --- SAFETY CHECK ---
    if (length(fragTexCoord) < 0.0001) {
        outColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // --- SPHERICAL UV MAPPING ---
    // Converts 3D directions into 2D UV coordinates for the panorama texture.
    float yaw;
    if (length(fragTexCoord.xz) < 0.0001) {
        yaw = 0.0;
    } else {
        yaw = -(atan(fragTexCoord.x, fragTexCoord.z) / 6.2831853 + 0.5);
    }
    float pitch = -(atan(fragTexCoord.y, length(fragTexCoord.xz)) / 3.14159265 + 0.5);
    vec2 uv = vec2(yaw, pitch);

    // Sample the Daytime texture
    vec4 dayColor = texture(texDay, uv);

    // --- PROCEDURAL NIGHT LOGIC ---
    // Convert day texture to greyscale (Luminance) using human perception weights.
    float luma = dot(dayColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    vec3 greyScale = vec3(luma);

    // Apply a Deep Navy Blue tint and increase contrast for a "concentrated" night feel.
    vec3 deepNightTint = vec3(0.1, 0.2, 0.5);
    vec3 nightColor = greyScale * deepNightTint;
    nightColor = pow(nightColor, vec3(1.3));

    // --- PROCEDURAL STARS (STABLE GRID METHOD) ---
    // Divide the sky into a massive grid of 350x350 cells.
    float scale = 350.0;
    vec2 gridUV = uv * scale;
    vec2 gridID = floor(gridUV);          // Unique ID for each star "cell"
    vec2 gridLocal = fract(gridUV) - 0.5; // Coordinate inside the specific cell

    float rnd = hash21(gridID);
    float starVal = 0.0;

    // Only spawn a star if the cell's random value is extremely high (> 0.99)
    if (rnd > 0.99) {
        vec2 offset = vec2((rnd - 0.5) * 0.5); // Slight random jitter
        float d = length(gridLocal - offset);

        // Smoothstep creates soft, anti-aliased edges for the stars
        float size = 0.15;
        starVal = smoothstep(size, size * 0.5, d);
        starVal *= (0.6 + 0.8 * rnd); // Randomize star brightness
    }

    // Horizon Mask: Prevents stars from showing below the ground line
    float horizonMask = smoothstep(0.48, 0.52, 1.0 - pitch);
    starVal *= horizonMask;
    vec3 stars = vec3(1.0) * starVal * 2.0;

    // Merge stars into the procedural night sky
    nightColor += stars;

    // --- FINAL COMPOSITION ---
    // Interpolate between Procedural Night and Texture Day based on blendFactor.
    float t = smoothstep(0.2, 0.8, ubo.settings.x);
    vec3 finalRGB = mix(nightColor, dayColor.rgb, t);

    // Darken the overall scene slightly more at night
    float overallBrightness = mix(0.7, 1.0, t);

    outColor = vec4(finalRGB * overallBrightness, dayColor.a);
}