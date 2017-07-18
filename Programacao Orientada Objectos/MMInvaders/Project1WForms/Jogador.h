#pragma once
#include "Defines.h"
#include <iostream>

using namespace std;
class Jogador
{
	int vidas;//quantas vidas ainda tem
	int pontos;//quantos pontos fez nesta partida 
	int posX;//coord x
	int posY;//coord y

public:
	Jogador(void);
	~Jogador();
	void Mexer(int direccao);//desloca o jogador na para a direita se positivo e para esquerda se negativo
	void GetPos(int &x, int &y);//obter posicao do jogador
	int GetPoints(){return pontos;}//retorna a pontuacao
	int GetVidas(){return vidas;}//retorna o numero de vidas
	void AddPoints(int _val);//adiciona pontos
	void RetiraVida(int _val);//retira vidas
	void Reset();//coloca o jogador com os valores de origem
};

