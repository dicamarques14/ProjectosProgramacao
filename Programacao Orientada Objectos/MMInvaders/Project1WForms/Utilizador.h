#pragma once
#include <list>
#include <iostream>
using namespace std;
class Utilizador
{
	int PontMax; //Pontuacao maxima que o jogador atingiu
	string User, pass;
	int ID;
public:
	Utilizador(void);
	Utilizador(string userconta, string passconta, int _ID, int pontos);
	~Utilizador(void);
	string Getname(){return User;};//retorna o nome do utilizador
	string Getpass(){return pass;};//retorna a password do utilizador
	int GetID(){return ID;} //retorna o id do o utilizador
	int GetHScore(){ return PontMax; } //retorna a pontuacao maxima do jogador
	void SetHScore(int pontos){ PontMax = pontos; }// altera a pontuacao maxima do jogador

	void EscreveFicheiro(ofstream &f);//escreve as infos do utilizador no ficheiro
};