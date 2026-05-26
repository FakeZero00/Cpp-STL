//Iterator2 + Container3
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================
// C++ STL을 떠받치는 3가지 요소: Container - Iterator - Algorithm
// Algorithm은 반복자로 코딩되어 있고 크게 3가지로 분류할 수 있다.
// 1. Non-modifying 알고리즘 : 원소 수정 X
// 2. Modifying 알고리즘 : 원소 수정 O
// 3. Sort and Related 알고리즘 : 정렬과 정렬 관련 알고리즘
// 
// STL Associative(연관) Container - 해싱을 위한 컨테이너, key - value pair, O(log n)
// set, multiset	- key == value
// map, multimap	- key를 정렬 기준으로 value를 검색
//================================================================

template <class IT, class VAL>
IT my_find(IT first, IT last, VAL val)
{
	while(first != last) {
		if (*first == val)
			return first;
		++first;
	}
	return last;
}

template <class IT, class PRED>
IT my_find_if(IT first, IT last, PRED pred)
{
	while (first != last) {
		if (pred(*first))
			return first;
		++first;
	}
	return last;
}

template <class IT, class OUT>
OUT my_copy(IT first, IT last, OUT out)
{
	while (first != last) {
		*out++ = *first++;
	}
	return out;
}

//std::less를 XString에 대해서 Specialization
template <>
struct less<XString> {
	bool operator() (const XString& a, const XString& b) const {
		//사전식 비교
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}
};



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
	
	//[문제] xs의 첫번째 홀수를 찾아라(xs에는 숫자만 있다)
	//XString xs{ "20260526" };

	//XString::iterator p = my_find_if(xs.begin(), xs.end(), [](char c) {
	//	//int i = c - '0';
	//	//if (0 != i % 2)
	//	if (c & 1)	//홀수는 1로 끝나기에 1과 비트 연산을 하면 홀수인지 짝수인지 알 수 있다. 아스키 코드도 그렇게 설계되었기 때문에 가능하다.
	//		return true;
	//	return false;
	//	});

	//if ( p != xs.end() )
	//	cout << distance(xs.begin(), p) + 1<< "에서 홀수 발견: " << * p << endl;
	//else 
	//	cout << "XS는 홀수가 없습니다." << endl;

	/*XString xs{ "2026년 05워 26일 12주 2일" };
	vector<char> v;
	v.reserve(xs.size());*/

	//[문제] xs에 있는 글자들을 v에 복사하라.
	//my_copy(xs.begin(), xs.end(), ostream_iterator<XString::value_type>{ cout });
	//my_copy(xs.begin(), xs.end(), v.begin());
	//이 상태에서는 vector의 size가 0이기 떄문에 v를 그냥 출력할 수가 없다.
	//my_copy(xs.begin(), xs.end(), back_inserter(v));	//back_inserter는 vector의 뒤에 원소를 추가하는 반복자 어댑터이다. v의 size가 늘어나면서 원소가 추가된다.

	//for(char c: v)
	//	cout << c;
	//cout << endl;

	//set이 원소의 uniqueness를 판단하는 기준 - equivalence
	//equality(동등) 와 equivalence(상등성)
	//equality는 ==로 같음을 판단, equivalence는 <로 같음을 판단.
	/*set<int> s{ 2, 4, 6, 1, 3, 1, 3 };
	less<int> cmp;
	cmp(2, 4);

	for (int n : s)
		cout << n << " ";
	cout << endl;*/

	//"main.cpp"의 단어를 set<XString>에 저장하라.
	//정렬은 길이 순서로 하라

	ifstream in{ "main.cpp" };
	if (not in)
		return 20260526;
	set<XString, less<XString>> s{ istream_iterator<XString>{in}, {} };

	while (true) {
		for (const XString& xs : s)
			cout << xs << endl;

		cout << "찾을 단어를 입력하시오: ";
		XString xs;
		cin >> xs;

		//[문제] set에 있는지 없는지 다음과 같이 출력하라.
		//있다면 - 3번째 단어입니다.
		//없다면 - 없는 단어입니다. set에 추가하시겠습니까?
		//		- 1. 추가한다. 2. 추가하지 않는다.

		auto p = s.find(xs);
		if (p != s.end()) {
			cout << xs << "는 " << distance(s.begin(), p) + 1 << "번째 단어입니다." << endl;
			system("pause");
		}
		else {
			cout << xs << "가 s에 존재하지 않습니다. s에 추가하시겠습니까?\n1. 추가한다\n2. 추가하지 않는다" << endl;
			int n{};
			cin >> n;
			if (n == 1) {
				s.insert(xs);
				cout << xs << "가 s에 추가되었습니다." << endl;
				system("pause");
			}
			else continue;
		}
	}

	save("main.cpp");
}