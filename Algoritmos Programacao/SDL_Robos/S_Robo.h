#ifndef S_ROBO_H_INC
#define	S_ROBO_H_INC

#define SUJO '0'  //caracter que simboliza sujo
#define OBSTACULO 'X' //caracter que simboliza obstaculo
#define CHARExtra '*' //caracter que simboliza mais de 9 passagens
#define CHARRobo 'R' //caracter que simboliza um Robo
#define MAXCOORD 15  //limite das coordenadas X ou Y
#define MAXROBOS 7 // limite de robos


#define BATInicial 1000 //a quanto a bateria dos robos deve comecar
#define PAUSAINICIAL 1000 //valor inicial de pausa entre movimentos

typedef struct //Edados que vai guardar a informacao individual de cada robo
{
	char id[3], Temporario;	//ID do robo, so precisa de 3 chars, 2 "letras" + '\0'; temporario-> guarda o valor da quadricula onde esta o robo para mais tarde repor o valor dessa quadricula
	int percurso[502];			//Array de Integer que regista por que casas passou
	int xAct, yAct, xObj, yObj, bateria, nMovimentos, nLimpezas;	//	X/Y actual, X/Y destino, Bateria do robo, Numero de Movimentos que o robo fez, Numero de Limpezas que o robo fez
	bool activo;				//Se o robo esta pronto ou nao para usar

}Robo;

typedef struct  //Edados para gerir um array de Robos e que guarda quantos robos foram criados
{
	int QtdRobo;	//Quantos robos existem
	Robo *R;		//Array do tipo Robo

}ImperioRobo;

typedef struct  //EDados que vai guardar as dimensoes da "divisao",
{
	int nX, nY, nSujos;  //nX é o numero de colunas e nY é o numero de linhas, nSujos é o numero de quadriculas com 0 (sujo)
	char *Dados; //Array de chars para guardar a informacao de cada quadricula

}Matriz;

typedef struct rb_s
{
	ImperioRobo *Imperio;
	Matriz *M;
}Robo_Struct;

void main_Robo(Robo_Struct* RoboData);

Robo_Struct* initRobo();

int Simulacao(ImperioRobo *Imperio, Matriz *M);

#endif // !S_ROBO_H_INC
