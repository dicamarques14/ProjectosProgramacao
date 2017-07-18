#include "Inimigo.h"
using namespace std;
Inimigo::Inimigo(int _tipo, int _id, int _x,int _y)
{
	id = _id;
	
	//A vida de um inimigo é igual ao tipo no inicio do jogo, logo os mais faceis sao de tipo 1, morre com 1 tiro
	vida = tipo = _tipo;

	posX = _x;
	posY = _y;

	Decay = DecayInimigo;
	
}
Inimigo::~Inimigo(void){
	
}

void Inimigo::getPos(int &_x,int &_y){
	_x=posX;
	_y=posY;
}

void Inimigo::Desloca(int &_x,int &_y){
	posX=_x;
	posY=_y;
}

int Inimigo::getDecay(){
	return Decay;
}


void Inimigo::ReduzDecay(){
	Decay--;
}

bool Inimigo::RetiraVida(int _dano){
	vida -=_dano;
	if (vida < 1){
		vida = 0;
		cout << "Inimigo " << id << " morreu" << endl;
		return true; //se ficar a 0 a vida, retorna true
	}
	return false;
}

int Inimigo::getVida(){
	return vida;
};

int Inimigo::getTipo(){
	return tipo;
};

int Inimigo::getId(){
	return id;
};