//Semi Infinite Data

//C++이 가능한 프로그래밍 패러다임 4가지
//1. 절차적 프로그래밍	>>C언어가 대표적
//2. 객체 지향 프로그래밍 >>Java가 대표적
//3. 함수형 프로그래밍 >> Haskell이 대표적
//4. 일반화 프로그래밍 >> 이게 특기

#include <iostream>
#include <Windows.h>
#include <random>
#include <print>
#include "save.h"
using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid{0, 9999};

int main()
{
	SetConsoleOutputCP(65001);
	srand(time(NULL));
	
	//[문제] 임의의 값을 갖는 int 1000개 생성, 모든 값 출력.
	int num[1000];
	for (int i = 0; i < 1000; ++i)
	{
		num[i] = uid(dre);
	}

	for (int number : num)
	{
		print("{:8}", number);
	}

	//save("main.cpp");
	system("pause");
}
