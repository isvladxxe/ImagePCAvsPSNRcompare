#include "MainForm.h"
using namespace DiplomaPCA; //name of your project

[STAThreadAttribute]
int main(cli::array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MainForm());
	return 0;
}