#include "console_window.h"

ConsoleWindow::ConsoleWindow(SHORT width, SHORT height) {
	this->bufferSize = { width, height };
	InitWindow();
}
ConsoleWindow::~ConsoleWindow() {
	for (size_t i = 0; i < this->pannels.size(); i++)	delete pannels.at(i);
	for (size_t i = 0; i < this->spliters.size(); i++)	delete spliters.at(i);
}
//��ʼ��
bool ConsoleWindow::InitWindow() {
	this->hInput = GetStdHandle(STD_INPUT_HANDLE);
	this->hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	this->hError = GetStdHandle(STD_ERROR_HANDLE);
	if (!this->hInput || !this->hOutput || !this->hError)
		return false;
	this->Resize(this->bufferSize);
	return true;
}

//�����趨���ڻ�������С
bool ConsoleWindow::Resize(COORD size) {
	//��¼ԭ���Ĵ�����Ϣ
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(this->hOutput, &info);
	//���û�������С
	//�Ƚ��������õ�Сһ�㣬��Ϊ���õĻ�������С������ڴ��ڴ�С
	SMALL_RECT rect = { 0, 0, 5, 5 };
	if (!SetConsoleWindowInfo(this->hOutput, true, &rect))
		return false;
	if (!SetConsoleScreenBufferSize(hOutput, { size.X, size.Y })) {
		SetConsoleWindowInfo(this->hOutput, true, &info.srWindow); //��ԭ����
		return false;
	}
	//���ô��ڴ�С
	rect = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleWindowInfo(this->hOutput, true, &rect);
	return true;
}

//��������
Pannel* ConsoleWindow::NewPannel(SMALL_RECT rect) {
	Pannel* pannel = new Pannel(this, rect);
	if(pannel)	this->pannels.push_back(pannel);
	return pannel;
}
//�����ָ���
Spliter* ConsoleWindow::NewSpliter(COORD pos, SHORT len, bool verticle, WORD attr) {
	Spliter* spliter = new Spliter(this, pos, len, verticle, attr);
	if (spliter)	this->spliters.push_back(spliter);
	return spliter;
}
//�Ƴ�����
void ConsoleWindow::RemovePannel(Pannel* pannel) {
	for (size_t i = 0; i < this->pannels.size(); i++) {
		if (this->pannels.at(i) == pannel) {
			delete this->pannels.at(i);
			this->pannels.erase(this->pannels.begin() + i);
			break;
		}
	}
}
//�Ƴ��ָ���
void ConsoleWindow::RemoveSpliter(Spliter* spliter) {
	for (size_t i = 0; i < this->spliters.size(); i++) {
		if (this->spliters.at(i) == spliter) {
			delete this->spliters.at(i);
			this->spliters.erase(this->spliters.begin() + i);
			break;
		}
	}
}