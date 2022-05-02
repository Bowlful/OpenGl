#include <iostream>
#include <GL/freeglut.h>
#include <math.h>

#define PI 3.14159265f

GLint windowWidth = 512;
GLint windowHeight = 512;
GLint TopLetfX, TopLeftY, BottomRightX, BottomRightY;

GLfloat ballRadius = 0.5f;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;

GLfloat colors[][3] = {
    {1.0, 0.0, 0.0,},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
};

int colorIdx = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(ballX, ballY, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glColor3fv(colors[colorIdx]);
        glVertex2f(0.0f, 0.0f);
        int numSegments = 100;
        GLfloat angle;
        for (int i = 0; i <= numSegments; i++) {
            angle = i * 2.0f * PI / numSegments;
            glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
        }

    glEnd();

    glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y){
    if (key == 27) {
        exit(0);
    }

}

void special(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        if (colorIdx < 2) {
            colorIdx++;
        }else{
            colorIdx = 0;
        }
    }

    glutPostRedisplay();
}

void wheel(int button, int direction, int x, int y) {

    if (direction > 0) {
        ballRadius -= 0.1f;
    }else{
        ballRadius += 0.1f;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        ballX = (float)(x - (float)512 / 2.0) * (float)(1.0 / (float)(512 / 2.0));
        ballY = -(float)(y - (float)512 / 2.0) * (float)(1.0 / (float)(512 / 2.0));
    }
    printf("(%d, %d) -> (%f, %f)\n",x,y,ballX, ballY);
}

void motion(int x, int y) {
    ballX = (float)(x - (float)512 / 2.0) * (float)(1.0 / (float)(512 / 2.0));
    ballY = -(float)(y - (float)512 / 2.0) * (float)(1.0 / (float)(512 / 2.0));
    printf("(%d, %d) -> (%f, %f)\n", x, y, ballX, ballY);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Moving ball");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseWheelFunc(wheel);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return EXIT_SUCCESS;
    
}