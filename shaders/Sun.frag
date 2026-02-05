#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(binding = 1, set = 1) uniform sampler2D tex;

void main() {
    // Emissive shader
    vec3 emissiveColor = texture(tex, fragUV).rgb;
    
    // Boost brightness
    outColor = vec4(emissiveColor * 10.0, 1.0);
}
