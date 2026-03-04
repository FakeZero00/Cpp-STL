//1주 2일차 26.03.04
//컴파일 환경 - Release/x64
//프로젝트 설정 - c++ 언어 표준 설정: 미리 보기 - 최신 C++ 초안의 기능(/std:c++latest), SDL 검사 : 아니오
#include <iostream>
#include <windows.h>
#include "save.h"

int main()
{
	SetConsoleOutputCP(65001);
	std::cout << "2026.03.03" << '\n';

	save("save.h");
	save("save.cpp");
	save("main.cpp");
	
	system("pause");
}
