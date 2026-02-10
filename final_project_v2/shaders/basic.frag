#version 410 core
/*
in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoords;

out vec4 fColor;

//matrices
uniform mat4 model;
uniform mat4 view;
uniform mat3 normalMatrix;
//lighting
uniform vec3 lightDir;
uniform vec3 lightColor;
// textures
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

//components
vec3 ambient;
float ambientStrength = 0.2f;
vec3 diffuse;
vec3 specular;
float specularStrength = 0.5f;

void computeDirLight()
{
    //compute eye space coordinates
    vec4 fPosEye = view * model * vec4(fPosition, 1.0f);
    vec3 normalEye = normalize(normalMatrix * fNormal);

    //normalize light direction
    vec3 lightDirN = vec3(normalize(view * vec4(lightDir, 0.0f)));

    //compute view direction (in eye coordinates, the viewer is situated at the origin
    vec3 viewDir = normalize(- fPosEye.xyz);

    //compute ambient light
    ambient = ambientStrength * lightColor;

    //compute diffuse light
    diffuse = max(dot(normalEye, lightDirN), 0.0f) * lightColor;

    //compute specular light
    vec3 reflectDir = reflect(-lightDirN, normalEye);
    float specCoeff = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    specular = specularStrength * specCoeff * lightColor;
}

void main() 
{
    computeDirLight();

    //compute final vertex color
    vec3 color = min((ambient + diffuse) * texture(diffuseTexture, fTexCoords).rgb + specular * texture(specularTexture, fTexCoords).rgb, 1.0f);

    fColor = vec4(color, 1.0f);
}*/

in vec3 fNormal;
in vec2 fTexCoords;

out vec4 fColor;

uniform mat3 normalMatrix;
uniform vec3 lightDir;

uniform sampler2D diffuseTexture;
uniform vec3 materialDiffuse;
uniform bool hasDiffuseTexture;

void main()
{
    vec3 N = normalize(normalMatrix * fNormal);
    vec3 L = normalize(lightDir);

    float diff = max(dot(N, L), 0.0);

    vec3 baseColor = hasDiffuseTexture
        ? texture(diffuseTexture, fTexCoords).rgb
        : materialDiffuse;

    vec3 ambient = 0.2 * baseColor;
    vec3 diffuse = diff * baseColor;

    vec3 color = ambient + diffuse;

    fColor = vec4(color, 1.0);
}

