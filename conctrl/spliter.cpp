#include "spliter.h"
#include "console_window.h"

Spliter::Spliter(ConsoleWindow* window, COORD pos, SHORT len, bool verticle, WORD attr) {
	this->window = window;
	this->position = pos;
	this->length = len;
	this->verticle = verticle;
	this->attribute = attr;
	this->draw();
}

Spliter::~Spliter() {
	this->Clear();
}

void Spliter::Clear() {
	this->draw(true);
}

//�ƶ������ó���
void Spliter::Move(COORD _position, SHORT len) {
	this->position = _position;
	this->length = len;
	this->draw();
}

//���ƻ����
void Spliter::draw(bool clear) {
	DWORD written;
	COORD curPosition = this->position;
	//�趨�����
	const char* spliter;
	if (clear) spliter = "  ";
	else spliter = this->verticle ? "��" : "��";
	//ȡ��������
	SHORT* direct = this->verticle ? &curPosition.Y : &curPosition.X;
	//���ָ���
	for (; *direct < this->length; ) {
		FillConsoleOutputAttribute(this->window->hOutput, this->attribute, 2, curPosition, &written);
		WriteConsoleOutputCharacter(this->window->hOutput, spliter, 2, curPosition, &written);
		this->verticle ? curPosition.Y += 1 : curPosition.X += 2;
	}
}
