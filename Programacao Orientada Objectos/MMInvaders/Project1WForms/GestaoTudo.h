#pragma once
//#include "Lista.h"
#include <list>
#include <iostream>
using namespace std;
#include "Jogador.h"
#include "Inimigo.h"
#include "Tiro.h"
#include "Defines.h"
#include "NivelClass.h"
#include "Utilizador.h"
#include <fstream>
#include <sstream>
#include <string>

class GestaoTudo
{
	
	list<Utilizador *> *list_utilizador; //lista de utilizadores no jogo
	list<Tiro *> *list_Tiro; //lista de tiros no ecra
	Jogador mariana; //objecto jogador
	int NUtilizadores, //quantos utilizadores estao registados
	IDUtilizadorActual,//qual é o id do utilizador que esta a jogar actualmente
	nivelActual, //em que nivel se esta
	NTiros, // disparados
	TirosNoEcra, //tiros no ecra
	EstadoDoJogo;//em que estado o jogo esta actualmente (menu, pausa, a correr)
	NivelClass *NivelObj;//o nivel actual, é alocado sempre que se inicializa um novo nivel

	//um nivelzinho é uma estrutura onde é guardado que inimigos sao usados num nivel
	list<Nivelzinho *> *list_Niveis;//list com ponteiros da estrutura Nivelzinho, cada ponteiro é um nivel;
	int NTotalNiveis;
		
public:
	GestaoTudo(void);
	~GestaoTudo(void);

	//Utilizador ----------------------
	void CriarContaUtilizador(string user, string pass, int pontos=0);//Cria uma conta de utilizador e coloca na lista
	void DestruirUtilizadores();//apagar a lista de utilizadores libertando a memoria
	bool ProcurarUtilizador(string user, string pass);//verifica se o utilizador e o login correspondem e define a variavel IDUtilizadoractual
	void setJogadorID(int id);//altera a variavel IDUtilizadorActual
	int GetJogadorID(); //obter o id do jogador actual
	string GetUserName();//retorna o nome do jogador actual
	void LeUtilizadoresFicheiro();//carrega do ficheiro os utilizadores criados
	void EscreveUtilizadoresFicheiro();//escreve o ficheiro com os utilizadores actualmente em memoria
	int GetHScore();//retorna a pontuacao maxima do utilizador actual
	void SetHScore(int pontos);//altera o HScore do utilizador actual
	bool ExisteUtilizador(string user); // verifica se o utilizador ja existe
	Utilizador* CriaListaOrdenada(int &nUser);//cria um array de utilizadores ordenados por pontucao para mostrar na tabela

	//Jogador ----------------------
	void GetPosJogador(int &x, int &y);//obter a posicao do jogador
	void MexerJogador(int direccao);//mexer o jogador para a esq se for negativo, direita se for positivo
	int GetVidas(); //obter as vidas do jogador
	int GetPoints(); //obter os pontos do jogador
	void AddPointsJogador(int _val);//adiciona pontos à pontucao
	void RetiraVidaJogador(int _val);//retira uma vida ao jogador
	void ResetJogador();	//reinicia ao estado inicial o jogador

	//inimigo ----------------------
	bool VerificarColisoes(int _idBala); //compara uma bala com os inimigos, se colidir, retorna true, para apagar essa bala
	void CriarInimigo(int _tipo); //criar um inimigo novo
	bool RetirarVidaInimigo(Inimigo* _inimigo, int _dano);//retira vida ao inimigo
	int GetVidaInimigo(int _id);//obter a vida do inimigo
	void GetPosInimigo(int _idInimigo, int &x, int &y); //obter a pos do inimigo e colocar por referencia
	int GetTipoInimigo(int _idInimigo);//de que tipo o inimigo é
	int getDecayInimigo(int _idInimigo);//quanto tempo falta para desaparecer o sinal de morto do inimigo
	void ReduzDecayInimigo(int _idInimigo);//decrementa o decay
	Inimigo* ProcuraInimigo(int _id); //procurar um inimogo por id
	int GetIDUltInimigo(); // id do ultimo inimig, tambem serve como quantidade de inimigos NOTA REINICIAR CONTAGEM AO FIM DE CADA NIVEL
	void GetSizeInimigo(int &_sizeW ,int &_sizeH); //tamanho do boss
	int GetInimigosVivos();// Quantos inimigos ainda estao vivos no jogo
	int getEstadoBoca();// estado da boca do boss
	void controlaBoca(int _EstadoBoca); //abre ou fecha a boca do boss
	void DeslocaInimigos();//desloca os inimigos todos

	//Tiro ---------------------
	int CriarTiro(int _TipoTiro); //cria um tiro e coloca na lista
	void DestruirTiros();//apagar a lista de tiros
	void RemoverTiro(int _idTiro); //remove um tiro da lista
	void DeslocarTiro(int _idTiro); //desloca o tiro
	void GetPosTiro(int _idTiro,int &x, int &y); // obter a posicao do tiro
	int GetTipoTiro(int _idTiro); //obter o tipo do tiro, se vem do jogador ou do inimigo
	Tiro *ProcuraTiro(int _idTiro);//procura um tiro na lista e retorna-o
	void ClearListTiros();//reinicia variaveis relacionadas com os tiros e apaga a lista

	//Nivel -------------------------
	void LerFicheiroNiveis(); //ler os niveis de um ficheiro;
	void PrepararNivel(int _nivel); //Cria varios inimigos; Prepara o nivel
	int GetNivel(); //obter o nivel actual
	int JogoACorrer(); //obter o estado da simulacao
	bool VerificarFimNivel();//verifica se ainda ha algum inimigo, se nao houver passa para o proximo nivel
	Nivelzinho *GetNivelzinho(int NumNivel);//retorna um nivelzinho da lista de niveis
	int GetTotalNiveis();//quantos niveis estao disponiveis
	void DestruirNivelzinho();//apagar a lista de nivelzinhos libertando a memoria
};

