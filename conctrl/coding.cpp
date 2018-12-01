#include <string>
#include <string.h>
#include <cstdlib>
#include "coding.h"

//��utf8������ı�ת��ΪANSI����(GBK)
std::string UTF8ToANSI(const char* str) {
	//ͳ���ַ���
	int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	if (wideCharCount == 0) {
		return "?";
	}
	//ΪUnicode����������ռ�
	//����ע��˴�����ؽ��ڴ��ʼ��Ϊ0ֵ����ΪMultiByteToWideChar��Ϊδ֪ԭ���ƺ�����������'\0'������
	wchar_t* wideCharBufer = (wchar_t*)calloc(wideCharCount, sizeof(wchar_t));
	//ת����Unicode
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), wideCharBufer, wideCharCount);
	//ת��ΪANSI
	int multiByteCharCount = WideCharToMultiByte(936, 0, wideCharBufer, wideCharCount, NULL, 0, NULL, NULL);
	char* mutiByteCharBuffer = (char*)calloc(multiByteCharCount, sizeof(char));
	int result = WideCharToMultiByte(936, 0, wideCharBufer, wideCharCount, mutiByteCharBuffer, multiByteCharCount, NULL, NULL);
	if (!result)
		return "???";
	std::string text(mutiByteCharBuffer);
	free(mutiByteCharBuffer);
	free(wideCharBufer);
	return text;
}