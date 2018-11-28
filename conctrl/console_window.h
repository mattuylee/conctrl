#ifndef _HEAD_CONSOLE_WINDOW_
#define _HEAD_CONSOLE_WINDOW_
#include <windows.h>
#include <vector>
#include "pannel.h"
#include "spliter.h"

class ConsoleWindow {
public:
	//����̨���
	HANDLE hInput;
	HANDLE hOutput;
	HANDLE hError;
	//��������С
	COORD bufferSize;
	ConsoleWindow(SHORT width = 80, SHORT height = 40);
	~ConsoleWindow();
	//��ʼ������̨���ڲ���
	bool InitWindow();
	//���ô��ڴ�С
	bool Resize(COORD size);
	//��������
	Pannel* NewPannel(SMALL_RECT rect);
	//�����ָ���
	Spliter* NewSpliter(COORD pos, SHORT len, bool verticle, WORD attr = 2);
	//�Ƴ�����
	void RemovePannel(Pannel* pannel);
	//�Ƴ��ָ���
	void RemoveSpliter(Spliter* spliter);
private:
	//����
	std::vector<Pannel*> pannels;
	//�ָ���
	std::vector<Spliter*> spliters;
};
#endif
