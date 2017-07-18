#include "Jogador.h"
using namespace std;

Jogador::Jogador(void)
{
	vidas = JogadorVidasIni;
	pontos = 0;
	//Posicao Inicial

}

Jogador::~Jogador(){

}

void Jogador::Mexer(int direccao)
{
	/*
	copia a posicao actual do jogador para uma var aux, depois verificamos se da para mover.
	Por fim verificamos se o jogador fica dentro dos limites e guardamos a nova pos
	*/
	int x = posX;
	x += JogadorVeloc * direccao;

	if(x >= 0 && x <= JogoSize_W-JogadorSize_W)
		posX = x;
	
}

void Jogador::GetPos(int &x, int &y)
{
	// retorna a posicao actual do jogador por parametro

	x = posX;
	y = posY;
}

void Jogador::AddPoints(int _val){
	pontos += _val;
}

void Jogador::RetiraVida(int _val){
	vidas -= _val;
	cout << "Nao acertem na Mariana!!" << endl;
}
void Jogador::Reset(){
	vidas = JogadorVidasIni;
	pontos = 0;
	
	posX = JogoSize_W/2;
	posY = JogoSize_H - JogadorSize_H ;
}

