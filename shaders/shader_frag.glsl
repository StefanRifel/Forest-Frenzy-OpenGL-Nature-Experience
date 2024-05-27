#version 330 core

uniform vec3 color;

in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

float ambientStrength = 0.1;
vec3 lightColor = vec3(1.0, 1.0, 1.0);
vec3 lightPos = vec3(1.0, 1.0, 1.0);

float specularStrength = 0.5;
vec3 viewPos = vec3(1.0, 7.0, 8.0);

void main() {
    // calculate ambient 
    vec3 ambient = lightColor * ambientStrength;
    
    // calculate diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //calculate specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 

    // calculate phong lighting
    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0);
}