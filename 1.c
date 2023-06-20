#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>



GLfloat rotation = 90.0;
int bullet_shot_target_hit=1;
float move_unit = 0.1f;
int enemyMoveDir[5] = {0, 1, 0, 1, 0}; // 0 is left 1 is right
float posX = 0, posY = -0.75, posZ = 0;
float bulletX = -0.8, bulletY = -0.8;
// float enemyX1 = 0, enemyX2 = 0.2,enemyX3 = 0.4,enemyX4 = 0.6,enemyX5 = 0.8;
float enemyX[5]={0, 0.2, -0.2, 0.4, -0.4};
float enemyY = 0.2;
int enemyAliveArr[5] = {1, 1, 1, 1, 1}; // 1 if alive, 0 if dead

int score = 0, level = 1;

//3D obj rendering
GLfloat theta[]={0.0, 0.0, 0.0};
GLint axis=1;

//Font styling
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

//Timer functions
void timer(int n)
{
    
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    if (bulletY <= 1.7)
    {
        bulletY += move_unit;
    }
    for(int i=0;i<5;i++){
        if (bulletY >= -enemyY&& bulletY <= -enemyY+0.4 && bulletX >= enemyX[i]-0.04 && bulletX <= enemyX[i]+0.04 && bullet_shot_target_hit==0 && enemyAliveArr[i]==1)
        {
            printf("Bullet X: %2f    Bullet Y: %2f\nEnemy X: %2f    Enemy Y: %2f\n", bulletX, bulletY, enemyX[i], enemyY);
            score++;
            if (score >= 5)
            {
                score = 0;
                level++;
                for(int j=0; j<5;j++){
                    enemyAliveArr[j]=1;
                }
                break;
            }
            glutPostRedisplay();
            bullet_shot_target_hit=1;
            enemyAliveArr[i]=0;
        }
    }
}

void enemyTimer(){
    glutPostRedisplay();
    int temp= 1000/level;
    glutTimerFunc(temp/(30*level), enemyTimer, 0);
    for(int i=0;i<5;i++){
        if(enemyMoveDir[i]==0){
            enemyX[i]-=move_unit+((0.01*(level-2))*i);
            if(enemyX[i]<=-1+(0.1*i)){
                enemyMoveDir[i]=1;
            }
        }
        if(enemyMoveDir[i]==1){
            enemyX[i]+=move_unit+((0.01*(level-2))*i);
            if(enemyX[i]>=1){
                enemyMoveDir[i]=0;
            }
        }
    }
    

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
    glVertex2f(-0.1, -0.1f);
    glVertex2f(0.1, -0.1f);
    glVertex2f(0.1, 0.04f);
    glVertex2f(-0.1, 0.04f);
    glEnd();
    glutPostRedisplay();
    glFlush();
}

void display()
{
    // Clear Window
    GLfloat mat_ambient[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_diffuse[]={0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[]={50.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	GLfloat lightIntensity[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[]={2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    introscreen();

    glPushMatrix();
        glTranslatef(posX, posY, posZ);
        rect();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(bulletX, bulletY + 0.1, posZ);
        shoot();
    glPopMatrix();

    //Enemies
    if(enemyAliveArr[0]==1){
        glPushMatrix();
            glTranslatef(enemyX[0], enemyY, posZ);
            glRotatef(theta[1], 1.0, 1.0, 0.0);
            glutWireTeapot(0.05);
            enemies();
        glPopMatrix();
    }
    
    if(enemyAliveArr[1]==1){
    glPushMatrix();
        glTranslatef(enemyX[1], enemyY, posZ);
		glRotatef(theta[1], 1.0, 1.0, 0.0);
		glutWireTeapot(0.05);
        enemies();
    glPopMatrix();
    }

if(enemyAliveArr[2]==1){
    glPushMatrix();
        glTranslatef(enemyX[2], enemyY, posZ);
		glRotatef(theta[1], 1.0, 1.0, 0.0);
		glutWireTeapot(0.05);
        enemies();
    glPopMatrix();
}

if(enemyAliveArr[3]==1){
    glPushMatrix();
        glTranslatef(enemyX[3], enemyY, posZ);
		glRotatef(theta[1], 1.0, 1.0, 0.0);
		glutWireTeapot(0.05);
        enemies();
    glPopMatrix();
}

if(enemyAliveArr[4]==1){
        glPushMatrix();
        glTranslatef(enemyX[4], enemyY, posZ);
		glRotatef(theta[1], 1.0, 1.0, 0.0);
		glutWireTeapot(0.05);
        enemies();
    glPopMatrix();
}

    glutSwapBuffers();
    glFlush();
}

void rotate(){
	theta[axis]+=1.5;
	if(theta[axis]>360.0) theta[axis]-=360.0;
	display();

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
        bullet_shot_target_hit=0;
        break;

    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Practice 1");
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
    glutIdleFunc(rotate);
    init();
    glutTimerFunc(1000, timer, 0);
    glutTimerFunc(3000, enemyTimer, 0);
    glutSpecialFunc(keyboardown);
    glutMainLoop();
}

// gcc 1.c -lglut -lGL -lGLU
//./a.out