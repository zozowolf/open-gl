/********************************************************/
/* didac01.cpp										    */
/********************************************************/
/* Premiers pas avec OpenGL. */
/* Objectif : afficher a l'ecran un triangle en couleur */
/* On peut bouger le triangle, afficher uniquement les  */
/* sommets ou les côtés									*/
/********************************************************/

// inclusion des fichiers d'en-tete Glut 

#include "GL/freeglut.h"
#include <stdio.h>

void affichage();
void clavier(unsigned char touche, int x, int y);

float rx = 0, ry = 0, rz = 0; // Rotations intiales = 0


/***********************************************************
   Fonction principale
***********************************************************/
int main(int argc, char** argv)
{
	// initialisation de glut et creation de la fenetre 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Un beau triangle");


	// Couleur de fond : noir
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(5.0);

	// enregistrement de la fonction d'affichage
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);

	// Entree dans la boucle principale glut 
	glutMainLoop();

	return 0;
}


/***********************************************************
   Fonction d'affichage
***********************************************************/
void affichage()
{
	// effacement de l'image avec la couleur de fond 
	glClear(GL_COLOR_BUFFER_BIT);


	glLoadIdentity();
	glRotatef(rx, 1, 0, 0); // rotation selon x
	glRotatef(ry, 0, 1, 0); // rotation selon y 
	glRotatef(rz, 0, 0, 1);  // rotation selon z 

	//-------- Dessin du polygone --------------
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, 0.5);
	glEnd();

	// on force l'affichage du resultat 
	glFlush();
}

/*********   Fonction de gestion du clavier ***********************/
void clavier(unsigned char touche, int x, int y)
{
	switch (touche)
	{
	case 'p': // affichage du carre plein 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;

	case 'f': /* affichage en mode fil de fer */
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;

	case 's': /* Affichage en mode sommets seuls */
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;

	case '4':
		rx++;
		glutPostRedisplay();
		break;

	case '5':
		ry++;
		glutPostRedisplay();
		break;

	case '6':
		rz++;
		glutPostRedisplay();
		break;


	case 'q': /*la touche 'q' permet de quitter le programme */
		exit(0);
	}
}


