/*
==================================================================================
Projecto de Estrutura de Dados - SuperMercado
Realizado por: Dg, D M , R A

13 de Junho de 2016
==================================================================================
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define def_MAXESPERA 120 //Num. Max pessoas em espera por caixa
#define def_MAXCAIXAS 6 //Num. Max de Caixas
#define def_TEMPO_ATENDIMENTO_PRODUTO 10 //Num. Max de tempo por produto em Segundos
#define def_MAXPRECO 20 //Preco max por produto
#define MAXProds 26 //Maximo de produtos no catalogo 
#define MAXProdsCliente 30 //Maximo de produtos no cliente 
#define MAXPALAVRA 256
#define TITULO "Continente Manager Simulator 2017 - Dg, D M, R A\n"
#define TEMPOACTUALIZACAO 2000 //Periodo de escrita para o ficheiro
#define ACTIVA true
#define DESACTIVA false
#define NEXISTE -1
#define PeriodoMostrarMenu 2500 
#define PeriodoRetiraCliente 9000 //em Milis, tempo em que retira um cliente da loja e acrescenta a uma caixa
#define PeriodoVerMaxEspera 15000 //em Milis, tempo em que verifica se estao clientes a mais numa caixa
#define PeriodoVerMinClientes 20000 //em Milis, tempo em que verifica se estao caixas a mais 
#define PeriodoColocaCliente 5500 //em Milis, tempo em que coloca um cliente na loja
#define PeriodoAnalisarOferta 3000 //em Milis, tempo em que vai analisar se deve fazer ofertas a um Cliente
#define PeriodoAtender 18000 //em Milis, tempo entre atender 1 cliente em todas as caixas
#define NumerodeNomes 7 //Quantos nomes para escolher para atribuir aos operadores

//Para Fazer Menus Giros
#define _1 putchar(187)
#define _2 putchar(188)
#define _3 putchar(201)
#define _4 putchar(200)
#define _5 putchar(205)
#define _6 putchar(203)
#define _7 putchar(186)
#define _8 putchar(202)
#define _9 putchar(185)
#define _10 putchar(204)// <--
#define _11 putchar(206)

#define _12 putchar(178)

#define NOVALINHA putchar('\n')
#define TABTAB putchar('\t')
//-----------------------------------------------------------

//--------------
typedef struct configs //Tempo max de espera | Maximo de caixas | Tempo max de atendimento por Prod. | Preco max por Prod.
{
	int MAXESPERA, //Num max de pessoas por Fila
		MAXCAIXAS, //Num. Max de Caixas
		TEMPO_ATENDIMENTO_PRODUTO, //Tempo Max de atendimento por prod. (em seg.)
		MAXPRECO;  //Preco Max de um Produto

}Configs;

typedef struct listadenomes
{
	char Nome[30];
}ListaDeNomes;

ListaDeNomes NomesOperadores[] = {"Joaquim Esteves","Bill Portoes","Steve Macas","A. Dell","H. Ramos","H. Raqui","Adolfo Dias"};

typedef struct arrayprodutos
{
	int IDProduto, //id do produto
		Preco,	//Preco do produto
		TempoProduto; //Tempo De atendimento do prod. (em seg.)
}ArrayProdutos;

typedef struct cliente
{
	int IDCliente, //id do cliente
		NProdutos, //Num. de produtos que o cliente leva
		TempoEspera, //quanto tempo teve à espera, vai decrementando; Em Segundos.
		TempoEntrada, //quanto tempo teve à espera, vai decrementando; Em Segundos.
		*LProdutos; //Lista dos Produtos
	bool ProdutoDescontado; //Se ja foi descontado algum produto
}Cliente;

typedef struct noclientes
{
	Cliente *InfoCliente;	//info do cliente
	struct noclientes* ClienteSeguinte;  //Ponteiro para o cliente seguinte na caixa
}NoClientes;

typedef struct listaclientes //
{
	int NClientes; //Num. de clientes numa caixa
	NoClientes *ClienteTopo; //Cliente a ser atendido
	NoClientes *ClienteFim;	//Cliente que acaba de chegar
}ListaClientes;

typedef struct caixa
{
	int IDCaixa, //ID da Caixa 
		ClientesAtendidos, // Clientes atendidos
		DinheiroGanho, //Quanto dinheiro recebeu
		DinheiroPerdido, //Quanto Dinheiro foi "oferecido"
		ProdutosVendidos, //Produtos Vendidos
		TMedioEsp, //tempo medio de espera ate ser atendido
		NProdsOferecidos; //Quantos prods ofereceu
	bool Activa, //Se esta activa ou nao
		 AdmitirClientes; //se esta disponivel para aceitar clientes
	char NomeOperador[30]; //Nome do Operador
	ListaClientes *LClientes; //lista dos clientes na caixa
	ListaClientes * LCatendidos; //ponteiro para atendidos
}Caixa;

typedef struct nocaixa
{
	Caixa *InfoCaixa; //Info da Caixa
	struct nocaixa *CaixaSeguinte; // Caixa seguinte na Lista
}NoCaixa;

typedef struct listacaixas
{
	int NCaixas, //Num. de caixas
		NClienteSeguinte, //ID para o cliente que entrar a seguir
		*EstadoCaixas; //Estado em que cada caixa esta, -1 inexistente, 0 fechada/Desactiva, 1 Aberta/Activa
	NoCaixa *CaixaPrimeira; //Primeira Caixa Na Lista

}ListaCaixa;

typedef struct historico
{
	int TempoSim, //Tempo total de simulacao
		TempoInicio, //A que horas iniciou o progr
		NClientesAtendidos, //Quantos clientes foram atendidos
		TempoMedioEspera, //Quanto tempo se espera na fila
		NProdsVendds, //Total Produtos vendidos
		TotalDinheiroRecebido, //Quanto dinheiro se recebeu
		TotalDinheiroPerdido, //Quanto valiam os prods oferecidos
		NProdsOfer; //Quantos produtos foram oferecidos por demora
}Historico;

typedef struct simulacao
{
	ListaCaixa *LCaixas; //Lista de Caixas
	Configs *Configuracoes; //Configuracoes do programa
	ListaClientes *LClientesNaLoja; // Lista de clientes na loja, por atender
	Historico *StructHistorico; //Historico para guardar totais
	ArrayProdutos LProdutos[MAXProds]; //Catalogo de produtos, disponivel online em www.continente.pt
}Simulacao;

//para ter acesso à funcao em qualquer parte do programa
int Randomizer(int min, int max); 
void DesActivarCaixa(Simulacao *Sim, int IDCaixa);
void EscreverFileHistorico(Simulacao *Sim);
void AdicClienteFim(ListaClientes *LCli, NoClientes *ClienteAdd);
NoCaixa *SelecionaCaixa(Simulacao *Sim, int IDCaixa);

void wait(int mlseconds)
{
	clock_t endwait;
	endwait = clock() + mlseconds;
	while (clock() < endwait) {} 
}

//----------------------------------------------------------
//------------------MALLOCS WORLD---------------------------

/*
CriarCliente:
Cria uma estrutura do tipo cliente, retorna um ponteiro do tipo cliente
*/
Cliente *CriarCliente(){ 
	Cliente *Clientezinho = (Cliente *)malloc(sizeof(Cliente));
	if (!Clientezinho)
		return nullptr;
	Clientezinho->IDCliente=NULL;
	Clientezinho->NProdutos=NULL;
	Clientezinho->TempoEspera=NULL;
	Clientezinho->LProdutos=nullptr;
	Clientezinho->ProdutoDescontado=false;
	Clientezinho->TempoEntrada=NULL;
	
	return Clientezinho;
}

/*
CriarNoClientes:
Cria uma estrutura do tipo NoClientes, retorna um ponteiro do tipo NoClientes
*/
NoClientes *CriarNoClientes(){
	NoClientes *NOClientes = (NoClientes *)malloc(sizeof(NoClientes));
	if(!NOClientes)
		return nullptr;

	NOClientes->ClienteSeguinte = nullptr;
	NOClientes->InfoCliente = nullptr;
	
	return NOClientes;
}

/*
CriarListaClientes:
Cria uma estrutura do tipo ListaClientes, retorna um ponteiro do tipo ListaClientes
*/
ListaClientes *CriarListaClientes(){
	ListaClientes *LClientes = (ListaClientes *)malloc(sizeof(ListaClientes));
	if(!LClientes)
		return nullptr;
	LClientes->ClienteTopo = nullptr;
	LClientes->ClienteFim = nullptr;
	LClientes->NClientes = 0;
	return LClientes;
}

/*
CriarCaixa:
Cria uma estrutura do tipo Caixa, retorna um ponteiro do tipo Caixa
*/
Caixa *CriarCaixa(){
	Caixa *Caixinha = (Caixa *)malloc(sizeof(Caixa));
	if(!Caixinha)
		return nullptr;
	Caixinha->Activa = 0;
	Caixinha->IDCaixa = 0;
	Caixinha->NProdsOferecidos = 0;
	Caixinha->NomeOperador[0] = '\0';
	Caixinha->ClientesAtendidos = 0;
	Caixinha->DinheiroGanho = 0;
	Caixinha->DinheiroPerdido = 0;
	Caixinha->ProdutosVendidos = 0;
	Caixinha->TMedioEsp = 0;
	Caixinha->LClientes = CriarListaClientes();
	Caixinha->LCatendidos = CriarListaClientes();
	if(!Caixinha->LClientes || !Caixinha->LCatendidos)
		return nullptr;
	return Caixinha;
}

/*
CriarNoCaixa:
Cria uma estrutura do tipo NoCaixa, retorna um ponteiro do tipo NoCaixa
*/
NoCaixa *CriarNoCaixa(){
	NoCaixa *NOCaixa = (NoCaixa *)malloc(sizeof(NoCaixa));
	if(!NOCaixa)
		return nullptr;

	NOCaixa->CaixaSeguinte = nullptr;
	NOCaixa->InfoCaixa = nullptr;
	return NOCaixa;
}

/*
CriarListaCaixas:
Cria uma estrutura do tipo ListaCaixa, retorna um ponteiro do tipo ListaCaixa
*/
ListaCaixa *CriarListaCaixas(){
	ListaCaixa *LCaixa = (ListaCaixa *)malloc(sizeof(ListaCaixa));
	if(!LCaixa)
		return nullptr;
	
	LCaixa->CaixaPrimeira = nullptr;
	LCaixa->NCaixas = 0;
	LCaixa->NClienteSeguinte = 0;
	return LCaixa;
}

/*
DefaultConfigs:
Atribui valores predefinidos à estrutura configs caso nao consiga ler do ficheiro
*/
void DefaultConfigs(Configs *c){
	c->MAXCAIXAS = def_MAXCAIXAS;
	c->MAXESPERA = def_MAXESPERA;
	c->MAXPRECO = def_MAXPRECO;
	c->TEMPO_ATENDIMENTO_PRODUTO = def_TEMPO_ATENDIMENTO_PRODUTO;
}

/*
LerConfigs:
Le do ficheiro Configuracao.txt as configuracoes e retorna uma estrutura Configs com os valores lidos.
*/
Configs *LerConfigs(){

	Configs *c = (Configs *)malloc(sizeof(Configs));
	
	FILE *G = fopen("..\\Configuracao.txt","r");
	if (!G){
		printf("!!!!Problema no ficheiro de configuracao!!!\nA carregar configuracoes predefinidas....\n");
		DefaultConfigs(c);//ler umas configuracoes por definicao
	}
	else{
		char buffer[MAXPALAVRA];
		bool Leitura1 = false,Leitura2 = false,Leitura3 = false,Leitura4 = false; //variaveis para dizer que leu o valor correctamente, se tiverem as 4 a true, foi lido com sucesso
		int temp = 0;

		while(!feof(G)){
			
			fscanf(G,"%s",buffer);
			//ler valor de MAXCAIXAS
			if(stricmp(buffer,"MAXCAIXAS") == 0){	//obrigado MLG, STRICMP NOT CASE SENSITIVE
				fscanf(G,"%s",buffer);
				temp = atoi(buffer);
				c->MAXCAIXAS = temp;
				Leitura1 = true;
			}
			//ler valor de MAXESPERA
			else if(stricmp(buffer,"MAXESPERA") == 0){	
				fscanf(G,"%s",buffer);
				temp = atoi(buffer);
				c->MAXESPERA = temp;
				Leitura2 = true;
			}
			//ler valor de MAXPRECO
			else if(stricmp(buffer,"MAXPRECO") == 0){	
				fscanf(G,"%s",buffer);
				temp = atoi(buffer);
				c->MAXPRECO = temp;
				Leitura3 = true;
			}
			//ler valor de TEMPO_ATENDIMENTO_PRODUTO
			else if(stricmp(buffer,"TEMPO_ATENDIMENTO_PRODUTO") == 0){	
				fscanf(G,"%s",buffer);
				temp = atoi(buffer);
				c->TEMPO_ATENDIMENTO_PRODUTO = temp;
				Leitura4 = true;
			}
		}
		if(!Leitura1 || !Leitura2 || !Leitura3 || !Leitura4){
			printf("!!!!Problema no ficheiro de configuracao!!!\nA carregar configuracoes predefinidas....\n");
			DefaultConfigs(c);
		}
		fclose(G);
	}
	return c;
}

/*
AbrirFicheiroInteraccao:
Abre o ficheiro para onde guardar as interaccoes que o utilizador faz no programa
*/
void AbrirFicheiroInteraccao(){
	FILE *G = fopen("..\\HISTORICO.csv", "w"); //criar o ficheiro onde as interaccoes do utilizador
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if(G){
		fprintf(G, "******HISTORICO******\nData: %02d/%02d/%d Hora: %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
		fclose(G);
	}
}

/*
FecharFicheiroInteraccao:
Termina o ficheiro para onde guardar as interaccoes que o utilizador faz no programa
*/
void FecharFicheiroInteraccao(){
	
	FILE *G = fopen("..\\HISTORICO.csv", "a"); //adiciona informacao ao ficheiro das interaccoes do utilizador
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	if(G){
		fprintf(G, "%02d:%02d:%02d FecharPrograma;\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		fclose(G);
	}
}

/*
CriarSimulacao:
Cria a estrutura simulacao, inserindo valores predfs, e outras sub estruturas. Retorna um ponteiro do tipo simulacao
*/
Simulacao *CriarSimulacao(){

	Simulacao *Sim = (Simulacao *)malloc(sizeof(Simulacao));
	if(!Sim)
		return nullptr;
	Sim->Configuracoes = LerConfigs(); //Carregar as configs
	Sim->LCaixas = CriarListaCaixas(); //Criamos a lista base para as caixas
	Sim->LClientesNaLoja = CriarListaClientes(); //criamos a lista base para os clientes que estao na loja
	Sim->StructHistorico = nullptr;
	Sim->LCaixas->EstadoCaixas = (int *)malloc(Sim->Configuracoes->MAXCAIXAS * sizeof(int));
	
	for (int i = 0; i < Sim->Configuracoes->MAXCAIXAS; i++)//Inicializa o array de estado a -1
		Sim->LCaixas->EstadoCaixas[i] = -1;
	
	Historico *StructHist = (Historico *)malloc(sizeof(Historico));
	if(!StructHist)
		return nullptr;
	StructHist->NClientesAtendidos = 0;
	StructHist->NProdsOfer = 0;
	StructHist->NProdsVendds = 0;
	StructHist->TempoInicio = time(NULL);
	StructHist->TempoMedioEspera = 0;
	StructHist->TempoSim = 0;
	StructHist->TotalDinheiroPerdido = 0;
	StructHist->TotalDinheiroRecebido = 0;
	
	Sim->StructHistorico = StructHist;

	//o ID 0 é quando um produto é descontado do cliente, esse produto fica com ID 0 no cliente quando e descontado
	Sim->LProdutos[0].IDProduto=0;
	Sim->LProdutos[0].Preco = 0;
	Sim->LProdutos[0].TempoProduto = 0;

	for (int i = 1; i < MAXProds; i++) //encher o array de produtos com precos aleatorios.
	{
		Sim->LProdutos[i].IDProduto=i;
		wait(10+i);
		Sim->LProdutos[i].Preco = Randomizer(1,Sim->Configuracoes->MAXPRECO);
		Sim->LProdutos[i].TempoProduto = Randomizer(2,Sim->Configuracoes->TEMPO_ATENDIMENTO_PRODUTO);
	}
	
	AbrirFicheiroInteraccao();
	return Sim;
}

//--------------------------------------------
//-----------FORGETFULLNESS LAND-------------

/*
LibertarCliente:
Desaloca memoria de um ponteiro cliente
*/
void LibertarCliente(Cliente *Clientezinho){
	if(!Clientezinho)
		return;
	if(Clientezinho->LProdutos)
		free(Clientezinho->LProdutos);
	free(Clientezinho);
}

/*
LibertarNOCliente:
Desaloca memoria de um ponteiro NoClientes
*/
void LibertarNOCliente(NoClientes *NOCliente){
	free(NOCliente);
}

/*
LibertarListaClientes:
Desaloca memoria de um ponteiro ListaClientes, Desalocando todos os nos la guardados
*/
void LibertarListaClientes(ListaClientes *LClientes){
	NoClientes *NOClientes = LClientes->ClienteTopo;
	NoClientes *Aux;
	while (NOClientes)// desalocar todos os clientes
	{
		Aux = NOClientes->ClienteSeguinte;
		LibertarCliente(NOClientes->InfoCliente);
		LibertarNOCliente(NOClientes);
		NOClientes = Aux;
	}
	free(LClientes);
}

/*
LibertarNoCaixa:
Desaloca memoria de um ponteiro NoCaixa, Desalocando tambem os ponteiros la guardados
*/
void LibertarNoCaixa(NoCaixa *NCaixa){
	LibertarListaClientes (NCaixa->InfoCaixa->LClientes);
	LibertarListaClientes (NCaixa->InfoCaixa->LCatendidos);
	free(NCaixa->InfoCaixa);
	free(NCaixa);

}

/*
LimparALoja:
Desaloca a estrutura simulacao e termina o ficheiro de interaccao
*/
void LimparALoja(Simulacao *Sim){
	if(!Sim) return;
	NoCaixa *NOCX,*NOCXSeguinte;
	NOCX = Sim->LCaixas->CaixaPrimeira;
	printf("\nA Limpar a Loja\n");
	while(NOCX){// desalocar todas as Caixas
		
		printf("Caixa %d: ",NOCX->InfoCaixa->IDCaixa);
		NOCXSeguinte = NOCX->CaixaSeguinte;
		LibertarNoCaixa(NOCX);
		NOCX = NOCXSeguinte;
		printf(" Limpa :D\n");
	}

	if(Sim->LClientesNaLoja){
		
		printf("A Limpar LClienteNaLoja: ");
		LibertarListaClientes(Sim->LClientesNaLoja);
		printf(" Limpos :D\n");
	}
	
	free(Sim->Configuracoes);
	free(Sim->LCaixas);
	free(Sim->StructHistorico);
	FecharFicheiroInteraccao();
	free(Sim);
	printf("Pode activar os robos de limpeza\n\n");
}

//---------------------------------------------------
//-----------FUNCTIONS THAT ACTUALLY DO SOMETHING----

/*
AdicClienteFim:
Adiciona um cliente no fim de uma ListadeClientes
*/
void AdicClienteFim(ListaClientes *LCli, NoClientes *ClienteAdd){
	ClienteAdd->ClienteSeguinte=nullptr;

	if(!LCli->ClienteTopo){ //se nao houver clientes, quer dizer que o topo = Fim
		LCli->ClienteTopo = ClienteAdd;  
		LCli->ClienteFim = ClienteAdd;
	}
	else{
		LCli->ClienteFim->ClienteSeguinte = ClienteAdd; //Colocar no fim da lista
		LCli->ClienteFim = ClienteAdd;
	}
		//printf("ClienteAdicionadoFim\n");
}

/*
AdicionarClienteLoja:
Adiciona um cliente à loja
*/
void AdicionarClienteLoja(Simulacao *Sim){
	Cliente *ClienteNovo = CriarCliente(); 
	if(!ClienteNovo)
		return;

	int R = Randomizer(1,MAXProdsCliente);
	ClienteNovo->IDCliente = Sim->LCaixas->NClienteSeguinte++; 
	ClienteNovo->NProdutos = R; 
	ClienteNovo->LProdutos = (int *)malloc(R * sizeof(int)); //inicializar Lista de produtos do cliente
	ClienteNovo->TempoEspera = Sim->Configuracoes->MAXESPERA;
	ClienteNovo->TempoEntrada = time(NULL);

	int r=0;
	for (int i = 0; i < R; i++)//colocar produtos no cliente
	{
		r = Randomizer(1,MAXProds-1);
		ClienteNovo->LProdutos[i] = Sim->LProdutos[r].IDProduto; //copia o id do produto que escolheu
		wait(3);
	}

	NoClientes *NozitoDeCliente = CriarNoClientes();
	if(!NozitoDeCliente)
		return;
		
	NozitoDeCliente->InfoCliente = ClienteNovo;
	printf("+++Cliente[%d]-->",ClienteNovo->IDCliente);
	AdicClienteFim(Sim->LClientesNaLoja,NozitoDeCliente);
	
	Sim->LClientesNaLoja->NClientes++;

}

/*
AdicionarCliente:
Adiciona um cliente a uma loja
*/
void AdicionarCliente(Simulacao *Sim ,int IDCaixa ,int nProdutos, int IDCliente){
	
	Cliente *ClienteNovo = CriarCliente();
	
	if(!ClienteNovo)
		return;
	
	NoCaixa *NoCaixaAux = Sim->LCaixas->CaixaPrimeira;

	while (NoCaixaAux != nullptr) //procura a caixa destino
	{
		if( NoCaixaAux->InfoCaixa->IDCaixa == IDCaixa )
			break;
		else
			NoCaixaAux = NoCaixaAux->CaixaSeguinte;
	}
	
	if(NoCaixaAux){
		if(IDCliente)//isto so será usado quando tiver a ler do dados.txt, pois nos outros casos o id é automatizado
		{
			ClienteNovo->IDCliente = IDCliente;	//COPIAR o id para ocliente novo
			if(IDCliente > Sim->LCaixas->NClienteSeguinte) //se o id colocado for maior que o NCLietneSeguinte, definir o novo maximo
				Sim->LCaixas->NClienteSeguinte = ++IDCliente;
		}
		else
			ClienteNovo->IDCliente = Sim->LCaixas->NClienteSeguinte++; //associar um id individual ao cliente e incrementar
		
		
		ClienteNovo->NProdutos = nProdutos;
		ClienteNovo->LProdutos = (int *)malloc(nProdutos * sizeof(int));
		ClienteNovo->TempoEspera = Sim->Configuracoes->MAXESPERA;
		ClienteNovo->TempoEntrada = time(NULL);

		int r=0;
		for (int i = 0; i < nProdutos; i++)//colocar produtos no cliente
		{
			r = Randomizer(1,MAXProds-1);
			ClienteNovo->LProdutos[i] = Sim->LProdutos[r].IDProduto; //copia a info de um produto para a lista do cliente
			wait(3);
		}


		NoClientes *NozitoDeCliente = CriarNoClientes(); //criar um no para colocar o cliente novo
		if(!NozitoDeCliente)
			return;
		
		NozitoDeCliente->InfoCliente = ClienteNovo; //colocar no NO o cliente
		AdicClienteFim(NoCaixaAux->InfoCaixa->LClientes,NozitoDeCliente);
		NoCaixaAux->InfoCaixa->LClientes->NClientes++; //inc. o n de clintes 

	}
	else
		return;
	
}

/*
AdicionarCaixa:
Adiciona uma caixa
*/
void AdicionarCaixa(Simulacao *Sim, int IDCaixa, bool Activa){
	
	if(Sim->LCaixas->NCaixas >= Sim->Configuracoes->MAXCAIXAS) //Verificar se atingiu o limite de caixas
		return;

	if (!Sim->LCaixas){ //se nao tiver uma lista de caixas feita, criar uma
		Sim->LCaixas = CriarListaCaixas();
		if(!Sim->LCaixas)
			return;
	}
	
	Caixa *CaixaNova = CriarCaixa();
	
	if(CaixaNova){
		if(CaixaNova->LClientes){
			
			CaixaNova->Activa = Activa; //copiar o estado da caixa
			CaixaNova->AdmitirClientes = ACTIVA;

			if(IDCaixa)// caso haja um id para colocar na caixa
			{
				CaixaNova->IDCaixa = IDCaixa;
				Sim->LCaixas->EstadoCaixas[IDCaixa-1]=Activa;
				Sim->LCaixas->NCaixas++;
			}
			else
			{
				Sim->LCaixas->EstadoCaixas[Sim->LCaixas->NCaixas]=Activa;
				CaixaNova->IDCaixa = ++Sim->LCaixas->NCaixas;
			}

			strcpy(CaixaNova->NomeOperador, NomesOperadores[Randomizer(0,NumerodeNomes-1)].Nome);//Dar um nome ao operador
			CaixaNova->ClientesAtendidos = 0;
			CaixaNova->DinheiroGanho = 0;
			CaixaNova->DinheiroPerdido = 0;
			CaixaNova->ProdutosVendidos = 0;


			NoCaixa *NovoNOCaixa = CriarNoCaixa();
			if(!NovoNOCaixa)
				return;
	
			NovoNOCaixa->InfoCaixa = CaixaNova;

	
			if(!Sim->LCaixas->CaixaPrimeira) //se for a 1º caixa
				Sim->LCaixas->CaixaPrimeira = NovoNOCaixa;
			else
			{
				NoCaixa *NoCaixaAux = Sim->LCaixas->CaixaPrimeira;
				while(NoCaixaAux->CaixaSeguinte){ //vamos por no fim da lista a nova caixa
					NoCaixaAux = NoCaixaAux->CaixaSeguinte;
				}
				NoCaixaAux->CaixaSeguinte = NovoNOCaixa;
			}
		}
		else
			return;
		printf("CaixaAdicionado\n");
	}
	else
		return;
}

/*
TirarP:
funcao para retirar o P dos clientes quando le do dados.txt
*/
int TirarP(char *buffer){ //funcao para retirar o P dos clientes quando le do dados.txt
	char Temporario[25];
	int i=0;
	while (buffer[i] != '\0')
	{
		Temporario[i]=buffer[i+1];
		i++;
	}
	Temporario[i] = '\0';
	return atoi(Temporario);
}

/*
ActualizarEstado:
funcao para sincronizar os estados das caixas com o array de estados das caixas
*/
void ActualizarEstado(Simulacao *Sim){
	NoCaixa *CaixaAux = Sim->LCaixas->CaixaPrimeira;
	while (CaixaAux)
	{
		if(CaixaAux->InfoCaixa->Activa)
			Sim->LCaixas->EstadoCaixas[CaixaAux->InfoCaixa->IDCaixa-1]=ACTIVA;
		else
			Sim->LCaixas->EstadoCaixas[CaixaAux->InfoCaixa->IDCaixa-1]=DESACTIVA;
		
		CaixaAux=CaixaAux->CaixaSeguinte;
	}
}

/*
LerDados:
funcao para ler o ficheiro Dados.txt
*/
void LerDados(Simulacao *Sim){

	char key;
	printf("Deseja Carregar do Dados.txt? [S/N]\n-> ");
	fflush(stdin);			//Limpar o buffer
	key = getch();
	putchar(key);
	NOVALINHA;
	if(key == 'S' || key == 's'){

		FILE *G = fopen("..\\Dados.txt","r");
		if (!G){
			printf("!!!!Problema no ficheiro de Dados!!!\nNao foi possivel carregar os Dados....\n");
			return ;
		}
		else{
			char buffer[MAXPALAVRA];
			bool Leitura1 = false,
				Leitura2 = false,
				Leitura3 = false,
				Leitura4 = false;
			int NumCaixas, NumClientes, activa, idCliente,NProds;

			while(!feof(G)){
				fscanf(G,"%s",buffer);
				//printf("[%s]",buffer);
				if (stricmp(buffer,"TempoRefrescamento") == 0){
					fscanf(G,"%s",buffer); // ":"
					fscanf(G,"%s",buffer); // Val do tempo de actualizacao
					fscanf(G,"%s",buffer); // Num de caixas
					NumCaixas = atoi(buffer);
					//printf("NumCaixas[%s]",buffer);

					for (int i = 0; i < NumCaixas; i++)
					{
						fscanf(G,"%s", buffer); //caixai, ID da caixa
						//printf("\nCaixa[%s]",buffer);
						fscanf(G,"%s",buffer); // :
						fscanf(G,"%s",buffer); //Activa ou nao
						sscanf(buffer,"%d",&activa);
						//printf("Activa[%s]",buffer);
					
						fscanf(G,"%s",buffer); //num de clientes
						NumClientes = atoi(buffer);
						//printf("NumClientes[%d]\n",NumClientes);
					
						AdicionarCaixa(Sim,i+1,activa);//adicionar uma caixa
						for (int h = 0; h < NumClientes; h++)
						{
							fscanf(G,"%s",buffer);// id cliente 
							//printf("Cliente (%s)",buffer);
							idCliente = TirarP(buffer);
							fscanf(G,"%s",buffer); // :
							//printf(": (%s)",buffer);
							fscanf(G,"%s",buffer); //n produtos
							//printf("NProds (%s)",buffer);
							sscanf(buffer,"%d",&NProds);
							//printf("\nIDCliente[%d][%d]",idCliente,b2);
							AdicionarCliente(Sim, i+1, NProds, idCliente);
						}					
					}
				}
			}

		fclose(G);
		printf("\nDados.txt lido!");
		ActualizarEstado(Sim);
		wait(250);
		}
	}
	else
	{
		printf("\nNao Carregar do Dados!");
		wait(250);
	}
}

/*
EscreverFileInter:
Escrever para o ficheiro de actividade do utilizador
*/
void EscreverFileInter(char *S){
	
	FILE *G = fopen("..\\HISTORICO.csv", "a");
		time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	if(G){
	fprintf(G,"%02d:%02d:%02d ", tm.tm_hour, tm.tm_min, tm.tm_sec);
	fprintf(G,S);
	fprintf(G,";\n");
	fclose(G);
	}
	
}

/*
EscreverFileDados:
Escrever para o ficheiro de dados.txt
*/
void EscreverFileDados(Simulacao *Sim)
{
	if (!Sim)
		return;
	if(!Sim->LCaixas)
		return;

	NoCaixa *NoCaixaAux = nullptr;
	NoClientes *NoClAux = nullptr;

	FILE *f = fopen("..\\Dados.txt", "w"); //criar o ficheiro onde escrever a matriz
	if (f) //se conseguir criar o ficheiro
	{
		fprintf(f, TITULO);
		fprintf(f, "TempoRefrescamento : %d\n", TEMPOACTUALIZACAO);
		fprintf(f,"%d\n",Sim->LCaixas->NCaixas);

		if(Sim->LCaixas->NCaixas > 0){ //Se nao houver caixas segue

			NoCaixaAux = Sim->LCaixas->CaixaPrimeira;
			while(NoCaixaAux){ //por cada caixa
			
				if(NoCaixaAux->InfoCaixa->Activa)
					fprintf(f,"Caixa%d : 1\n",NoCaixaAux->InfoCaixa->IDCaixa);		
				else
					fprintf(f,"Caixa%d : 0\n",NoCaixaAux->InfoCaixa->IDCaixa);
			
				fprintf(f,"%d\n",NoCaixaAux->InfoCaixa->LClientes->NClientes);

				if(NoCaixaAux->InfoCaixa->LClientes->NClientes > 0){ //Se nao houver clientes segue viagem
					NoClAux = NoCaixaAux->InfoCaixa->LClientes->ClienteTopo;
					
					while (NoClAux) // por cada cliente na caixa
					{
						fprintf(f,"P%d : %d\n", NoClAux->InfoCliente->IDCliente, NoClAux->InfoCliente->NProdutos);
					
						NoClAux = NoClAux->ClienteSeguinte;
					}
				}
				NoCaixaAux = NoCaixaAux->CaixaSeguinte;
			}
		}
		
		fclose(f);
	}
	else
	{
			printf("**********\nERRO DE ESCRITA1!!!!\n*****************\n"); 
			getch();

	}

}

/*
Randomizer:
Retorna um valor aleatoriom dando lhe limites
*/
int Randomizer(int min, int max){
	srand(clock()+1);
	return min + rand()% (max - min + 1);
}

/*
RetirarCliente:
Retira um Cliente de uma caixa para outra caixa destino
*/
void RetirarCliente(Simulacao *Sim,int IDCaixaRetira,int IDCliente,int IDCaixaColoca){
	NoCaixa *CaixaARetirar, *CaixaAColocar;
	NoClientes *ClienteRetirar;
	NoClientes *Aux = nullptr;
	
	CaixaARetirar = SelecionaCaixa(Sim,IDCaixaRetira);
	CaixaAColocar = SelecionaCaixa(Sim,IDCaixaColoca);

	if(!CaixaARetirar || !CaixaAColocar){
		printf("Caixa invalida\n");
		return;
	}

	ClienteRetirar = CaixaARetirar->InfoCaixa->LClientes->ClienteTopo;


	while (ClienteRetirar!=nullptr && ClienteRetirar->InfoCliente->IDCliente != IDCliente) //enquanto houver Cliente e o id nao corresponder
	{
		Aux = ClienteRetirar;
		ClienteRetirar = ClienteRetirar->ClienteSeguinte;
	}

	if(!ClienteRetirar){
		printf("cliente invalida\n");
		return; //printf erro, cliente n encontrado
	}

	if(ClienteRetirar == CaixaARetirar->InfoCaixa->LClientes->ClienteFim) //caso o cliente seja o ultimo da fila, tem de se actualizar este parametro
	{
		CaixaARetirar->InfoCaixa->LClientes->ClienteFim = Aux;
		if(Aux)
			Aux->ClienteSeguinte = nullptr;
	}
	else
		Aux->ClienteSeguinte = ClienteRetirar->ClienteSeguinte;

	CaixaARetirar->InfoCaixa->LClientes->NClientes--; //decrementar o num de clientes na CaixaARetirar
	
	AdicClienteFim(CaixaAColocar->InfoCaixa->LClientes,ClienteRetirar); //adicionamos o cliente ao fim da caixaAColocar

	CaixaAColocar->InfoCaixa->LClientes->NClientes++; //incrementar o num de clientes na CaixaAColocar
	printf("Cliente[%d] de [%d] para [%d]\n",ClienteRetirar->InfoCliente->IDCliente ,CaixaARetirar->InfoCaixa->IDCaixa ,CaixaAColocar->InfoCaixa->IDCaixa);

}

/*
listarclientes:
Lista todos os clientes e seus ids numa lista de clientes
*/
void listarclientes(ListaClientes *LC){
	NoClientes *Aux = LC->ClienteTopo;
	int contar = 0;

	printf("\nListaCli:");
	
	while(Aux){
		printf(" Cliente[%d] C[%d]->",Aux->InfoCliente->IDCliente,contar++);
		Aux = Aux->ClienteSeguinte;
	}
	NOVALINHA;
	

}

/*
RetirarDaLoja:
Retira aleatoriamente um cliente da loja, para posteriormente colocar numa caixa
*/
NoClientes *RetirarDaLoja(Simulacao *Sim){
	//listarclientes(Sim->LClientesNaLoja);
	if(!Sim)
		return nullptr;
	if(Sim->LClientesNaLoja->NClientes == 0)  //se nao houver clientes, sair logo
		return nullptr;
	int R = 0;

	NoClientes *ret = Sim->LClientesNaLoja->ClienteTopo; //cliente a retornar
	NoClientes *Anterior;

	R = Randomizer(0,Sim->LClientesNaLoja->NClientes);
	printf("NumeroATirar [%d]\n", R);

	if( R == 0)
		return nullptr;

	if( R == 1){// se for o 1º cliente

		if(Sim->LClientesNaLoja->NClientes == 1){
			Sim->LClientesNaLoja->ClienteTopo = Sim->LClientesNaLoja->ClienteFim = nullptr;
		}

		else{
			Sim->LClientesNaLoja->ClienteTopo = Sim->LClientesNaLoja->ClienteTopo->ClienteSeguinte;
		}
	}

	else if( R == Sim->LClientesNaLoja->NClientes){ //se for o ultimo cliente

		Anterior = Sim->LClientesNaLoja->ClienteTopo;

		for (int i = 0; i < Sim->LClientesNaLoja->NClientes-2; i++){ //queremos chegar antes do ultimo cliente
			Anterior = Anterior->ClienteSeguinte;
		}
		ret = Sim->LClientesNaLoja->ClienteFim;
		Sim->LClientesNaLoja->ClienteFim = Anterior; //retiramos um cliente do fim
	}

	else//the bug was here
	{
		
		Anterior = Sim->LClientesNaLoja->ClienteTopo;
		for (int i = 0; i < R-1; i++){ //percorre a lista toda
			Anterior = ret;
			ret = ret->ClienteSeguinte;
		}

			Anterior->ClienteSeguinte=ret->ClienteSeguinte; //mantemos a ligacao na lista
	}
	
	Sim->LClientesNaLoja->NClientes--;

	return ret;
}

/*
PrintarClientezinho:
Escreve no ecra informacoes relativamente a um cliente
*/
void PrintarClientezinho(Simulacao *Sim, Cliente *Clientezinho) {

    if (!Clientezinho) return;
    int CTBanana = 0;

    printf("----------------------THE-CLIENT-BRIEFING------------------------------\n");
    printf("\tDados do Cliente %d:\n", Clientezinho->IDCliente);
    printf("\tNumero de produtos: %d\n", Clientezinho->NProdutos);
    for (int i = 0; i < Clientezinho->NProdutos; i++)
    {
        printf("\tCusto do Produto %d: %d\n",Sim->LProdutos[Clientezinho->LProdutos[i]].IDProduto, Sim->LProdutos[Clientezinho->LProdutos[i]].Preco );
        CTBanana = Sim->LProdutos[Clientezinho->LProdutos[i]].Preco + CTBanana;
    }
    printf("\tO custo total dos produtos e: %d\n", CTBanana);

}

/*
PrintarCaixazinha:
Escreve no ecra informacoes relativamente a uma Caixa
*/
void PrintarCaixazinha(Caixa *Caixinha) {
	NoClientes *Aux = Caixinha->LClientes->ClienteTopo;

    printf(" ----------------------------------ENTER-THE-CAIXA-BRIEFING-------------------------");
    printf("\n\tID da Caixa: %d", Caixinha->IDCaixa);
	printf("\n\tEstado da Caixa: %d", Caixinha->Activa);
	printf("\n\tN de Clientes: %d", Caixinha->LClientes->NClientes);
	printf("\n\tNome Operador: %s", Caixinha->NomeOperador);
    printf("\n\tNumero de produtos oferecidos: %d\n", Caixinha->NProdsOferecidos);
	printf("\n\tIDs de Cliente:");
	while(Aux){
		printf(" [%d],", Aux->InfoCliente->IDCliente);
		Aux = Aux->ClienteSeguinte;
	}
	NOVALINHA;
    printf(" ---------------------------------------------------------------------------------");
}

/*
EstadosCaixas:
Escreve no ecra informacoes relativamente ao estado de todas as caixas, -1 nao existe, 0 desactiva,1 activa
*/
void EstadosCaixas(Simulacao *Sim){
	for (int i = 0; i < Sim->Configuracoes->MAXCAIXAS; i++)
		printf("Caixa[%d] Estado[%d]\n",i+1,Sim->LCaixas->EstadoCaixas[i]);
}

/*
SelecionaCaixa:
Seleciona uma caixa dando o id e retorna o seu no
*/
NoCaixa *SelecionaCaixa(Simulacao *Sim, int IDCaixa){
	NoCaixa *EncontraCx = Sim->LCaixas->CaixaPrimeira;
	while (EncontraCx != nullptr && EncontraCx->InfoCaixa->IDCaixa != IDCaixa)
		EncontraCx = EncontraCx->CaixaSeguinte;
	return EncontraCx;

}

/*
ActivarCaixa:
Activa uma caixa
*/
void ActivarCaixa(Simulacao *Sim, int IDCaixa){
	NoCaixa *CaixaAux = SelecionaCaixa(Sim,IDCaixa);
	if(CaixaAux){
		CaixaAux->InfoCaixa->Activa = ACTIVA;
		CaixaAux->InfoCaixa->AdmitirClientes = ACTIVA;
		Sim->LCaixas->EstadoCaixas[IDCaixa-1] = ACTIVA;
	}
}

/*
TeclaPressionada:
Retorna true se uma tecla for pressionada
*/
bool TeclaPressionada()
{
	// foi necessario incluir #include <conio.h>
	return kbhit();
}

/*
Menu:
Printa as opcoes e le a opcao que o utilizador que r
*/
int Menu()
{
	int opcao;
	char c[10];
	do{
	NOVALINHA;
    printf("1 - Adicionar Caixa \n");
    printf("2 - Adicionar Cliente \n");
    printf("3 - Listar Produtos \n");
    printf("4 - Listar Caixa \n");
    printf("5 - Listar Cliente\n");
    printf("6 - Retirar Cliente\n");
    printf("7 - Activar Caixa\n");
    printf("8 - Desactivar Caixa\n");
    printf("9 - EscreverFileHistorico\n");
    printf("10 - Caixa que Mais Vendeu\n"); 
	printf("11 - Caixa que Mais Atendeu\n"); 
	printf("12 - Operador que Menos Atendeu\n"); 
    printf("99 - Sair Do Programa\n");
	printf("0 - Sair do Menu\n");
     
    printf("Qual a Opcao: ");
	fflush(stdin);			//Limpar o buffer
	
	scanf("%s", c);
	}while (!isdigit(c[0]));
	opcao = atoi(c);
    return opcao;
	
}

/*
SomarClientes:
percorrer as caixas todas e somar o nclientes nelas, retorna o total
*/
int SomarClientes(Simulacao *Sim){
	if(!Sim->LCaixas->CaixaPrimeira)
		return 0;
	nocaixa *aux = nullptr;
	int TotalCli = 0;

	aux = Sim->LCaixas->CaixaPrimeira;

	while (aux)
	{
		if(aux->InfoCaixa->Activa)
			TotalCli += aux->InfoCaixa->LClientes->NClientes;
		aux = aux->CaixaSeguinte;
	}
	return TotalCli;
}

/*
PrintStatus:
Print do estado actual da simulacao
*/
void PrintStatus(Simulacao *Sim){
	int i = 0;

		NOVALINHA;
	_3;	for(i=0;i<15;i++)_5;			_6;	for(i=0;i<23;i++)_5;										_6;		for(i=0;i<23;i++)_5;				_1;
		NOVALINHA;
	_7;	printf("M - Abre MENU");TABTAB;	_7;printf("N. Caixas Activas: %d",Sim->LCaixas->NCaixas); TABTAB;_7;printf("TempoDecorrido: %d",clock());TABTAB;_7;
		NOVALINHA;			
	_10;	for(i=0;i<15;i++)_5;			_11;	for(i=0;i<23;i++)_5;										_11;		for(i=0;i<23;i++)_5;				_9;
		NOVALINHA;

	_7;	_12;_12;_12;_12;_12;_12;_12;_12;_12;_12;_12;_12;_12;_12;TABTAB;	_7;printf("Clientes em Fila: %d",SomarClientes(Sim)); TABTAB;_7;printf("Clientes em Loja: %d",Sim->LClientesNaLoja->NClientes);TABTAB;_7;
			NOVALINHA;
	_4;	for(i=0;i<15;i++)_5;			_8;	for(i=0;i<23;i++)_5;										_8;		for(i=0;i<23;i++)_5;				_2;
		NOVALINHA;

		//listarclientes(Sim->LClientesNaLoja);
		//printf("Pool : %d ",Sim->LClientesNaLoja->NClientes);
	
	
}

/*
AtenderCliente:
Atende um cliente, fazendo os respectivos calculos
*/
void AtenderCliente(Simulacao *Sim, Caixa *Caixinha, Cliente *Clientezinho){
	Caixinha->ClientesAtendidos++;
	int TotalPreco = 0;
	for (int i = 0; i < Clientezinho->NProdutos; i++)
		TotalPreco += Sim->LProdutos[Clientezinho->LProdutos[i]].Preco;
	//printf("%d money got\n",TotalPreco);
	Caixinha->DinheiroGanho += TotalPreco;  
	Caixinha->ProdutosVendidos += Clientezinho->NProdutos;

}

/*
AtenderCaixas:
Percorre as caixas todas e atende um cliente em cada
*/
void AtenderCaixas(Simulacao *Sim){//feito num 2 cavalos a caminho das aulas
	NoCaixa *auxCaixa = Sim->LCaixas->CaixaPrimeira;
	NoClientes *auxNoCliente;
	while (auxCaixa)
	{
		if(auxCaixa->InfoCaixa->LClientes->NClientes > 0){
			if( auxCaixa->InfoCaixa->Activa == ACTIVA){
			
				auxNoCliente = auxCaixa->InfoCaixa->LClientes->ClienteTopo; //para depois fazer free
				printf("A Atender Caixa[%d]\n",auxCaixa->InfoCaixa->IDCaixa);

				if(auxNoCliente == auxCaixa->InfoCaixa->LClientes->ClienteFim)//se for o ultimo cliente 
					auxCaixa->InfoCaixa->LClientes->ClienteTopo = auxCaixa->InfoCaixa->LClientes->ClienteFim = nullptr;//por o Topo e o Fim a null
				else
					auxCaixa->InfoCaixa->LClientes->ClienteTopo = auxCaixa->InfoCaixa->LClientes->ClienteTopo->ClienteSeguinte;//mover a fila
				
				auxCaixa->InfoCaixa->LClientes->NClientes--;//decrementar o num de clientes na caixa
				AtenderCliente(Sim, auxCaixa->InfoCaixa, auxNoCliente->InfoCliente);
				
				AdicClienteFim(auxCaixa->InfoCaixa->LCatendidos,auxNoCliente);
				auxCaixa->InfoCaixa->LCatendidos->NClientes++;
				/*				
				LibertarCliente(auxNoCliente->InfoCliente);
				LibertarNOCliente(auxNoCliente);
				*/
				if(auxCaixa->InfoCaixa->AdmitirClientes == DESACTIVA && auxCaixa->InfoCaixa->LClientes->NClientes == 0){ //verificar se a caixa esta para fechar
					auxCaixa->InfoCaixa->Activa = DESACTIVA;
					Sim->LCaixas->EstadoCaixas[auxCaixa->InfoCaixa->IDCaixa-1] = DESACTIVA;
				}

			}
		}
		
		auxCaixa = auxCaixa->CaixaSeguinte; //Next Caixa
	}
}

/*
AnalisarOfertas:
Analise se ja passou tempo de espera admissivel por cada cliente nas filas, caso isso acontece um produto e removido do cliente
*/
void AnalisarOfertas(Simulacao *Sim){
	NoCaixa *CaixaAux = Sim->LCaixas->CaixaPrimeira;
	NoClientes *CliAux = nullptr;
	int r=0;
	for (int i = 0; i < Sim->LCaixas->NCaixas; i++)
	{
		if(CaixaAux)//se existe caixa
		{
			if(CaixaAux->InfoCaixa->Activa && CaixaAux->InfoCaixa->LClientes->NClientes > 0) //se for activa e tiver clientes
			{
				CliAux = CaixaAux->InfoCaixa->LClientes->ClienteTopo;

				for (int j = 0; j < CaixaAux->InfoCaixa->LClientes->NClientes; j++)
				{
					if(!CliAux->InfoCliente->ProdutoDescontado) // se nao foi descontado anda nenhum produto
					{
						if(time(NULL) - CliAux->InfoCliente->TempoEntrada > 300) // se ja passou o tempo de espera 5mins
						{
							printf("A Descontar Produto, Cli [%d], Caixa [%d]\n",CliAux->InfoCliente->IDCliente,CaixaAux->InfoCaixa->IDCaixa);
							r = Randomizer(0, CliAux->InfoCliente->NProdutos-1);
							CaixaAux->InfoCaixa->DinheiroPerdido += Sim->LProdutos[CliAux->InfoCliente->LProdutos[r]].Preco;
							CaixaAux->InfoCaixa->NProdsOferecidos++;
							
							CliAux->InfoCliente->LProdutos[r] = 0;
							CliAux->InfoCliente->NProdutos--;
							CliAux->InfoCliente->ProdutoDescontado = true;
						}
					}
					CliAux = CliAux->ClienteSeguinte;
				}
			}
		}
		CaixaAux = CaixaAux->CaixaSeguinte;
	}
}

/*
MenorClientes:
retorna a Caixa com menos clientes
*/
Caixa *MenorClientes(Simulacao *Sim){
	NoCaixa *Aux = nullptr;
	Caixa *MenorCaixa = nullptr;
	int MenoRClientes;
	Aux = Sim->LCaixas->CaixaPrimeira;
	if(!Aux)
		return nullptr;
	
	MenoRClientes = Aux->InfoCaixa->LClientes->NClientes;

	while (Aux != nullptr)
	{
		if(Aux->InfoCaixa->Activa && Aux->InfoCaixa->LClientes->NClientes <= MenoRClientes){
			MenorCaixa = Aux->InfoCaixa;
			MenoRClientes = Aux->InfoCaixa->LClientes->NClientes;
		}

		Aux = Aux->CaixaSeguinte;
	}

	return MenorCaixa;
}

/*
DespacharCliente:
Coloca um cliente na caixa com menoos clientes
*/
int DespacharCliente(Simulacao *Sim, NoClientes *ClienteDespach){
	if(!ClienteDespach){
		return 0;
	}

	Caixa *CaixaSelec = MenorClientes(Sim);//procurar a caixa com menos clientes 
	if(!CaixaSelec) // se nao encontrar sai da funcao
		return 0;

	AdicClienteFim(CaixaSelec->LClientes,ClienteDespach);
	CaixaSelec->LClientes->NClientes = CaixaSelec->LClientes->NClientes+1;
	printf("\nCliente[%d] Adicionado a Caixa[%d]\n",ClienteDespach->InfoCliente->IDCliente, CaixaSelec->IDCaixa);
	return 1;
}

/*
DesActivarCaixa:
Desactiva uma caixa e recoloca os clientes todos noutra (caso existam)
*/
void DesActivarCaixa(Simulacao *Sim, int IDCaixa){

	NoCaixa *CaixaAux = SelecionaCaixa(Sim,IDCaixa); //procurar a caixa
	if(CaixaAux){//Se foi encontrada, definir la como desactivada
		CaixaAux->InfoCaixa->Activa = DESACTIVA; 
		Sim->LCaixas->EstadoCaixas[IDCaixa-1] = DESACTIVA;
		if(CaixaAux->InfoCaixa->LClientes->NClientes > 0){//se tiver clientes colocar noutras caixas
			
			NoClientes *CliAux = CaixaAux->InfoCaixa->LClientes->ClienteTopo;
			NoClientes *CliAux2 =nullptr;
			
			while (CliAux)//enquanto tiver clientes
			{
				CliAux2 = CliAux->ClienteSeguinte;
				DespacharCliente(Sim,CliAux);
				CliAux = CliAux2;
			}
			CaixaAux->InfoCaixa->LClientes->ClienteTopo = CaixaAux->InfoCaixa->LClientes->ClienteFim = nullptr;
			CaixaAux->InfoCaixa->LClientes->NClientes = 0;
		}
	}
}

/*
EncherHistorico:
Prencher a estrutura historico com informacao
*/
void EncherHistorico(Simulacao *Sim){
	Historico *hist = Sim->StructHistorico;
	hist->TempoSim = clock();
	nocaixa *aux = Sim->LCaixas->CaixaPrimeira;
	while (aux)
	{
		hist->NClientesAtendidos += aux->InfoCaixa->ClientesAtendidos;
		hist->NProdsVendds += aux->InfoCaixa->ProdutosVendidos;
		///hist->TempoMedioEspera += aux->InfoCaixa->TMedioEsp;
		hist->TotalDinheiroRecebido += aux->InfoCaixa->DinheiroGanho;
		hist->TotalDinheiroPerdido += aux->InfoCaixa->DinheiroPerdido;
		hist->NProdsOfer += aux->InfoCaixa->NProdsOferecidos;
		aux = aux->CaixaSeguinte;
	}

}

/*
EscreverFileHistorico:
Escrever o ficheiro com o historico e algumas estatisticas
*/
void EscreverFileHistorico(Simulacao *Sim){
	Historico *hist = Sim->StructHistorico;
	char buffer[MAXPALAVRA],nome[MAXPALAVRA], x;
	int i = 0;
	printf("Nome do ficheiro para guardar o historico: ");
	
	do {
		fflush(stdin);			//Limpar o buffer
		while (i < MAXPALAVRA-4)
		{
			buffer[i] = getchar();	//le o char introduzido no ecra
			if (buffer[0] == '\n')break; // nao queremos strings vazias, nem que passem para a proxima linha
			if (buffer[i] == '\n'){// assim que chegar a um \n colocar um fim de string
				buffer[i] = '\0';
				break;
			}
			i++;
		}
	} while (buffer[0] == '\n');  // nao queremos strings vazias, nem que passem para a proxima linha

	//printf("\nLIDO[%s],",buffer);
	strcat(buffer,".csv");
	//printf("CAT[%s]\n",buffer);
	strcpy(nome,"..\\");
	strcat(nome,buffer);
	//printf("nome[%s]\n",nome);
	time_t basf = hist->TempoInicio;
	
	FILE *f = fopen(nome, "w"); //criar o ficheiro onde escrever a matriz
	if (f){ //se conseguir criar o ficheiro
		fprintf(f, TITULO);
		fprintf(f, "Ficheiro de Historico\n");
		fprintf(f, "Simul. Iniciada : ");
		fprintf(f,ctime(&basf));
		fprintf(f, "Clientes Atendidos : %d\n",hist->NClientesAtendidos);
		fprintf(f, "Tempo Medio De Espera : %d\n",hist->TempoMedioEspera);
		fprintf(f, "N. Prods. Vendidos : %d\n",hist->NProdsVendds);
		fprintf(f, "Dinheiro Recebido : %d\n",hist->TotalDinheiroRecebido);
		fprintf(f, "N. Prods. Oferecidos : %d\n",hist->NProdsOfer);
		fprintf(f, "Dinheiro Perdido : %d\n",hist->TotalDinheiroPerdido);		
		fclose(f);
	}
	else{
		printf("*********************\nERRO DE ESCRITA1!!!!\n*****************************************\n"); 
		getch();
	}
}

/*
SelecionaCliente:
Seleciona uma cliente, retornando o seu no
*/
NoClientes *SelecionaCliente(Simulacao *Sim, int IDCaixa, int IDCliente){
	NoClientes *EncontraCl;
	NoCaixa *EncontraCx = SelecionaCaixa(Sim,IDCaixa);
	if(!EncontraCx) return nullptr;
	EncontraCl = EncontraCx->InfoCaixa->LClientes->ClienteTopo;

	while (EncontraCl != nullptr && EncontraCl->InfoCliente->IDCliente != IDCliente)
		EncontraCl = EncontraCl->ClienteSeguinte;

	return EncontraCl;
}

/*
VerificarMinClientes:
Verifica se ha um minimo admissivel de clientes para ter x caixas abertas, caso contrario fecha
*/
void VerificarMinClientes(Simulacao *Sim){
	int TotalCli = SomarClientes(Sim),
		TotalActiv = 0;

	for (int i = 0; i < Sim->Configuracoes->MAXCAIXAS; i++)
	{
		if(Sim->LCaixas->EstadoCaixas[i] == 1)
			TotalActiv++;
	}

	if(TotalActiv > 2 && TotalCli/TotalActiv < 12){
		Caixa *Aux = MenorClientes(Sim);
		if(Aux){
			Aux->AdmitirClientes = DESACTIVA;
		}

	}

	
}

/*
VerificarMaxEspera:
Verifica se ha um maximo admissivel de clientes em fila entao abre outra caixa
*/
void VerificarMaxEspera(Simulacao *Sim){
	nocaixa *aux = nullptr;
	int id = 0;
	printf("Em Ver.MAXESPERA  ");
	if(Sim->LCaixas->CaixaPrimeira){
		aux = Sim->LCaixas->CaixaPrimeira;
		while (aux)
		{
			if(aux->InfoCaixa->Activa && aux->InfoCaixa->LClientes->NClientes > Sim->Configuracoes->MAXESPERA){ //se tiver clientes a mais
				for (int i = 0; i < Sim->Configuracoes->MAXCAIXAS; i++)//procura caixas, que existam mas estejas desactivadas
				{
					if(Sim->LCaixas->EstadoCaixas[i] == 0){
						id = i+1; //copiar o id de uma caixa que ja exista mas esteja desactivada
						break; // sair logo se for activar
					}
				}

				if(id != 0){
					ActivarCaixa(Sim,id);//se encontrar, activar a caixa
					printf("Caixa com Clientes a +, a Activar [%d]",id);
				}
				else{
					AdicionarCaixa(Sim,NULL,ACTIVA);
					printf("Caixa com Clientes a +, a AdicionarCaixa");
				}
				break; //para nao adicionar + que 1 caixa num ciclo
			}
			aux = aux->CaixaSeguinte;
		}
	}
}

/*
CaixaMaisAtendeu:
Qual foi a caixa que atendeu mais clientes
*/
void CaixaMaisAtendeu(Simulacao *Sim){
	nocaixa *aux = nullptr;
	if(!Sim->LCaixas->CaixaPrimeira)
		return;
	aux = Sim->LCaixas->CaixaPrimeira;
	int MaisCli = 0;
	int ID = 0;
	
	while (aux)
	{
		if(MaisCli < aux-> InfoCaixa->ClientesAtendidos){
			MaisCli = aux-> InfoCaixa->ClientesAtendidos;
			ID = aux-> InfoCaixa->IDCaixa;
		}
		aux = aux ->CaixaSeguinte;
	}	
	if(ID !=0){
		printf("\n A Caixa que atendeu mais foi [%d] com [%d] clientes\n",ID, MaisCli);
	}
	else
		printf("\n Nao encontrado\n");
}

/*
CaixaMaisVendeu:
Qual foi a caixa que mais vendeu
*/
void CaixaMaisVendeu(Simulacao *Sim){
	nocaixa *aux = nullptr;
	if(!Sim->LCaixas->CaixaPrimeira)
		return;
	aux = Sim->LCaixas->CaixaPrimeira;
	int MaisVendeu = 0;
	int ID = 0;
	
	while (aux)
	{
		if(MaisVendeu < aux-> InfoCaixa->ProdutosVendidos){
			MaisVendeu = aux-> InfoCaixa->ProdutosVendidos;
			ID = aux-> InfoCaixa->IDCaixa;
		}
		aux = aux ->CaixaSeguinte;
	}	
	if(ID !=0){
		printf("\n A Caixa que vendeu mais foi [%d] com [%d] BitCoins\n",ID, MaisVendeu);
	}
	else
		printf("\n Nao encontrado\n");
}

/*
MaisPreguicoso:
Qual foi o operador que menos clientes atendeu
*/
void MaisPreguicoso(Simulacao *Sim){
	nocaixa *aux = nullptr;
	if(!Sim->LCaixas->CaixaPrimeira){
		printf("Nao ha caixas!\n");
		return;
	}
	aux = Sim->LCaixas->CaixaPrimeira;
	int MenosAtendeu = aux->InfoCaixa->ClientesAtendidos;
	int ID = aux->InfoCaixa->IDCaixa;
	
	while (aux)
	{
		if(MenosAtendeu > aux->InfoCaixa->ClientesAtendidos){
			MenosAtendeu = aux->InfoCaixa->ClientesAtendidos;
			ID = aux-> InfoCaixa->IDCaixa;
		}
		aux = aux ->CaixaSeguinte;
	}	
	if(ID != 0){
		aux = SelecionaCaixa(Sim,ID);
		printf("\n O que atendeu menos clientes foi [%s] com [%d] Clientes\n",aux->InfoCaixa->NomeOperador, MenosAtendeu);
	}
	else
		printf("\n Nao encontrado\n");
}

/*
ExecutarEvento:
Verifica se ja passou um periodo desde o ultimo evento e executa-o
*/
void ExecutarEvento(Simulacao *Sim, int *TempoPrintEcra, int *TempoEscritaDados,
					int *TempoPassadoAddCli, int *TempoPassadoRemCli, int *TempoPassadoAnalisarOferta, int *TempoPassadoAtender,
					int *TempoVerMaxEspera, int *TempoVerMinCLientes ){

	if(clock() - *TempoPrintEcra > PeriodoMostrarMenu){ //mostrar o menu a cada segundo
			//system("cls"); //limpar o ecra 
			PrintStatus(Sim);
			*TempoPrintEcra=clock();
	}

	if( clock() - *TempoEscritaDados > TEMPOACTUALIZACAO){ //Periodo de escrita para o ficheiro
			EscreverFileDados(Sim);
			*TempoEscritaDados = clock();
	}

	if( clock() - *TempoPassadoRemCli > PeriodoRetiraCliente){	//retira um cliente da loja e se NAO foi colocado numa caixa fazer print.
		if( !DespacharCliente(Sim,RetirarDaLoja(Sim)) ) 
			printf("!! Cliente NAO Despachado\n");
		*TempoPassadoRemCli = clock();
	}

	if( clock() - *TempoPassadoAddCli > PeriodoColocaCliente){//coloca cliente na loja
		AdicionarClienteLoja(Sim);
		printf("Cliente Adicionado a Loja\n");
		*TempoPassadoAddCli = clock();
	}
	if( clock() - *TempoPassadoAnalisarOferta > PeriodoAnalisarOferta){//coloca cliente na loja
		AnalisarOfertas(Sim);
		printf("Ofertas Analisadas\n");
		*TempoPassadoAnalisarOferta = clock();
	}

	if(clock() - *TempoVerMaxEspera > PeriodoVerMaxEspera){ // verifica se estao clientes a mais numa caixa
		VerificarMaxEspera(Sim);
		*TempoVerMaxEspera = clock();
	}
	if(clock() - *TempoVerMinCLientes > PeriodoVerMinClientes){ //verifica se estao caixas a mais para o n de clientes_questao 7
		VerificarMinClientes(Sim);
		*TempoVerMinCLientes = clock();
	}

	if( clock() - *TempoPassadoAtender > PeriodoAtender){
		AtenderCaixas(Sim);
		printf("Caixas Atendidas\n");
		*TempoPassadoAtender = clock();
	}

}

/*
SwitchMenu:
Executa a opcao selecionada em Menu();
*/
bool SwitchMenu(Simulacao *Sim,int opcao){
	char c[10], buffer[MAXPALAVRA],buffer2[MAXPALAVRA];
	int subopc1 = 0,subopc2 = 0;
	switch (opcao)
	{
		case 99:{
			EscreverFileInter("SairPrograma");
			return 1;
				}
		case 1:{//add caixa
			EstadosCaixas(Sim);
			do{
				printf("ID Caixa: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c);

			if(subopc1 > Sim->Configuracoes->MAXCAIXAS){
				printf("Valor invalido\n");
				break;
			}

			if(Sim->LCaixas->EstadoCaixas[subopc1-1] == -1)
				AdicionarCaixa(Sim,subopc1,ACTIVA);
			else{
				printf("Caixa ja existe\n");
				if(Sim->LCaixas->EstadoCaixas[subopc1-1] == 0){
					printf("Deseja activar caixa [%d]?[S/N]\n->",subopc1);
					fflush(stdin);			//Limpar o buffer
					char key = getch();
					putchar(key);
					if(key == 'S' || key == 's')
						ActivarCaixa(Sim,subopc1);
				}
			}
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"AdicionarCaixa");
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);
			getch();
			break;
			   }

		case 2:{// add cliente
			EstadosCaixas(Sim);
			do{
				printf("ID Caixa: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c);
			if(subopc1 > Sim->Configuracoes->MAXCAIXAS || subopc1 < 1)
				break;
			if(Sim->LCaixas->EstadoCaixas[subopc1-1] == 1)
				AdicionarCliente(Sim,subopc1,Randomizer(1,MAXProdsCliente),NULL);
			else
				printf("Caixa desactivada ou inexistente\n");
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"AdicionarCliente_Cx");
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);	
			getch();

			break;
			   }

		case 3:{// Listar Prods
			printf("Catalogo de Produtos, Disponivel em www.Continente.pt\n");
			for (int i = 0; i < MAXProds; i++)
			{
				printf("ID Prod [%d]\tPreco [%d]\tTempo Atend. [%d]\n",Sim->LProdutos[i].IDProduto,Sim->LProdutos[i].Preco,Sim->LProdutos[i].TempoProduto);
			}
			EscreverFileInter("ListarProdutos");
			getch();
			break;
			   }

		case 4:{//Listar Caixa
			EstadosCaixas(Sim);
			do{
				printf("Id. Caixa: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c);
			NoCaixa *NoCxTemp = SelecionaCaixa(Sim,subopc1);
			if(NoCxTemp)
				PrintarCaixazinha(NoCxTemp->InfoCaixa);
			else
				printf("\nCaixa nao Encontrado...");	
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"ListarCaixa");
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);
			getch();
			break;
			   }

		case 5:{//Listar Cliente

			do{
				printf("Id. Cliente: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c); // id do cliente
		
			NoClientes *NoCliTemp = nullptr;
			for (int i = 0; i < Sim->Configuracoes->MAXCAIXAS; i++)
			{
				NoCliTemp = SelecionaCliente(Sim,i+1,subopc1);
				if(NoCliTemp) break;
			}
			if(NoCliTemp)
				PrintarClientezinho(Sim, NoCliTemp->InfoCliente);
			else 
				printf("\nCliente nao Encontrado...");
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"ListarCliente");
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);
			getch();
			break;
			   }

		case 6:{//RetirarCliente
			EstadosCaixas(Sim);
			do{
				printf("Id. Caixa a Tirar: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c);
			do{
				printf("Id. Caixa a Colocar: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			int subopc3 = atoi(c);
			do{
				printf("Id. Cliente: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc2 = atoi(c); // id do cliente
			RetirarCliente(Sim,subopc1,subopc2,subopc3);
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"RetirarCliente_");
			strcat(buffer2,buffer);
			strcat(buffer2,"_");
			itoa(subopc2,buffer,10);
			strcat(buffer2,buffer);
			strcat(buffer2,"_");
			itoa(subopc3,buffer,10);
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);
			break;
			}
		case 7:{//Activar Caixa
			EstadosCaixas(Sim);
			do{
				printf("ID Caixa: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c);
			if(subopc1 > Sim->Configuracoes->MAXCAIXAS || subopc1 < 1)
				break;
			if(Sim->LCaixas->EstadoCaixas[subopc1-1] == -1)//se a caixa ainda nao existir
				printf("Caixa inexistente...\n");
			else{
				if(Sim->LCaixas->EstadoCaixas[subopc1-1] == 1)
					printf("Caixa ja activa...\n");
				else{
					printf("Deseja activar caixa [%d]?\n[S/N]\n->",subopc1);
					fflush(stdin);			//Limpar o buffer
					char key = getch();
					putchar(key);
					if(key == 'S' || key == 's')
						ActivarCaixa(Sim,subopc1);
				}
			}
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"ActivarCaixa");
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);
			getch();
			break;
			   }

		case 8:{//DesActivar Caixa
			EstadosCaixas(Sim);
			do{
				printf("ID Caixa: ");
				scanf("%s",c);
			}while (!isdigit(c[0]));
			subopc1 = atoi(c);
			if(subopc1 > Sim->Configuracoes->MAXCAIXAS || subopc1 < 1)
				break;
			if(Sim->LCaixas->EstadoCaixas[subopc1-1] == -1)//se a caixa ainda nao existir
				printf("Caixa inexistente...\n");
			else{
				if(Sim->LCaixas->EstadoCaixas[subopc1-1] == 0)
					printf("Caixa ja Desactivada...\n");
				else{
					printf("Deseja Desactivar caixa [%d]?[S/N]\n->",subopc1);
					fflush(stdin);			//Limpar o buffer
					char key = getch();
					putchar(key);
					if(key == 'S' || key == 's')
						DesActivarCaixa(Sim,subopc1);
				}
			}
			itoa(subopc1,buffer,10);
			strcpy(buffer2,"DesActivarCaixa");
			strcat(buffer2,buffer);
			EscreverFileInter(buffer2);
			getch();
			break;
			   }

		case 9:{//EscreverFileHistorico
			EscreverFileHistorico(Sim);
			EscreverFileInter("EscreverFileHistorico");
			break;
			   }

		case 10:{//CaixaMaisVendeu
			CaixaMaisVendeu(Sim);
			EscreverFileInter("CaixaMaisVendeu");
			break;
			   }

		case 11:{//CaixaMaisAtendeu
			CaixaMaisAtendeu(Sim);
			EscreverFileInter("CaixaMaisAtendeu");
			break;
			   }
		case 12:{//MaisPreguicoso
			MaisPreguicoso(Sim);
			EscreverFileInter("MaisPreguicoso");
			break;
			   }

		default:
			break;
	}
	return 0;
}

/*
checkbug:
Havia um bug, esta funcao ajudou a encontrar o que acontecia
*/
void checkbug(Simulacao *Sim){
	NoCaixa *Aux = nullptr; 
	NoClientes *AuxCli = nullptr;
	//printf("CheckingBug...");
	for (int i = 0; i < Sim->Configuracoes->MAXCAIXAS; i++)
	{
		Aux = SelecionaCaixa(Sim,i+1);
		if(Aux){
			AuxCli = Aux->InfoCaixa->LClientes->ClienteTopo;
			while(Aux->InfoCaixa->LClientes->ClienteFim != AuxCli){
				if(AuxCli)
					AuxCli = AuxCli->ClienteSeguinte;
				else
					break;
			}
			if(AuxCli && AuxCli->ClienteSeguinte){
				printf("!!!!!!!!!!!!!!BUG ALERT!!_Caixa[%d]_!!!!",Aux->InfoCaixa->IDCaixa);
				getch();
			}

		}
	}
	//printf("NoBug\n");
}

//-----------------------------
/*
FSimulacao:
Funcao principal da simulacao
*/
int FSimulacao(Simulacao *Sim){
	if(!Sim) return 0;
	int opcao,
		TempoPrintEcra = 0,		//Tempo Passado desde a ultima vez que foi mostrado o Menu
		TempoEscritaDados = 0,	//Tempo Passado desde a ultima vez que foi escrito o Dados.TXT
		TempoPassadoAddCli = 0,	//Tempo Passado desde a ultima vez que foi Adicionado um Cliente a loja
		TempoPassadoRemCli = 0,	//Tempo Passado desde a ultima vez que foi Retirado um Cliente da Loja
		TempoPassadoAnalisarOferta = 0, //Tempo Passado desde a ultima Analise de Ofertas
		TempoPassadoAtender = 0, //Tempo Passado desde o ultima atendimento
		TempoVerMaxEspera = 0,	//Tempo passado para verificar se ha clientes a mais numa caixa
		TempoVerMinCLientes = 0, //Tempo passado para verificar se ha demasiadas Caixas
		TempoCicloInicio=0,		//Quando iniciou o Ciclo
		TempoCicloFim = 0,		//Quando terminou o Ciclo
		TempoWait = 0;			//Diferenca entre TempoCicloFim e TempoCicloInicio, se for <=500 é usado para por o programa em pausa

	bool Simular = true;
	char key;
	//Here stays nice Intro Screen :3
	
	LerDados(Sim);

	while (Simular)
	{
		TempoCicloInicio = clock();

		if(TeclaPressionada()){
			key = getch();
			fflush(stdin);			//Limpar o buffer
			if(key == 'M' || key == 'm'){
				
				opcao = Menu();//mostrar menu e ler opcao
				
				if(SwitchMenu(Sim,opcao))
					Simular = false; //se for 1, a opcao 0 foi selecionada,sair do loop
				
				if(!Simular) break;
			}
		}
				
		ExecutarEvento(Sim, &TempoPrintEcra, &TempoEscritaDados,
			&TempoPassadoAddCli, &TempoPassadoRemCli, &TempoPassadoAnalisarOferta, &TempoPassadoAtender,
			&TempoVerMaxEspera, &TempoVerMinCLientes );

		//checkbug(Sim);

		//Calcular Se deve esperar ou nao, caso ja tenha passado 500ms desde o ultimo ciclo
		TempoCicloFim = clock();
		TempoWait = TempoCicloFim - TempoCicloInicio;
		
		//printf("Passaram %dms\n",tempWait);
		if(TempoWait < 500 && TempoWait > 0){
			
			//printf("A esperar %dms\n",tempWait);
			wait(TempoWait);
		}
	}
	printf("\nA terminar a Simulacao");
	return 1;
}
//-----------------------------

void main (int argc, char *argv[]){
	printf(TITULO);
	Simulacao *Sim = CriarSimulacao();
	
	if( !FSimulacao(Sim)){
		printf("\n Saiu da simulacao com erro!!!!!");
		getch();
	}
	LimparALoja(Sim); //desalocar tudo
}



/*
NoClientes *RetirarDaLojaOLD(Simulacao *Sim){
	
	if(!Sim)
		return nullptr;
	if(Sim->LClientesNaLoja->NClientes == 0)  //se nao houver clientes, sair logo
		return nullptr;

	int NumeroRetirar = Randomizer(0, Sim->LClientesNaLoja->NClientes);
	NoClientes *Retirar = Sim->LClientesNaLoja->ClienteTopo; //seleciona o 1º cliente naloja
	NoClientes *Aux = nullptr;
	int j=0;
	while (j < NumeroRetirar-1)
	{
		Aux = Retirar;
		Retirar = Retirar->ClienteSeguinte;
		j++;
	}

	if(Aux!=nullptr){
		Aux->ClienteSeguinte=Retirar->ClienteSeguinte;
	}
	//
	for (int i = 0; i < NumeroRetirar; i++){//percorre a lista de clientes ate chegar ao n-esimo cliente
		Aux = Retirar;
		if(i+1 < NumeroRetirar)
			Retirar = Retirar->ClienteSeguinte;
	}

	
	if(!Aux)//se for null, quer dizer que nem entrou no FOR e que esta no topo da lista
		Sim->LClientesNaLoja->ClienteTopo = Retirar->ClienteSeguinte;
	else//caso contrario mantem o estrutura da lista
		Aux->ClienteSeguinte = Retirar->ClienteSeguinte;
	//
	if(Retirar){
		Sim->LClientesNaLoja->NClientes--;
		//Retirar->ClienteSeguinte=nullptr;
	}
	return Retirar;
}
*/

	/*
	#ifdef DEBUG
	for (int i = 0; i < 25; i++)
	{
		printf("ID = %d ; Preco = %d ;\n",Sim->LProdutos[i].IDProduto ,Sim->LProdutos[i].Preco);
	}

	#endif // DEBUG
	*/
	/*
	AdicionarCaixa(Sim, 1, ACTIVA);
	AdicionarCliente(Sim, 1, 5, NULL);
	AdicionarCliente(Sim, 1, 6, NULL);
	AdicionarCliente(Sim, 1, 5, NULL);
	AdicionarCliente(Sim, 1, 6, NULL);

	AdicionarCaixa(Sim, 2, ACTIVA);
	AdicionarCliente(Sim, 2, 5, NULL);
	AdicionarCliente(Sim, 2, 6, NULL);
	AdicionarCliente(Sim, 2, 3, NULL);

	AdicionarCaixa(Sim, 3, ACTIVA);
	AdicionarCliente(Sim, 3, 4, NULL);
	AdicionarCliente(Sim, 3, 3, NULL);
	CagarCaixazinha(Sim->LCaixas->CaixaPrimeira->InfoCaixa);
	CagarClientezinho(Sim->LCaixas->CaixaPrimeira->InfoCaixa->LClientes->ClienteTopo->InfoCliente);
	*/
	/*
	LerDados(Sim);

	//getch();
	
	//RetirarCaixa(Sim,2);
	
	//RetirarCliente(Sim->LCaixas->CaixaPrimeira->InfoCaixa->LClientes, 2);
	
	EscreverFileDados(Sim);*/
	/*
int QuantosClientes(Simulacao *Sim,int IDCaixa){
	if(!Sim||!IDCaixa)
		return NULL;
	
	NoCaixa *Caixinha = Sim->LCaixas->CaixaPrimeira; //Criamos uma caixinha temporaria
	while (Caixinha->InfoCaixa->IDCaixa != IDCaixa)
	{
		if (Caixinha->CaixaSeguinte == nullptr)
		{
			printf("Caixa Nao Encontrada"); //Andas a inventar caixas?
			return NULL;
		}
		Caixinha = Caixinha->CaixaSeguinte;
	}
	
	if(Caixinha->InfoCaixa->LClientes->ClienteTopo == Caixinha->InfoCaixa->LClientes->ClienteFim){ //Neh se o 1º é igual ao ultimo é porque so ha 1
		return 1;
	}
	
	NoClientes *Clientezinho = Caixinha->InfoCaixa->LClientes->ClienteTopo; // E um Clientezinho temporario
	int TotalClientes = 0;
	while (Clientezinho != nullptr)
	{
		TotalClientes++;
		Clientezinho = Clientezinho->ClienteSeguinte;
	}
	return TotalClientes;
}
*/

/*void RetirarCaixa(Simulacao *Sim,int IDCaixa){
	if(!Sim)
		return;
	NoCaixa *CaixaRetirar = Sim->LCaixas->CaixaPrimeira;
	NoCaixa *Aux;
	while (CaixaRetirar != nullptr && CaixaRetirar->InfoCaixa->IDCaixa != IDCaixa) //enquanto houver caixas e o id nao corresponder
	{
		Aux = CaixaRetirar;
		CaixaRetirar = CaixaRetirar->CaixaSeguinte;
	}
	if(!CaixaRetirar) return; //Caixa nao encontrada
	
	Aux->CaixaSeguinte = CaixaRetirar->CaixaSeguinte;
	LibertarNoCaixa(CaixaRetirar); //Limpar a caixa antiga da memoria
	Sim->LCaixas->NCaixas--; //decrementar o num -de caixas
	
}*/

/*


*/
/*
void calcularTMedio(caixa* Caixinha,int TempoEntrada){
	//Media * ncliAtendidos = R
	// R + nova val = R
	//R / ncliAtendidos +1 = r

}
*/