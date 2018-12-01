#ifndef _HEAD_HRIZEN_
#define _HEAD_HRIZEN_
#include <windows.h>

class ConsoleWindow;

//分割线
class Spliter {
public:
	WORD attribute; //字符样式
	COORD position; //位置
	SHORT length; //宽度/高度
	Spliter(ConsoleWindow* window, COORD pos, SHORT len, bool verticle, WORD attr = 7);
	~Spliter();
	//从屏幕清除
	void Clear();
	//移动或重新设置长度
	void Move(COORD position, SHORT len);
private:
	//绘制或清除
	void draw(bool clear = false);
	ConsoleWindow* window; //所属窗口
	bool verticle; //水平或者垂直分割线
};

#endif // !_HEAD_HRIZEN_

