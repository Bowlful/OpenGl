#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/vec2.hpp>

#define BUFFER_OFFSET(offset)   ((GLvoid*) (offset))

GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

using namespace glm;

const int NumTimesToSubdivide = 5;
const int NumTriangles = 243;
const int NumVertices = 3 * NumTriangles;

vec2 points[NumVertices];

void triangle(vec2 a, vec2 b, vec2 c)
{
	static int i = 0;
	points[i++] = a;
	points[i++] = b;
	points[i++] = c;

}

void divide_triangle(vec2 a, vec2 b, vec2 c, int m) {

	vec2 ab, ac, bc;
	if (m > 0) {

		ab = (a + b) / (vec2)2;
		ac = (a + c) / (vec2)2;
		bc = (b + c) / (vec2)2;

		divide_triangle(a, ab, ac, m - 1);
		divide_triangle(c, ac, bc, m - 1);
		divide_triangle(b, bc, ab, m - 1);
	}
	else {
		triangle(a, b, c);
	}
}

void init(void) {

	glm::vec2 verticaes[3] = {
		glm::vec2(-1.0, -1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(1.0, -1.0)
	};

	divide_triangle(verticaes[0], verticaes[1], verticaes[2], NumTimesToSubdivide);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFinish();

}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Sierpinski Gasket");
	glutDisplayFunc(display);

	glewInit();
	init();

	glutMainLoop();

	return EXIT_SUCCESS;

}