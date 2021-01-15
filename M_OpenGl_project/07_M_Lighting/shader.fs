#version 330 core
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
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * lightColor * tex;
    
    // Difuse
    vec3 norm = normalize(Normal); // La Direction de chaques faces du cube
    vec3 lightDir = normalize( lightPos - FragPos ); // La distance du Pixel à lumiere B-A = distance
    float diff = max( dot(norm, lightPos) ,0.0 ); // Est ce que la lumiere est rasante, Perpendiculaire ou dépassée en dessous de 0.
    vec3 diffuse = diff * lightColor * 0.1 * tex; // Hop jolie petite diffuse

    // Specular
    float specularStrength = 1;
    vec3 viewDir = normalize( viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

   // FragColor = vec4(lightColor,0) * tex;
    vec3 result = (  ambient + diffuse + specular);
    FragColor = vec4( result,0) ;
}