#version 450


layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform GeneralData {
    vec2 resolution;
} generalData;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
//    outColor = texture(texSampler, fragTexCoord);
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
    outColor /= 2;
//    outColor *= ((floor(gl_FragCoord.x/10)*10)/generalData.resolution.x)/2+((floor(gl_FragCoord.y/10)*10)/generalData.resolution.y)/2;
}