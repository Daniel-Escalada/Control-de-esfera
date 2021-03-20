#include "freeglut.h"

void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
float radio_esfera = 2.0f;
int rojo_esfera = 255;
int verde_esfera = 255;
int azul_esfera = 255;
float x_esfera = 0.0f;
float y_esfera = 0.0f;


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
	gluLookAt(0.0, 10, 20, // posicion del ojo
		0.0, 0, 0.0, // hacia que punto mira (0,0,0) 
		
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		
		//aqui es donde hay que poner el código de dibujo
	glColor3ub(rojo_esfera, verde_esfera, azul_esfera);
	glTranslatef(x_esfera, y_esfera, 0);
	glutSolidSphere(radio_esfera, 20, 20);
	


	//Al final, cambiar el buffer (redibujar)
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void OnTimer(int value)
{
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	if (key == '+' && radio_esfera < 3)
		radio_esfera += 0.5f;
	if (key == '-' && radio_esfera > 1)
		radio_esfera -= 0.5f;
	if (key == 'r')
	{
		rojo_esfera = 255;
		verde_esfera = 0;
		azul_esfera = 0;
	}
	if (key == 'g')
	{
		rojo_esfera = 0;
		verde_esfera = 255;
		azul_esfera = 0;
	}
	if (key == 'b')
	{
		rojo_esfera = 0;
		verde_esfera = 0;
		azul_esfera = 255;
	}
	if (key == 'a')//izq, X negativo
		x_esfera -= 0.1f;
	if (key == 'd')//der, X positivo
		x_esfera += 0.1f;
	if (key == 'w')//arriba, Y positivo
		y_esfera += 0.1f;
	if (key == 's')//abajo, Y negativo
		y_esfera -= 0.1f;
	glutPostRedisplay();
}