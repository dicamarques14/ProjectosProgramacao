#include "GestaoTudo.h"


GestaoTudo::GestaoTudo(void)
{
	cout << "OLA GESTOR"<< endl;
	list_utilizador = new list<Utilizador *>();
	list_Tiro = new list<Tiro *>();
	NTiros = 0;
	nivelActual = 1;
	TirosNoEcra = 0;
	EstadoDoJogo = 0;
	NivelObj = NULL;
	NUtilizadores = 0;
	list_Niveis = new list<Nivelzinho *>();
	LerFicheiroNiveis();
	cout << "Gestor Morgado Pronto"<<endl;
}

GestaoTudo::~GestaoTudo(void)
{
	
	DestruirUtilizadores();//apagar a lista de utilizadores
    delete list_utilizador;
	DestruirTiros();//apagar a lista de tiros
	delete list_Tiro;
	DestruirNivelzinho();//apagar a lista de nivelzinhos
	delete list_Niveis;
	delete NivelObj;
	cout << "Adeus gestor :(" << endl;
}

//Utilizador ----------------------
void GestaoTudo:: CriarContaUtilizador (string user, string pass, int pontos)
{
	Utilizador* pessoazinha = NULL;
	pessoazinha = new Utilizador(user, pass, NUtilizadores++,pontos); //cria o util. e incrementa o n. de util.
	list_utilizador->push_back(pessoazinha);
	cout << "Novo Utilizador " << user <<endl;
}

void GestaoTudo::DestruirUtilizadores()
{
    for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
    {
        //(*it) Da o ponteiro para o Utilizador
        delete *it;
    }
	list_utilizador->clear();
}

bool GestaoTudo:: ProcurarUtilizador(string user, string pass)
{
	for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
	{
		if( ((*it)->Getname().compare(user)== 0 ) && ( (*it)->Getpass().compare(pass)== 0) ){
			setJogadorID((*it)->GetID());
			return true;
		}
	}
	return false;
}

void GestaoTudo::setJogadorID(int id){
	IDUtilizadorActual = id;
}

int GestaoTudo::GetJogadorID(){
	return IDUtilizadorActual;
}

string GestaoTudo::GetUserName(){
	for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
	{
		if((*it)->GetID()==IDUtilizadorActual){
			return (*it)->Getname();
		}

	}
	return "null";
}

void GestaoTudo::LeUtilizadoresFicheiro(){
	ifstream fin;
	string u;
	string p;
	int pontos;
	string line;
	string csvItem;

	fin.open(NomeFichUtilizadores);
	if(fin.is_open()){
		while (getline(fin,line)) {//ler uma linha

                istringstream myline(line);
				getline(myline, csvItem, ',');
                u=csvItem;
				getline(myline, csvItem, ',');
                p=csvItem;
				getline(myline, csvItem, ',');
				pontos=atoi(csvItem.c_str());
				CriarContaUtilizador(u,p,pontos);
		}
	}
}

void GestaoTudo::EscreveUtilizadoresFicheiro(){
	ofstream fout;
	fout.open(NomeFichUtilizadores);    // open file for appending
    if(fout.is_open()){
		for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
			(*it)->EscreveFicheiro(fout);	
		fout.close( );       //close file
	}
	else
		cout << "[ERRO] Nao abriu o fich dos utilizadores" << endl;
	}

int GestaoTudo::GetHScore(){
	for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
	{
		if((*it)->GetID()==IDUtilizadorActual){
			return (*it)->GetHScore();
		}

	}
	return 0;
}

void GestaoTudo::SetHScore(int pontos){
	for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
	{
		if((*it)->GetID()==IDUtilizadorActual){
			(*it)->SetHScore(pontos);
		}

	}
}

bool GestaoTudo:: ExisteUtilizador(string user)
{
	for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
	{
		if( ((*it)->Getname().compare(user)== 0 ) ){
			
			return true;
		}
	}
	return false;
}

Utilizador* GestaoTudo::CriaListaOrdenada(int &nUser){
	Utilizador* ArrayU = nullptr;
	Utilizador UTemp;
	nUser = list_utilizador->size();
	ArrayU = new Utilizador[nUser]; // allocar um array com o tamanho actual da lista de users
	int aa = 0;
	bool ordenada =false;

	//copiar para o array os utilizadores todos
	for (list<Utilizador*>::iterator it = list_utilizador->begin(); it != list_utilizador->end(); it++)
	{
		ArrayU[aa] = *(*it);
		aa++;
	}
	//ordenar o array utilizando o bubble sort
	while( !ordenada){
		ordenada = true;
		for (int i = 0; i < nUser-1; i++)
		{
			if(ArrayU[i].GetHScore() < ArrayU[i+1].GetHScore())
			{
				UTemp = ArrayU[i];
				ArrayU[i] = ArrayU[i+1];
				ArrayU[i+1]=UTemp;
				ordenada = false;
			}
		}
	}

	return ArrayU;

/*	list<Utilizador*> NOVALista;
	NOVALista = *lutilizador;
	bool ordenada =false;
	Utilizador* UTemp1 = nullptr;
	Utilizador* UTemp2 = nullptr;
	list<Utilizador*>::iterator seguinte;
	int i = 0;
	
	while (!ordenada)
	{
		ordenada = true;
		 i = 0;
		for (list<Utilizador*>::iterator it = NOVALista.begin(); it != NOVALista.end(); it++)
		{
			if(i < NOVALista.size()){
				//se a pontuacao do elemento anterio for maior que a actual, trocar posicoes
				cout << (*it)->GetHScore() << " > " << (it._Ptr->_Next->_Myval)->GetHScore() << endl;
				if((*it)->GetHScore() < (it._Ptr->_Next->_Myval)->GetHScore()){
					UTemp1 = (*it);
					(*it) = (it._Ptr->_Next->_Myval);
					(it._Ptr->_Next->_Myval) = UTemp1;
					ordenada = false;
				}
				i++;
			}
			
		}
	}
	
	return NOVALista;*/
}

//Jogador ----------------------
void GestaoTudo::GetPosJogador(int &x, int &y){
	mariana.GetPos(x,y);
}

void GestaoTudo::MexerJogador(int direccao){
	mariana.Mexer(direccao);
}

int GestaoTudo::GetPoints(){
	return mariana.GetPoints();
}

int GestaoTudo::GetVidas(){
	return mariana.GetVidas();
}

void GestaoTudo::AddPointsJogador(int _val){
	mariana.AddPoints(_val);
}

void GestaoTudo::RetiraVidaJogador(int _valor){
	mariana.RetiraVida(_valor);
}

void GestaoTudo::ResetJogador(){
	mariana.Reset();
}

//inimigo ----------------------
bool GestaoTudo::VerificarColisoes(int _idBala){
	int tiroLeft,  tiroRight,  tiroBottom,  tiroTop, tipo;
	bool colisao = false;
	GetPosTiro(_idBala,tiroLeft,tiroTop);
	tipo = GetTipoTiro(_idBala);
	tiroRight = tiroLeft + TiroSize_H;
	tiroBottom = tiroTop + TiroSize_W;

	colisao = NivelObj->VerificarColisoes(tiroLeft,tiroTop,tiroRight,tiroBottom, tipo, &mariana);

	if(colisao){
		if( tipo == TiroJogador)
			AddPointsJogador(1);
		return true;//retorna true para poder apagar este tiro
	}
	return false;

}

void GestaoTudo::CriarInimigo(int _tipo){
	NivelObj->CriarInimigo(_tipo);
}

bool GestaoTudo::RetirarVidaInimigo(Inimigo* _inimigo, int _dano){
	return NivelObj->RetirarVidaInimigo(_inimigo,_dano);
}

int GestaoTudo::GetVidaInimigo(int _id){
	return NivelObj->GetVidaInimigo(_id);
}

void GestaoTudo::GetPosInimigo(int _idInimigo, int &x, int &y){
	NivelObj->GetPosInimigo(_idInimigo,x,y);
}

int GestaoTudo::GetTipoInimigo(int _idInimigo){
	return NivelObj->GetTipoInimigo(_idInimigo);
}

int GestaoTudo::getDecayInimigo(int _id){
	return NivelObj->getDecayInimigo(_id);
}

void GestaoTudo::ReduzDecayInimigo(int _id){
	NivelObj->ReduzDecayInimigo(_id);
}

Inimigo* GestaoTudo::ProcuraInimigo(int _id){
	 return NivelObj->ProcuraInimigo(_id);
}

int GestaoTudo::GetIDUltInimigo(){
	return NivelObj->GetIDUltInimigo();
}

void GestaoTudo::GetSizeInimigo(int &_sizeW ,int &_sizeH){
	NivelObj->GetSizeInimigo(_sizeW,_sizeH);
}

int GestaoTudo::GetInimigosVivos(){
	return NivelObj->GetInimigosVivos();
}

int GestaoTudo::getEstadoBoca(){
	return NivelObj->getEstadoBoca();
}

void GestaoTudo::controlaBoca(int _EstadoBoca){
	NivelObj->controlaBoca(_EstadoBoca);
}

void GestaoTudo::DeslocaInimigos(){
	NivelObj->DeslocaInimigos();
}

//Tiro ---------------------
int GestaoTudo::CriarTiro(int _TipoTiro)//se criar um tiro retorna o seu id,caso contrario retorna -1;
{

	int x=0,y=0;

	Tiro *NovoTiro;
	if(_TipoTiro==TiroJogador) //Jogador
	{
		if(TirosNoEcra >= LimiteTiros)
			return -1;
		GetPosJogador(x,y);
		NovoTiro = new Tiro(NTiros++,x,y,_TipoTiro);
		list_Tiro->push_back(NovoTiro);
		TirosNoEcra++;
		cout << "Tiro do Jogador" << endl;
	}
	else if(_TipoTiro == TiroInimigo)
	{	
		NivelObj->GetInimigoRandom(x,y);
		NovoTiro = new Tiro(NTiros++,x,y,_TipoTiro);
		list_Tiro->push_back(NovoTiro);
		cout << "Tiro do Inimigo" << endl;
	}

	return NTiros-1;
}

void GestaoTudo::DestruirTiros(){
    for (list<Tiro *>::iterator it = list_Tiro->begin(); it != list_Tiro->end(); it++)
    {
       
        delete *it;
    }
	list_Tiro->clear();
}

void GestaoTudo::RemoverTiro(int _idTiro)
{
	Tiro *X = NULL;
    for (list<Tiro*>::iterator it = list_Tiro->begin(); it != list_Tiro->end(); it++)
    {
		if((*it)->GetID() == _idTiro)
		{
			   X = (*it);
			   break;
		}
    }
	if(X != NULL)
	{
		if(X->GetTipo() == TiroJogador)
		TirosNoEcra--;
		list_Tiro->remove(X);
	}


}

void GestaoTudo::DeslocarTiro(int _idTiro)//procura o tiro na lista e executa o deslocar
{
	Tiro *Biala=NULL;
	Biala = ProcuraTiro(_idTiro);
	if(Biala)
	{
		if(Biala->GetTipo()==TiroJogador) //Jogador
			Biala->DeslocaY(TiroVeloc);
		else                  //Inimigo
			Biala->DeslocaY(-TiroVeloc);
	}
}

void GestaoTudo::GetPosTiro(int _idTiro,int &x, int &y){
	Tiro *Biala=NULL;
	Biala = ProcuraTiro(_idTiro);
	if(Biala)
		Biala->GetPos(x,y);
}

int GestaoTudo::GetTipoTiro(int _idTiro){
	return ProcuraTiro(_idTiro)->GetTipo();
}

Tiro *GestaoTudo::ProcuraTiro(int _idTiro){
	for (list<Tiro*>::iterator it = list_Tiro->begin(); it != list_Tiro->end(); it++)
	{
		if( (*it)->GetID() == _idTiro ){
			return (*it);
			
		}
	}
	return NULL;
}

void GestaoTudo::ClearListTiros(){
	DestruirTiros();
	NTiros = 0;
    TirosNoEcra = 0;
}

//Nivel -------------------------
void GestaoTudo::LerFicheiroNiveis(){
	
	ifstream fin;
	string line;
	string csvItem;
	int contar=0;
	
	fin.open("niveis.csv");
	Nivelzinho *Nivel = nullptr;

	if(fin.is_open()){
		
		getline(fin,line);//ler o n de niveis;
	    
		istringstream myline(line);
		getline(myline, csvItem, ',');//retorna so uma string ate ao delimitador, sem o delimitador
		NTotalNiveis=atoi(csvItem.c_str());

		while (getline(fin,line)){//ler uma linha
			if(contar>NTotalNiveis-1){
				cout<< "ERRO, NIVEIS A MAIS"<< endl;
				break;}

			Nivel = new Nivelzinho;
            istringstream myline(line);
			for (int i = 0; i < MAXInimigoPNivel; i++)
			{
				if(getline(myline, csvItem, ','))//se ainda nao chegou ao fim da linha
					Nivel->Array_Inimigos[i]=atoi(csvItem.c_str());
				else
					Nivel->Array_Inimigos[i]=0;//encher o resto com 0s
	
			}

			list_Niveis->push_back(Nivel);//colocar o nivel na lisat
			contar++;

		}
	}else
		cout << "ERRO: Ficheiro \"niveis.csv\" nao encontrado" << endl;
	cout << "Niveis carregados" << endl;
}

void GestaoTudo::PrepararNivel(int _nivel){
	//Criar varios inimigos, e consoante o nivel escolher qual tipo colocar

	//se o Nivel ja tiver sido alocado, apagar antes de criar o proximo
	if(NivelObj != NULL){
		delete NivelObj;
	}

	if(_nivel != NULL){
		NivelObj = new NivelClass(_nivel, GetNivelzinho(_nivel-1),NTotalNiveis);
		nivelActual = _nivel;
	}
	else//seguir a ordem dos niveis
	{
		if(nivelActual > NTotalNiveis) //Volta ao nivel, chegamos ao fim do jogo
			nivelActual = 1;
		NivelObj = new NivelClass(nivelActual,GetNivelzinho(nivelActual-1),NTotalNiveis);
		
	}
	
}

int GestaoTudo::GetNivel(){
	return nivelActual;
}

int GestaoTudo::JogoACorrer(){
	return EstadoDoJogo;
}

bool GestaoTudo::VerificarFimNivel(){
	if(GetInimigosVivos() < 1 || GetVidas() < 1){//se ainda houver inimigos vivos ou ainda tiver vidas o jogador, ainda nao acabamos este nivel
		if(mariana.GetPoints() > GetHScore()){
			cout << "Novo HScore " << mariana.GetPoints() <<endl;
			SetHScore(mariana.GetPoints());
		}
		ClearListTiros();
		nivelActual++;
		return true;
	}
	return false;
}

Nivelzinho *GestaoTudo::GetNivelzinho(int NumNivel){
	int i = 0;
	for (list<Nivelzinho*>::iterator it = list_Niveis->begin(); it != list_Niveis->end(); it++)
	{
		if(i==NumNivel)
			return (*it);
		i++;
	}
	return nullptr;
}

int GestaoTudo::GetTotalNiveis(){
	return NTotalNiveis;
}

void GestaoTudo::DestruirNivelzinho(){
	 for (list<Nivelzinho*>::iterator it = list_Niveis->begin(); it != list_Niveis->end(); it++)
    {
        //(*it) Da o ponteiro para o Nivelzinho
        delete *it;
    }
	list_Niveis->clear();
}
