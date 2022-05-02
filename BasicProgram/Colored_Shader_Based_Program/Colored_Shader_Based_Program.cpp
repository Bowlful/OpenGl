#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#define BUFFER_OFFSET(offset)   ((GLvoid*) (offset))


GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

void init() {

    glm::vec2 points[3] = {
        glm::vec2(0.0, 0.0),
        glm::vec2(0.0, 1.0),
        glm::vec2(1.0, 1.0) };

    glm::vec3 colors[3] = {
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0) };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc2 = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc2);
    glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(sizeof(points)));
}

void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
    glFlush();
}
void myIdle() {
    glutPostRedisplay();

}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutIdleFunc(myIdle);
    glutCreateWindow("simple");
    glutDisplayFunc(mydisplay);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    init();

    glutMainLoop();

    return EXIT_SUCCESS;
}

