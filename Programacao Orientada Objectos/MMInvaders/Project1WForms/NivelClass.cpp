#include "NivelClass.h"
#include "GestaoTudo.h"
#include <time.h>

/*int Nivel[][24] = {
					{1,1,1,1,1,1,1,1},//Nivel 1
					{2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1},//Nivel 2
					{3,3,3,3,3,3,3,3,1,2,1,2,1,2,1,2},//Nivel 3
					{7,6,6,7,7,6,6,7,5,5,4,4,5,5,4,4,3,2,2,3,3,2,2,3},//Nivel 4
					{8}//Nivel 5
};*/

NivelClass::NivelClass(int _nivelActual, Nivelzinho* Nivel, int _NTotalNiveis)
{
	id_inimigos = 0;
	inimigosVivos = 0;
	list_Inimigo = new list<Inimigo *>();
	DireccaoInimigo = MovDir;
	nivelActual = _nivelActual;
	NTotalNiveis = _NTotalNiveis;

	for(int i = 0; i < MAXInimigoPNivel; i++){
		
		if(Nivel->Array_Inimigos[i] != 0 && Nivel->Array_Inimigos[i] != BossID) // se o tipo do inimigo for diferente de 0, nao colocar inimigos "mortos"
			CriarInimigo(Nivel->Array_Inimigos[i]);
		
		else if(Nivel->Array_Inimigos[i] == BossID)		
			CriarBoss();
		
	}
	cout<<"Nivel "<< _nivelActual<<" carregado" << endl;

}


NivelClass::~NivelClass(void)
{

    DestruirInimigos();
    delete list_Inimigo;
	
}
void NivelClass::DestruirInimigos(){
	for (list<Inimigo*>::iterator it = list_Inimigo->begin(); it != list_Inimigo->end(); it++)
    {
        delete *it;
    }
	list_Inimigo->clear();
}


void NivelClass::CriarBoss(){
	
	InimigoBoss *inimi;
	inimi = new InimigoBoss(BossID,1,170,35 ); //pos inicial do boss!!!
	list_Inimigo->push_back(inimi);
	id_inimigos++;
	inimigosVivos++;
}

void NivelClass::CriarInimigo(int _tipo)
{
	int x = InimigoSize_W, y = InimigoSize_H;


	//Calcular a posicao do inimigo
	x += id_inimigos % InimigoPLinha * InimigoSize_W;	
	y += id_inimigos / InimigoPLinha * InimigoSize_H;
	id_inimigos++;//incrementa o id dos inimigos
	inimigosVivos++;//incrementa o numero de inimigos vivos

	Inimigo *inimi;
	inimi = new Inimigo(_tipo,id_inimigos,x,y);
	list_Inimigo->push_back(inimi);
}

Inimigo* NivelClass::ProcuraInimigo(int _id){
	 for (list<Inimigo*>::iterator it = list_Inimigo->begin(); it != list_Inimigo->end(); it++)
    {
        if ((*it)->getId() == _id){
			return (*it);
		}
    }
	 return nullptr;
}

void NivelClass::GetPosInimigo(int _idInimigo, int &x, int &y){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(_idInimigo);
	if(Ini){
		Ini->getPos(x,y);
	}

}
int NivelClass::GetTipoInimigo(int _idInimigo){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(_idInimigo);
	if(Ini){
		return Ini->getTipo();
	}
	return -1;

}

bool NivelClass::VerificarColisoes(int tiroLeft,int tiroTop,int tiroRight,int tiroBottom, int tipo, Jogador *mariana){
		
	int enemyLeft, enemyRight, enemyBottom, enemyTop;
	if(tipo == TiroJogador){
		for (list<Inimigo*>::iterator it = list_Inimigo->begin(); it != list_Inimigo->end();it++)
		{
		
			if((*it)->getVida() > 0){
				if( nivelActual != NTotalNiveis){//para todos os niveis menos o boss
					(*it)->getPos(enemyLeft,enemyTop); //buscar a posicao do inimigo
					enemyRight = enemyLeft + InimigoSize_W;		
					enemyBottom = enemyTop + InimigoSize_H;
					
					if(tiroLeft <= enemyRight) 
						if(tiroRight >= enemyLeft)
							if(tiroBottom >= enemyTop) 
								if(tiroTop <= enemyBottom){
									if(RetirarVidaInimigo((*it),1)) //se o inimigo morreu decrementar
										inimigosVivos--;
									return true;//bateu em alguem pode sair do ciclo
								}
				}
				else//no nivel boss
				{

					int sizeW,sizeH;
					(*it)->getSize(sizeW,sizeH);//buscar o tamanho do inimigo
					(*it)->getPos(enemyLeft,enemyTop); //buscar a posicao do inimigo cabeca

					float ratioW = (float)sizeW/(float)BossSizeFinal_W;
					float ratioH = (float)sizeH/(float)BossSizeFinal_H;

					enemyTop = enemyTop + (int)((float)BossBoca_Y * ratioH);
					enemyLeft = enemyLeft + (int)((float)BossBoca_X * ratioW);
					enemyRight = enemyLeft + (int)((float)BossBoca_W*ratioW);		
					enemyBottom = enemyTop + (int)((float)BossBoca_H*ratioH);
				
					if(tiroLeft <= enemyRight) 
						if(tiroRight >= enemyLeft)
							if(tiroBottom >= enemyTop) 
								if(tiroTop <= enemyBottom){
									if(RetirarVidaInimigo((*it),1)) //se o inimigo morreu decrementar
										inimigosVivos--;
									if((*it)->getEstadoBoca())//boca aberta, aumentar pontuacao
										return true;//bateu em alguem pode sair do ciclo
									else//boca fechada
										return false;
								}
				}
			}
		}
	}
	
	if(tipo == TiroInimigo){
		mariana->GetPos(enemyLeft,enemyTop);
		enemyRight = enemyLeft + JogadorSize_W;		
		enemyBottom = enemyTop + JogadorSize_H;
		if(tiroLeft <= enemyRight) 
			if(tiroRight >= enemyLeft)
				if(tiroBottom >= enemyTop) 
					if(tiroTop <= enemyBottom){
						mariana->RetiraVida(1);
						return true;//bateu em alguem pode sair do ciclo
					}

	}
	return false;
}

bool NivelClass::RetirarVidaInimigo(Inimigo* _inimigo, int _dano){

	if(_inimigo)
		return _inimigo->RetiraVida(_dano);
	return false;
}


int NivelClass::GetVidaInimigo(int _id){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(_id);
	if(Ini){
		return Ini->getVida();
	}
	return 0;
}

int NivelClass::getDecayInimigo(int _id){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(_id);
	if(Ini){
		return Ini->getDecay();
	}
	return 0;
}

void NivelClass::ReduzDecayInimigo(int _id){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(_id);
	if(Ini){
		Ini->ReduzDecay();
	}
	
}


int NivelClass::GetIDUltInimigo(){
	return id_inimigos;
}

int NivelClass::GetInimigosVivos(){
	return inimigosVivos;
}

void NivelClass::GetSizeInimigo(int &_sizeW ,int &_sizeH){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(1);
	Ini->getSize(_sizeW,_sizeH);

}

int NivelClass::getEstadoBoca(){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(1);
	return Ini->getEstadoBoca();

}

void NivelClass::controlaBoca(int _EstadoBoca){
	Inimigo* Ini = nullptr;
	Ini = ProcuraInimigo(1);//1 pois so existe 1 inimigo
	Ini->controlaBoca(_EstadoBoca);

}

void NivelClass::DeslocaInimigos(){
	int x,y;
	int ExtremoDireito,ExtremoEsquerdo;

	if(nivelActual != NTotalNiveis){//se nao estivermos no ultimo nivel
		ProcuraInimigo(1)->getPos(x,y); //encontra o inimigo mais à esquerda
		 ExtremoDireito =  x + (InimigoSize_W * InimigoPLinha) + (InimigoDesloca * DireccaoInimigo) ; //calcula o extremo direito dos inimigos
		 ExtremoEsquerdo = x + (InimigoDesloca * DireccaoInimigo); //calculo do extremo esquerdo dos inimigos
		
		//caso passe algum dos limites da area de jogo
		//mudar a direcao de deslocamento
		if( ExtremoEsquerdo < 0  ) 
			DireccaoInimigo = 1; 
		
		if(ExtremoDireito > JogoSize_W)
			DireccaoInimigo = -1;
	}
	else
	{
		//para o boss
		Inimigo* Ini = nullptr;
		int sizeW,sizeH;
		Ini = ProcuraInimigo(1);
		Ini->getPos(x,y); //encontra o inimigo mais à esquerda
		Ini->getSize(sizeW,sizeH);
		
		ExtremoDireito =  x + sizeW + (InimigoDesloca * DireccaoInimigo) ; //calcula o extremo direito dos inimigos
		ExtremoEsquerdo = x + (InimigoDesloca * DireccaoInimigo); //calculo do extremo esquerdo dos inimigos
		
		//caso passe algum dos limites da area de jogo
		//mudar a direcao de deslocamento
		if( ExtremoEsquerdo < 0  ) 
			DireccaoInimigo = 1; 
		
		if(ExtremoDireito > JogoSize_W)
			DireccaoInimigo = -1;
		

	}

	for (list<Inimigo*>::iterator it = list_Inimigo->begin(); it != list_Inimigo->end();it++){
			(*it)->getPos(x,y);
			x = x+(InimigoDesloca * DireccaoInimigo);
			(*it)->Desloca(x,y);

	}

}

void NivelClass::GetInimigoRandom(int &_x, int&_y)
{
	int size = list_Inimigo->size();
	Inimigo* Inim = nullptr;

	srand(time(NULL));
	int ran;
	int trys = 0;
	bool sucesso = false;
	if(size >0){
		//enquanto nao encontrar um inimigo vivo
		do{
			trys++;
			ran = rand() % size+1; //numero random entre 1 e size
			Inim = ProcuraInimigo(ran);
			if(Inim!=NULL)
				if( Inim->getVida() > 0 )//verifica se ta vivo
				{
					Inim->getPos(_x,_y); //mais eficiente
					//GetPosInimigo(ran,_x,_y);
					sucesso = true;
					break;
				}	

		}while ( !sucesso || trys > 10);//desiste de procurar
	}

}