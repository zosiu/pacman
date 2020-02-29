#version 400 core
in vec3 frag_color;
out vec4 FragColor;

uniform mat4 u_view_projection;
uniform mat4 u_model_transformation;

void main() { FragColor = vec4(frag_color, 1.0); }
