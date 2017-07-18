#pragma once

#include <string>
#include <iostream>

using namespace std;

#include "GestaoTudo.h"
#include "FormSelectNivel.h"
#include "Defines.h"
#include "FormLogin.h"
#include "FormTabela.h"

namespace Project1WForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	using namespace System::Collections::Generic; //For Generic List <-- LISTA PB
	
	/// <summary>
	/// Summary for FormJogo
	/// </summary>
	public ref class FormJogo : public System::Windows::Forms::Form
	{
		int TiroImag; //contador de imagens para os tiros
		int EstadoDoJogo; // estado em que se encontra o jogo
		int moverJogador; //Se é ou nao para deslocar o jogador e em que direccao
		int disparaJogador; //variavel que diz se o espaco esta a ser pressionado ou nao
		int ImagemJogador;//qual a imagem que o jogador mostra

		int ContarAbreBoca;//decrementa, se for 0 Abre
		int ContarFechaBoca;//decrementa, se for 0 Fecha
		int ContarMexeInimigo;//decrementa, se 0 desloca os inimigos
		int ContarActualizaDados;
		int ContarMudaImagemJogador;
		int ContarDispararTiroInimigo;


		GestaoTudo *GMorg;//ponteiro para o gestor

		//Imagens do BOSS
		Image ^ImgBossHead;
		Image ^ImgBossBoca;

		//LISTA DAS IMAGENS
		ImageList ^ListaImgTiros;
		ImageList ^ListaImgInimigos;
		ImageList ^ListaImgJogador;

		//Lista das PICTUREBOXES
		List<PictureBox^>^ ListPBTiros ;
		List<PictureBox^>^ ListPBInimigos ;

	private: System::Windows::Forms::PictureBox^  Player_PB;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  Points_LB;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  Lifes_LB;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  Level_LB;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  LimitV_LB;
	private: System::Windows::Forms::Label^  LimitH_LB;
	private: System::Windows::Forms::Label^  username_LB;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  hscore_LB;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  scrbrd_BTN;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  Fire_BTN;
	private: System::Windows::Forms::Button^  Exit_BTN;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  Start_BTN;
	private: System::Windows::Forms::Button^  Stop_BTN;
	private: System::ComponentModel::IContainer^  components;

	public:

		FormJogo(void)
		{
			InitializeComponent();

			GMorg = new GestaoTudo();
			
			GMorg->LeUtilizadoresFicheiro();//carregar os users ja existentes

			KeyPreview=true;	// para funcionar as teclas
			
			ListaImgTiros = gcnew ImageList();
			ListaImgTiros->ColorDepth= ColorDepth::Depth32Bit;
			ListaImgTiros->ImageSize = System::Drawing::Size(TiroSize_W, TiroSize_H);

			ListaImgInimigos = gcnew ImageList();
			ListaImgInimigos->ColorDepth= ColorDepth::Depth32Bit;
			ListaImgInimigos->ImageSize = System::Drawing::Size(InimigoSize_W, InimigoSize_H);

			ListaImgJogador = gcnew ImageList();
			ListaImgJogador->ColorDepth= ColorDepth::Depth32Bit;
			ListaImgJogador->ImageSize = System::Drawing::Size(JogadorSize_W, JogadorSize_H);
			
			ImgBossHead = Image::FromFile("..\\Imagens\\Enemy\\boss_head.dg");
			ImgBossBoca =  Image::FromFile("..\\Imagens\\Enemy\\boss_boca.dg");
			


			ListPBTiros = gcnew(List<PictureBox^>);  //http://stackoverflow.com/questions/23519002/visual-c-2012-using-a-stdvector-or-stdlist-in-class
			ListPBInimigos = gcnew(List<PictureBox^>);

			//CARREGAR AS IMAGENS
			addImage(ListaImgTiros,"..\\Imagens\\Bullet\\mm1.png");
			addImage(ListaImgTiros,"..\\Imagens\\Bullet\\mm2.png");
			addImage(ListaImgTiros,"..\\Imagens\\Bullet\\mm3.png");
			addImage(ListaImgTiros,"..\\Imagens\\Bullet\\mm4.png");
			addImage(ListaImgTiros,"..\\Imagens\\Bullet\\mm5.png");
			addImage(ListaImgTiros,"..\\Imagens\\Bullet\\mm6.png");

			
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_dead.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_1.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_2.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_3.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_4.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_5.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_6.png");
			addImage(ListaImgInimigos,"..\\Imagens\\Enemy\\enemy_7.png");
			
			addImage(ListaImgJogador,"..\\Imagens\\Player\\mariana_dir1.png");
			addImage(ListaImgJogador,"..\\Imagens\\Player\\mariana_dir2.png");
			addImage(ListaImgJogador,"..\\Imagens\\Player\\mariana_esq1.png");
			addImage(ListaImgJogador,"..\\Imagens\\Player\\mariana_esq2.png");

			cout << "Imagens Prontas"<<endl;

			EstadoDoJogo = Est_Parado;
			TiroImag = 0;
			moverJogador = 0;
			disparaJogador = 0;

			ContarAbreBoca=TimerAbreBoca;
			ContarFechaBoca=TimerFechaBoca;
			ContarMexeInimigo=TimerMexeInimigo;
			ContarActualizaDados=TimerActualizaDados;
			ContarDispararTiroInimigo = TimerDispararTiroInimigo;
			ContarMudaImagemJogador = TimerMudaImagemJogador;

			ImagemJogador = 0;
			Player_PB->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			Player_PB->BackColor = Drawing::Color::Transparent;//colocar fundo da PB transparente
			Player_PB->Image = ListaImgJogador->Images[0];
			
			//colocar limites da area de jogo
			LimitV_LB->Location = Drawing::Point(JogoSize_W,0);
			LimitV_LB->Size = Drawing::Size(20,JogoSize_H+20);

			LimitH_LB->Location = Drawing::Point(0,JogoSize_H);
			LimitH_LB->Size = Drawing::Size(JogoSize_W+20,20);
		}

	protected:
		~FormJogo()
		{
			GMorg->EscreveUtilizadoresFicheiro();
			delete GMorg;
			
			if (components)
			{
				delete components;
			}

			
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormJogo::typeid));
			this->Exit_BTN = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Start_BTN = (gcnew System::Windows::Forms::Button());
			this->Stop_BTN = (gcnew System::Windows::Forms::Button());
			this->Fire_BTN = (gcnew System::Windows::Forms::Button());
			this->Player_PB = (gcnew System::Windows::Forms::PictureBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Points_LB = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Lifes_LB = (gcnew System::Windows::Forms::Label());
			this->Level_LB = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->LimitV_LB = (gcnew System::Windows::Forms::Label());
			this->LimitH_LB = (gcnew System::Windows::Forms::Label());
			this->username_LB = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->hscore_LB = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->scrbrd_BTN = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Player_PB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// Exit_BTN
			// 
			this->Exit_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Exit_BTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Purple;
			this->Exit_BTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Navy;
			this->Exit_BTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Exit_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Exit_BTN->Location = System::Drawing::Point(800, 450);
			this->Exit_BTN->Name = L"Exit_BTN";
			this->Exit_BTN->Size = System::Drawing::Size(131, 35);
			this->Exit_BTN->TabIndex = 0;
			this->Exit_BTN->TabStop = false;
			this->Exit_BTN->Tag = L"15";
			this->Exit_BTN->Text = L"EXIT";
			this->Exit_BTN->UseVisualStyleBackColor = true;
			this->Exit_BTN->Click += gcnew System::EventHandler(this, &FormJogo::Exit_BTN_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &FormJogo::Game_Loop);
			// 
			// Start_BTN
			// 
			this->Start_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Start_BTN->BackColor = System::Drawing::Color::Lime;
			this->Start_BTN->CausesValidation = false;
			this->Start_BTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->Start_BTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LimeGreen;
			this->Start_BTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Start_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Start_BTN->Location = System::Drawing::Point(800, 262);
			this->Start_BTN->Name = L"Start_BTN";
			this->Start_BTN->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->Start_BTN->Size = System::Drawing::Size(131, 35);
			this->Start_BTN->TabIndex = 0;
			this->Start_BTN->Tag = L"15";
			this->Start_BTN->Text = L"Start Game";
			this->Start_BTN->UseVisualStyleBackColor = false;
			this->Start_BTN->Click += gcnew System::EventHandler(this, &FormJogo::Start_BTN_click);
			// 
			// Stop_BTN
			// 
			this->Stop_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Stop_BTN->BackColor = System::Drawing::Color::Red;
			this->Stop_BTN->Enabled = false;
			this->Stop_BTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Salmon;
			this->Stop_BTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::DarkRed;
			this->Stop_BTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Stop_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Stop_BTN->Location = System::Drawing::Point(800, 303);
			this->Stop_BTN->Name = L"Stop_BTN";
			this->Stop_BTN->Size = System::Drawing::Size(131, 37);
			this->Stop_BTN->TabIndex = 0;
			this->Stop_BTN->Tag = L"15";
			this->Stop_BTN->Text = L"Stop Game";
			this->Stop_BTN->UseVisualStyleBackColor = false;
			this->Stop_BTN->Click += gcnew System::EventHandler(this, &FormJogo::Stop_BTN_Click);
			// 
			// Fire_BTN
			// 
			this->Fire_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->Fire_BTN->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Fire_BTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->Fire_BTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Fire_BTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Fire_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Fire_BTN->Location = System::Drawing::Point(800, 346);
			this->Fire_BTN->Name = L"Fire_BTN";
			this->Fire_BTN->Size = System::Drawing::Size(131, 35);
			this->Fire_BTN->TabIndex = 0;
			this->Fire_BTN->TabStop = false;
			this->Fire_BTN->Tag = L"15";
			this->Fire_BTN->Text = L"FIRE";
			this->Fire_BTN->UseVisualStyleBackColor = false;
			this->Fire_BTN->Click += gcnew System::EventHandler(this, &FormJogo::Fire_BTN_Click);
			// 
			// Player_PB
			// 
			this->Player_PB->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Player_PB->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Player_PB.Image")));
			this->Player_PB->Location = System::Drawing::Point(285, 262);
			this->Player_PB->Name = L"Player_PB";
			this->Player_PB->Size = System::Drawing::Size(55, 75);
			this->Player_PB->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->Player_PB->TabIndex = 17;
			this->Player_PB->TabStop = false;
			// 
			// listBox1
			// 
			this->listBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->listBox1->CausesValidation = false;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(737, 468);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(54, 17);
			this->listBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Yellow;
			this->label1->Location = System::Drawing::Point(685, 93);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 25);
			this->label1->TabIndex = 18;
			this->label1->Text = L"SCORE:";
			// 
			// Points_LB
			// 
			this->Points_LB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Points_LB->BackColor = System::Drawing::Color::Transparent;
			this->Points_LB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Points_LB->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Points_LB->Location = System::Drawing::Point(789, 93);
			this->Points_LB->Name = L"Points_LB";
			this->Points_LB->Size = System::Drawing::Size(132, 25);
			this->Points_LB->TabIndex = 19;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Yellow;
			this->label2->Location = System::Drawing::Point(685, 118);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 25);
			this->label2->TabIndex = 20;
			this->label2->Text = L"LIFES:";
			// 
			// Lifes_LB
			// 
			this->Lifes_LB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Lifes_LB->BackColor = System::Drawing::Color::Transparent;
			this->Lifes_LB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Lifes_LB->ForeColor = System::Drawing::Color::DarkRed;
			this->Lifes_LB->Location = System::Drawing::Point(773, 120);
			this->Lifes_LB->Name = L"Lifes_LB";
			this->Lifes_LB->Size = System::Drawing::Size(148, 23);
			this->Lifes_LB->TabIndex = 21;
			// 
			// Level_LB
			// 
			this->Level_LB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Level_LB->BackColor = System::Drawing::Color::Transparent;
			this->Level_LB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Level_LB->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Level_LB->Location = System::Drawing::Point(781, 68);
			this->Level_LB->Name = L"Level_LB";
			this->Level_LB->Size = System::Drawing::Size(140, 25);
			this->Level_LB->TabIndex = 23;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Yellow;
			this->label4->Location = System::Drawing::Point(685, 68);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(90, 25);
			this->label4->TabIndex = 22;
			this->label4->Text = L"LEVEL:";
			// 
			// LimitV_LB
			// 
			this->LimitV_LB->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(167)), 
				static_cast<System::Int32>(static_cast<System::Byte>(167)));
			this->LimitV_LB->Location = System::Drawing::Point(640, 0);
			this->LimitV_LB->Name = L"LimitV_LB";
			this->LimitV_LB->Size = System::Drawing::Size(20, 109);
			this->LimitV_LB->TabIndex = 24;
			// 
			// LimitH_LB
			// 
			this->LimitH_LB->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(167)), static_cast<System::Int32>(static_cast<System::Byte>(167)), 
				static_cast<System::Int32>(static_cast<System::Byte>(167)));
			this->LimitH_LB->Location = System::Drawing::Point(0, 480);
			this->LimitH_LB->Name = L"LimitH_LB";
			this->LimitH_LB->Size = System::Drawing::Size(260, 20);
			this->LimitH_LB->TabIndex = 25;
			// 
			// username_LB
			// 
			this->username_LB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->username_LB->BackColor = System::Drawing::Color::Transparent;
			this->username_LB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->username_LB->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->username_LB->Location = System::Drawing::Point(768, 5);
			this->username_LB->Name = L"username_LB";
			this->username_LB->Size = System::Drawing::Size(153, 25);
			this->username_LB->TabIndex = 27;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Yellow;
			this->label5->Location = System::Drawing::Point(686, 5);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(81, 25);
			this->label5->TabIndex = 26;
			this->label5->Text = L"USER:";
			// 
			// hscore_LB
			// 
			this->hscore_LB->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hscore_LB->BackColor = System::Drawing::Color::Transparent;
			this->hscore_LB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->hscore_LB->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->hscore_LB->Location = System::Drawing::Point(819, 30);
			this->hscore_LB->Name = L"hscore_LB";
			this->hscore_LB->Size = System::Drawing::Size(102, 25);
			this->hscore_LB->TabIndex = 29;
			// 
			// label7
			// 
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::Yellow;
			this->label7->Location = System::Drawing::Point(685, 30);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(128, 25);
			this->label7->TabIndex = 28;
			this->label7->Text = L"H. SCORE:";
			// 
			// scrbrd_BTN
			// 
			this->scrbrd_BTN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->scrbrd_BTN->BackColor = System::Drawing::Color::Navy;
			this->scrbrd_BTN->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DodgerBlue;
			this->scrbrd_BTN->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->scrbrd_BTN->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->scrbrd_BTN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->scrbrd_BTN->ForeColor = System::Drawing::Color::White;
			this->scrbrd_BTN->Location = System::Drawing::Point(800, 409);
			this->scrbrd_BTN->Name = L"scrbrd_BTN";
			this->scrbrd_BTN->Size = System::Drawing::Size(131, 35);
			this->scrbrd_BTN->TabIndex = 30;
			this->scrbrd_BTN->TabStop = false;
			this->scrbrd_BTN->Tag = L"15";
			this->scrbrd_BTN->Text = L"SCORE BOARD";
			this->scrbrd_BTN->UseVisualStyleBackColor = false;
			this->scrbrd_BTN->Click += gcnew System::EventHandler(this, &FormJogo::scrbrd_BTN_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(690, 156);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(230, 100);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 31;
			this->pictureBox1->TabStop = false;
			// 
			// FormJogo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(938, 501);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->scrbrd_BTN);
			this->Controls->Add(this->hscore_LB);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->username_LB);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->LimitH_LB);
			this->Controls->Add(this->LimitV_LB);
			this->Controls->Add(this->Level_LB);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->Lifes_LB);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Points_LB);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->Player_PB);
			this->Controls->Add(this->Fire_BTN);
			this->Controls->Add(this->Stop_BTN);
			this->Controls->Add(this->Start_BTN);
			this->Controls->Add(this->Exit_BTN);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1036, 544);
			this->Name = L"FormJogo";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MMInvaders BetaV1 by: Diogos and Mariana";
			this->Load += gcnew System::EventHandler(this, &FormJogo::FormJogo_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FormJogo::FormJogo_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FormJogo::FormJogo_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Player_PB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Exit_BTN_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 // Ver https://www.youtube.com/watch?v=U14ZpnAmoXg
				 Close();
			 }
	private: System::Void FormJogo_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				cout << "A Aguardar Login" << endl;
				FormLogin ^MarianaEMachado =gcnew FormLogin(GMorg);
				MarianaEMachado->ShowDialog();
				GMorg->EscreveUtilizadoresFicheiro();//escrever as alteracoes feitas;
				cout << "Login Feito" << endl;

			 }

private: System::Void Start_BTN_click(System::Object^  sender, System::EventArgs^  e)
		 {
			 //COMECA O JOGO
			 cout << "Start Game" << endl;
			 
			 //troca os botoes activos
			 Start_BTN->Enabled=false;
			 Stop_BTN->Enabled=true;
			 Fire_BTN->Enabled=true;

			 //Perguntar que nivel deseja carregar
			 int *nivel = new int;
			 *nivel = 1;
			 IntDados ^F = gcnew IntDados(nivel,GMorg->GetTotalNiveis());
			 if (F->ShowDialog() == Windows::Forms::DialogResult::OK){
				 PrepararNivel(*nivel);
			 }
			 else{
				 PrepararNivel(NULL);
			 }
			 delete nivel;
			
			 GMorg->ResetJogador();
			 listBox1->Select();
			 EstadoDoJogo = Est_Correr;
			 timer1->Start();
			 timer1->Interval = 2;
		 }

private: System::Void Stop_BTN_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //Parar o jogo
			 cout << "Stop Game" << endl;
			 timer1->Stop();
			 //troca os botoes activos
			 Stop_BTN->Enabled=false;
			 Fire_BTN->Enabled=false;
			 Start_BTN->Enabled=true;
			 EstadoDoJogo = Est_Parado;
			for (int i = 0; i < ListPBTiros->Count; i++)
				Controls->Remove(ListPBTiros[i]);
			ListPBTiros->Clear();

			for (int i = 0; i < ListPBInimigos->Count; i++)
				Controls->Remove(ListPBInimigos[i]);
			ListPBInimigos->Clear();
				
		 }

private: System::Void Game_Loop(System::Object^  sender, System::EventArgs^  e) 
		{  
			if(EstadoDoJogo == Est_Correr){
				this->SuspendLayout();//pausa o processamento do layout enquanto preparamos o proximo frame

				//Logic---------------------------------------------------------------------
				//verifica se ainda existe algum inimigo vivo
				if( !VerificarFimNivel(sender, e)){
				
					DeslocaJogador();//desloca o jogador
					if (disparaJogador)
					{
						Fire_BTN_Click(sender,e);
						disparaJogador = 0;
					}				
					DeslocaTiros();//desloca os tiros, verifica as colisoes e dispara um tiro dos inimigos se for altura
				
					DeslocaInimigos();//deslocar os inimigos

					ControlaBoca();//Caso seja o nivel do boss controla a boca

				}

				//Rendering---------------------------------------------------------------------

				DesenhaJogador();
			
				DesenhaTiros();
			
				DesenhaInimigos();

				ActualizarDados(); //actualiza a info nas labels
			

				this->PerformLayout();//mostra o frame novo
			}
		}

private: System::Void PrepararNivel(int _nivel) {
			 //manda o gestor preparar o nivel, cria os inimigos na parte grafica
			 GMorg->PrepararNivel(_nivel);
			 if(GMorg->GetNivel() != GMorg->GetTotalNiveis()){
				for (int i = 0; i < GMorg->GetIDUltInimigo(); i++)
				{
					CriarInimigo(i+1); //i+1 porque nao comecamos no 0
				}

			 }
			 else
			 {
				 CriarBoss();
			 }
			int x,y;
			GMorg->GetPosJogador(x,y);
			Player_PB->Location = System::Drawing::Point(x,y);
		 }


private: System::Void Fire_BTN_Click(System::Object^  sender, System::EventArgs^  e) {
			 //quando é carregado o botao de disparo
			 if(EstadoDoJogo == Est_Correr){
				CriarTiro(TiroJogador);
			 }

		 }
		 
private: System::Void CriarTiro(int _tipo) {
			 //cada PB tem como nome o id do tiro correspondente
			 int id = GMorg->CriarTiro(_tipo);
			 int x=0, y=0;

			 if(id == -1){ //falhou criar o tiro nogestor, ou atingiu limite
				 Console::WriteLine("[ERRO]falhou criar tiro, limite atingido?");
				 return;
			 }

			 PictureBox ^PB = gcnew PictureBox();	
			 PB->Image = ListaImgTiros->Images[TiroImag++];

			 if(TiroImag > 5)//reiniciar o loop de imagens
				 TiroImag = 0;

			 GMorg->GetPosTiro(id, x, y);
			 PB->Location = Drawing::Point(x,y);

			 PB->Name = id.ToString(); //https://social.msdn.microsoft.com/Forums/vstudio/en-US/d55e67ff-1ae5-44fd-8627-c7373a15d4b3/
			 PB->Size = System::Drawing::Size(TiroSize_W, TiroSize_H);
			 PB->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 PB->BackColor = Drawing::Color::Transparent;
			 PB->TabStop = false;
			 PB->Visible = true;

			 
			 //adicionar as PB nas listas
			 Controls->Add(PB);
			 ListPBTiros->Add(PB);

			 //Ficar á frente a imagem
			 PB->BringToFront();
			 UpdateZOrder();
				
		 }

private: System::Void CriarInimigo(int _id) {
			 //alocar nova PB, e sincroniza com o inimigo no gestor
			 PictureBox ^PB = gcnew PictureBox();
			 

			 PB->Image = ListaImgInimigos->Images[GMorg->GetTipoInimigo(_id)];//ir buscar a imagem correspondente ao tipo
			 int x=0,y=0;
			 GMorg->GetPosInimigo(_id,x,y);
			 
			 PB->Location = Drawing::Point(x,y);
			 PB->Name = _id.ToString();
			 PB->Size = System::Drawing::Size(InimigoSize_W, InimigoSize_H);
			 PB->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 //PB->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			 PB->TabStop = false;
			 PB->Visible = true;
			 PB->BackColor = Drawing::Color::Transparent;
			 
			 Controls->Add(PB);
			 ListPBInimigos->Add(PB);
			 
			 //Trazer para a frente a Imagem
			 PB->BringToFront();
			 UpdateZOrder();
				
		 }

private: System::Void CriarBoss() {
			 //alocar nova PB, e sincroniza com o inimigo no gestor
			 PictureBox ^PBHead = gcnew PictureBox();
			 PictureBox ^PBBoca = gcnew PictureBox();

						PBHead->Image = ImgBossHead;
						PBBoca->Image = ImgBossBoca;

			 int x=0,y=0;
			 GMorg->GetPosInimigo(1,x,y);
			 
			 PBHead->Location = Drawing::Point(x,y);
			 PBHead->Name = "1";
			 PBHead->Size = System::Drawing::Size(BossSizeInit_W, BossSizeInit_H);
			 PBHead->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 PBHead->Visible = true;
			 PBHead->BackColor = Drawing::Color::Transparent;
			
			 float ratioW = (float)BossSizeInit_W/(float)BossSizeFinal_W;

	
			 float ratioH = (float)BossSizeInit_H/(float)BossSizeFinal_H;

			 int bocax = x+ (int)((float)BossBoca_X * ratioW);
			 int bocay= y+ (int)((float)BossBoca_Y * ratioH);

			 PBBoca->Location = Drawing::Point(bocax ,  bocay ); //80 230 no max!
			 PBBoca->Size = System::Drawing::Size((int)((float)BossBoca_W*(ratioW)), (int)((float)BossBoca_H*(ratioH)));
			 PBBoca->Name = "0";
			 //PBBoca->Size = System::Drawing::Size(BossBoca_W, BossBoca_H);
			 //PBBoca->Location = Drawing::Point( x,  y); 
			 PBBoca->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 PBBoca->Visible = true;
			 //PBBoca->BackColor = Drawing::Color::Transparent;

			 Controls->Add(PBHead);
			 ListPBInimigos->Add(PBHead);
			 Controls->Add(PBBoca);
			 ListPBInimigos->Add(PBBoca);

			 //Trazer para a frente a Imagem
			 PBHead->BringToFront();
			 UpdateZOrder();
			 PBBoca->BringToFront();
			 UpdateZOrder();
				
		 }

private: System::Void FormJogo_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 switch (e->KeyCode)
			 {
			 case(Keys::A):{//mexe esquerda
				if(ImagemJogador<2) //se tiver uma imagem da direcao diferente
					ImagemJogador = 2;
				 if(ContarMudaImagemJogador==0 ){ 
					 if(ImagemJogador==2 || ImagemJogador<2)//se tiver na imagem 2 
						ImagemJogador = 3;
					 else
						ImagemJogador = 2;
					 
					 ContarMudaImagemJogador=TimerMudaImagemJogador;
				 }
				 else
					 ContarMudaImagemJogador--;

				 moverJogador = MovEsq;//activa a variavel de direcao com a direccao em que se desloca o jogador
				 break;}
			 case(Keys::D):{//mexe direita
				if(ImagemJogador>1) //se tiver uma imagem da direcao diferente
					ImagemJogador = 1;

				if(ContarMudaImagemJogador==0){
				if(ImagemJogador==0)//se tiver na imagem 0
					ImagemJogador = 1;
					else
					ImagemJogador = 0;

					ContarMudaImagemJogador=TimerMudaImagemJogador;
				}
				else
				ContarMudaImagemJogador--;
				moverJogador = MovDir;//activa a variavel de direcao com a direccao em que se desloca o jogador

				 break;}
			 case(Keys::Space):{
				 listBox1->Select();//seleciona a lb para nao activar nenhum botao
				 disparaJogador = 1;//activa a variavel de disparo

				 //Fire_BTN_Click(sender,e);
				 break;}
			 default:
				 break;
			 }
			 
		 }
private: System::Void FormJogo_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 switch (e->KeyCode)
			 {
			 case(Keys::A):{
				 moverJogador = MovSTOP;//parou de carregar a tecla, coloca a 0
				 break;}
			 case(Keys::D):{
				 moverJogador = MovSTOP;
				 break;}
			 case(Keys::Space):{
				 listBox1->Select();
				 disparaJogador = 0;
							   }
			 default:
				 break;
			 }
		 }

private: String ^ConverterstringToString(string &s){
			 return gcnew String(s.c_str());

		 }
private: void addImage(ImageList ^ListaAUsar,String^ imageToLoad)
        {
			//carregar uma imagem e coloca na lista a usar
			if (imageToLoad != "")
                ListaAUsar->Images->Add(Image::FromFile(imageToLoad));
        }
private: bool VerificarFimNivel(System::Object^  sender, System::EventArgs^  e){//se o nivel tiver terminado retorna true e avanca um nivel
			 if(GMorg->VerificarFimNivel()){
				cout << "Terminou o nivel" << endl;
				
				for (int i = 0; i < ListPBTiros->Count; i++)
					Controls->Remove(ListPBTiros[i]);
 				ListPBTiros->Clear();

				for (int i = 0; i < ListPBInimigos->Count; i++)
					Controls->Remove(ListPBInimigos[i]);
				ListPBInimigos->Clear();
				
				//MessageBox::Show("Uau, nivel completo");
				if(GMorg->GetVidas() > 0){
					if((GMorg->GetNivel()-1) != GMorg->GetTotalNiveis())//se nao for o ultimo
						PrepararNivel(NULL);//avancar de nivel
					else
					{
						Stop_BTN_Click(sender,e);
						MessageBox::Show("      CONGRATS\nYOU COMPLETED THE GAME\n SCORE: "+GMorg->GetPoints());
					}
				}
				else
				{
					Stop_BTN_Click(sender,e);
					MessageBox::Show("      GAME OVER\n  SCORE: "+GMorg->GetPoints());
				}
				return true;
			}
			return false;
		 }

private: void DeslocaJogador(){
			//Verifica se esta a ser pedido para mover o jogador
			if(moverJogador != 0){
				GMorg->MexerJogador(moverJogador);
				
			}
		 }

private: void DeslocaTiros(){//desloca os tiros e verifica as colisoes
	
			 	int yBala = 0;
				 int xBala = 0;
				 PictureBox ^PBTemp=nullptr;
				 int IDBala;
				//Verifica se existem balas disparadas
				if(ListPBTiros->Count > 0){
					for (int i = 0; i < ListPBTiros->Count; i++)
					{
						PBTemp = ListPBTiros[i];//optimizacao, em vez de ir ao array temos um ponteiro para a picturebox actual

						IDBala = int::Parse(PBTemp->Name);
						GMorg->GetPosTiro( IDBala , xBala , yBala);
						//Verificar se a bala esta fora do ecra OU se colidiu com algum inimigo
						if(yBala < 0-TiroSize_H || yBala > JogoSize_H-TiroSize_H || GMorg->VerificarColisoes(IDBala) ) 
						{
							//http://stackoverflow.com/questions/21471858/unable-to-dispose-and-remove-controls-from-control-list
							ListPBTiros[i]->Visible = false;
							Controls->Remove(PBTemp);
							ListPBTiros->Remove(PBTemp);
							GMorg->RemoverTiro( IDBala );
						}
						else{
							GMorg->DeslocarTiro( IDBala ); //manda deslocar um tiro;

						}
					}
				}

				//verifica se é altura para disparar um tiro
				if(ContarDispararTiroInimigo == 0){
					CriarTiro(TiroInimigo);
					ContarDispararTiroInimigo = TimerDispararTiroInimigo - RatioDificuldade*GMorg->GetNivel();//conforme o nivel diminuir o tempo entre disparos
				}else
					ContarDispararTiroInimigo--;

		 }

private: void DeslocaInimigos(){
			if(ContarMexeInimigo==0){
				GMorg->DeslocaInimigos();
				ContarMexeInimigo=TimerMexeInimigo - RatioDificuldade*GMorg->GetNivel();//conforme o nivel diminuir o tempo entre disparos
			}
			else
				ContarMexeInimigo--;
		 }

private: void ControlaBoca(){//Caso seja o nivel do boss controla a boca
			 
				if(GMorg->GetNivel()== GMorg->GetTotalNiveis()){
					//aberta 1, fechada 0
					if(GMorg->getEstadoBoca())
						ContarFechaBoca--;					
					else					
						ContarAbreBoca--;
					
				
					if(ContarAbreBoca== 0){
						GMorg->controlaBoca(Aberta);
						srand(3525656);
						
						ContarAbreBoca=TimerAbreBoca - 10+rand() % 200;//calcula um tempo aleatorio para abrir a boca
						cout << "Vai Fechar daqui a " << ContarAbreBoca << endl;
					}
					if(ContarFechaBoca== 0){
						GMorg->controlaBoca(Fechada);
						ContarFechaBoca=TimerFechaBoca;
						cout << "Vai Abrir daqui a " << ContarFechaBoca << endl;
					}
				}
		 }

private: void DesenhaJogador(){//verifica se o jogador foi mexido e actualiza a posicao
			
				int x = 0, y =0;
				GMorg->GetPosJogador(x,y);
				Player_PB->Location = Drawing::Point(x,y);
				Player_PB->Image = ListaImgJogador->Images[ImagemJogador];//actualiza a imagem com a direccao que esta a ir o jogador
			
			
		 }

private: void DesenhaTiros(){
			 	 //Deslocar as balas
				 int yBala = 0;
				 int xBala = 0;
				 int IDBala;
				 PictureBox ^PBTemp=nullptr;
				 if(ListPBTiros->Count > 0){
					for (int i = 0; i < ListPBTiros->Count; i++)
					{
						PBTemp = ListPBTiros[i];//optimizacao, em vez de ir ao array temos um ponteiro para a picturebox actual
						IDBala = int::Parse(PBTemp->Name);
						GMorg->GetPosTiro( IDBala , xBala , yBala);
						PBTemp->Location = System::Drawing::Point(xBala,yBala);	//actualizar a posicao da bala na parte grafica
					}
				 }

		 }

private: void DesenhaInimigos(){
			//Mudar a imagem dos inimigos de acordo com a sua vida
			//se tiver morto iniciar a decrementar o decay cada vez que passa por aqui o programa
			int IniX,IniY;
			if(ListPBInimigos->Count > 0){
				
				if(GMorg->GetNivel() != GMorg->GetTotalNiveis()){//se nao tiver no nivel do boss
					PictureBox ^PBTemp2=nullptr;
					for (int i = 0; i < ListPBInimigos->Count; i++)
					{
						PBTemp2 = ListPBInimigos[i];
						int IDInimigo = int::Parse(PBTemp2->Name);
						int imagem = GMorg->GetVidaInimigo(IDInimigo);
						if(imagem > 0){
							PBTemp2->Image = ListaImgInimigos->Images[imagem];
							GMorg->GetPosInimigo(IDInimigo,IniX,IniY);
							PBTemp2->Location = System::Drawing::Point(IniX,IniY);
						}
						else
						{
							if(GMorg->getDecayInimigo(IDInimigo) > 0 && PBTemp2->Visible){
								PBTemp2->Image = ListaImgInimigos->Images[imagem];
								GMorg->ReduzDecayInimigo(IDInimigo);
							}
							else if(PBTemp2->Visible)
							{
								PBTemp2->Visible = false;
							}

						}
					}
				}
				else{//NIVEL BOSS!!!!!!!!!!!!!!!!!!!
					int sizeW,sizeH;
					int x,y;

					GMorg->GetSizeInimigo(sizeW,sizeH);
					GMorg->GetPosInimigo(1,x,y);//obter a posicao do inimigo
					
					ListPBInimigos[0]->Location = Drawing::Point(x ,  y ); //posiciona a cabeca
					ListPBInimigos[0]->Size = System::Drawing::Size(sizeW ,sizeH); //coloca o tamanho da cabeca
					
					//calcula o tamanho da boca
					 float ratioW = (float)sizeW/(float)BossSizeFinal_W;
					 float ratioH = (float)sizeH/(float)BossSizeFinal_H;

					 int bocax = x+ (int)((float)BossBoca_X * ratioW);
					 int bocay= y+ (int)((float)BossBoca_Y * ratioH);
					 
					 if(GMorg->getEstadoBoca()){//posiciona a boca em estado aberto ou fechado
						 bocay += (int)((float)BossBoca_H*(ratioH));
					 }

					 ListPBInimigos[1]->Location = Drawing::Point(bocax ,  bocay ); //posiciona a boca
					 ListPBInimigos[1]->Size = System::Drawing::Size((int)((float)BossBoca_W*(ratioW)), (int)((float)BossBoca_H*(ratioH)));//coloca o tamanho da boca
					 
					}
				
			}
		 }
private: void ActualizarDados(){
			if(ContarActualizaDados == 0){
				//Escrever nas labels os pontos, vida e nivel actual
				String ^points =  Convert::ToString(GMorg->GetPoints());
				Points_LB->Text = points;
				String ^lifes =  Convert::ToString(GMorg->GetVidas());
				Lifes_LB->Text = lifes;
				String ^level =  Convert::ToString(GMorg->GetNivel());
				Level_LB->Text = level;
				String ^username =  ConverterstringToString(GMorg->GetUserName());
				username_LB->Text = username;
				String ^HScore = Convert::ToString(GMorg->GetHScore());
				hscore_LB->Text = HScore;
				ContarActualizaDados = TimerActualizaDados;
			}
			else
				ContarActualizaDados--;
		 }

private: System::Void scrbrd_BTN_Click(System::Object^  sender, System::EventArgs^  e) {
			 	FormTabela ^Tabela = gcnew FormTabela(GMorg);
				if (Tabela->ShowDialog() == Windows::Forms::DialogResult::OK){
				 //scrbrd_BTN->DialogResult
				}
				
		 }
};
}


