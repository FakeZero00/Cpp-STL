//Iterator
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>
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

template <class IT>
void f(IT iter)
{
	//이렇게 타입 구분하면 안된다;;
	/*cout << typeid(iter).name() << endl;
	if (typeid(iter) == typeid(std::_Vector_iterator<class std::_Vector_val<struct std::_Simple_types<int> > >))
		cout << "벡터 반복자" << endl;*/

	//반복자가 제공하는 부가 정보를 사용하여 종류를 판단한다.
	cout << typeid(IT::iterator_category).name() << endl;
}

int main()
{
	//XString xs{ "the quick brown fox jumps over the lazy dog" };	//영문에서 모든 알파벳을 포함하는 문장.
	//sort(xs.begin(), xs.end());

	////range-for문을 사용하려면 반복자 인터페이스가 필요하다.
	//for (char c : xs)
	//	cout << c << '-';
	//cout << endl;

	//1.반복자를 직접 사용한 코딩 - ex)출력 반복자
	//ostream_iterator<char> p{ cout };
	/*vector<char> v;
	v.reserve(10);
	auto p = v.begin();*/
	//* 연산자나 ++연산자가 없어도 ostream_iterator는 출력 반복자이기에 출력이 가능하지만
	//만약 ostream_iterator가 아닌 Vector의 이터레이터라도 코딩이 가능하도록 하는 것이 바람직하다.
	//p.operator*(), p.operator++()
	//*p++ = 'a';
	//*p++ = 'B';
	//*p++ = '\n';

	//2.반복자를 인자로 받는 코딩 -> 알고리즘 함수가 하고 있다.
	//3.반복자의 종류를 판단하는 방법
	f(istream_iterator<char>{ cin });
	f(ostream_iterator<int>{ cout });
	f(forward_list<int>::const_iterator{});
	f(list<XString>::const_reverse_iterator{});

	f(deque<char>::reverse_iterator{});
	f(vector<int>::iterator{});
	f(array<int, 0>{}.begin());

	//반복자는 포인터를 일반화 한 것이지만 그 역은 성립하지 않는다.
	char* p;
	//f(p);

	save("main.cpp");
}