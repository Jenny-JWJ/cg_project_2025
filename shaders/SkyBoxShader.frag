#version 450
layout(location = 0) in vec3 fragTexCoord;
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform skyBoxUniformBufferObject {
    mat4 mvpMat;
    vec4 settings; // x = Time of Day (1.0 = Day, 0.0 = Night)
} ubo;

layout(binding = 1) uniform sampler2D texDay;

// Lightweight and fast pseudo-random function (2D input)
float hash21(vec2 p) {
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

void main() {
    // --- SAFETY CHECK (ANTI-CRASH) ---
    // Prevents division by zero or invalid operations if the vector is (0,0,0)
    if (length(fragTexCoord) < 0.0001) {
        outColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // 1. Spherical UV Mapping
    // Handles the singularity at the poles to prevent artifacts
    float yaw;
    if (length(fragTexCoord.xz) < 0.0001) {
        yaw = 0.0;
    } else {
        yaw = -(atan(fragTexCoord.x, fragTexCoord.z) / 6.2831853 + 0.5);
    }
    float pitch = -(atan(fragTexCoord.y, length(fragTexCoord.xz)) / 3.14159265 + 0.5);
    vec2 uv = vec2(yaw, pitch);

    // Sample the day texture
    vec4 dayColor = texture(texDay, uv);

    // --- NIGHT LOGIC (Concentrated & Deep) ---
    // Calculate luminance (convert to greyscale based on human perception)
    float luma = dot(dayColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    vec3 greyScale = vec3(luma);

    // Deep Navy Blue Tint for the night
    vec3 deepNightTint = vec3(0.1, 0.2, 0.5);

    // Apply tint and increase contrast using pow() to make the darks "concentrated"
    vec3 nightColor = greyScale * deepNightTint;
    nightColor = pow(nightColor, vec3(1.3));

    // --- STAR LOGIC (Stable Grid Method) ---
    // High scale makes the grid cells tiny, resulting in pinpoint stars (not UFOs)
    float scale = 350.0;

    vec2 gridUV = uv * scale;
    vec2 gridID = floor(gridUV);          // ID of the grid cell
    vec2 gridLocal = fract(gridUV) - 0.5; // Local coordinates within the cell

    // Random value for this specific grid cell
    float rnd = hash21(gridID);
    float starVal = 0.0;

    // THRESHOLD:
    // Only draw a star if random value is > 0.99 (Makes stars rare)
    if (rnd > 0.99) {
        // Small random offset to keep stars from looking too perfectly aligned
        vec2 offset = vec2((rnd - 0.5) * 0.5);
        float d = length(gridLocal - offset);

        // SIZE:
        // 0.15 keeps the star small and sharp inside its tiny cell
        float size = 0.15;

        // smoothstep prevents aliasing/flickering by softening the edges
        starVal = smoothstep(size, size * 0.5, d);

        // Randomize brightness between stars
        starVal *= (0.6 + 0.8 * rnd);
    }

    // Horizon Mask: Fade out stars near the horizon and remove them below the ground
    float horizonMask = smoothstep(0.48, 0.52, 1.0 - pitch);
    starVal *= horizonMask;

    // Star Color: Multiplied by 2.0 to make them pop against the dark sky
    vec3 stars = vec3(1.0) * starVal * 2.0;

    // Add stars to the night sky
    nightColor += stars;

    // --- FINAL MIX (Day vs Night cycle) ---
    // Smooth transition based on ubo.settings.x
    float t = smoothstep(0.2, 0.8, ubo.settings.x);

    // Mix the Night (with stars) and the Day texture
    vec3 finalRGB = mix(nightColor, dayColor.rgb, t);

    // Adjust overall brightness (Night is slightly darker overall)
    float overallBrightness = mix(0.7, 1.0, t);

    outColor = vec4(finalRGB * overallBrightness, dayColor.a);
}