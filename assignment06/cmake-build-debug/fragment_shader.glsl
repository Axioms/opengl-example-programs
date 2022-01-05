#version 430 core

out vec4 fColor;

in vec2 vTextureCoord;
in vec4 vPosition;

uniform sampler2D  sampler2;
uniform samplerCube  samplerC;
uniform int surface_effect;
uniform vec4 diffuse_color;

void main()
{
    if(surface_effect == 0) {
        fColor = diffuse_color * texture(sampler2, vTextureCoord);
    } else if(surface_effect == 1) {
        fColor = texture(sampler2, vTextureCoord);
    } else if(surface_effect == 2) {
        fColor = diffuse_color;
    } else if (surface_effect == 3) {
        fColor = texture(samplerC, vPosition.xyz);
    }else {
        fColor = vec4(0,1,0,1);
    }
}
