//Iterator
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>
#include <concepts>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================
//Iterator는 포인터를 일반화한 것으로 자료형에 구애받지 않고 똑같이 코딩할 수 있게한다(Uniform manner).
//1.반복자를 직접 사용한 코딩
//2.반복자를 인자로 받는 코딩
//3.반복자의 종류를 판단하는 방법
//반복자는 3가지의 정보를 제공한다.
//iterator_category, difference_type(반복자끼리의 연산), value_type, pointer, reference
//difference_type은 반복자끼리의 연산에 사용되는 타입으로, 예를 들어 vector<int>::iterator는 difference_type이 ptrdiff_t로 정의되어 있다.
//================================================================

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

//이렇게 하면 어떤 타입이든 함수에 다 들어가버린다. 이때 필요한 것이 concepts이다.
//concepts를 쓰면 함수에 필요한 자료형만 들어올 수 있도록 제한할 수 있다.
template <class IT>
void f(IT iter)
{
	//이렇게 타입 구분하면 안된다;;
	/*cout << typeid(iter).name() << endl;
	if (typeid(iter) == typeid(std::_Vector_iterator<class std::_Vector_val<struct std::_Simple_types<int> > >))
		cout << "벡터 반복자" << endl;*/

	//반복자가 제공하는 부가 정보를 사용하여 종류를 판단한다. 다만 이렇게 판단하면 포인터는 받아올 수 없다.
	//cout << typeid(IT::iterator_category).name() << endl;
	
	//iterator_traits를 이용해서 우회로를 사용한다.
	cout << typeid(iterator_traits<IT>::iterator_category).name() << endl;
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
	// 반복자라면 제공해야하는 연산자로만 코딩하는 것이 좋다.
	//p.operator*(), p.operator++()
	//*p++ = 'a';
	//*p++ = 'B';
	//*p++ = '\n';

	//reserve로 용량을 확보하긴 해도 size 데이터가 0이므로 begin()과 end()가 같은 위치를 가리키게 돼서 for(char &c: v)로는 출력할 수 없다.
	/*for (int i = 0; i < v.capacity(); ++i)
		cout << v[i];
	cout << endl;*/

	//2.반복자를 인자로 받는 코딩 -> 알고리즘 함수가 하고 있다.
	//3.반복자의 종류를 판단하는 방법
	//알고리즘이 자료구조를 알 수 있다면 더 효율적으로 코딩할 수 있기 때문. distance 함수가 좋은 예
	//f(ostream_iterator<int>{ cout });
	////여기서부터는 상속관계(inheritance hierarchy)
	//f(istream_iterator<int>{ cin });
	//f(forward_list<int>::iterator());
	//f(list<char>{}.rbegin());

	////여기서부터는 []연산자를 사용할 수 있는 랜덤 반복자
	//f(deque<char>::reverse_iterator{});
	////여기서부터는 contigous한 메모리를 사용하는 자료형
	//f(array < XString, 0>::const_reverse_iterator{});
	//f(vector<XString>{}.crend());
	//f(string{}.end());
	//다만 그냥은 countigus_iterator가 나오지 않는다.

	//반복자는 포인터를 일반화 한 것이지만 그 역은 성립하지 않는다.
	//포인터는 반복자와 같이 부가정보를 가지고 있지 않다.
	/*XString* xp;
	f(xp);*/

	//p가 contigous_iterator임을 확인하는 방법
	//C++20의 concepts을 이용하면 된다.
	/*cout << "벡터 반복자는 contiguous인가? - " << boolalpha << contiguous_iterator<vector<int>::iterator> << endl;
	cout << "덱 반복자는 contiguous인가? - " << boolalpha << contiguous_iterator<deque<int>::iterator> << endl;
	cout << "덱 반복자는 bidirectional인가? - " << boolalpha << bidirectional_iterator<deque<int>::iterator> << endl;*/

	XString xs{ "Iterators are a generalization of pointers" };

	/*for (auto i = xs.rbegin(); i != xs.rend(); ++i)
		cout << *i << ' ';
	cout << endl;*/

	//f(xs.rbegin());	//반복자 종류 출력

	/*for (auto i = xs.begin(); i != xs.end(); ++i)
		cout << *i << '-';
	cout << endl;*/

	//[문제] xs를 오름차순 정렬하라.
	//다으 코드가 수정없이 실행되어야 한다.

	sort(xs.begin(), xs.end());
	cout << xs << endl;

	save("main.cpp");
}