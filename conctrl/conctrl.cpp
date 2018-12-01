#define _CRT_SECURE_NO_WARNINGS
#include "console_window.h"
#include "pannel.h"
#include "spliter.h"
#include "coding.h"
#include "conctrl.h"

//������ǰ����̨���ڶ�Ӧ�Ŀ��ƴ���
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

//�������ô��ںͻ�������С
bool ResizeScreenBuffer(ConsoleWindow* window, int width, int height) {
	if (width <= 5 || height <= 5 || width > 32767 || height > 32767)
		return false;
	return window->Resize({ (SHORT)width, (SHORT)height });
}
//���ÿ���̨���ڱ���
bool SetConsoleWindowTitle(char* _title, bool utf8) {
	if (utf8) {
		std::string title;
		title = UTF8ToANSI(_title);
		return SetConsoleTitle(title.c_str());
	}
	return SetConsoleTitle(_title);
}
//����һ������
Pannel* CreatePannel(ConsoleWindow* window, int left, int top, int width, int height) {
	if (left < 0 || top < 0
		|| left > 32767 || top > 32767 || width > 32767 || height > 32767
		) return NULL;
	return window->NewPannel({ (SHORT)left, (SHORT)top, (SHORT)(left + width - 1), (SHORT)(top + height - 1) });
}
//ɾ������
void DestroyPannel(ConsoleWindow* window, Pannel* pannel) {
	window->RemovePannel(pannel);
}
//����Pannel�л����С
bool SetMaxLineCache(Pannel* pannel, int lineCount) {
	if (lineCount < 0) return false;
	pannel->maxLineCount = lineCount;
	return true;
}
//��Pannel������ı�
void AddPannelText(Pannel* pannel, const char* _text, bool focus, bool utf8, int attribute) {
	std::string text;
	if (utf8)	text = UTF8ToANSI(_text);
	else	text = _text;
	pannel->AddText(text, focus, attribute);
}
//��Pannel�������
void AddPannelLine(Pannel* pannel, const char* _text, bool focus, bool utf8, int attribute) {
	std::string text;
	if (utf8)	text = UTF8ToANSI(_text);
	else	text = _text;
	pannel->AddLine(text, focus, attribute);
}
//���Pannel
void ClearPannel(Pannel* pannel) {
	pannel->Clear();
}
//�ƶ���ı�Pannel��С
bool MovePannel(Pannel* pannel, int left, int top, int width, int height) {
	if(left > 32767 || top > 32767 || width > 32767 || height > 32767) return false;
	if (left < 0)	left = pannel->area.Left;
	if (top < 0)	top = pannel->area.Top;
	if (width <= 5)	width = pannel->area.Right - pannel->area.Left + 1;
	if (height <= 5)	height = pannel->area.Bottom - pannel->area.Top+ 1;
	pannel->Move({ (SHORT)left, (SHORT)top, (SHORT)(left + width - 1), (SHORT)(top + height - 1)});
	return true;
}
//��ǰ����
bool ScrollPannelBackward(Pannel* pannel, int lineCount) {
	return pannel->ScrollBackward(lineCount);
}
//������
bool ScrollPannelForward(Pannel* pannel, int lineCount) {
	return pannel->ScrollForward(lineCount);
}
//�������ض���
bool ScrollPannelTo(Pannel* pannel, int lineTo) {
	return pannel->ScrollTo(lineTo);
}
//��������õ�������ض�λ��
bool FocusOnPannel(Pannel* pannel, int offsetLeft, int offsetTop) {
	return pannel->Focus({ (SHORT)offsetLeft, (SHORT)offsetTop });
}
//����һ���ָ��ߡ�
Spliter* CreateSpliter(ConsoleWindow* window, int left, int top, int length, bool verticle, int attribute) {
	if (length <= 0
		|| left < 0 || left >= window->bufferSize.X
		|| top < 0 || top >= window->bufferSize.Y
		) return NULL;
	return window->NewSpliter({ (SHORT)left, (SHORT)top}, length, verticle, attribute);
}
//ɾ���ָ���
void DestroySpliter(ConsoleWindow* window, Spliter* spliter) {
	window->RemoveSpliter(spliter);
}
//�ƶ��������趨�ָ��߳���
bool MoveSpliter(Spliter* spliter, int left, int top, int len) {
	if (left < 0 || left > 32767 || top < 0 || top > 32767 || len < 0) return false;
	spliter->Move({ (SHORT)left, (SHORT)top }, len);
	return true;
}
