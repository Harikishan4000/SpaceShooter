#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

int gameOver=0; //0 if game not over


GLfloat rotation = 90.0;
int bullet_shot_target_hit=1;
float move_unit = 0.1f;
int enemyMoveDir[5] = {0, 1, 0, 1, 0}; // 0 is left 1 is right
float posX = 0, posY = -0.75, posZ = 0;
float bulletX = 0, bulletY = -0.8;
// float enemyX1 = 0, enemyX2 = 0.2,enemyX3 = 0.4,enemyX4 = 0.6,enemyX5 = 0.8;
float enemyX[5]={0, 0.2, -0.2, 0.4, -0.4};
float enemyY = 0.6;
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

void scorenleveltext()
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

void introscreen(){

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
        if (bulletY >= enemyY&& bulletY <= enemyY+0.4 && bulletX >= enemyX[i]-(0.04-((level-1)*0.005))&& bulletX <= enemyX[i]+(0.04-((level-1)*0.005)) && bullet_shot_target_hit==0 && enemyAliveArr[i]==1)
        {
            printf("Bullet X: %2f    Bullet Y: %2f\nEnemy X: %2f    Enemy Y: %2f\n", bulletX, bulletY, enemyX[i], enemyY);
            score++;
            if (score >= 5)
            {
                score = 0;
                level++;
                enemyY=0.6;
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

void enemyYtimer(){
    glutTimerFunc(2000, enemyYtimer, 0);
    enemyY-=0.2;
    if(enemyY<=-0.7){
        gameOver=1;
        int finalScore=((level-1)*5)+score;
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nGame over, Your score was: %d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", finalScore);
        if(finalScore<=5){
            printf("You might not take this seriously -_-\n\n");
        }
        else if(finalScore<=10){
            printf("Try harder, you got potential ('w')\n\n");
        }
        else if(finalScore<=15){
            printf("Damn, you play well \\('o')/\n\n");
        }
        else if(finalScore<=20){
            printf("Please give me an autograph |owo|\n\n");
        }
        else if(finalScore<=25){
            printf("You are a beast |o-O|\n\n");
        }
        else if(finalScore<=30){
            printf("I'm scared of you (o o)\n\n");
        }
        else if(finalScore<=35){
            printf("You aren't real |0oO|\n\n");
        }
        else{
            printf("HOW DID YOU DO THAT??! (x-x)\n\n");
        }
        exit(0);
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

void display()
{
    // Clear Window
    if(gameOver==0){
		glPushMatrix();
     // GLfloat mat_ambient[]={1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat mat_diffuse[]={(level*0.3), (level*0.2), (level*0.1), 1.0f};
        GLfloat mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat mat_shininess[]={50.0f};
        GLfloat mat_shininess_bullet[]={500.0f};
		GLfloat mat_diffuse_gun[]={0.19f, 0.2f, 0.09f, 1.0f};
		GLfloat mat_diffuse_bullet[]={0.5706f, 0, 0, 1.0f};
        
        // // glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
            glTranslatef(bulletX, bulletY-0.09, posZ);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_bullet);
        	// glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_bullet);
            // shoot();
            glColor3f(1,0,0);
            GLUquadric *quad;
            quad = gluNewQuadric();
            gluSphere(quad,0.05,10,4);
        glPopMatrix();

		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_gun);
        	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
			glTranslatef(posX, posY, posZ);
			// gun();
			glColor3f(1,0,0);
			glRotatef(90, 1, 0, 0);
            GLUquadric *quad2;
            quad2 = gluNewQuadric();
			gluCylinder(quad2, 0.05,0.15 ,0.2, 10, 5);
            GLUquadric *quad3;
            quad3 = gluNewQuadric();
			gluCylinder(quad3, 0.05,0.05 ,0.8, 10, 5);
    	glPopMatrix();

        //Enemies
        for(int i=0;i<5;i++){
            if(enemyAliveArr[i]==1){
            glPushMatrix();
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
                glTranslatef(enemyX[i], enemyY, posZ);
                glRotatef(theta[1], 1.0, 1.0, 0.0);
                glutWireTeapot(0.05);
                // enemies();
            glPopMatrix();
            }
        }
    glPopMatrix();

    scorenleveltext();
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
    glutTimerFunc(3000, timer, 0);
    glutTimerFunc(3000, enemyTimer, 0);
    glutTimerFunc(5000, enemyYtimer, 0);
    glutSpecialFunc(keyboardown);
    glutMainLoop();
}

// gcc 1.c -lglut -lGL -lGLU
//./a.out