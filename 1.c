#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>


GLfloat rotation = 90.0;
float posX = -0.85, posY = -0.75, posZ = 0;
int bulletShow=1;
float bulletX= -0.8, bulletY= -0.8;
float enemyX=0, enemyY=0.2;
int score=00;

void timer(int n){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    // if(enemyX>=2){
    //     enemyX-=0.1;
    // }else if(enemyX<=-2){
    //     enemyX+=0.1;
    // }

    if(bulletY<=1.7){
        bulletY+=0.1;
    }
    if(bulletY>=-0.2&& bulletY<=-0.1&& bulletX>=-0.8&&bulletX<=0.8){
        score++;
        glutPostRedisplay();
    }
    // printf("The score is: %d at Y: %f\n", score, bulletY);
    printf("The score is: %d\n", score);
}

void renderbitmap(float x, float y, void *font, char* string){
    char* c;
    glRasterPos2d(x, y);
    for(c=string; *c!='\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}

void introscreen(){
    glColor3f(1.0f, 1.0f, 0.0f);
    char buf[1000]= {0};
    char s[]="Your Score is:";
    char sc[10];
    sprintf(sc, "%2d", score);
    strcat(s, sc);
    snprintf(buf, 17, s);
    renderbitmap(-0.8, 0.8, GLUT_BITMAP_TIMES_ROMAN_24, buf);
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

void enemies(){
    glColor3f(0.0, 1.0, 0.0);
        // OpenGL commands to draw a rectangle
        glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.2f);
        glVertex2f(0.8f, -0.2f);
        glVertex2f(0.8f, 0.2f);
        glVertex2f(-0.8f, 0.2f);
        glEnd();
        glutPostRedisplay();
        glFlush();

}

void display(){
    //Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    introscreen();
    glPushMatrix();
        glTranslatef(posX,posY,posZ);
        rect();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(bulletX, bulletY+0.1,posZ);
        shoot();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(enemyX, enemyY+0.1,posZ);
        enemies();
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
            if(posX<=0.9){
                posX+=move_unit;
            }
            break;
        case GLUT_KEY_LEFT:
            if(posX>=-0.9){
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