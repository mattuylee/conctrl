#include "console_window.h"
#include "pannel.h"

Pannel::Pannel(ConsoleWindow* _controller, SMALL_RECT rect) {
	this->window = _controller;
	this->area = rect;
	this->from = -1; //Ĭ�ϴ�ӡ������
	this->maxLineCount = 4096;
}
//�����������
void Pannel::SetMaxLine(SHORT lineCount) {
	if (lineCount < 0) lineCount = 0;
	this->maxLineCount = lineCount;
	if (this->lines.size() > (size_t)maxLineCount) {
		std::vector<Line>::iterator from = this->lines.begin() + this->lines.size() - maxLineCount;
		std::vector<Line>::iterator to = this->lines.begin();
		do {
			*(to++) = *(from++);
		} while (from != this->lines.end());
	} //�Ƴ�������
}
//����ı�����
void Pannel::Clear() {
	COORD coord;
	coord.X = this->area.Left;
	coord.Y = this->area.Top;
	this->clearScreen();
	this->lines.clear();
	this->from = -1;
}

//�ı䴰�ڴ�С
void Pannel::Move(SMALL_RECT rect) {
	if (rect.Right - rect.Left == this->area.Right - this->area.Left || !this->lines.size()) {
		this->area = rect;
		this->Flush();
		return;
	} //���ı��Ȼ�����Ϊ��
	this->clearScreen();
	this->area = rect;
	//ͳ��'��'�У�����Ȼ���е���
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
	} //���·ָ��ı���
	this->Flush();
}
/**
 * �򴰸�����ı�
 * @return value, �ɹ�����true, ���򷵻�false
 * @param text, Ҫд����ı�
 * @param attribute, �ı����ԣ���� FORGROUND_*��BACKGROUND_* ����
 */
void Pannel::AddText(std::string text, int attribute) {
	//��Ҫ��ӵ��ı������һ��ƴ�ӡ�����ÿ�ε��ñ�������ֱ��д������
	if (this->lines.size() > 0 && !this->isTrueLine(lines.back())) {
		text = this->lines.back().text + text;
		lines.pop_back();
	}
	//���ı��ָ���ı��У����뵽��������
	std::vector<std::string> textLines = splitToLines(text);
	int toDeleteCount = (this->lines.size() + textLines.size()) - this->maxLineCount;
	for (int i = 0; i < toDeleteCount; i++) {
		this->lines.erase(this->lines.begin());
	} //�ƶ����飬ɾ���������Χ���ı���
	for (size_t i = 0; i < textLines.size(); i++) {
		Line line;
		line.text = textLines.at(i);
		line.attribute = attribute;
		this->lines.push_back(line);
	} //�����µ��ı���
	this->Flush();
}
//�����
void Pannel::AddLine(std::string text, int attribute) {
	if (text.size() && !this->isTrueLine(text)) text += '\n';
	this->AddText(text, attribute);
};

//ˢ����ʾ
void Pannel::Flush() {
	int lineCount = this->area.Bottom - this->area.Top + 1; //�������ʾ����(ȥ���߿�)
	int charCount = this->area.Right - this->area.Left + 1; //ÿ�п���ʾ�ַ�����ȥ���߿�
	//�������ߴ�̫С�޷���ʾ�ַ�
	if (this->lines.size() == 0
		|| lineCount <= 0
		|| charCount <= 0)
		return;
	this->clearScreen(); //����
	if (this->lines.size() == 0) return; //�ջ�����
	//��ȡ�������
	std::vector<Line>::iterator iter;
	if (this->lines.size() <= (size_t)lineCount) {
		iter = this->lines.begin();
	} //��ʾ������
	else if (this->from < 0 || this->from >= this->lines.size()) {
		iter = this->lines.end() - lineCount;
	} //��ʾ���һ��
	else {
		iter = this->lines.begin() + this->from;
	} //��ʾ�ض���
	//д�ı���
	COORD lineStart = { 0, 0 };
	for (size_t i = 0; i < (size_t)lineCount; i++) {
		DWORD writtenCount;
		//��ȡ��ȥ���з����ַ�����
		int length = iter->text.size();
		length = isTrueLine(*iter) ? length - 1 : length;
		lineStart = { area.Left, area.Top + SHORT(i)}; //��ʼд��λ��
		FillConsoleOutputAttribute(this->window->hOutput, iter->attribute, charCount, lineStart, &writtenCount);
		WriteConsoleOutputCharacter(this->window->hOutput, iter->text.c_str(), length, lineStart, &writtenCount);
		if (++iter == this->lines.end()) break;
	}
}

//��ǰ����
bool Pannel::ScrollBackward(int lineCount) {
	int to = this->from;
	if (this->from == 0 || lineCount < 0)	return false;
	else if (this->from > 0)	to -= lineCount;
	else	to = this->lines.size() - lineCount - 1;
	return ScrollTo(to < 0 ? 0 : to);
}
//������
bool Pannel::ScrollForward(int lineCount) {
	int to = this->from;
	if (this->from < 0 || lineCount < 0)	return false;
	else	to += lineCount;
	return ScrollTo(to < (int)this->lines.size() ? to : -1);
}
//����
bool Pannel::ScrollTo(int line) {
	if (line >= (int)this->lines.size()) return false;
	int to = line < 0 ? -1 : line;
	if (this->from != to) {
		this->from = to;
		this->Flush();
	}
	return true;
}

//�۽�
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

//���ı��ָ�Ϊ�����У����ٱ�֤һ��
std::vector<std::string> Pannel::splitToLines(std::string _text) {
	int charCount = this->area.Right - this->area.Left + 1;
	if (charCount <= 0) {
		charCount = 0x7FFFFFFF;
	} //�����У�����Ȼ����
	std::vector<std::string> textLines; //�ָ�����
	//�õ��ı����ַ�����
	const char* text = _text.c_str();
	int start = 0; //��ɨ�迪ʼλ��
	std::string line = ""; //��ǰɨ����
	do {
		int i;
		line = "";
		for (i = 0; text[start + i] && i < charCount; i++) {
			if (text[start + i] == '\r' || text[start + i] == '\n') {
				line += "\r\n";
				break;
			} //��Ȼ���е���β�������з�
			//�����һ���ַ��޷���ʾ˫�ֽ��ַ�
			if (i == charCount - 1 && text[i + start] > 127) break;
			line += text[i + start];
		} //ɨ��һ�У��Ѽ���߿�
		//���˻��з�
		start += i;
		if (text[start] == '\r')
			start++;
		if (text[start] == '\n')
			start++;
		textLines.push_back(line);
	} while (text[start]);
	return textLines;
}

//�ж��Ƿ���Ȼ����
bool Pannel::isTrueLine(std::string line) {
	if (!line.size()) return false;
	else if (line.back() == '\n') return true;
	else return false;
}
bool Pannel::isTrueLine(Line line) {
	return this->isTrueLine(line.text);
}
//����
void Pannel::clearScreen() {
	DWORD written;
	for (SHORT i = 0; i < this->area.Bottom - this->area.Top + 1; i++) {
		COORD coord = { this->area.Left, this->area.Top + i };
		FillConsoleOutputCharacter(this->window->hOutput, ' ', this->area.Right - this->area.Left + 1, coord, &written);
	}
}

