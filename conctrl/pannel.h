#ifndef _HEAD_PANNEL_
#define _HEAD_PANNEL_

class ConsoleWindow; 

//声明一行
struct Line {
	WORD attribute;
	std::string text;
};
//定义窗格
class Pannel {
public:
	SHORT maxLineCount; //最大保存文本行数
	SMALL_RECT area; //窗格区域（包含边框）
	Pannel(ConsoleWindow* window, SMALL_RECT rect);
	//设置最大缓存行数
	void SetMaxLine(SHORT lineCount);
	//清空窗格文本
	void Clear();
	//移动窗格和重新设置大小
	void Move(SMALL_RECT rect);
	//向窗格中加入文本
	void AddText(std::string text, int attribute = 7);
	//向窗格中加入文本行
	void AddLine(std::string text, int attribute = 7);
	//从特定行开始打印一屏。若this.from无效则打印最后一屏
	void Flush();
	//向前滚动，当前已到达最前页返回false，否则返回true
	bool ScrollBackward(int lineCount);
	//向后滚动，当前已到达最后页返回false，否则返回true
	bool ScrollForward(int lineCount);
	//滚动到某一行，行号无效则滚动到最后
	bool ScrollTo(int line);
	//将光标定位到此窗格的相对位置
	bool Focus(COORD coord);
private:
	size_t from; //从这一行开始显示
	ConsoleWindow* window; //所属的控制台窗口
	std::vector<Line> lines; //窗格文本行，自动拆分
	//将文本分割为若干行。至少保证返回一行
	std::vector<std::string> splitToLines(std::string text);
	//判断是否自然分行
	bool isTrueLine(std::string line);
	bool isTrueLine(Line line);
	//清屏
	void clearScreen();
};

#endif // !_HEAD_PANNEL_
