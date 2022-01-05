#version 430 core

out vec4 fColor;

in vec4 wNormal;
in vec2 vTextureCoord;
in vec4 wPosition;

/**
Light attributes and material attributes passed as uniform values.
*/
// light
uniform vec4 ambient_light;
uniform vec4 specular_light;
uniform vec4 diffuse_light;
uniform vec4 light_position; // position of the light
uniform vec4 camera_position;

// material
uniform vec4 specular_color;
uniform float specular_shininess;     // exponent for sharpening highlights
uniform float specular_strength;      // extra factor to adjust shininess
uniform sampler2D  sampler2;
uniform samplerCube  samplerC;
uniform int surface_effect;
uniform vec4 diffuse_color;

void main()
{
    vec4 color;
    if(surface_effect == 0) {
        color = diffuse_color * texture(sampler2, vTextureCoord);
    } else if(surface_effect == 1) {
        color = texture(sampler2, vTextureCoord);
    } else if(surface_effect == 2) {
        color = diffuse_color;
    } else if (surface_effect == 3) {
        fColor = texture(samplerC, wPosition.xyz);
    }else {
        color = vec4(0,1,0,1);
    }

    vec3 light_direction = wPosition.xyz - light_position.xyz;

    vec3 vnn = normalize(wNormal.xyz);

    float diffuse_factor = max(0.0, dot(vnn, -normalize(light_direction)));



    vec3 half_vector = normalize(normalize(-light_direction) - normalize(wPosition.xyz-camera_position.xyz));
    float specular_factor = max(0.0, dot(vnn, half_vector));

    if (diffuse_factor == 0.0)
    specular_factor = 0.0;
    else

    specular_factor = pow(specular_factor, specular_shininess) * specular_strength;  // sharpen the highlight


    vec4 texture_sample = texture(sampler2, vTextureCoord);

    vec4 ambient_component = texture_sample * color * ambient_light;
    vec4 diffuse_component = diffuse_factor * texture_sample  * diffuse_light;
    vec4 specular_component = specular_factor * specular_color * specular_light;

    vec4 total = ambient_component + diffuse_component + specular_component;
    if (surface_effect != 3) {
        fColor = vec4(total.rgb, 1.0);
    }
}
