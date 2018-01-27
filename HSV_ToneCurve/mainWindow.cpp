#include "mainWindow.h"

using namespace HSV_ToneCurve;

[STAThreadAttribute]
int main(){
	Application::EnableVisualStyles();
	Application::Run(gcnew mainWindow());
}