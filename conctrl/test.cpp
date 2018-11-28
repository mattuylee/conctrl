#include <iostream>
#include "conctrl.h"
int main() {
	ConsoleWindow* window = CreateConsoleWindow(80, 40);
	Pannel* writePannel = window->CreatePannel({ 0, 0, 79, 24 });
	Pannel* messagePannel = window->CreatePannel({ 0, 26, 79, 39 });
	Spliter* spliter = window->CreateSpliter({ 0, 25 }, 80, false, FOREGROUND_GREEN);
	messagePannel->AddLine("hello world.");
	writePannel->Focus({ 0,0 });
	getchar();
}