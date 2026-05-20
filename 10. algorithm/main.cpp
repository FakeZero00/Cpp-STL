//Algorithm
#include <iostream>
#include <algorithm>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================
// C++ STL을 떠받치는 3가지 요소: Container - Iterator - Algorithm
// Algorithm은 반복자로 코딩되어 있고 크게 3가지로 분류할 수 있다.
// 1. Non-modifying 알고리즘 : 원소 수정 X
// 2. Modifying 알고리즘 : 원소 수정 O
// 3. Sort and Related 알고리즘 : 정렬과 정렬 관련 알고리즘
//================================================================

template <class IT, class VAL>
IT my_find(IT first, IT last, VAL val)
{
	while(first != last) {
		if (*first == val)
			return first;
		++first;
	}
	return first;
}

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

int main()
{
	//XString xs{ "Iterators are a generalization of pointers" };

	//[문제] 찾는 글자가 xs에 있나 출력하라.
	//있다면 몇 번째 문자인지, 없다면 없는 문자라고 출력하라.

	/*while(true){
		char c{};
		cout << "찾을 문자를 입력하시오: ";
		cin >> c;

		XString::iterator p = my_find(xs.begin(), xs.end(), c);
		if (p != xs.end()) {
			cout << c << "는 " << distance(xs.begin(), p) + 1 << "번째 문자입니다." << endl;
		}
		else {
			cout << c << "는 없는 문자입니다." << endl;
		}
	}*/
	
	//[문제] xs의 첫번째 짝수를 찾아라(xs에는 숫자만 있다)
	XString xs{ "4165416541634864153416584168468741231653168797498641536851879" };

	find_if(xs.begin(), xs.end(), [](char c) {
		int i = c - '0';
		if (0 == i % 2)
			return true;
		})

	save("main.cpp");
}