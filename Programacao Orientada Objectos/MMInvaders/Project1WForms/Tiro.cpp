#include "Tiro.h"


Tiro::Tiro(int _id, int _posX, int _posY, int _tipo)
{
	id = _id;
	posX = _posX;
	posY = _posY;
	tipo = _tipo;
}
void Tiro::GetPos(int &_X, int &_Y){
	_X = posX;
	_Y = posY;
}

Tiro::~Tiro(void)
{
}

void Tiro::DeslocaX(int _val)
{
	posX -= _val;
}

void Tiro::DeslocaY(int _val)
{
	posY -= _val;
}
int Tiro::GetTipo(){
	return tipo;
}
