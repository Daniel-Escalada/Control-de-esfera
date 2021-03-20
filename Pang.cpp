#include "freeglut.h"
#include <math.h>
#include <stdio.h>

struct Esfera
{
	float radio;
	float x;
	float y;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
};
Esfera esfera = { 1,0,0,255,255,255 };
Esfera esfera2 = { 1,3,0,0,255,255 };

struct Mundo
{
	double x_ojo;
	float y_ojo;
	double z_ojo; 
	float x_obs;
	float y_obs; 
	float z_obs;
	float x_eje;
	float y_eje;
	float z_eje;

};
Mundo Mundo1 = { 0.0, 0, 20, 0.0, 0, 0.0, 0.0, 1.0, 0.0 };

void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void Dibuja(Esfera e);
void Mueve(Esfera* e);void Color(Esfera* e);

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas FREEGLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");
	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);//25 ms
	glutKeyboardFunc(OnKeyboardDown);
	//pasarle el control a FREEGLUT,que llamara a los callbacks
	glutMainLoop();
	return 0;
}
void OnDraw(void)
{
	//Borrado de la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Mundo1.x_ojo,Mundo1.y_ojo,Mundo1.z_ojo,Mundo1.x_obs,Mundo1.y_obs,Mundo1.z_obs,Mundo1.x_eje,Mundo1.y_eje,Mundo1.z_eje);
  Dibuja(esfera);
  Dibuja(esfera2);


	//Al final, cambiar el buffer (redibujar)
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnTimer(int value)
{
	//Movimiento camara
	double d = 40;
	double theta = atan2(Mundo1.z_ojo, Mundo1.x_ojo);
	theta += 0.031415;
	Mundo1.x_ojo = d * cos(theta);
	Mundo1.z_ojo = d * sin(theta);
	
	//poner aqui el código de animacion
	Mueve(&esfera);
	Color(&esfera);
	Mueve(&esfera2);
	Color(&esfera2);
	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	
	if (key == '+' && esfera.radio < 3)
		esfera.radio += 0.5f;
	if (key == '-' && esfera.radio > 1)
		esfera.radio -= 0.5f;
	if (key == 'r')
	{
		esfera.rojo = 255;
		esfera.verde = 0;
		esfera.azul = 0;
	}
	if (key == 'g')
	{
		esfera.rojo = 0;
		esfera.verde = 255;
		esfera.azul = 0;
	}
	if (key == 'b')
	{
		esfera.rojo = 0;
		esfera.verde = 0;
		esfera.azul = 255;
	}
	if (key == 'a')//izq, X negativo
		esfera.x -= 0.1f;
	if (key == 'd')//der, X positivo
		esfera.x += 0.1f;
	if (key == 'w')//arriba, Y positivo
		esfera.y += 0.1f;
	if (key == 's')//abajo, Y negativo
		esfera.y -= 0.1f;
	glutPostRedisplay();
}void Dibuja(Esfera e){	glColor3ub(e.rojo, e.verde, e.azul);
	glTranslatef(e.x, e.y, 0);
	glutSolidTeapot(3);
	//Vuelve al punto inicial de dibujo
	glTranslatef(-e.x, -e.y, 0);}void Mueve(Esfera* e)
{
	e->radio += 0.1f;
	if (e->radio > 3)
		e->radio = 0.5f;
}void Color(Esfera* e){	e->rojo += 255;}