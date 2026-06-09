//Iterator2 + Container3
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <array>
#include <fstream>
#include <ranges>
#include <list>
#include <random>
#include <unordered_set>
#include <print>
#include <chrono>
#include <array>
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
// STL Associative(연관) Container - 해싱을 위한 컨테이너, key - value pair, O(log n), index로 access하지 않는 컨테이너
// set, multiset	- key == value
// map, multimap	- key를 정렬 기준으로 value를 검색
// 
// unordered_set, unordered_map은 순서가 보장되지 않는 대신 O(1)로 검색이 가능하다.
// hahser를 통해 key값을 해싱해서 hash_value를 저장한다. 그렇기 때문에 메모리를 제물로 속도를 얻는 것이나 다름 없다.
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
//template <>
//struct less<XString> {
//	bool operator() (const XString& a, const XString& b) const {
//		//사전식 비교
//		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
//	}
//};

//class Dog {
//public:
//	bool operator() (const XString& a, const XString& b) const {
//		return a.size() > b.size();
//	}
//};

//class Dog {
//public:
//	size_t operator() (const XString& xs) const {
//		return std::hash<string>{}(string{xs.begin(), xs.end()});
//	}
//};

//std의 구조체를 Specialization 하는 것은 권장하지 않는다.
template <>
struct hash<XString> {
	size_t operator() (const XString& xs) const {
		return std::hash<string>{}(string{ xs.begin(), xs.end() });
	}
};

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수
default_random_engine dre;
//normal_distribution nd{ 0.0, 0.01 };


const size_t NUM{ 1000'0000 };
const size_t FNUM{ 1'0000 };

array<int, NUM> num;
array<int, FNUM> fnum;
uniform_int_distribution uid{ 1, (int)(1.3 * (int)NUM) };

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

	//ifstream in{ "main.cpp" };
	//if (not in)
	//	return 20260526;
	//set<XString> s{ istream_iterator<XString>{in}, {} };

	//while (true) {
	//	for (const XString& xs : s)
	//		cout << xs << endl;

	//	cout << "찾을 단어를 입력하시오: ";
	//	XString xs;
	//	cin >> xs;

	//	//[문제] set에 있는지 없는지 다음과 같이 출력하라. != xs가 set에 있는지 없는지 출력하라.
	//	//있다면 - 3번째 단어입니다.
	//	//없다면 - 없는 단어입니다. set에 추가하시겠습니까?
	//	//		 - 1. 추가한다.  2. 추가하지 않는다.

	//	auto p = s.find(xs);
	//	if (p != s.end()) {
	//		cout << xs << "는 " << distance(s.begin(), p) + 1 << "번째 단어입니다." << endl;
	//		system("pause");
	//	}
	//	else {
	//		cout << xs << "가 s에 존재하지 않습니다. s에 추가하시겠습니까?\n1. 추가한다\n2. 추가하지 않는다" << endl;
	//		int n{};
	//		cin >> n;
	//		if (n == 1) {
	//			s.insert(xs);
	//			cout << xs << "가 s에 추가되었습니다." << endl;
	//			system("pause");
	//		}
	//		else continue;
	//	}
	//	//[문제] xs가 set에 있는지 없는지 출력하라.
	//	//if(s.contains(xs)){
	//		//cout << "있는 단어" << endl;
	//	//}
	//}

	//ifstream in{ "main.cpp" };
	//if (not in)
	//	return 20260526;
	//set<XString> s{ istream_iterator<XString>{in}, {} };
	//vector<XString> v{ s.begin(), s.end() };

	////[문제] xs가 vector에 있는지 없는지 출력하라.
	//while (true) {
	//	for (const XString& xs : s)
	//		cout << xs << endl;

	//	cout << "찾을 단어를 입력하시오: ";
	//	XString xs;
	//	cin >> xs;

	//	//모처럼 set의 정렬된 데이터를 받아왔는데 그냥 find를 쓰면 시퀀셜 서치로 찾게 되어서 비효율적이다.
	//	//데이터가 정렬되어 있다면 바이너리 서치를 하는 편이 좋다.
	//	//Vector랑 같은 구조이면서 항상 정렬된 상태를 유지하고 싶다면 flat_set이라는 컨테이너 어댑터가 있다.
	//	auto p = find(v.begin(), v.end(), xs);
	//	if (p != v.end()) {
	//		cout << "있다." << endl;
	//		system("pause");
	//	}
	//	else {
	//		cout << "없다." << endl;
	//		system("pause");
	//	}
	//}

	//ifstream in{ "이상한 나라의 앨리스.txt" };
	//if(not in)
	//	return 20260526;

	////[문제] "이상한 나라의 앨리스.txt"에 사용된 알파벳의 개수를 다음과 같이 출렧하라.
	////알파벳의 개수만 센다. 대문자는 소문자로 변환
	//// 많이 출현한 순서대로 화면에 출력하라
	////a -
	////b -

	//array<int, 26> alphaNum{};

	//char c;
	//while (in >> c) {
	//	if (isalpha(c)) {
	//		c = tolower(c);
	//		alphaNum[c - 'a']++;
	//	}
	//}

	////c = 'a';
	////for (int num : alphaNum) {
	////	cout << c++ << " - " << num << endl;
	////}
	////이 대로는 알파벳도 같이 많이 나온대로 정렬하기 힘들다. 이중배열이나 써야 할 수 있을 것이다.

	//map<int, char, greater<int>> icmap;

	//for (int i = 0; i < alphaNum.size(); ++i) {
	//	icmap.insert(make_pair(alphaNum[i], 'a' + i));
	//}

	//for (const auto& [count, c] : icmap) {
	//	cout << c << " - " << count << endl;
	//}

	/*ifstream in{ "이상한 나라의 앨리스.txt" };
	if(not in)
		return 20260526;*/

	//[문제] "이상한 나라의 앨리스.txt"에 가장 많이 사용된 문자 순으로 다음과 같이 출력하라
	//e - 3000
	//o - 2500
	//a - 2200

	/*map<int, char> icmap;
	map<char, int> cimap;

	char c;
	while (in >> c) {
		if (isalpha(c)) {
			c = tolower(c);
			cimap[c]++;
		}
	}

	for(const auto& [c, count] : cimap) {
		icmap[count] =  c;
	}

	for (const auto& [count, c] : icmap | views::reverse) {
		cout << c << " - " << count << endl;
	}*/

	/*ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	return 20260526;*/

	//[문제]소설에 사용된 단어와 개수를 출력하라.
	/*map<XString, int> ximap;

	XString word;
	while (in >> word) {
		ximap[word]++;
	}

	for (const auto& [word, count] : ximap) {
		cout << word << " - " << count << endl;
	}
	cout << "단어의 개수: " << ximap.size() << endl;*/

	//[문제] set<XString>에 읽어와라.
	//multiset<XString> s{ istream_iterator<XString>{in}, {} };

	//for(const XString& xs : s)
	//	cout << xs << "\t";
	//cout << endl;
	//cout << "단어의 개수: " << s.size() << endl;
	//
	//while (true) {
	//	cout << "찾을 단어를 입력하시오: ";
	//	XString xs;
	//	cin >> xs;

	//	/*auto [lower, upper] = s.equal_range(xs);
	//	if (lower != upper) {
	//		cout << xs << "는 " << distance(lower, upper) << "개 있습니다." << endl;
	//	}
	//	else {
	//		cout << xs << "는 없는 단어입니다." << endl;
	//	}*/

	//	//[문제] 입력한 단어가 있다면 몇 개인지, 없다면 없는 단어라고 출력하라.
	//	int cnt = s.count(xs);
	//	if (cnt) {
	//		cout << xs << "는 " << cnt << "개 있습니다." << endl;
	//	}
	//	else {
	//		cout << xs << "는 없는 단어입니다." << endl;
	//	}
	//}

	//[문제] 파일에 사용된 단어와 사용된 횟수를 출력하라.
	//map<XString, size_t> xsmap;
	//
	//ifstream in{ "이상한 나라의 앨리스.txt" };
	//if (not in)
	//	return 20260526;

	//XString xs;
	//while (in >> xs) {
	//	xsmap[xs]++;
	//}

	///*for (const auto& [word, count] : xsmap) {
	//	cout << word << " - " << count << endl;
	//}*/

	////[문제] 많이 사용된 단어 순으로(개수 기준으로 내림차순) 출력하라.
	//multimap<size_t, XString, greater<size_t>> sxmap;
	//for (const auto& [word, count] : xsmap) {
	//	sxmap.insert(make_pair(count, word));
	//}

	//for (const auto& [count, word] : sxmap) {
	//	cout << word << " - " << count << endl;
	//}

	//[문제] 게임회사와 히트게임을 map으로 관리한다.
	/*map<XString, list<XString>> game;
	game.insert(pair<XString, list<XString>>("펄어비스", { "검은 사막", "붉은 사막" }));
	game["펄어비스"].emplace_back("보라 사막");

	game.insert(make_pair("닌텐도", list<XString>{"젤다", "마리오"}));

	for (const auto& [company, games] : game) {
		cout << company;
		for (const auto& game : games) {
			cout << " - " << game;
		}
		cout << endl;
	}*/

	//입력한 단어를 정렬 후 출력하라.
	/*set<XString> s{ istream_iterator<XString>{cin}, {} };

	for (const XString& xs : s)
		cout << xs << endl;*/

	//[문제] 정규분포를 화면에 출력하라.
	//map<size_t, size_t> normal_Dist;
	//for (int i = 0; i < 100'0000; ++i) {
	//	double num = nd(dre);
	//	num = num * 5000 + 5000;	//정규분포의 평균이 0이고 표준편차가 1이므로, 평균이 5000이고 표준편차가 5000인 정규분포로 변환한다.
	//	if (num < 0) num = 0;
	//	if (num > 10000) num = 10000;

	//	normal_Dist[static_cast<int>(num) / 100]++;
	//}

	//for (const auto& [range, count] : normal_Dist) {
	//	cout << range << " - " << count << endl;
	//}

	//=============================================
	//Unordered Set
	//=============================================
	
	/*unordered_set<int> us{1, 2, 3, 4};
	
	for (int n : us)
		cout << n << " ";
	cout << endl;
	
	us.insert(9);

	for(int n : us)
		cout << n << " ";
	cout << endl;*/

	//순서가 보장되지 않는다. -> insert 했을때 insert한 순서대로 안나올 수도 있다.
	//중요! bucket의 구조를 보여주는 코드
	//unordered_multiset<int> us{ 1, 2, 3, 4 };

	//for (int i = 0; i < 511; ++i) {
	//	us.insert(i);
	//}
	//for (int i = 0; i < us.bucket_count(); ++i) {
	//	print("[{:>03}] ", i);
	//	for (auto p = us.begin(i); p != us.end(i); ++p) {
	//		cout << "--> " << *p;
	//	}
	//	cout << endl;
	//}

	//1, 2, 3, 4 ->, 4, 7, 6, 1 bucket
	/*while (true) {
		for (int i = 0; i < us.bucket_count(); ++i) {
			print("[{:>03}] ", i);
			for (auto p = us.begin(i); p != us.end(i); ++p) {
				cout << "--> " << *p;
			}
			cout << endl;
		}
		
		cout << endl;
		cout << "추가할 값 - ";
		int num;
		cin >> num;
		us.insert(num);
	}*/

	/*unordered_multiset<XString> us{ "2026", "6월", "2일", "화요일"};

	while (true) {
		for (int i = 0; i < us.bucket_count(); ++i) {
			print("[{:>03}] ", i);
			for (auto p = us.begin(i); p != us.end(i); ++p) {
				cout << " --> " << *p;
			}
			cout << endl;
		}

		cout << endl;
		cout << "추가할 문장 - ";
		XString xs;
		cin >> xs;
		us.insert(xs);
	}*/

	//서치 시간 비교
	//1. vector				O(N)
	//2. set				O(log N)
	//3. unordered_set		O(1)
	//cout << "데이터 생성 중...";
	//for(int& num : num)
	//	num = uid(dre);

	//for (int& num : fnum)
	//	num = uid(dre);
	//cout << "완료" << endl;

	//{
	//	vector<int> v; 
	//	v.reserve(num.size());
	//	v.assign( num.begin(), num.end() );
	//	cout << "벡터에서 찾기" << endl;

	//	size_t cnt{};
	//	auto start = chrono::high_resolution_clock::now();
	//	for (int num : fnum) {
	//		if (v.end() != find(v.begin(), v.end(), num))
	//			++cnt;
	//	}
	//	auto end = chrono::high_resolution_clock::now();
	//	cout << "찾은 개수: " << cnt << endl;
	//	cout << "걸린 시간: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs" << endl;
	//	cout << endl;
	//}

	//{
	//	cout << "세트 구성하는 중..." << endl;
	//	multiset<int> v{ num.begin(), num.end() };

	//	cout << "세트에서 찾기" << endl;
	//	size_t cnt{};
	//	auto start = chrono::high_resolution_clock::now();
	//	for (int num : fnum) {
	//		if (v.contains(num))
	//			++cnt;
	//	}
	//	auto end = chrono::high_resolution_clock::now();
	//	cout << "찾은 개수: " << cnt << endl;
	//	cout << "걸린 시간: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs" << endl;
	//	cout << endl;
	//}

	//{
	//	cout << "언오더드 세트 구성하는 중..." << endl;
	//	unordered_multiset<int> v{ num.begin(), num.end() };

	//	cout << "언오더드 세트에서 찾기" << endl;
	//	size_t cnt{};
	//	auto start = chrono::high_resolution_clock::now();
	//	for (int num : fnum) {
	//		if (v.contains(num))
	//			++cnt;
	//	}
	//	auto end = chrono::high_resolution_clock::now();
	//	cout << "찾은 개수: " << cnt << endl;
	//	cout << "걸린 시간: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs" << endl;
	//	cout << endl;
	//}

	////정렬된 데이터에선 셋 보다도 flat_set이 훨씬 서치가 빠르다.
	//{
	//	vector<int> v;
	//	v.reserve(num.size());
	//	v.assign(num.begin(), num.end());
	//
	//	cout << "벡터 정렬하는 중..." << endl;
	//	sort(v.begin(), v.end());
	//	cout << "정렬된 벡터에서 찾기(C++23의 flat_set)" << endl;

	//	size_t cnt{};
	//	auto start = chrono::high_resolution_clock::now();
	//	for (int num : fnum) {
	//		if (binary_search(v.begin(), v.end(), num))
	//			++cnt;
	//	}
	//	auto end = chrono::high_resolution_clock::now();
	//	cout << "찾은 개수: " << cnt << endl;
	//	cout << "걸린 시간: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "μs" << endl;
	//	cout << endl;
	//}

	

	save("main.cpp");
}