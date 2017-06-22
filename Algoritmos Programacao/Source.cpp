/*
==================================================================================
Projecto de Algoritmos e programação - Robo de Limpeza
Realizado por: Dg, D M , R A
Projecto de avaliacao final da UC Algoritmos e Programação 
2 de Janeiro de 2016
==================================================================================
*/

/*
XXXXXXXXXXXXXXXXXXX
Y [X,Y]
Y
Y
Y
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <dos.h>

#define _CRT_SECURE_NO_WARNINGS

#define MAXCOORD 20  //limite das coordenadas X ou Y
#define BATInicial 1000 //a quanto a bateria dos robos deve comecar
#define MAXROBOS 10 // limite de robos
#define PAUSAINICIAL 1000 //valor inicial de pausa entre movimentos
#define SUJO '0'  //caracter que simboliza sujo
#define OBSTACULO 'X' //caracter que simboliza obstaculo
#define CHARExtra '*' //caracter que simboliza mais de 9 passagens
#define CHARRobo 'R' //caracter que simboliza um Robo

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

//----------------------------------------------------
/// Funcao: ReportarErroMsg
/// Descricao: Esta funcao escreve no ecran o erro que aconteceu
/// Parametros: 
///     msg_erro: mensagem do erro 
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//----------------------------------------------------
void ReportarErroMsg(char *msg_erro)
{
	printf("Erro : %s \n", msg_erro);
}
//----------------------------------------------------
/// Funcao: ReportarErro
/// Descricao: Esta funcao escreve no ecran o erro que aconteceu
/// Parametros: 
///     nerro: numero do erro 
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//----------------------------------------------------
void ReportarErro(int nerro)
{
	switch (nerro)
	{
	case 1: ReportarErroMsg("Ficheiro nao existe");
		break;
	case 2: ReportarErroMsg("Formato da linha Ficheiro Incorrrectos");
		break;
	case 3: ReportarErroMsg("Esta opcao Nao Existe");
		break;
	case 4: ReportarErroMsg("Est. de Dados e NULA");
		break;
	case 5: ReportarErroMsg("Não Consegui Escrever no Ficheiro");
		break;
	case 6: ReportarErroMsg("Nao Consegui Alocar a Matriz");
		break;
	case 7: ReportarErroMsg("Matriz e nula");
		break;
	case 8: ReportarErroMsg("Robo e nulo");
		break;
	case 10: ReportarErroMsg("Nao Consegui Criar o Ficheiro");
		break;
		//........
	default:
		ReportarErroMsg("Erro indefinido");
	}
}
//----------------------------------------------------
/// Funcao: ReportarAviso
/// Descricao: Esta funcao escreve no ecran um Aviso
/// Parametros: 
///     naviso: numero do aviso 
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void ReportarAviso(int naviso)
{
	switch (naviso)
	{
	case 1: printf("Chegou ao limite de velocidade MAXIMA\n");
		break;
	case 2: printf("Chegou ao limite de velocidade MINIMA\n");
		break;
	case 3: printf("A Escrever Para o Ficheiro de Estats.\n");
		break;
	case 4: printf("Limite De Robos Atingido\n");
		break;
	case 5: printf("Encontrei Um Obstaculo\n");
		break;
	case 6: printf("Fiquei Sem Bateria, Recarregue Por Favor\n");
		break;
	case 7: printf("A Reiniciar a Simulacao\n");
		break;
	case 8: printf("Cheguei Ao Destino\n");
		break;
	case 9: printf("Robo Inativo\n");
		break;
	case 10: printf("Acabou a Bateria\n");
		break;
	case 11: printf("Matriz Limpa\n");
		break;
	case 12: printf("Escrito com Sucesso Para o Ficheiro de Estats.\n");
		break;

		//........
	default:
		ReportarErroMsg("Aviso indefinido");
	}
}
//----------------------------------------------------
/// Funcao: TeclaPressionada
/// Descricao: Esta funcao retorna True caso seja premida uma tecla
/// Parametros: ---
/// Retorno: Retorna True caso seja premida uma tecla
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
bool TeclaPressionada()
{
	// foi necessario incluir #include <conio.h>
	return kbhit();
}
//----------------------------------------------------
/// Funcao: IsDigit
/// Descricao: Esta funcao verifica se o char é um digito e retorna 1 caso seja um digito
/// Parametros: 
///     c: char a verificar
/// Retorno: retorna 1 se o char for um digito, se nao for retorna 0
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
int IsDigit(char c)
{
	if ((c >= '0') && (c <= '9'))
		return 1;
	else
		return 0;
}
//----------------------------------------------------
/// Funcao: LerString
/// Descricao: Esta funcao escreve no ecran texto, lê a string introduzida e processa-a de forma que nao parta o programa e limita por n chars
/// Parametros: 
///     naviso: numero do aviso 
///		*Texto:	texto a ser escrito no ecran
///		n: limite de chars que a string tem que ter
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void LerString(char *Texto, char s[], int n)
{
	do {
		fflush(stdin);			//Limpar o buffer
		printf("%s", Texto);	//Escreve o texto no ecra

		for (int i = 0; i < n; i++) //enquanto nao for atingido o n de chars 
		{
			s[i] = getchar();	//le o char introduzido no ecra
			if (s[0] == '\n')break; // nao queremos strings vazias, nem que passem para a proxima linha
			if (s[i] == '\n')s[i] = '\0'; // assim que chegar a um \n colocar um fim de string
		}
	} while (s[0] == '\n');  // nao queremos strings vazias, nem que passem para a proxima linha

	s[n] = '\0';
}
//----------------------------------------------------
/// Funcao: LerNumero
/// Descricao: Esta funcao escreve no ecran um texto, lê a string introduzida e processa-a de forma que nao parta o programa, verificando se são digitos ou nao introduzidos
/// Parametros: 
///     *Texto: texto a ser escrito no ecran 
/// Retorno: i, numero introduzido no ecra
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
int LerNumero(char *Texto)
{
	int i;
	char buffer[256];
	
	fflush(stdin);			//Limpar o buffer
	printf("%s", Texto);	//Escreve o texto no ecra
	fgets(buffer, 256, stdin); //le o que é introduzido no ecra
	if (IsDigit(buffer[0]))	//se for um digito
		i = atoi(buffer);	//converter char para integer
	else
		i = 0;
	return i;
}
//----------------------------------------------------
/// Funcao:	wait
/// Descricao: Esta funcao coloca o programa em pausa mlseconds
/// Parametros: 
///     mlseconds: quantos mili segundos colocar o programa em pausa
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void wait(int mlseconds)
{
	clock_t endwait;
	endwait = clock() + mlseconds;
	while (clock() < endwait) {}
}
//----------------------------------------------------
/// Funcao: GetPosicaoVector
/// Descricao: Esta funcao retorna a posicao no vector dando x y e o num de colunas
/// Parametros: 
///     nY: coordenada Y
///     nX: coordenada X
///     numColu: quantas colunas tem a matriz
/// Retorno: posicao no vector
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
int GetPosicaoVector(int nY, int nX, int numColu)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	return nY*numColu + nX;
}
//----------------------------------------------------
/// Funcao: GetIJMatriz
/// Descricao: Esta funcao encontra as coordenadas num matriz dando a posicao no vector e o numero de colunas
/// Parametros: 
///     pos: posicao no vector
///     nY: coordenada Y
///     nX: coordenada X
///     numColu: quantas colunas tem a matriz
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void GetIJMatriz(int pos, int numColu, int *nY, int *nX)
{
	*nY = pos / numColu;
	*nX = pos % numColu;
}
//----------------------------------------------------
/// Funcao: MoveRobot
/// Descricao: Esta funcao desloca o robot segundo uma formula, dando XYactual e XYobjectivo
/// Parametros: 
///     x_old: coordenada X actual
///     y_old: coordenada Y actual
///     x_obj: coordenada X objectivo
///		y_obj: coordenada Y objectivo
///     *xnew: coordenada X para onde vai o robo
///     *ynew: coordenada Y para onde vai o robo
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void MoveRobot(int x_old, int y_old, int x_obj, int y_obj, int *xnew, int *ynew)
{
	double angle;
	// calculate the angle
	angle = atan2((double)(y_obj - y_old), (double)(x_old - x_obj));

	// calculate the new position
	*xnew = floor(x_old - cos(angle) + 0.5);
	*ynew = floor(y_old + sin(angle) + 0.5);
}
//----------------------------------------------------
/// Funcao: ContarSujo
/// Descricao: Esta funcao conta quantas quadriculas ainda estão sujas
/// Parametros: 
///     Matriz: matriz a contar
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void ContarSujo(Matriz *M)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	int k = 0, Tamanho = M->nY*M->nX;
	for (int i = 0; i < Tamanho; i++)
	{
		if (M->Dados[i] == SUJO) k++;  //caso a quadricula estiver suja, incrementar k
	}
	M->nSujos = k;
}
//----------------------------------------------------
/// Funcao: EncheMatriz
/// Descricao: Esta funcao enche a matriz com chars sujo, neste caso 0
/// Parametros: 
///     Matriz: matriz a encher
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void EncheMatriz(Matriz *M)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	int Tamanho = M->nY*M->nX;
	for (int i = 0; i < Tamanho; i++)
	{
		M->Dados[i] = SUJO;
	}
	
}
//----------------------------------------------------
/// Funcao: PrintMatriz
/// Descricao: Esta funcao escreve no ecra uma matriz, separando cada quadricula por ';'
/// Parametros: 
///     Matriz: matriz a mostrar no ecra
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void PrintMatriz(Matriz *M)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	int cont = 0;
	for (int i = 0; i < M->nY; i++)//por cada linha
	{
		for (int j = 0; j < M->nX; j++)//por cada coluna
			printf("%c;", M->Dados[cont++]);//escrever a quadricula mais ';'
		printf("\n");//na ultima coluna passar para outra linha
	}
}
//----------------------------------------------------
/// Funcao: EscreverFile
/// Descricao: Esta funcao escreve no ficheiro Dados.csv para ser lido pelo programa de visualizaçao
/// Parametros: 
///     Matriz: matriz a escrever no ficheiro
/// Retorno: retorna 1 se houver erro, ou 0 se completou com sucesso
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
int EscreverFile(Matriz *M)
{
	if (!M)
	{
		ReportarErro(7);return 1; //se a matriz for nula, reportar erro e sair da funcao
	}
	int erro = 0,cont = 0;
	FILE *f = fopen("Dados.csv", "w"); //criar o ficheiro onde escrever a matriz
	if (f) //se conseguir criar o ficheiro
	{
		fprintf(f, "Autores: Dg; R A ; D M \n");
		fprintf(f, "%d;%d\n", M->nY, M->nX);
		for (int i = 0; i < M->nY; i++)//por cada linha
		{
			for (int j = 0; j < M->nX; j++)//por cada coluna
				fprintf(f, "%c;", M->Dados[cont++]);//escrever a quadricula mais ';'
			fprintf(f, "\n");
		}
		fclose(f);
		erro = 0; // Sem Erro
	}
	else
	{
		ReportarErro(5);// Não gravou, apresenta erro
			//printf("*********************\nERRO DE ESCRITA1!!!!\n*****************************************\n"); 
		erro = 1;
	}
	return erro;
}
//----------------------------------------------------
/// Funcao: EscreverEstatsFile
/// Descricao: Esta funcao escreve num ficheiro as informacoes actuais de cada robo, a matriz actual e a data e hora actual
/// Parametros: 
///     Matriz: matriz a escrever no ficheiro
///     Imperio: lista de robos a escrever no ficheiro
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
int EscreverEstatsFile(Matriz *M, ImperioRobo *Imperio)
{
	if (!M)
	{
		ReportarErro(7);return 1; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!Imperio)
	{
		ReportarErro(4);return 1; //se a EDados for nula, reportar erro e sair da funcao
	}

	int erro = 0, xF, yF;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	ReportarAviso(3);
	//printf("*****************************************\nA Escrever Estats\n*****************************************\n");

	FILE *f = fopen("Estatisticas.txt", "w");
	if (f)
	{
		int cont = 0;
		fprintf(f, "******Estatisticas******\nData: %d/%d/%d Hora: %d:%d:%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(f, "\nMatriz Actual:\n%d;%d\n", M->nY, M->nX);
		for (int i = 0; i < M->nY; i++)//por cada linha
		{
			for (int j = 0; j < M->nX; j++)//por cada coluna
				fprintf(f, "%c;", M->Dados[cont++]);//escrever a quadricula mais ';'
			fprintf(f, "\n");
		}

		ContarSujo(M);
		fprintf(f, "NumSujos: %d\n", M->nSujos);

		fprintf(f, "\n==========Info Robos============\n");
		for (int i = 0; i < Imperio->QtdRobo; i++)
		{
			fprintf(f, "ID do robo: [%s]\n", Imperio->R[i].id);
			fprintf(f, "Limpezas feitas: %d\n", Imperio->R[i].nLimpezas);
			fprintf(f, "XYAct: [%d][%d]\n", Imperio->R[i].xAct + 1, Imperio->R[i].yAct + 1);
			fprintf(f, "XYObj: [%d][%d]\n", Imperio->R[i].xObj + 1, Imperio->R[i].yObj + 1);
			fprintf(f, "Bateria: %d%%\n", Imperio->R[i].bateria);
			fprintf(f, "NumMovimentos: %d\n", Imperio->R[i].nMovimentos);
			fprintf(f, "Activo: %d\n", Imperio->R[i].activo);
			fprintf(f, "Percurso: ");

			for (int k = 0; k <= Imperio->R[i].nMovimentos; k++)
			{
				xF = 0; yF = 0;
				GetIJMatriz(Imperio->R[i].percurso[k], M->nX, &yF, &xF);
				fprintf(f, "[%d][%d];", xF + 1, yF + 1);
			}

			fprintf(f, "\n======================\n");
		}
		fclose(f);
		erro = 0; // Sem Erro
		ReportarAviso(12); //Foi escrito com sucesso
				  //printf("*****************************************\nEscrito!!!\n*****************************************\n");
	}
	else
	{
		ReportarErro(5);
		//printf("*****************************************\nERRO DE ESCRITA!!!!\n*****************************************\n");
		erro = 1; // Não gravou, apresenta erro
	}
	return erro;
}
//----------------------------------------------------
/// Funcao: ObstaculosMatriz
/// Descricao: Esta funcao coloca obstaculos aleatoriamente na matriz
/// Parametros: 
///     Matriz: matriz a alterar 
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void ObstaculosMatriz(Matriz *M)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	int i = 0, j = 0, Tamanho = M->nX * M->nY, obst = Tamanho / 9; //Limitar o numero de obstaculos ao tamnho da matriz
	printf("\nA gerar %d obstaculos: ", obst);

	for (int i = 0; i < obst; i++)
	{
		srand(time(NULL));
		j = rand() % Tamanho;  //gerar um numero aleatorio limitado pelo tamanho da matriz
		printf("%d;", j);
		M->Dados[j] = OBSTACULO; // escrever na posicao um obstaculo na matriz	
		wait(1000); //Esperar 1s caso contrario gera numeros repetidos
	}
	printf("\n");
}
//----------------------------------------------------
/// Funcao: AlocarMatriz
/// Descricao: Esta funcao aloca na memoria, espaco para a matriz de acordo com o tamanho introduzido pelo utilizador, tambem a prepara para ser usado no resto do programa
/// Parametros: 
///     nX: num de colunas que a matriz vai ter 
///     nY: num de linhas que a matriz vai ter
/// Retorno: Retorna a posicao na memoria da matriz
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
Matriz *AlocarMatriz(int nX, int nY)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	Matriz *M;
	M = (Matriz *)malloc(sizeof(Matriz));
	M->nX = nX;
	M->nY = nY;
	M->Dados = (char *)malloc(nX*nY*sizeof(char));
	M->nSujos = 0;
	if ((M->Dados) == NULL)
	{
		//EXECUTAR ERRO
		ReportarErro(6); //nao conseguiu alocar a matriz
		//printf("*****************************************\nERRO DE Alocacao da Matriz!!!!\n*****************************************\n");
		return 0;
	}
	else
	{
		EncheMatriz(M);
		ObstaculosMatriz(M);
		ContarSujo(M);
		return M;
	}
}
//----------------------------------------------------
/// Funcao: GeraPosicao
/// Descricao: Esta funcao gera uma posicao inicial aleatoria para o robo, verificando se pode ou nao colocalo nesse sitio
/// Parametros: 
///     R1: Robo a posicionar
///     Matriz: matriz para verificar se pode ser colocado o robo naquelas coord e o tamanho da matriz 
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void GeraPosicao(Robo *R1, Matriz *M)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!R1)
	{
		ReportarErro(8);return; //se o robo for nulo, reportar erro e sair da funcao
	}

	int i, Tamanho = M->nX * M->nY;
	do
	{
		srand(time(NULL));
		i = rand() % Tamanho; //gerar um numero aleatorio limitado pelo tamanho da matriz
		wait(1000); //Esperar 1s caso contrario gera numeros repetidos
	} while (M->Dados[i] == OBSTACULO || (M->Dados[i] == CHARRobo)); //verificar se é seguro colocar nesse sitio o robo
	
	GetIJMatriz(i, M->nX, &R1->yAct, &R1->xAct); 
}
//----------------------------------------------------
/// Funcao: GeraDestino
/// Descricao: Esta funcao gera uma posicao destino aleatoria para o robo, verificando se pode ou nao colocalo nesse sitio
/// Parametros: 
///     R1: Robo a posicionar
///     Matriz: matriz para verificar se pode definir aquele destino ao robo e o tamanho da matriz 
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void GeraDestino(Robo *R1, Matriz *M)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!R1)
	{
		ReportarErro(8);return; //se o robo for nulo, reportar erro e sair da funcao
	}
	
	int i, Tamanho = M->nX * M->nY;
	do
	{
		srand(time(NULL));
		i = rand() % Tamanho; //gerar um numero aleatorio limitado pelo tamanho da matriz
		GetIJMatriz(i, M->nX, &R1->yObj, &R1->xObj); //obter as coordenadas XY
		wait(1000);//Esperar 1s caso contrario gera numeros repetidos
	} while ((M->Dados[i] == OBSTACULO) || (M->Dados[i] == CHARRobo) || ((R1->xObj == R1->xAct) && (R1->yObj == R1->yAct))); //verificar se é seguro definir esse destino ao robo

}
//----------------------------------------------------
/// Funcao: IniciaRobo
/// Descricao: Esta funcao inicializa o robo com os valores predefinidos, uma posicao e destino inicial aleatoria, o seu ID
/// Parametros: 
///     R1: Robo a inicializar
///     Matriz: matriz associada
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void IniciaRobo(Matriz *M, Robo *R1)
{
	//printf("Funcao < %s >\n", __FUNCTION__);
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!R1)
	{
		ReportarErro(8);return; //se o robo for nulo, reportar erro e sair da funcao
	}

	R1->bateria = BATInicial;
	R1->xObj = 0; R1->yObj = 0;
	R1->xAct = 0; R1->yAct = 0;
	R1->nMovimentos = 0;
	R1->activo = true;
	R1->nLimpezas = 0;

	char nome[3];
	LerString("ID do Robo (2 Char's): ", nome, 2);
	strcpy(R1->id, nome);

	GeraPosicao(R1, M);//Gerar a 1º Posicao
	GeraDestino(R1, M);//Gerar o 1º Destino

	int i = GetPosicaoVector(R1->yAct, R1->xAct, M->nX);
	M->Dados[i]++; //Incrementar a posicao inicial do robo na matriz
	R1->percurso[0] = i; //Regista a posicao inicial do robo no percurso

	printf("XYComeca: [%d][%d]\n", R1->xAct + 1, R1->yAct + 1);
	R1->Temporario = M->Dados[i]; //copiar o que esta na quadricula para a variavel temporaria
	M->Dados[i] = CHARRobo; //colocar um R para saber que esta ali um robo
}
//----------------------------------------------------
/// Funcao: AlocarImperio
/// Descricao:  Esta funcao aloca na memoria, espaco para o imperio de acordo com o numero limite de robos definido, pergunta tambem quantos robos estao disponiveis no inicio do programa
/// Parametros: -------
/// Retorno: retorna a posicao na memoria do Imperio
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
ImperioRobo *AlocarImperio()
{
	int Qtd = 0;
	do {
		Qtd = LerNumero("Quantos Robos? 1-10: ");
	} while (Qtd<1 || Qtd>MAXROBOS);

	ImperioRobo *Imperio;
	Imperio = (ImperioRobo *)malloc(MAXROBOS*sizeof(ImperioRobo));
	Imperio->R = (Robo *)malloc(MAXROBOS*sizeof(Robo));
	Imperio->QtdRobo = Qtd;  //robos disponiveis no inicio do programa
	return Imperio;
}
//----------------------------------------------------
/// Funcao: RealocarImperio
/// Descricao: Esta funcao é chamada quando é premida a tecla A, incrementa o numero de robos disponiveis
/// Parametros: 
///     Imperio: EDados a alterar valores 
///     Matriz: matriz associada
///     ret: valor a retornar
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void RealocarImperio(ImperioRobo *Imperio, Matriz *M, int *ret)
{
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!Imperio)
	{
		ReportarErro(4);return; //se a EDados for nula, reportar erro e sair da funcao
	}

	if (Imperio->QtdRobo<MAXROBOS)
	{

		Imperio->QtdRobo++;		//incrementar a quantida de robos		
		*ret = 2; //foi acrescentado um robo, retorno é 2, reinicia o ciclo for
	}
	else
	{
		ReportarAviso(4);
		//printf("----Limite De Robos atingido----\n");
		*ret = 0; //nao foi acrescentado, retorno é 0, nao reinica o ciclo for
	}
}
//----------------------------------------------------
/// Funcao: Bateria
/// Descricao: Esta funcao gera um valor aleatorio entre 8 e 2 e subtrai esse valor à bateria do robo
/// Parametros: 
///     R1: robo a subtrair a bateria 
/// Retorno: Nao retorna nada
/// Autor: D M
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void Bateria(Robo *R1)
{
	if (!R1)
	{
		ReportarErro(8);return; //se o robo for nulo, reportar erro e sair da funcao
	}
	//Feito com muito esforco pelo machado
	srand(time(NULL));
	int bat;
	bat = 1 + rand() % 9 + 1; //gera valor entre 8 e 2
	R1->bateria = R1->bateria - bat; // subtrai o valor à bateria do robo
	if (R1->bateria < 0)  // caso seja inferior a 0 o resultado, igualar a 0
		R1->bateria = 0;
}
//----------------------------------------------------
/// Funcao: MexeRobo
/// Descricao: Esta funcao desloca o robo, verificando se pode mexer lo verificando a quadricula com um switch case
/// Parametros: 
///     R1: robo a utilizar
///		Matriz: matriz associada
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void MexeRobo(Robo *R1, Matriz *M)
{
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!R1)
	{
		ReportarErro(8);return; //se o robo for nulo, reportar erro e sair da funcao
	}

	bool posOK = false;
	int xPoss = 0, yPoss = 0, i;
	if (R1->bateria > 0)
	{
		i = GetPosicaoVector(R1->yAct, R1->xAct, M->nX);
		M->Dados[i] = R1->Temporario;//voltar a colocar o valor da matriz na matriz e retirar o R 

		while (posOK == false)
		{

			MoveRobot(R1->xAct, R1->yAct, R1->xObj, R1->yObj, &xPoss, &yPoss); //tentar mover o robo para a posicao seguinte
			i = GetPosicaoVector(yPoss, xPoss, M->nX);//pos seguinte
			switch (M->Dados[i])
			{
			case OBSTACULO:case CHARRobo: //caso a proxima posicao seja um obstaculo, gerar novo destino
			{
				posOK = false;
				ReportarAviso(5);
				//printf("**************Obstaculo no caminho ");
				GeraDestino(R1, M);
				printf(" Novo Destino: [%d][%d]\n", R1->xObj + 1, R1->yObj + 1);
				break;
			}
			case SUJO: // se for um 0 a proxima posicao, limpar, incrementar os contadores do robo, definir os xy possiveis como xy do robo
			{
				posOK = true;
				M->Dados[i]++;
				R1->nLimpezas++;
				R1->xAct = xPoss; R1->yAct = yPoss;
				R1->nMovimentos++;
				R1->percurso[R1->nMovimentos] = i;
				break;
			}
			case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': //se for outro numero, nao incrementa o nº de limpezas 
			{
				posOK = true;
				M->Dados[i]++;
				R1->xAct = xPoss;  R1->yAct = yPoss;
				R1->nMovimentos++;
				R1->percurso[R1->nMovimentos] = i;
				break;
			}
			case '9':case CHARExtra: //se for um 9, como sao variaveis char coloca-se um char para significar mais de 9 passagens
			{
				posOK = true;
				M->Dados[i] = CHARExtra;
				R1->xAct = xPoss;  R1->yAct = yPoss;
				R1->nMovimentos++;
				R1->percurso[R1->nMovimentos] = i;
				break;
			}
			}
		}
		R1->Temporario = M->Dados[i];// voltar a copiar a quadricula para o Temporario
		M->Dados[i] = CHARRobo;// e colocar um R na posicao nova do robo
		ContarSujo(M); printf("Sujo:%d\n", M->nSujos);// actualizar a contagem de sujos
		Bateria(R1);// subtrair a bateria do robo
	}
	else
	{
		R1->activo = 0;// se o robo ficar sem bateria, desactivar lo
		ReportarAviso(6);
		//printf("\n MORREU: Por Favor recarregar\n");
	}
}
//----------------------------------------------------
/// Funcao: InactivaRobos
/// Descricao: Esta funcao escreve server para quando se carrega no Q para desactivar os robos todos
/// Parametros: 
///     Imperio: lista de robos
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void InactivaRobos(ImperioRobo *Imperio)//desactiva os robos todos
{
	if (!Imperio)
	{
		ReportarErro(4);return; //se a EDados for nula, reportar erro e sair da funcao
	}
	for (int i = 0; i < Imperio->QtdRobo; i++)
	{
		Imperio->R[i].activo = false;
	}

}
//----------------------------------------------------
/// Funcao: MenuCase
/// Descricao: Esta funcao efectua a operacao de acordo com a tecla pressionada
/// Parametros: 
///     Parar: variavel para parar o ciclo 
///     key: tecla pressionada
///     TempoPausa: tempo de pausa entre movimentos
///     Imperio: lista de robos 
///     Matriz: matriz associada 
///     ret: valor de retorno
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void MenuCase(bool *Parar, char key, int *TempoPausa, ImperioRobo *Imperio, Matriz *M, int *ret)
{
	if (!M)
	{
		ReportarErro(7);return; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!Imperio)
	{
		ReportarErro(4);return; //se a EDados for nula, reportar erro e sair da funcao
	}

	int Temp, WrtError;
	switch (key)
	{
		case 'x': case 'X': //acelera
		{
			Temp = *TempoPausa;
			Temp -= 10;
			if (Temp > 50)
				*TempoPausa = Temp;
			else
				ReportarAviso(1);
				//printf("Chegou ao limite de velocidade MAXIMA\n");
			printf("\b\bAcelera... TempoPausa=%d\n", *TempoPausa);
			break;
		}
		case 'z': case 'Z':// abrandar
		{
			Temp = *TempoPausa;
			Temp += 20;
			if (Temp < 3000)
				*TempoPausa = Temp;
			else
				ReportarAviso(2);
				//printf("Chegou ao limite de velocidade MINIMA\n");
			printf("\b\bAbranda... TempoPausa=%d\n", *TempoPausa);
			break;
		}
		case 'q': case 'Q':// sair da simula
			{
				*Parar = true;
				InactivaRobos(Imperio);
				break;
			}
		case 'i': case 'I'://reiniciar simulacao
		{
			ReportarAviso(7);
			//printf("*****************************************\n ***A REINICIAR A SIMULACAO*** \n*****************************************\n");
			free(Imperio->R);
			free(Imperio);
			free(M->Dados);
			free(M);
			*ret = 1;
			break;
		}										
		case 'p': case 'P':// pausar simulacao
		{
			system("pause"); break;
		}
		case 'a': case 'A':// adiciona robot
		{
			RealocarImperio(Imperio, M, ret); break; 
		}
		case 'e': case 'E':// Escrever algumas estatisticas para um ficheiro
		{
			WrtError = EscreverEstatsFile(M, Imperio); break; 
		}
	}
}
//----------------------------------------------------
/// Funcao: Simulacao
/// Descricao: Esta funcao é a funcao principal da simulacao dos robos
/// Parametros: 
///     Imperio: lista de robos 
///     Matriz: matriz associada 
/// Retorno: retorna 1 caso seja premido I para reiniciar a simulacao, retorna 0 no fim da simulacao
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
int Simulacao(ImperioRobo *Imperio, Matriz *M)
{
	if (!M)
	{
		ReportarErro(7);return 1; //se a matriz for nula, reportar erro e sair da funcao
	}
	if (!Imperio)
	{
		ReportarErro(4);return 1; //se a EDados for nula, reportar erro e sair da funcao
	}

	bool Parar = false;
	int WrtError = 0, Pausa = PAUSAINICIAL;
	char key;

	while (!Parar)
	{
		int nInactivos = 0; //Contar quantos robos tao inactivos
		for (int i = 0; i < Imperio->QtdRobo; i++)
		{

			if (TeclaPressionada())//se for premida uma tecla
			{
				int ret = 0;
				key = getch(); //copiar la para um char
				MenuCase(&Parar, key, &Pausa, Imperio, M, &ret);
				if (ret == 1) return ret; // Para reiniciar a simulacao o valor de retorno tem de ser 1
				if (ret == 2)// reiniciar o for caso adicione um robo;
				{
					printf("Robo %d: ", Imperio->QtdRobo);
					IniciaRobo(M, &Imperio->R[Imperio->QtdRobo - 1]);
					break; 
				}
			}


			printf("=========================================================================================\nPrima: X-Acelerar Z-Abrandar Q-Sair P-Pausar I-Reiniciar E-Escrever Ficheiro A-Adic. Robo\n=========================================================================================\n");
			printf("ESTAMOS NO ROBO NUM. [%d] DE [%d] ROBOS \n", i + 1, Imperio->QtdRobo);
			fflush(stdin);
			WrtError = EscreverFile(M);
			if (WrtError == 0) // Quer dizer Sem ERROS na GRAVACAO
			{
				if (M->nSujos>0) // Com quadriculas por limpar
				{
					if (Imperio->R[i].activo == 1)// E o robo está activo, mover o robot
					{
						MexeRobo(&Imperio->R[i], M);// mexer o robo
						printf("ID: [%s]\tXYAct: [%d][%d]\tXYObj: [%d][%d]\tBateria: %d%%\tNMovimentos: %d\n", Imperio->R[i].id, Imperio->R[i].xAct + 1, Imperio->R[i].yAct + 1, Imperio->R[i].xObj + 1, Imperio->R[i].yObj + 1, Imperio->R[i].bateria, Imperio->R[i].nMovimentos);

						if (Imperio->R[i].xAct == Imperio->R[i].xObj && Imperio->R[i].yAct == Imperio->R[i].yObj)  //chegou ao destino, gera um novo
						{
							ReportarAviso(8);
							//printf("**************Chegou ao destino ");
							GeraDestino(&Imperio->R[i], M);
							printf("Novo Destino: [%d][%d]\n", Imperio->R[i].xObj + 1, Imperio->R[i].yObj + 1);
						}
						PrintMatriz(M); printf("\n");
						wait(Pausa);
					}
					else
					{
						ReportarAviso(9);
						//printf("Robo Inactivo!!!\n");//se ja esta sem bateria/inactivo, nao fazer nada com este robo
						int h = GetPosicaoVector(Imperio->R[i].yAct, Imperio->R[i].xAct, M->nX);
						M->Dados[h] = Imperio->R[i].Temporario;
						nInactivos++;
						if (Imperio->QtdRobo == nInactivos)
						{
							Parar = true;//definir a variavel parar para verdadeiro
							do
							{
								WrtError = EscreverFile(M);
							} while (WrtError == 1);
							ReportarAviso(10);
							//printf("\n--------------ACABARAM AS BATERIAS-----------------\n");
						}
					}
				}
				else
				{
					Parar = true;
					do
					{
						WrtError = EscreverFile(M);
					} while (WrtError == 1);
					ReportarAviso(11);
					//printf("\n--------------LIMPINHO-----------------\n");
				}
			}
			else
			{
				if (WrtError == 1)// se der erro na escrita
				{
					ReportarErro(5);
					//printf("\nERROR NA ESCRITA\n");
					wait(100);
				}
			}
		}
	}
	return 0; //Retorna 0, simulacao acabou com sucesso
}

//----------------------------------------------------
/// Funcao: main
/// Descricao: Esta funcao é a funcao principal do programa
/// Parametros: -------
/// Retorno: Nao retorna nada
///
/// Data: 2015-12-20
/// Versao: 1.5
//-----------------
void main()
{
	Matriz *M;
	ImperioRobo *Imperio;
	int Exit = 0, WrtError = 0;

	printf("                        _         ____   _    _               \n     /\\                (_)       / __ \\ | |  | |              \n    /  \\    ___  _ __   _  _ __ | |  | || |__| | _ __    ___  \n   / /\\ \\  / __|| '_ \\ | || '__|| |  | ||  __  || '_ \\  / _ \\ \n  / ____ \\ \\__ \\| |_) || || |   | |__| || |  | || |_) || (_) |\n /_/    \\_\\|___/| .__/ |_||_|    \\____/ |_|  |_|| .__/  \\___/ \n                | |                             | |           \n                |_|                             |_|           \n\n");

	do
	{
		int  mX = 0, mY = 0;
		do {
			mX = LerNumero("Tamanho Matriz [X]: ");
			mY = LerNumero("Tamanho Matriz [Y]: ");
		} while ((mX <= 0) || (mY <= 0) || (mX > MAXCOORD) || (mY > MAXCOORD));  //Pedir ao utilizador o tamanho da divisao e impor uns limites

		M = AlocarMatriz(mX, mY);	//Preparar a matriz, alocar na memoria, colocar obstaculos
		PrintMatriz(M); printf("\n");
		//MATRIZ FEITA

		Imperio = AlocarImperio();
		for (int i = 0; i < Imperio->QtdRobo; i++)
		{
			printf("Robo %d: ", i + 1);
			IniciaRobo(M, &Imperio->R[i]); //iniciar o 1º robo, gerar o seu destino, o seu inicio e colocar os valores predefinidos (bateria, activo etc.)
		}
		//ROBO PRONTO

		Exit = Simulacao(Imperio, M);

	} while (Exit == 1);

	printf("\n***************************************\n***************A TERMINAR**************\n***************************************\n");
	do {
		WrtError = EscreverEstatsFile(M, Imperio);
		wait(300);
	} while (WrtError == 1);

	free(Imperio->R);
	free(Imperio);
	free(M->Dados);
	free(M);
}