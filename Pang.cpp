#include "freeglut.h"
#include <math.h>
#include <stdio.h>

struct Esfera
{
	float radio;
	float x;
	float y;
	float z;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
};
Esfera esfera = { 1,20,0,0,255,0,0};
Esfera esfera2 = { 1,3,0,0,255,255 };
float r=1.5;

struct Mundo
{
	double x_ojo;
	double y_ojo;
	double z_ojo; 
	float x_obs;
	float y_obs; 
	float z_obs;
	float x_eje;
	float y_eje;
	float z_eje;

};
Mundo Mundo1 = { 50, 0, 0, 0.0, 0, 0.0, 0.0, 0.0, 1.0 };

void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void Dibuja(Esfera e);
void Mueve(Esfera* e);void Color(Esfera* e);void Obstaculos(float* e);

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
	//Toroides exteriores
	glColor3ub(0, 255, 255);
	glTranslatef(0, 0, 7);
	glutSolidTorus(1, 20, 50, 50);
	glTranslatef(0, 0, -14);
	glutSolidTorus(1, 20, 50, 50);
	glTranslatef(0, 0, 7);
	//Cubos
	glColor3ub(255, 0, 255);
	glTranslatef(0, 20, 4.5);
	glutSolidSphere(r, 50, 50);	glTranslatef(14.14, -5.86, -6.75);
	glutSolidSphere(r, 50, 50);
	glTranslatef(5.86, -14.14, 2.25);
	glutSolidSphere(r, 50, 50);
	//Doble
	glTranslatef(-5.86, -14.14, 3.25);
	glutSolidSphere(r, 50, 50);
	glTranslatef(0, 0, -6.5);
	glutSolidSphere(r, 50, 50);
	glTranslatef(-14.14, -5.86, 3.25);
	glutSolidSphere(r, 50, 50);
	glTranslatef(-14.14, 5.86, -4.5);
	glutSolidSphere(r, 50, 50);
	glTranslatef(-5.86, 14.14, 6.5);
	glutSolidSphere(r, 50, 50);
	//Triple
	glTranslatef(5.86, 14.14, 2.5);
	glutSolidSphere(r, 50, 50);
	glTranslatef(0, 0, -9);
	glutSolidSphere(r, 50, 50);
	glTranslatef(0, 0, 4.5);
	glutSolidSphere(r, 50, 50);

	glTranslatef(14.14, -14.14, 0);
	

	Dibuja(esfera);
   
	printf("%d\n",esfera.rojo);

	//Al final, cambiar el buffer (redibujar)
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnTimer(int value)
{
	//Movimiento camara
	double d = 50;
	double theta = atan2(Mundo1.y_ojo, Mundo1.x_ojo);
	theta += 0.0091415;
	Mundo1.x_ojo = d * cos(theta);
	Mundo1.y_ojo = d * sin(theta);
	
	//poner aqui el código de animacion
	Obstaculos(&r);

	

	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	
	if (key == '+' && esfera.radio < 3)
		esfera.radio += 0.1;
	if (key == '-' && esfera.radio > 0.3)
		esfera.radio -= 0.1;
	
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
	/*
	if (key == 'a')//izq, X negativo
		esfera.x -= 1;
	if (key == 'd')//der, X positivo
		esfera.x += 1;
	if (key == 'w')//arriba, Y positivo
		esfera.y += 1;
	if (key == 's')//abajo, Y negativo
		esfera.y -= 1;
		*/
	if (key == 'j')//arriba, z positivo
		esfera.z += 0.5;
	if (key == 'm')//abajo, z negativo
		esfera.z -= 0.5;
	
	//glutPostRedisplay();
}void Dibuja(Esfera e){	glColor3ub(e.rojo, e.verde, e.azul);
	//Angulos esfera
	
	double d = 20;
	double theta = atan2(esfera.y, esfera.x);
	theta += 0.0091415;
	esfera.x = d * cos(theta);
	esfera.y = d * sin(theta);
	
	glTranslatef(esfera.x, esfera.y, esfera.z);
	glutSolidSphere(esfera.radio,50,50);
	//Vuelve al punto inicial de dibujo
	glTranslatef(-esfera.x, -esfera.y, -esfera.z);	}void Mueve(Esfera* e)
{
	e->radio += 0.1f;
	if (e->radio > 3)
		e->radio = 0.5f;
}void Color(Esfera* e){	unsigned int choice1 = rand();	unsigned int choice2 = rand();	unsigned int choice3 = rand();	e->rojo = choice1;	e->verde = choice2;	e->azul = choice3;}void Obstaculos(float* e){	*e += 0.02;
	if (*e > 1.5) 		*e = 0.5;}