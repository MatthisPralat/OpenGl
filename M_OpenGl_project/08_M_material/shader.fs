#version 330 core
struct Material{
    vec3 ambiant;
    vec3 diffuse;
    sampler2D diffuse_tex;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light{
    vec3 position;
    vec3 ambiant;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight{
    vec3 direction;
};
uniform DirectionalLight directionalLight;
uniform Light light;
out vec4 FragColor;
  
//in vec3 ourColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
// uniform float mixValue;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

void main()
{   
    
    vec4 tex = texture(texture1, TexCoord);
    
    // Ambiant
    vec3 ambiant = light.ambiant * material.ambiant;
    
    // Difuse
    vec3 norm = normalize(Normal); // La Direction de chaques faces du cube
    vec3 lightDir = normalize( light.position - FragPos ); // La distance du Pixel à lumiere B-A = distance
    float diff = max( dot(norm, lightDir) ,0.0 ); // Est ce que la lumiere est rasante, Perpendiculaire ou dépassée en dessous de 0.
    vec3 diffuse = light.diffuse * (diff * material.diffuse) * tex.xyz; // La diffuse est 

    // Diffuse - Directional

    vec3 dir_lightDir = normalize( - directionalLight.direction); // Par convention elle est retournée pour que ce soit plus simple à imaginer 
    float dir_diff = max( dot(norm, dir_lightDir) ,0.0 ); // Est ce que la lumiere est rasante, Perpendiculaire ou dépassée en dessous de 0.
    vec3 dir_diffuse = dir_diff * tex.xyz; // La diffuse est directionalDirection 


    // Specular
    vec3 viewDir = normalize( viewPos - FragPos);  
    vec3 reflectDir = reflect(-lightDir, norm);  // Position inversée de la lumiere par rapport à la normale 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // La reflexion ne peux pas être inferieure à 0
    vec3 specular =  light.specular * (spec * material.specular);  

    vec3 result = (  ambiant +   diffuse + dir_diffuse + specular);
    FragColor = vec4( result,0) ;
}