attribute vec3 position;
attribute vec2 texture_coord;
attribute vec3 normals;

varying vec2 out_texture;
varying vec3 out_fragPos;
varying vec3 out_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(position,1.0);
    out_texture = vec2(texture_coord);
    out_fragPos = vec3(position);
    out_normal = normals;
}
