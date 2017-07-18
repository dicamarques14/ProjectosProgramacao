#pragma once
#include <list>
#include <iostream>
using namespace std;
#include "Inimigo.h"
#include "InimigoBoss.h"
#include "Jogador.h"
class NivelClass
{
	list<Inimigo *> *list_Inimigo;
	int id_inimigos; // id do ultimo inimig, tambem serve como quantidade de inimigos NOTA REINICIARCONTAGEM AO FIM DE CADA NIVEL
	int inimigosVivos; //quantos inimigos estao vivos
	int nivelActual; //o numero do nivel
	int DireccaoInimigo; //se for 1 vao para a direita se for -1 vao para a esquerda
	int NTotalNiveis; //n total de niveis existentes no jogo 
public:
	NivelClass(int _nivelActual,Nivelzinho* Nivel,int _NTotalNiveis);
	~NivelClass(void);

	void DestruirInimigos();//limpa a lista dos inimigos
	int GetVidaInimigo(int _id); //retorna a vida de um inimigo
	Inimigo* ProcuraInimigo(int _id); //procurar um inimogo por id
	void RemoverInimigo(int _id); //apagar inimigo da lista
	void CriarBoss();//cria um inimigo do tipo boss
	int GetIDUltInimigo();//retorna o id do ultimo inimigo criado
	void CriarInimigo(int _tipo);//cria um inimigo com o tipo pedido 
	void GetPosInimigo(int _idInimigo, int &x, int &y);//obter a posicao do inimigo
	int GetTipoInimigo(int _idInimigo);//obter o tipo do inimigo
	int getDecayInimigo(int _idInimigo);//retorna quanto tempo falta para o inimigo desaparecer depois de morto
	void ReduzDecayInimigo(int _idInimigo);
	bool VerificarColisoes(int tiroLeft,int tiroTop,int tiroRight,int tiroBottom, int tipo, Jogador *mariana);
	bool RetirarVidaInimigo(Inimigo* _inimigo, int _dano);//retira vida a um inimigo e retorna true caso fique sem vida
	int GetInimigosVivos(); //quantos inimigos ainda estao vivos
	void DeslocaInimigos(); // desloca os inimigos
	void GetInimigoRandom(int &x, int &y);// Escolhe um inimigo aleatoriamente, retorna a pos dele, para o fazer disparar

	void GetSizeInimigo(int &_sizeW ,int &_sizeH); //tamanho do boss
	int getEstadoBoca(); //retorna se a boca esta aberta ou nao
	void controlaBoca(int _EstadoBoca); //controla a abertura da boca

};

