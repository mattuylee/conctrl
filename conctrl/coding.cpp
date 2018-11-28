#include <string>
#include <string.h>
#include <cstdlib>
#include "coding.h"

//��utf8������ı�ת��ΪANSI����(GBK)
std::string UTF8ToANSI(const char* str) {
	//ͳ���ַ���
	int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), NULL, 0);
	if (wideCharCount == 0) {
		return "?";
	}
	//ΪUnicode����������ռ�
	wchar_t* wideCharBufer = (wchar_t*)malloc(sizeof(wchar_t) * wideCharCount);
	//ת����Unicode
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), wideCharBufer, wideCharCount);
	//ת��ΪANSI
	int multiByteCharCount = WideCharToMultiByte(CP_ACP, 0, wideCharBufer, wideCharCount, NULL, 0, NULL, NULL);
	char* mutiByteCharBuffer = (char*)malloc(sizeof(char) * multiByteCharCount);
	int result = WideCharToMultiByte(CP_ACP, 0, wideCharBufer, wideCharCount, mutiByteCharBuffer, multiByteCharCount, NULL, NULL);
	if (!result)
		return "???";
	std::string text(mutiByteCharBuffer);
	free(mutiByteCharBuffer);
	free(wideCharBufer);
	return text;
}