#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

void enemies()
{
    glColor3f(0.0, 1.0, 0.0);
    // OpenGL commands to draw a rectangle
    glBegin(GL_QUADS);
    glVertex2f(-0.8, -0.2f);
    glVertex2f(0.8, -0.2f);
    glVertex2f(0.8, 0.2f);
    glVertex2f(-0.8, 0.2f);
    glEnd();
    glutPostRedisplay();
    glFlush();
}

void sq(){
    glColor3f(1.0, 0.0, 0.0);
    // OpenGL commands to draw a rectangle
    glBegin(GL_QUADS);
    glVertex2f(-0.5, -0.2f);
    glVertex2f(0.5, -0.2f);
    glVertex2f(0.5, 0.2f);
    glVertex2f(-0.5, 0.2f);
    glEnd();
    glutPostRedisplay();
    glFlush();
}

void display()
{
    // Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0, 0.2 + 0.1, 0);
    enemies();
    glPopMatrix();
    glPushMatrix();
    // glTranslatef(0, 0.2 + 0.1, 0);
    sq();
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}
void init()
{
    // set clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // set fill color to white
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Practice 1");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}