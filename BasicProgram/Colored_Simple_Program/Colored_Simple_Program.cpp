#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

void mydisplay() {

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	//red
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	//green
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5, 0.5);
	//blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, 0.5);
	//black
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5, -0.5);
	glEnd();

	glFinish();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);

	glutMainLoop();

	return EXIT_SUCCESS;
}