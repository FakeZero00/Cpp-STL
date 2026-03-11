//Semi Infinite Data

//C++이 가능한 프로그래밍 패러다임 4가지
//1. 절차적 프로그래밍	>>C언어가 대표적
//2. 객체 지향 프로그래밍 >>Java가 대표적
//3. 함수형 프로그래밍 >> Haskell이 대표적
//4. 일반화 프로그래밍 >> 이게 특기

#include <iostream>
#include <Windows.h>
#include <random>
#include <fstream>
#include "save.h"
using namespace std;

//default_random_engine dre;
random_device rd;
default_random_engine dre{rd()};
uniform_int_distribution<int> uid{0, 9999};

int main()
{
	SetConsoleOutputCP(65001);
	
	//[문제] 임의의 값을 갖는 int 1000,0000 개 생성, int천만개.txt에 저장
	ofstream out{ "int천만개.txt" };
	for (int i = 0; i < 10000000; ++i) {
		out << uid(dre) << '\n';
	}

	save("main.cpp");
	system("pause");
}
