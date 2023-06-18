#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

GLfloat rotation = 90.0;
float move_unit = 0.1f;
int enemyMoveDir = 0; // 0 is left 1 is right
float posX = -0.85, posY = -0.75, posZ = 0;
float bulletX = -0.8, bulletY = -0.8;
float enemyX = 0, enemyY = 0.2;
int score = 0, level = 1;
int enemyXarr[5] = {0, 0, 0, 0, 0};
int enemyYarr[5] = {0.2, 0, 0, 0, 0};
int enemyAliveArr[5] = {0, 0, 0, 0, 0}; // 1 if alive, 0 if dead

void timer(int n)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    if (bulletY <= 1.7)
    {
        bulletY += move_unit;
    }

    if (bulletY >= -enemyY&& bulletY <= -enemyY + 0.1 && bulletX >= enemyX-0.8 && bulletX <= enemyX+0.8)
    {
        printf("Bullet X: %2f    Bullet Y: %2f\nEnemy X: %2f    Enemy Y: %2f\n", bulletX, bulletY, enemyX, enemyY);
        score++;
        if (score >= 10)
        {
            score = 0;
            level++;
        }
        glutPostRedisplay();
    }
    // printf("The score is: %d at Y: %f\n", score, bulletY);
    // printf("The score is: %f\n", enemyX);
}

void enemyTimer(){
    glutPostRedisplay();
    glutTimerFunc(2000/60, enemyTimer, 0);
    if(enemyMoveDir==0){
        enemyX-=move_unit;
        if(enemyX<=-1){
            enemyMoveDir=1;
        }
    }
    if(enemyMoveDir==1){
        enemyX+=move_unit;
        if(enemyX>=1){
            enemyMoveDir=0;
        }
    }

}

void renderbitmap(float x, float y, void *font, char *string)
{
    char *c;
    glRasterPos2d(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void introscreen()
{
    glColor3f(0.7f, 0.7f, 0.7f);
    char buf[1000] = {0};
    char s[] = "Your Score is: ";
    char sc[10];
    sprintf(sc, "%d", score);
    strcat(s, sc);
    snprintf(buf, 17, s);
    renderbitmap(-0.9, 0.85, GLUT_BITMAP_TIMES_ROMAN_24, buf);

    glColor3f(0.7f, 0.7f, 0.7f);
    char buf2[1000] = {0};
    char s2[] = "Level: ";
    char lv[10];
    sprintf(lv, "%d", level);
    strcat(s2, lv);
    snprintf(buf2, 9, s2);
    renderbitmap(0.6, 0.85, GLUT_BITMAP_TIMES_ROMAN_24, buf2);
}

void reshape(int width, int height)
{
    /* window ro reshape when made it bigger or smaller*/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // clip the windows so its shortest side is 2.0
    if (width < height)
    {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)height / (GLfloat)width, 2.0 * (GLfloat)height / (GLfloat)width, 2.0, 2.0);
    }
    else
    {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)width / (GLfloat)height, 2.0 * (GLfloat)width / (GLfloat)height, 2.0, 2.0);
    }
    // set viewport to use the entire new window
    glViewport(0, 0, width, height);
}

void rect()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.05, -0.1);
    glVertex2f(-0.05, 0.1);
    glVertex2f(0.05, 0.1);
    glVertex2f(0.05, -0.1);
    glEnd();
}

void shoot()
{
    glColor3f(1.0, 0.0, 1.0);
    // OpenGL commands to draw a rectangle
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(0.05f, 0.05f);
    glVertex2f(-0.05f, 0.05f);
    glEnd();
    glutPostRedisplay();
    glFlush();
}

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

void display()
{
    // Clear Window
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    introscreen();
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    rect();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(bulletX, bulletY + 0.1, posZ);
    shoot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(enemyX, enemyY, posZ);
    enemies();
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

void keyboardown(int key, int x, int y)
{
    // printf("%d", key);
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (posX <= 0.9)
        {
            posX += move_unit;
        }
        break;
    case GLUT_KEY_LEFT:
        if (posX >= -0.9)
        {
            posX -= move_unit;
        }
        break;

    case GLUT_KEY_UP:
        bulletY = -0.65;
        bulletX = posX;
        display();
        break;

    default:
        break;
    }
    glutPostRedisplay();
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
    glutTimerFunc(1000, timer, 0);
    glutTimerFunc(2000, enemyTimer, 0);
    glutSpecialFunc(keyboardown);
    glutMainLoop();
}

// gcc 1.c -lglut -lGL -lGLU
//./a.out