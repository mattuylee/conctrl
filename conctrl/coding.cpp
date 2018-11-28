#include <string>
#include <string.h>
#include <cstdlib>
#include "coding.h"

//将utf8编码的文本转换为ANSI编码(GBK)
std::string UTF8ToANSI(const char* str) {
	//统计字符数
	int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), NULL, 0);
	if (wideCharCount == 0) {
		return "?";
	}
	//为Unicode缓冲区申请空间
	wchar_t* wideCharBufer = (wchar_t*)malloc(sizeof(wchar_t) * wideCharCount);
	//转换成Unicode
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), wideCharBufer, wideCharCount);
	//转换为ANSI
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
