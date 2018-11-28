#ifndef _HEAD_PANNEL_
#define _HEAD_PANNEL_

class ConsoleWindow; 

//����һ��
struct Line {
	WORD attribute;
	std::string text;
};
//���崰��
class Pannel {
public:
	SHORT maxLineCount; //��󱣴��ı�����
	SMALL_RECT area; //�������򣨰����߿�
	Pannel(ConsoleWindow* window, SMALL_RECT rect);
	//������󻺴�����
	void SetMaxLine(SHORT lineCount);
	//��մ����ı�
	void Clear();
	//�ƶ�������������ô�С
	void Move(SMALL_RECT rect);
	//�򴰸��м����ı�
	void AddText(std::string text, int attribute = 7);
	//�򴰸��м����ı���
	void AddLine(std::string text, int attribute = 7);
	//���ض��п�ʼ��ӡһ������this.from��Ч���ӡ���һ��
	void Flush();
	//��ǰ��������ǰ�ѵ�����ǰҳ����false�����򷵻�true
	bool ScrollBackward(int lineCount);
	//����������ǰ�ѵ������ҳ����false�����򷵻�true
	bool ScrollForward(int lineCount);
	//������ĳһ�У��к���Ч����������
	bool ScrollTo(int line);
	//����궨λ���˴�������λ��
	bool Focus(COORD coord);
private:
	size_t from; //����һ�п�ʼ��ʾ
	ConsoleWindow* window; //�����Ŀ���̨����
	std::vector<Line> lines; //�����ı��У��Զ����
	//���ı��ָ�Ϊ�����С����ٱ�֤����һ��
	std::vector<std::string> splitToLines(std::string text);
	//�ж��Ƿ���Ȼ����
	bool isTrueLine(std::string line);
	bool isTrueLine(Line line);
	//����
	void clearScreen();
};

#endif // !_HEAD_PANNEL_
