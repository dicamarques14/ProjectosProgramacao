#include "Utilizador.h"
#include <fstream>

Utilizador::Utilizador(void)
{

}

Utilizador::Utilizador(string userconta, string passconta, int _ID, int pontos)
{
	PontMax = pontos;
	User = userconta;
	pass = passconta;
	ID = _ID;
	
}
Utilizador::~Utilizador(void)
{
}

void Utilizador::EscreveFicheiro(ofstream &f){
	f << User.c_str() << "," << pass.c_str() << "," << PontMax <<","<< endl;
}

