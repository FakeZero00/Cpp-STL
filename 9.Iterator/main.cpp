//Iterator
#include <iostream>
#include <algorithm>
#include <vector>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================
//Iterator는 포인터를 일반화한 것으로 자료형에 구애받지 않고 똑같이 코딩할 수 있게한다.
//1.반복자를 직접 사용한 코딩
//2.반복자를 인자로 받는 코딩
//3.반복자의 종류를 판단하는 방법
//================================================================

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

int main()
{
	//XString xs{ "the quick brown fox jumps over the lazy dog" };	//영문에서 모든 알파벳을 포함하는 문장.
	//sort(xs.begin(), xs.end());

	////range-for문을 사용하려면 반복자 인터페이스가 필요하다.
	//for (char c : xs)
	//	cout << c << '-';
	//cout << endl;

	//1.반복자를 직접 사용한 코딩 - ex)출력 반복자
	ostream_iterator<char> p{ cout };
	/*vector<char> v;
	v.reserve(10);
	auto p = v.begin();*/
	//* 연산자나 ++연산자가 없어도 ostream_iterator는 출력 반복자이기에 출력이 가능하지만
	//만약 ostream_iterator가 아닌 Vector의 이터레이터라도 코딩이 가능하도록 하는 것이 바람직하다.
	*p++ = 'a';
	//p.operator*(), p.operator++()
	*p++ = 'B';
	*p++ = '\n';

	//2.반복자를 인자로 받는 코딩
	//3.반복자의 종류를 판단하는 방법

	save("main.cpp");
}