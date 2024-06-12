#version 330 core

out vec4 FragColor;

in vec3 FragPos; // vertex in worldspace
in vec3 Normal; // normal in worldspace

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

vec4 specularMat = vec4(0.73, 0.63, 0.63, 0.5);

void main() {
    // ambient
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 lightDirection = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(Normal, lightDirection), 0.0) * lightColor;

    // specular
    float matrialShininess = 76.8; // s

    //vec3 reflectDirection = reflect(-lightDirection, Normal);  //r


    vec3 viewDirection = normalize(viewPos - FragPos); //a

    vec3 halfWayVector = normalize(lightDirection + viewDirection); //h

    //vec3 spekularReflect = pow(max(dot(reflectDirection , viewDirection), 0.0f), matrialShininess) * lightColor;
    vec3 specular = pow(max(dot(halfWayVector , Normal), 0.0), matrialShininess) * lightColor;
    // result
    vec3 result = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(result, 1.0);
}