#version 330 core
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoords;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;
out mat3 TBN;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    fragPos = vec3(uModel * vec4(inPos, 1.0));
    fragNormal = inNormal;
    fragTexCoords = inTexCoords;

    gl_Position = uProjection * uView * vec4(fragPos, 1.0);
}
