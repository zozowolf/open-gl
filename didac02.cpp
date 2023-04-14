/********************************************************
 * didac02.cpp
 *
 * Theiere                              
 ********************************************************
 *  Objectif : Application des transformations de visualisation
 ********************************************************/
/* inclusion des fichiers d'en-tete Glut */

#include "GL/freeglut.h"
#include <math.h>

void display();
void mousePress(int bouton,int state,int x,int y);
void MouseMotion(int x,int y);


#define abx(x) ((x)>= 0 ? (x):-1*(x))

float xcam=0 , ycam=0 , zcam=10 , Rotation=0 , tx=0 , ty=0;
bool Zoom=false, Tourne=false , Deplace=false;

/***********************************************************************
 Fonction principale
 ***********************************************************************/
int main(int argc,char **argv)
{
	/* initialisation de glut et creation de la fenetre */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(500,500);
	glutCreateWindow("Un petit thé ?");

	/* Initialisation d'OpenGL */
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.6,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glEnable(GL_DEPTH_TEST);

	/* enregistrement des fonctions de rappel */
	glutDisplayFunc(display);
	glutMouseFunc(mousePress);
	glutMotionFunc(MouseMotion);
	
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

	glTranslatef(tx,ty,0);
	glRotatef(Rotation,0,1,0);

	glutSolidTeapot(1.0);

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



