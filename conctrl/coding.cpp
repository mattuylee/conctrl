#include <string>
#include <string.h>
#include <cstdlib>
#include "coding.h"

//将utf8编码的文本转换为ANSI编码(GBK)
std::string UTF8ToANSI(const char* str) {
	//统计字符数
	int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	if (wideCharCount == 0) {
		return "?";
	}
	//为Unicode缓冲区申请空间
	//！！注意此处，务必将内存初始化为0值。因为MultiByteToWideChar因为未知原因似乎不会主动添'\0'结束符
	wchar_t* wideCharBufer = (wchar_t*)calloc(wideCharCount, sizeof(wchar_t));
	//转换成Unicode
	MultiByteToWideChar(CP_UTF8, 0, str, strlen(str), wideCharBufer, wideCharCount);
	//转换为ANSI
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