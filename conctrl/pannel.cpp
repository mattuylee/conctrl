#include "console_window.h"
#include "pannel.h"

Pannel::Pannel(ConsoleWindow* _controller, SMALL_RECT rect) {
	this->window = _controller;
	this->area = rect;
	this->from = -1; //默认打印最新行
	this->maxLineCount = 4096;
}
//设置最大行数
void Pannel::SetMaxLine(SHORT lineCount) {
	if (lineCount < 0) lineCount = 0;
	this->maxLineCount = lineCount;
	if (this->lines.size() > (size_t)maxLineCount) {
		std::vector<Line>::iterator from = this->lines.begin() + this->lines.size() - maxLineCount;
		std::vector<Line>::iterator to = this->lines.begin();
		do {
			*(to++) = *(from++);
		} while (from != this->lines.end());
	} //移除超出行
}
//清空文本缓存
void Pannel::Clear() {
	COORD coord;
	coord.X = this->area.Left;
	coord.Y = this->area.Top;
	this->clearScreen();
	this->lines.clear();
	this->from = -1;
}

//改变窗口大小
void Pannel::Move(SMALL_RECT rect) {
	if (rect.Right - rect.Left == this->area.Right - this->area.Left || !this->lines.size()) {
		this->area = rect;
		this->Flush();
		return;
	} //不改变宽度或内容为空
	this->clearScreen();
	this->area = rect;
	//统计'真'行，即自然分行的行
	std::vector<Line> newLines;
	newLines.push_back(this->lines.front());
	for (size_t i = 1; i < this->lines.size(); i++) {
		if (isTrueLine(newLines.back())) newLines.push_back(this->lines.at(i));
		else newLines.at(newLines.size() - 1).text += this->lines.at(i).text;
	}
	this->lines.clear();
	for (size_t i = 0; i < newLines.size(); i++) {
		std::vector<std::string> textLines = splitToLines(newLines.at(i).text);
		for (size_t j = 0; j < textLines.size(); j++) {
			Line line;
			line.attribute = newLines.at(i).attribute;
			line.text = textLines.at(j);
			this->lines.push_back(line);
		}
	} //重新分割文本行
	this->Flush();
}
/**
 * 向窗格添加文本
 * @return value, 成功返回true, 否则返回false
 * @param text, 要写入的文本
 * @param attribute, 文本属性，详见 FORGROUND_*和BACKGROUND_* 常量
 */
void Pannel::AddText(std::string text, int attribute) {
	//将要添加的文本与最后一行拼接。否则每次调用本函数将直接写到新行
	if (this->lines.size() > 0 && !this->isTrueLine(lines.back())) {
		text = this->lines.back().text + text;
		lines.pop_back();
	}
	//将文本分割成文本行，加入到行数组中
	std::vector<std::string> textLines = splitToLines(text);
	int toDeleteCount = (this->lines.size() + textLines.size()) - this->maxLineCount;
	for (int i = 0; i < toDeleteCount; i++) {
		this->lines.erase(this->lines.begin());
	} //移动数组，删除超出最大范围的文本行
	for (size_t i = 0; i < textLines.size(); i++) {
		Line line;
		line.text = textLines.at(i);
		line.attribute = attribute;
		this->lines.push_back(line);
	} //加入新的文本行
	this->Flush();
}
//添加行
void Pannel::AddLine(std::string text, int attribute) {
	if (text.size() && !this->isTrueLine(text)) text += '\n';
	this->AddText(text, attribute);
};

//刷新显示
void Pannel::Flush() {
	int lineCount = this->area.Bottom - this->area.Top + 1; //窗格可显示行数(去除边框)
	int charCount = this->area.Right - this->area.Left + 1; //每行可显示字符数（去除边框）
	//如果窗格尺寸太小无法显示字符
	if (this->lines.size() == 0
		|| lineCount <= 0
		|| charCount <= 0)
		return;
	this->clearScreen(); //清屏
	if (this->lines.size() == 0) return; //空缓冲区
	//获取迭代起点
	std::vector<Line>::iterator iter;
	if (this->lines.size() <= (size_t)lineCount) {
		iter = this->lines.begin();
	} //显示所有行
	else if (this->from < 0 || this->from >= this->lines.size()) {
		iter = this->lines.end() - lineCount;
	} //显示最后一屏
	else {
		iter = this->lines.begin() + this->from;
	} //显示特定屏
	//写文本行
	COORD lineStart = { 0, 0 };
	for (size_t i = 0; i < (size_t)lineCount; i++) {
		DWORD writtenCount;
		//获取除去换行符的字符长度
		int length = iter->text.size();
		length = isTrueLine(*iter) ? length - 1 : length;
		lineStart = { area.Left, area.Top + SHORT(i)}; //开始写的位置
		FillConsoleOutputAttribute(this->window->hOutput, iter->attribute, charCount, lineStart, &writtenCount);
		WriteConsoleOutputCharacter(this->window->hOutput, iter->text.c_str(), length, lineStart, &writtenCount);
		if (++iter == this->lines.end()) break;
	}
}

//向前滚动
bool Pannel::ScrollBackward(int lineCount) {
	int to = this->from;
	if (this->from == 0 || lineCount < 0)	return false;
	else if (this->from > 0)	to -= lineCount;
	else	to = this->lines.size() - lineCount - 1;
	return ScrollTo(to < 0 ? 0 : to);
}
//向后滚动
bool Pannel::ScrollForward(int lineCount) {
	int to = this->from;
	if (this->from < 0 || lineCount < 0)	return false;
	else	to += lineCount;
	return ScrollTo(to < (int)this->lines.size() ? to : -1);
}
//滚到
bool Pannel::ScrollTo(int line) {
	if (line >= (int)this->lines.size()) return false;
	int to = line < 0 ? -1 : line;
	if (this->from != to) {
		this->from = to;
		this->Flush();
	}
	return true;
}

//聚焦
bool Pannel::Focus(COORD _coord){
	if (_coord.X < 0 || _coord.Y < 0
		|| _coord.X > this->area.Right - this->area.Left
		|| _coord.Y > this->area.Bottom - this->area.Top) {
		return false;
	}
	COORD coord;
	coord.X = this->area.Left + _coord.X;
	coord.Y = this->area.Top + _coord.Y;
	return SetConsoleCursorPosition(this->window->hOutput, coord);
}

//将文本分割为若干行，至少保证一行
std::vector<std::string> Pannel::splitToLines(std::string _text) {
	int charCount = this->area.Right - this->area.Left + 1;
	if (charCount <= 0) {
		charCount = 0x7FFFFFFF;
	} //不断行，仅自然换行
	std::vector<std::string> textLines; //分割结果集
	//得到文本的字符数组
	const char* text = _text.c_str();
	int start = 0; //行扫描开始位置
	std::string line = ""; //当前扫描行
	do {
		int i;
		line = "";
		for (i = 0; text[start + i] && i < charCount; i++) {
			if (text[start + i] == '\r' || text[start + i] == '\n') {
				line += "\r\n";
				break;
			} //自然换行的行尾保留换行符
			//行最后一个字符无法显示双字节字符
			if (i == charCount - 1 && text[i + start] > 127) break;
			line += text[i + start];
		} //扫描一行（已计算边框）
		//过滤换行符
		start += i;
		if (text[start] == '\r')
			start++;
		if (text[start] == '\n')
			start++;
		textLines.push_back(line);
	} while (text[start]);
	return textLines;
}

//判断是否自然分行
bool Pannel::isTrueLine(std::string line) {
	if (!line.size()) return false;
	else if (line.back() == '\n') return true;
	else return false;
}
bool Pannel::isTrueLine(Line line) {
	return this->isTrueLine(line.text);
}
//清屏
void Pannel::clearScreen() {
	DWORD written;
	for (SHORT i = 0; i < this->area.Bottom - this->area.Top + 1; i++) {
		COORD coord = { this->area.Left, this->area.Top + i };
		FillConsoleOutputCharacter(this->window->hOutput, ' ', this->area.Right - this->area.Left + 1, coord, &written);
	}
}

