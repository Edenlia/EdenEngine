#version 330 core
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 FragColor;

uniform sampler2D uAlbedoTexture;
uniform sampler2D uNormalTexture;

uniform vec3 uLightPos;
uniform vec3 uCameraPos;
uniform vec3 uLightIntensity;

void main() {
    vec3 albedo = texture(uAlbedoTexture, fragTexCoords).rgb;

    vec3 normal = normalize(fragNormal);
    vec3 wi = normalize(uLightPos - fragPos);
    vec3 wo = normalize(uCameraPos - fragPos);

    // Blinn-Phong
    vec3 ka = vec3(0.001, 0.001, 0.001);
    vec3 kd = albedo;
    vec3 ks = vec3(0.7937, 0.7937, 0.7937);
    float p = 200.0;

    vec3 h = normalize(wi + wo);
    float r2 = dot((uLightPos - fragPos), (uLightPos - fragPos));
    vec3 I = uLightIntensity / 255.0;

    vec3 L_s = ks * I * pow(max(0.0, dot(h, normal)), p) / r2;
    vec3 L_d = kd * I * max(0.0, dot(wi, normal)) / r2;
    vec3 L_a = ka * I;

    vec3 color = (L_a + L_d + L_s);

    FragColor = vec4(color, 1.0);
}
