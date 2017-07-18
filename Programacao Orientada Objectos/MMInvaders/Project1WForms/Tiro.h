#pragma once
class Tiro
{
	int posX;//coord x
	int posY;//coord y
	int id;//id do tiro 
	int tipo; //origem do tiro 0->jogador, 1->inimigo
public:
	Tiro(int _id, int _posX, int _posY, int _tipo);
	void DeslocaX(int _val); // val a subtrair
	void DeslocaY(int _val); // val a subtrair
	int GetID(){ return id; }//retorna o ID da bala
	void GetPos(int &_X, int &_Y);//retorna a posicao da bala
	int GetTipo();//retorna o tipo do tiro, se vem do jogador ou utilizador
	~Tiro(void);
};

