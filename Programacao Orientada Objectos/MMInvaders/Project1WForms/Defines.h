#pragma once

#define MAXInimigoPNivel 24 // quantos inimigos no maximo no ecra
typedef struct nivelzinho{
	int Array_Inimigos[MAXInimigoPNivel];
}Nivelzinho;

#define InimigoSize_W 50 //tamanho da imagem do inimigo
#define InimigoSize_H 50 

#define InimigoPLinha 8 //quantos inimigos numa linha
#define InimigoDesloca 5 //quantos pixeis os inimigos deslocam
#define DecayInimigo 70 //quanto tempo o inimigo fica no ecra depois de morrer
#define BossID 8 //o numero do boss na lista de inimigos no nivel
#define RatioDificuldade 2 //quanto maior, mais dificil se torna o jogo
//#define NumNiveis 5//quantos niveis disponiveis


#define TiroSize_W 22 //tamanho da imagem do Tiro
#define TiroSize_H 22
#define TiroVeloc 20 //Velocidade de deslocamento do tiro
#define LimiteTiros 6 //limite de tiros no ecra

#define JogadorSize_W 55
#define JogadorSize_H 75 //tamanho da imagem do Jogador
#define JogadorVeloc 10 //velocidade de movimento do jogador
#define JogadorVidasIni 3

#define JogoSize_W 640
#define JogoSize_H 480 //tamanho da area de jogo

#define MovEsq -1 //para que lado esta a deslocar
#define MovSTOP 0
#define MovDir 1

#define Est_Parado 0//estado da simulacao
#define Est_Correr 1

#define BossSizeInit_W 125 //min
#define BossSizeInit_H 140 //min
#define BossSizeFinal_W 250 //max 
#define BossSizeFinal_H 280 //max 
#define BossGrowPTiro 5 //quanto cresce por tiro
#define BossBoca_W 91 
#define BossBoca_H 51
#define BossBoca_X 80
#define BossBoca_Y 230

//80,230 -> 170,230  w=90 h=50
#define Aberta 1
#define Fechada 0

#define TimerAbreBoca 500
#define TimerFechaBoca 250
#define TimerMexeInimigo 25
#define TimerActualizaDados 20
#define TimerDispararTiroInimigo 80
#define TimerMudaImagemJogador 3
#define NomeFichUtilizadores "dbusers.csv" //ficheiro dos utilizadores

#define TiroJogador 0 //tiro vem do Jogador
#define TiroInimigo 1 //tiro vem do inimigo