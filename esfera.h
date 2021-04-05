#pragma once
class Esfera
{
public:
	float radio;
	float x;
	float y;
	float z;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;

	//Modificar color esfera
	void setColor(unsigned char r, unsigned char v, unsigned char a);
	
};