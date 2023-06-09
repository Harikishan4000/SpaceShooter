#include <stdio.h>
#include <GL/glut.h>

GLfloat rotation = 90.0;
float posX = -0.85, posY = -0.75, posZ = 0;
int bulletShow=1;
float bulletX= -0.85, bulletY= -0.75;

void timer(int n){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    if(bulletY<=1.7){
        bulletY+=0.1;
    }
}

void reshape(int width, int heigth){
    /* window ro reshape when made it bigger or smaller*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //clip the windows so its shortest side is 2.0
    if (width < heigth) {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)heigth / (GLfloat)width, 2.0 * (GLfloat)heigth / (GLfloat)width, 2.0, 2.0);
    }
    else{
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)width / (GLfloat)heigth, 2.0 * (GLfloat)width / (GLfloat)heigth,2.0 , 2.0);
    }
    // set viewport to use the entire new window
    glViewport(0, 0, width, heigth);
}

void rect(){
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.05, -0.1);
    glVertex2f(-0.05, 0.1);
    glVertex2f(0.05, 0.1);
    glVertex2f(0.05, -0.1);
    glEnd();

}

void shoot(){    
    if (bulletShow)
    {
        glColor3f(1.0, 0.0, 1.0);
        // OpenGL commands to draw a rectangle
        glBegin(GL_QUADS);
        glVertex2f(-0.05f, -0.05f);
        glVertex2f(0.05f, -0.05f);
        glVertex2f(0.05f, 0.05f);
        glVertex2f(-0.05f, 0.05f);
        glEnd();
    }
    glutPostRedisplay();
    glFlush();
}

void display(){
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
        glTranslatef(posX,posY,posZ);
        rect();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(bulletX, bulletY+0.1,posZ);
        shoot();
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}


void init(){
    // set clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // set fill color to white
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

}

float move_unit = 0.1f;

void keyboardown(int key, int x, int y)
{
    // printf("%d", key);
    switch (key){
        case GLUT_KEY_RIGHT:
            if(posX<=0.85){
                posX+=move_unit;
            }
            break;
        case GLUT_KEY_LEFT:
            if(posX>=-0.85){
                posX-=move_unit;
            }
            break;

        case GLUT_KEY_UP:
            bulletY=-0.65;
            bulletX=posX;            
            display();
            break;

        default:
         break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Practice 1");
    glutDisplayFunc(display);
    init();
    glutTimerFunc(1000, timer, 0);
    glutSpecialFunc(keyboardown);
    glutMainLoop();

}

//gcc 1.c -lglut -lGL -lGLU
//./a.out