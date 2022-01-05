#version 430 core

out vec4 fColor;

uniform vec4 diffuse_color = vec4(1, 1, 1, 1);
in vec4 vColor;



void main()
{
    /*
     * Mix the shape color pattern with the material diffuse color.
     */
    fColor = diffuse_color * vColor;
}
