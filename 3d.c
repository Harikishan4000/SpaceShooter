#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int lightOn = 0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat light_position[] = {0.0, 0.0, 3.0, 1.0};
    GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};

    if (lightOn) {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    } else {
        glDisable(GL_LIGHT0);
    }

    glutWireTeapot(0.5);  // Render an object (e.g., a teapot)

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
}

void toggleLight() {
    lightOn = !lightOn;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27)  // ESC key
        exit(0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Window with Light Toggle");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutCreateMenu(toggleLight);
    glutAddMenuEntry("Toggle Light (L)", 'l');
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}