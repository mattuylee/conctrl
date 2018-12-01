#ifndef _HEAD_HRIZEN_
#define _HEAD_HRIZEN_
#include <windows.h>

class ConsoleWindow;

//�ָ���
class Spliter {
public:
	WORD attribute; //�ַ���ʽ
	COORD position; //λ��
	SHORT length; //���/�߶�
	Spliter(ConsoleWindow* window, COORD pos, SHORT len, bool verticle, WORD attr = 7);
	~Spliter();
	//����Ļ���
	void Clear();
	//�ƶ����������ó���
	void Move(COORD position, SHORT len);
private:
	//���ƻ����
	void draw(bool clear = false);
	ConsoleWindow* window; //��������
	bool verticle; //ˮƽ���ߴ�ֱ�ָ���
};

#endif // !_HEAD_HRIZEN_

