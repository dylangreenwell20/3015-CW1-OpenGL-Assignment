#version 460

in vec3 Position;
in vec3 Normal;
in vec3 LightDir;
in vec3 ViewDir;
in vec3 LightIntensity;
in vec2 TexCoord;
in vec3 Vec;

layout (binding = 0) uniform sampler2D ColorTex;
layout (binding = 1) uniform sampler2D NormalMapTex;
layout (binding = 2) uniform sampler2D mossTex;
layout (binding = 3) uniform samplerCube SkyBoxTex;

layout (location = 0) out vec4 FragColor;

uniform struct LightInfo{
    vec4 Position; //light position
    vec3 La; //ambient
    vec3 L; //diffuse and specular
} Light;

uniform struct MaterialInfo{
    vec3 Kd; //diffuse
    vec3 Ka; //ambient
    vec3 Ks; //specular
    float Shininess; //shininess
} Material;

const int levels = 5;
const float scaleFactor = 1.0 / levels;

vec3 blinnPhong(vec3 n){
    vec3 diffuse = vec3(0);
    vec3 spec = vec3(0);

    vec4 rockColor = texture(ColorTex, TexCoord);
    vec4 mossColor = texture(mossTex, TexCoord);
    vec3 texColor = mix(rockColor.rgb, mossColor.rgb, mossColor.a);
    

    vec3 ambient = Light.La * texColor;
    vec3 s = normalize(LightDir);

    float sDotN = max(dot(s, n), 0.0);

    diffuse = texColor * floor(sDotN * levels) * scaleFactor;
      
    //diffuse = Material.Kd * floor(sDotN * levels) * scaleFactor;

    if (sDotN > 0.0){
        vec3 v = normalize(ViewDir);
        vec3 h = normalize(v + s);
        spec = Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
    }

    return ambient + (diffuse + spec) * Light.L;
}

void main() {
    vec3 skyboxTexColor = texture(SkyBoxTex, normalize(Vec)).rgb;

    vec3 norm = texture(NormalMapTex, TexCoord).xyz;
    norm.xy = 2.0 * norm.xy - 1.0;
    
    FragColor = vec4(skyboxTexColor, 1.0) + vec4(blinnPhong(normalize(norm)), 1.0);
}
