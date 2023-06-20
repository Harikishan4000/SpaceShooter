#include<GL/glut.h>
#include<stdio.h>
int show=0;

void wall(double thickness){
	glPushMatrix();
	glTranslated(0.5, 0.0, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void tableLeg(double thick, double len){
	glPushMatrix();
	glTranslated(0, len/2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
	
}

void table(double topWid, double topThick, double legThick, double legLen){
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist=0.95*topWid/2.0-legThick/2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2*dist);
	tableLeg(legThick, legLen);
	glTranslated(-2*dist, 0, 2*dist);
	tableLeg(legThick, legLen);
	glTranslated(0, 0, -2*dist);
	tableLeg(legThick, legLen);
	glPopMatrix();
}

GLfloat theta[]={0.0, 0.0, 0.0};
GLint axis=1;

void displaySolid(void){
	GLfloat mat_ambient[]={1.0f, 0.3f, 0.8f, 1.0f};
	GLfloat mat_diffuse[]={0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[]={50.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	GLfloat lightIntensity[]={1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightPosition[]={2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.3, 1.3, -1.3, 1.3, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3, 1.3, 2.0, 0.0, 0.25, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(show==3 || show==4 || show==5)
	{
		glPushMatrix();
		glTranslated(0.4, 0.38, 0.45);
		glRotated(30, 0, 1, 0);
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		glutWireTeapot(0.10);
		glPopMatrix();
	}
	if(show==3 || show==4){
		glPushMatrix();
		glTranslated(0.4, 0, 0.4);
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		table(0.6, 0.02, 0.02, 0.3);
		glPopMatrix();
	}
	if(show==2 || show==4){
		wall(0.02);
		glPushMatrix();
		glRotated(90, 0, 0, 1.0);
		wall(0.02);
		glPopMatrix();
		glPushMatrix();
		glRotated(-90, 1.0, 0, 0.0);
		wall(0.02);
		glPopMatrix();
	}
	glFlush();
}

void rotate(){
	theta[axis]+=0.1;
	if(theta[axis]>360.0) theta[axis]-=360.0;
	
	displaySolid();

}
void mouse(int btn, int state, int x, int y){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) axis=0;
	//if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) axis=1;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) axis=2;
}

void myMenu(int opt){
	if(opt==1){
		show=1;	
	}else if(opt==2){
		show=2;
	}else if(opt==3){
		show=3;
	}else if(opt==4){
		show=4;
	}else if(opt==5){
		show=5;
	}
	else if(opt==6){
		theta[0]=0.0;
		theta[1]=0.0;
		theta[2]=0.0;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple Shaded scene");
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glutMouseFunc(mouse);
	glutIdleFunc(rotate);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Clear screen", 1);
	glutAddMenuEntry("Show only walls", 2);
	glutAddMenuEntry("Show only table", 3);
	glutAddMenuEntry("Show everything", 4);
	glutAddMenuEntry("Show only teapot", 5);
	glutAddMenuEntry("Reset", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glClearColor(0, 0, 0, 1.0);
	glViewport(0.0, 0.0, 640, 480);
	glutMainLoop();
}






