#pragma once
#include "Inimigo.h"
class InimigoBoss :
	public Inimigo
{
	int TamanhoH;//o tamanho do boss
	int TamanhoW; 
	int EstadoBoca; //se esta aberta ou nao a boca

public:
	InimigoBoss(int _tipo, int _id, int _x,int _y);
	~InimigoBoss(void);
	bool RetiraVida(int _dano); //vai fazer o inimigo crescer
	int getEstadoBoca(); //retorna se a boca esta aberta ou nao
	void controlaBoca(int _EstadoBoca); //controla a abertura da boca
	void getSize(int &_w,int &_h); //tamanho actual do boss
};

