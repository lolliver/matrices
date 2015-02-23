#version 330

uniform vec3 colorUniform;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform int flip = 0;
in vec3 Color;
in vec2 Texcoords;
out vec4 outColor;

void main()
{
    //outColor = vec4(Color.r+colorUniform.r,Color.g+colorUniform.g,Color.b+colorUniform.b,1.0); //flashydog
    //outColor = texture(tex,Texcoords)+vec4(Color.r+colorUniform.r,Color.g+colorUniform.g,Color.b+colorUniform.b,1.0); //flashy-brick-dog
    vec2 smileCoords = Texcoords;
    if(flip == 1)
    {
        smileCoords.x = 1-smileCoords.x;
    }
    outColor = mix(texture(tex,Texcoords),texture(tex2,smileCoords),0.2); //nice dog
}
