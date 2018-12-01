#include "console_window.h"

ConsoleWindow::ConsoleWindow(SHORT width, SHORT height) {
	this->bufferSize = { width, height };
	InitWindow();
}
ConsoleWindow::~ConsoleWindow() {
	for (size_t i = 0; i < this->pannels.size(); i++)	delete pannels.at(i);
	for (size_t i = 0; i < this->spliters.size(); i++)	delete spliters.at(i);
}
//初始化
bool ConsoleWindow::InitWindow() {
	this->hInput = GetStdHandle(STD_INPUT_HANDLE);
	this->hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	this->hError = GetStdHandle(STD_ERROR_HANDLE);
	if (!this->hInput || !this->hOutput || !this->hError)
		return false;
	this->Resize(this->bufferSize);
	return true;
}

//重新设定窗口缓冲区大小
bool ConsoleWindow::Resize(COORD size) {
	bool success = false;
	//记录原来的窗口信息
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->hOutput, &info);
	//设置缓冲区大小
	//先将窗口设置得小一点，因为设置的缓冲区大小必须大于窗口大小
	SMALL_RECT rect = { 0, 0, 5, 5 };
	if (!SetConsoleWindowInfo(this->hOutput, true, &rect))
		return false;
	success = SetConsoleScreenBufferSize(hOutput, { size.X, size.Y });
	rect = info.srWindow;
	//调整窗口
	if (rect.Right - rect.Left + 1 > size.X || !success) rect.Right = rect.Left + size.X - 1;
	if (rect.Bottom - rect.Top + 1 > size.Y || !success) rect.Bottom = rect.Top + size.Y - 1;
	SetConsoleWindowInfo(this->hOutput, true, &rect); //还原窗口
	return success;
}

//创建窗格
Pannel* ConsoleWindow::NewPannel(SMALL_RECT rect) {
	Pannel* pannel = new Pannel(this, rect);
	if(pannel)	this->pannels.push_back(pannel);
	return pannel;
}
//创建分割线
Spliter* ConsoleWindow::NewSpliter(COORD pos, SHORT len, bool verticle, WORD attr) {
	Spliter* spliter = new Spliter(this, pos, len, verticle, attr);
	if (spliter)	this->spliters.push_back(spliter);
	return spliter;
}
//移除窗格
void ConsoleWindow::RemovePannel(Pannel* pannel) {
	for (size_t i = 0; i < this->pannels.size(); i++) {
		if (this->pannels.at(i) == pannel) {
			delete this->pannels.at(i);
			this->pannels.erase(this->pannels.begin() + i);
			break;
		}
	}
}
//移除分割线
void ConsoleWindow::RemoveSpliter(Spliter* spliter) {
	for (size_t i = 0; i < this->spliters.size(); i++) {
		if (this->spliters.at(i) == spliter) {
			delete this->spliters.at(i);
			this->spliters.erase(this->spliters.begin() + i);
			break;
		}
	}
}