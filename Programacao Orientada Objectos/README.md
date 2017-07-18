# Projecto de POO
Projeto Final – “MMInvaders”


![Screenshot](https://github.com/dicamarques14/ProjectosProgramacao/raw/master/Estrutura%20de%20Dados/Screen.png)

![Screenshot](https://github.com/dicamarques14/ProjectosProgramacao/raw/master/Estrutura%20de%20Dados/Screen.png)


Projeto de POO: Jogo 
Pretende-se realizar um jogo com o objetivo de aplicar os conhecimentos adquiridos em POO. 
Em termos gerais o jogo consiste em movimentar um dado objeto (Arma) e disparar sobre  outros objetos que podem estar ou não em movimento. 
O  jogo  deve  contemplar  a  existência  de  vários  tipos  de  armas,  cada  uma  com  o  seu  comportamento, bem como vários tipos de alvos. 

Funcionalidades básicas: 
- A configuração inicial deve ser lida de ficheiro; 
- Cada tipo de alvo terá o seu comportamento (por ex. para ser destruído alguns alvos têm de ser mais atingidos, o comportamento na destruição deve ser diferente em cada alvo, os alvos podem movimentar-se, podem esconder-se) 
- Podemos ter vários tipos de armas, onde cada arma tem comportamento diferente; 
- Pretende-se que sejam gravadas em ficheiro ou base de dados, todos os movimentos/ações efetuados de modo a mais tarde se poder fazer uma análise estatística do perfil do jogador; 
- Deve ser registado o login de cada utilizador, e deve aparecer nas informações do jogo os 10 melhores jogadores; 
- O jogo pode ser ou não mais “acelerado”; 
- O jogo deveria ter uma versão em que é o computador a jogar. 

A ideia das figuras e o tema do jogo surgiu devido à nossa colega de grupo possuir o nome de praxe m&m´s, originando os tiros em forma de m&m´s e ser a personagem do jogo (cara do boneco que dispara m&m´s).

Para controlar o jogo usa-se as seguintes teclas:
● Space - para disparar
● A - mover o jogador para a esquerda
● D - mover o jogador para a direita

Soluções para problemas
Durante a realização do projecto surgiram algumas dificuldades e erros de
compilação, mas com muito esforço e dedicação conseguimos resolver todos esses
erros, e os mesmos se encontram descritos abaixo.
1. Fazer uma lista com as PictureBoxes (ou qualquer outro objecto do Windows
Forms):
- Colocar “using namespace System::Collections::Generic; ”
- Declarar a variável “List<PictureBox^>^ ListPBTiros ;”
- Inicializar “ListPBTiros = gcnew(List<PictureBox^>); “
- Adicionar uma PB à lista “ListPBTiros->Add(PB);”
- Aceder a uma PB na lista “ListPBTiros[i];”
- Apagar o conteúdo da lista:
for (int i = 0; i < ListPBTiros->Count; i++)
Controls -> Remove(ListPBTiros[i]);
ListPBTiros->Clear();
2. Fazer uma ImageList, para colocar imagens para usar mais tarde:
- Declarar a variável “ImageList ^ListaImgTiros;”
- Inicializar a variável “ListaImgTiros = gcnew ImageList();”
- Definir a qualidade das imagens:
“ListaImgTiros->ColorDepth= ColorDepth::Depth32Bit;”
- Definir o tamanho das imagens:
“ListaImgTiros->ImageSize = System::Drawing::Size(TiroSize_W,
TiroSize_H);”
- Para colocar as imagens na lista, pode se usar uma função que recebe
como parâmetro a imagem e a lista a adicionar :
void addImage(ImageList ^ListaAUsar,String^ imageToLoad)
{ //carregar uma imagem e coloca na lista a usar
if (imageToLoad != “”)
ListaAUsar->Images->Add(Image::FromFile(imageToLoad));
}