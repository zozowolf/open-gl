/********************************************************
 * didac03.cpp
 *
 * Theiere                              
 ********************************************************
 *  Objectif : Eclairage
 ********************************************************/
/* inclusion des fichiers d'en-tete Glut */

#include "GL/freeglut.h"
#include <stdio.h>
#include <math.h>

void display();
void mousePress(int bouton,int state,int x,int y);
void MouseMotion(int x,int y);
void clavier(unsigned char touche,int x,int y);


#define abx(x) ((x)>= 0 ? (x):-1*(x))

float xcam=0 , ycam=0 , zcam=10 , Rotation=0 , tx=0 , ty=0;
bool Zoom=false, Tourne=false , Deplace=false;


GLfloat L0pos[]={10,10,20.0};
GLfloat L0dif[]={ 0.3,0.3,0.8};
GLfloat L1pos[]={ -10,-10,20.0};
GLfloat L1dif[]={ 0.5,0.5,0.5};
GLfloat Mspec[]={0.5,0.5,0.5};
GLfloat Mshiny=50;


/***********************************************************************
 Fonction principale
 ***********************************************************************/
int main(int argc,char **argv)
{
	/* initialisation de glut et creation de la fenetre */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(500,500);
	glutCreateWindow("Un petit thé ? : Quelle idée lumineuse !");

	/* Initialisation d'OpenGL */
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.6,0.0);
//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glEnable(GL_DEPTH_TEST);


	/* Paramétrage des lumières */
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,L0dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR,L0dif);
	//glLightfv(GL_LIGHT1,GL_DIFFUSE,L1dif);
	glLightfv(GL_LIGHT1,GL_SPECULAR,L1dif);

	// Paramétrage du matériau 
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Mspec);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Mshiny);



	/* enregistrement des fonctions de rappel */
	glutDisplayFunc(display);
	glutMouseFunc(mousePress);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(clavier);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50,1,1,500);
	
	glMatrixMode(GL_MODELVIEW);

	/* Entre dans la boucle principale glut */
	glutMainLoop();

return 0;
}


/***********************************************************************
 Affichage
 ***********************************************************************/
void display()
{
	/* effacement de l'image avec la couleur de fond */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	gluLookAt(xcam,ycam,zcam,0,0,0,0,1,0);

	glLightfv(GL_LIGHT0,GL_POSITION,L0pos);
	glLightfv(GL_LIGHT1,GL_POSITION,L1pos);

	glTranslatef(tx,ty,0);
	glRotatef(Rotation,0,1,0);


	glutSolidTeapot(1.0);

	glTranslatef(5, 2, 0);
	glutSolidTeapot(0.5);

	glutSwapBuffers();
}



/***********************************************************************
  Gestion de l'appui sur une touche de la souris
 ***********************************************************************/
void mousePress(int bouton,int state,int x,int y)
{
	Zoom=false;
	Tourne=false;
	Deplace=false;

	if (state == GLUT_DOWN && bouton==GLUT_MIDDLE_BUTTON)
			Zoom=true;
	if (state == GLUT_DOWN && bouton==GLUT_LEFT_BUTTON)
		Tourne=true;

	if (state == GLUT_DOWN && bouton==GLUT_RIGHT_BUTTON)
		Deplace=true;
	
}

/***********************************************************************
 Gestion des déplacements de la souris
 ***********************************************************************/
void MouseMotion(int x,int y)
{
	static int oldy=0 , oldx=0;

	if (Zoom)
	{
		if (y>oldy)	zcam++;
		else if (y<oldy) zcam--;
	
	}

	else
	{
		if (Tourne) 
		{
			if (x>oldx)	Rotation++;
			else if (x<oldx) Rotation --;
		}

		if (Deplace)
		{
			if (abs(x-oldx)>abs(y-oldy))
			{
				if (x>oldx) tx+=0.2; else tx-=0.2;
			}
			else
			{
				if (y>oldy) ty-=0.2; else ty+=0.2;
			}
		}

	}


	oldy=y;
	oldx=x;
	glutPostRedisplay();
}

/***********************************************************************
 Gestion du clavier
 ***********************************************************************/
void clavier(unsigned char touche,int x,int y)
{
	switch (touche)
	{
	case 'w' : /* Lampe 0 on */
		glEnable(GL_LIGHT0);
		break;

	case 'x' : /* Lampe 0 off */
		glDisable(GL_LIGHT0);
		break;

	case 'c': /* lampe 1 on */
		glEnable(GL_LIGHT1);
		break;

	case 'v': /* lampe 1 off */
		glDisable(GL_LIGHT1);
		break;

	case 'm': /* increment reflexion speculaire */
		Mspec[0]+=0.1;
		if (Mspec[0]>1) Mspec[0]=1;
		Mspec[1]+=0.1;
		if (Mspec[1]>1) Mspec[1]=1;
		Mspec[2]+=0.1;
		if (Mspec[2]>1) Mspec[2]=1;
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Mspec);
		break;

	case 'l': /* decrement reflexion speculaire */
		Mspec[0]-=0.1;
		if (Mspec[0]<0) Mspec[0]=0;
		Mspec[1]-=0.1;
		if (Mspec[1]<0) Mspec[1]=0;
		Mspec[2]-=0.1;
		if (Mspec[2]<0) Mspec[2]=0;
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Mspec);
		break;

	case 'j': /* increment de la brillance */
		Mshiny-=1;
		if (Mshiny<0) Mshiny=0;
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Mshiny);
		break;

	case 'k': /* decrement de la brillance */
		Mshiny+=1;
		if (Mshiny>128) Mshiny=128;
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Mshiny);
		break;
	
	case 'q' : exit(0);
	}

	glutPostRedisplay();
}


