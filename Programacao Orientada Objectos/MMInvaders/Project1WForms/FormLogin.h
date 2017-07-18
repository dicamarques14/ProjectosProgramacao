#pragma once
#include "FormTabela.h"
#include "GestaoTudo.h"

namespace Project1WForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormLogin
	/// </summary>
	public ref class FormLogin : public System::Windows::Forms::Form
	{
		GestaoTudo *ref_g;
	public:
		FormLogin(GestaoTudo *g)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			ref_g = g;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormLogin()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormLogin::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::ForestGreen;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Location = System::Drawing::Point(134, 114);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 35);
			this->button1->TabIndex = 2;
			this->button1->Text = L"&Login";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &FormLogin::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(130, 36);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Location = System::Drawing::Point(41, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Username:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(44, 78);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(80, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Password:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(130, 77);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Gold;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button2->Location = System::Drawing::Point(28, 114);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(96, 35);
			this->button2->TabIndex = 3;
			this->button2->Text = L"&Create User";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &FormLogin::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(91, 7);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &FormLogin::button3_Click);
			// 
			// FormLogin
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(264, 181);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(280, 220);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(280, 220);
			this->Name = L"FormLogin";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Login";
			this->Load += gcnew System::EventHandler(this, &FormLogin::FormLogin_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //fazer o login da conta

			 String^ user = textBox1->Text;
			 String^ pass = textBox2-> Text;
			 if((user->Length != 0) && (pass->Length !=0))
			 {
				string usernew, passnew;
				usernew = ConverterStringTostring(user);
				passnew = ConverterStringTostring(pass);
				if(ref_g->ProcurarUtilizador(usernew, passnew)){
					//String^ Mensagem = "Bem-vindo " + user;
					String^ Mensagem = "Welcome " + user;
					MessageBox::Show( Mensagem );
					Form::Close();
				}
				else
					// MessageBox::Show("Cuidado! Username ou password errada");
					MessageBox::Show("Username and password don't match");
			 }
			else
				//MessageBox::Show("Preencha o(s) campo(s) em falta para fazer login! Obrigado!");
				MessageBox::Show("Please fill all the fields to login!");
		 }

	/// Permite Converter uma String numa cadeia de caracteres (char *)
	/// e alocada mem�ria!, NAO ESQUECER DE DESALOCAR !!!!!
	private: char *ConverterStringToChar(String ^s)
	 {
		 int nc = s->Length;
		 char *dados = new char[nc+1];
		 for(int i = 0; i < nc ; i++)
			 dados[i] = (char)s[i];
		 dados[nc]='\0';
		 return dados;
	 }
	/// Permite Converter uma String numa string
	private: string ConverterStringTostring(String ^s)
	 {
		char *ptr_string = ConverterStringToChar(s);
		string value(ptr_string);
		delete [] ptr_string;
		return value;
	 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 //criar nova conta
			 String^ user = textBox1->Text;
			 String^ pass = textBox2-> Text;
			 if((user->Length != 0) && (pass->Length !=0))
			 {
				string usernew, passnew;
				usernew = ConverterStringTostring(user);
				passnew = ConverterStringTostring(pass);
				if(!ref_g->ExisteUtilizador(usernew)){
					ref_g->CriarContaUtilizador(usernew, passnew);
					//MessageBox::Show( "Conta criada com sucesso" );
					MessageBox::Show( "User successfully created!" );
				}
				else
					//MessageBox::Show("Utilizador j� existe!");
					MessageBox::Show("User already exists!");
			 }
			else
				//MessageBox::Show("Preencha o(s) campo(s) em falta para poder criar uma nova conta! Obrigado!");
				MessageBox::Show("Please fill all the fields to create a new user!");
		 }	
	private: System::Void FormLogin_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 	FormTabela ^Tabela = gcnew FormTabela(ref_g);
				Tabela->Show();
		 }
};
}
