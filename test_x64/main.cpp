#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "conctrl.h"
#pragma comment(lib, "conctrl.lib")
int main() {
	ConsoleWindow* window = CreateConsoleWindow(80, 40);
	Pannel* messagePannel = CreatePannel(window, 0, 0, 78, 25);
	Pannel* writePannel = CreatePannel(window, 0, 26, 80, 40);
	Spliter* spliter = CreateSpliter(window, 0, 25, 80, false, FOREGROUND_GREEN);
	AddPannelText(messagePannel, "请在下方输入任意内容", true, true, 7);
	FocusOnPannel(writePannel, 0, 0);
	while (true) {
		char text[1024];
		gets(text);
		AddPannelText(messagePannel, text, false, false, FOREGROUND_RED | FOREGROUND_GREEN);
		ClearPannel(writePannel);
		FocusOnPannel(writePannel, 0, 0);
	}
}