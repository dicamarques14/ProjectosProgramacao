#include "FormJogo.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Project1WForms;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew FormJogo());
	return 0;
}