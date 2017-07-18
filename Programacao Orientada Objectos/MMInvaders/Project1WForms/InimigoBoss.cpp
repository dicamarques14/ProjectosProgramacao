#include "InimigoBoss.h"


InimigoBoss::InimigoBoss(int _tipo, int _id, int _x,int _y)
	:Inimigo( _tipo,  _id,  _x, _y)
{
	TamanhoH = BossSizeInit_H;
	TamanhoW = BossSizeInit_W;
	EstadoBoca = Fechada;
	
}

InimigoBoss::~InimigoBoss(void)
{

}

bool InimigoBoss::RetiraVida(int _dano){
	//se estiver com a boca aberta, pode sofrer dano, isto e aumenta em tamanho
	if(EstadoBoca){
		TamanhoH += BossGrowPTiro;
		TamanhoW += BossGrowPTiro;
	}
	
	//se ja atingir o limite de tamanho, morre
	if(TamanhoH > BossSizeFinal_H || TamanhoW > BossSizeFinal_W){
		return true;
	}

	return false; 

}

int InimigoBoss::getEstadoBoca(){
	return EstadoBoca;
}

void InimigoBoss::controlaBoca(int _EstadoBoca){
	EstadoBoca = _EstadoBoca;
}

void InimigoBoss::getSize(int &_w,int &_h){ //tamanho actual
	_h = TamanhoH;
	_w = TamanhoW;
}