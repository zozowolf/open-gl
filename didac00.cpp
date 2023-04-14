/********************************************************/
/* didac00.cpp											*/
/********************************************************/
/* Premiers pas avec OpenGL. */
/* Objectif : afficher a l'ecran un triangle en couleur */
/********************************************************/
/* inclusion des fichiers d'en-tete Glut */

#include "GL/freeglut.h"
#include <stdio.h>

void affichage();


/***********************************************************
   Fonction principale
***********************************************************/
int main(int argc, char** argv)
{
	// initialisation de glut et creation de la fenetre 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(500,500);
	glutCreateWindow("Un beau triangle");


	// Couleur de fond : noir
	glClearColor(0.0,0.0,0.0,0.0);

	// enregistrement de la fonction d'affichage
	glutDisplayFunc(affichage);

	
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

	//-------- Dessin du polygone --------------
	glBegin(GL_POLYGON);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(-0.5,-0.5);
		glColor3f(0.0,1.0,0.0);
		glVertex2f(0.5,-0.5);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(0.5,0.5);
	glEnd();

	// on force l'affichage du resultat 
	glFlush();
}

