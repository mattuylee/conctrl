#ifndef _HEAD_CONSOLE_WINDOW_
#define _HEAD_CONSOLE_WINDOW_
#include <windows.h>
#include <vector>
#include "pannel.h"
#include "spliter.h"

class ConsoleWindow {
public:
	//控制台句柄
	HANDLE hInput;
	HANDLE hOutput;
	HANDLE hError;
	//缓冲区大小
	COORD bufferSize;
	ConsoleWindow(SHORT width = 80, SHORT height = 40);
	~ConsoleWindow();
	//初始化控制台窗口参数
	bool InitWindow();
	//设置窗口大小
	bool Resize(COORD size);
	//创建窗格
	Pannel* NewPannel(SMALL_RECT rect);
	//创建分割线
	Spliter* NewSpliter(COORD pos, SHORT len, bool verticle, WORD attr = 2);
	//移除窗格
	void RemovePannel(Pannel* pannel);
	//移除分割线
	void RemoveSpliter(Spliter* spliter);
private:
	//窗格
	std::vector<Pannel*> pannels;
	//分割线
	std::vector<Spliter*> spliters;
};
#endif
