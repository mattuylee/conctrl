#define _CRT_SECURE_NO_WARNINGS
#include "console_window.h"
#include "pannel.h"
#include "spliter.h"
#include "coding.h"
#include "conctrl.h"

//创建当前控制台窗口对应的控制窗口
ConsoleWindow* CreateConsoleWindow(int width, int height) {
	if (width <= 5 || height <= 5 || width > 32767 || height > 32767)
		return new(std::nothrow)  ConsoleWindow();
	else {
		return new(std::nothrow) ConsoleWindow(width, height);
	}
}

void DestroyConsoleWindow(ConsoleWindow* window) {
	delete window;
}

//重新设置窗口和缓冲区大小
bool ResizeScreenBuffer(ConsoleWindow* window, int width, int height) {
	if (width <= 5 || height <= 5 || width > 32767 || height > 32767)
		return false;
	return window->Resize({ (SHORT)width, (SHORT)height });
}
//设置控制台窗口标题
bool SetConsoleWindowTitle(char* _title, bool utf8) {
	if (utf8) {
		std::string title;
		title = UTF8ToANSI(_title);
		return SetConsoleTitle(title.c_str());
	}
	return SetConsoleTitle(_title);
}
//创建一个窗格
Pannel* CreatePannel(ConsoleWindow* window, int left, int top, int width, int height) {
	if (left < 0 || top < 0
		|| left > 32767 || top > 32767 || width > 32767 || height > 32767
		) return NULL;
	return window->NewPannel({ (SHORT)left, (SHORT)top, (SHORT)(left + width - 1), (SHORT)(top + height - 1) });
}
//删除窗格
void DestroyPannel(ConsoleWindow* window, Pannel* pannel) {
	window->RemovePannel(pannel);
}
//设置Pannel行缓存大小
bool SetMaxLineCache(Pannel* pannel, int lineCount) {
	if (lineCount < 0) return false;
	pannel->maxLineCount = lineCount;
	return true;
}
//向Pannel中添加文本
void AddPannelText(Pannel* pannel, const char* _text, bool focus, bool utf8, int attribute) {
	std::string text;
	if (utf8)	text = UTF8ToANSI(_text);
	else	text = _text;
	pannel->AddText(text, focus, attribute);
}
//向Pannel中添加行
void AddPannelLine(Pannel* pannel, const char* _text, bool focus, bool utf8, int attribute) {
	std::string text;
	if (utf8)	text = UTF8ToANSI(_text);
	else	text = _text;
	pannel->AddLine(text, focus, attribute);
}
//清空Pannel
void ClearPannel(Pannel* pannel) {
	pannel->Clear();
}
//移动或改变Pannel大小
bool MovePannel(Pannel* pannel, int left, int top, int width, int height) {
	if(left > 32767 || top > 32767 || width > 32767 || height > 32767) return false;
	if (left < 0)	left = pannel->area.Left;
	if (top < 0)	top = pannel->area.Top;
	if (width <= 5)	width = pannel->area.Right - pannel->area.Left + 1;
	if (height <= 5)	height = pannel->area.Bottom - pannel->area.Top+ 1;
	pannel->Move({ (SHORT)left, (SHORT)top, (SHORT)(left + width - 1), (SHORT)(top + height - 1)});
	return true;
}
//向前滚屏
bool ScrollPannelBackward(Pannel* pannel, int lineCount) {
	return pannel->ScrollBackward(lineCount);
}
//向后滚屏
bool ScrollPannelForward(Pannel* pannel, int lineCount) {
	return pannel->ScrollForward(lineCount);
}
//滚动到特定行
bool ScrollPannelTo(Pannel* pannel, int lineTo) {
	return pannel->ScrollTo(lineTo);
}
//将光标设置到窗格的特定位置
bool FocusOnPannel(Pannel* pannel, int offsetLeft, int offsetTop) {
	return pannel->Focus({ (SHORT)offsetLeft, (SHORT)offsetTop });
}
//创建一条分隔线。
Spliter* CreateSpliter(ConsoleWindow* window, int left, int top, int length, bool verticle, int attribute) {
	if (length <= 0
		|| left < 0 || left >= window->bufferSize.X
		|| top < 0 || top >= window->bufferSize.Y
		) return NULL;
	return window->NewSpliter({ (SHORT)left, (SHORT)top}, length, verticle, attribute);
}
//删除分隔线
void DestroySpliter(ConsoleWindow* window, Spliter* spliter) {
	window->RemoveSpliter(spliter);
}
//移动或重新设定分隔线长度
bool MoveSpliter(Spliter* spliter, int left, int top, int len) {
	if (left < 0 || left > 32767 || top < 0 || top > 32767 || len < 0) return false;
	spliter->Move({ (SHORT)left, (SHORT)top }, len);
	return true;
}
