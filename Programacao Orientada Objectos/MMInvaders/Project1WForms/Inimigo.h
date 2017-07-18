#pragma once
#include "Defines.h"
#include <iostream>

class Inimigo
{
	int tipo; //de que tipo é, por ex: inimigo de nivel 1 
	int vida; //quanta vida tem
	int id;     //id do inimigo
	int posX;	//Localizacao
	int posY;
	int Decay; //vai removendo se um inimigo tiver morrido, quando for 0, esconde-se a PB do inimigo;
public:
	Inimigo(int _tipo, int _id, int _x,int _y);
	~Inimigo(void);

	int getTipo();//retorna o tipo de inimigo
	int getId();//retorna o id de inimigo
	int getVida();//retorna a vida do inimigo
	void getPos(int &_x,int &_y);//retorna a posicao do inimigo
	void Desloca(int &_x,int &_y);//desloca um inimigo
	int getDecay();
	void ReduzDecay();//decrementa o decay
	virtual bool RetiraVida(int _dano); //se ficar a 0 a vida, retorna true
	virtual void getSize(int &_w,int &_h){ return; }//retorna o tamanho 
	virtual int getEstadoBoca(){ return 0; }//retorna o estado da boca 
	virtual void controlaBoca(int _EstadoBoca){ return; }//controla a abertura da boca do boss
};

