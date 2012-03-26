layout(location = 0) in vec3 Position;

void main() {
gl_Position.xyz = Position;
}
