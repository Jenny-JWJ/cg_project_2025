#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(binding = 1, set = 1) uniform sampler2D tex;

void main() {
    // Emissive shader - no lighting, just emit bright color
    vec3 emissiveColor = texture(tex, fragUV).rgb;
    
    // Boost brightness significantly (5x multiplier for very bright sun)
    outColor = vec4(emissiveColor * 5.0, 1.0);
}
