#version 330 core

out vec4 FragColor;

in vec3 pointNormal;
in vec3 pointPosition;
in mat4 model_;
in vec2 texCoord;

uniform vec3 viewPosition;
uniform vec3 lightPosition;

struct Material {
    float ambient;
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

uniform Material material;

void main()
{
    // diffuse
    vec3 sunshineDirection = normalize(lightPosition - pointPosition);
    float sunshineAngle = max(dot(sunshineDirection, normalize(vec4(pointNormal, 0) * model_).xyz), 0);
    vec3 diffuseeComponent = (sunshineAngle * texture(material.diffuse, texCoord)).rgb;

    // ambient
    vec3 ambitentComponent = material.ambient * texture(material.diffuse, texCoord).rgb;

    // specular
    vec3 reflectLight = normalize(reflect(-sunshineDirection, normalize(pointNormal)));
    vec3 sightDirection = normalize(viewPosition - pointPosition);
    vec3 specularComponent = pow(max(dot(sightDirection, reflectLight), 0), material.shininess) * texture(material.specular, texCoord).rgb;

    vec3 resultColor = diffuseeComponent + ambitentComponent + specularComponent;
    FragColor = vec4(resultColor, 1.0);
}
