//Algorithm
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <print>
#include <thread>
#include <chrono>
#include <numeric>
#include <fstream>
#include <ranges>
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
// 알고리즘 Complexity 순위
// 1 - partition
// 2 - nth_element
// 3 - partial_sort
// 4 - sort
// 5 - stable_sort
// 
// range 용어
// view
// filter
// lazy-evaluation
// universal reference - perfect forwarding(완벽 전달)을 위한 것
// type traits
// concept
// constrained algorithm
// projection
//================================================================

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

default_random_engine dre{ random_device{}()};

int main()
{
	save("main.cpp");
	//이번주에 살 로또 번호 출력
	/*vector<int> v(45);
	for (int i = 0; i < v.size(); ++i)
		v[i] = i + 1;
	
	shuffle(v.begin(), v.end(), dre);

	for(int num : v)
		cout << num << " ";
	cout << endl;

	cout << "이번 주 추천번호입니다: " << endl;
	sample(v.begin(), v.end(), ostream_iterator<int>{cout, ""}, 6, dre);
	cout << endl;*/

	//글자가 흘러가는 전광판
	//XString xs{" The Youth of the soul is everlasting "};
	//for (int i = 0; i < 12; ++i)
	//	cout << endl;

	////그냥 하면 캐릭터가 하나씩 출력된다. print가 잘 인식하는 string으로 전달한다.
	////print("{:^80}", string{xs.begin(), xs.end()});

	//while (true){
	//	print("{:^80}", string{ xs.begin(), xs.end() });
	//	cout << "\r";
	//	rotate(xs.begin(), xs.end() - 1, xs.end());
	//	this_thread::sleep_for(200ms);
	//}

	//[문제] 1부터 100까지의 숫자를 랜덤하게 섞여 있는 v를 홀수, 짝수 순으로 분리하라.
	/*vector<int> v(100);
	iota(v.begin(), v.end(), 1);
	shuffle(v.begin(), v.end(), dre);

	auto p = partition(v.begin(), v.end(), [](int num) {
		if (num % 2)
			return true;
		return false;
		});

	cout << "홀수의 개수 - " << p - v.begin() << endl;
	for(auto i = v.begin(); i < p; ++i)
		print("{:4}", *i);
	cout << endl;*/

	//[문제] 1부터 100까지의 숫자를 랜덤하게 섞여 있는 v를 앞에서 부터 30등 까지만 추려줘.
	/*vector<int> v(100);
	iota(v.begin(), v.end(), 1);
	shuffle(v.begin(), v.end(), dre);

	nth_element(v.begin(), v.begin() + 30, v.end());

	cout << "앞에서 부터 30등 까지의 숫자: " << endl;
	for (auto i = v.begin(); i < v.begin() + 30; ++i)
		print("{:4}", *i);
	cout << endl;*/

	//[문제] 1부터 100까지의 숫자를 랜덤하게 섞여 있는 v를 앞에서 부터 30등 까지만 정렬해줘.
	/*vector<int> v(100);
	iota(v.begin(), v.end(), 1);
	shuffle(v.begin(), v.end(), dre);

	cout << "앞에서 부터 30등까지 정렬" << endl;
	partial_sort(v.begin(), v.begin() + 30, v.end());
	for (auto i = v.begin(); i < v.begin() + 30; ++i)
		print("{:4}", *i);

	cout << "31등에서 부터 100등 까지의 숫자: " << endl;
	for (auto i = v.begin() + 30; i < v.end(); ++i)
		print("{:4}", *i);
	cout << endl;*/


	//[문제] 중복 단어를 제거하라.
	/*ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
		return 20260610;*/

	//vector<XString> v{ istream_iterator<XString>{in}, {}};

	//sort(v.begin(), v.end());
	//unique는 sort 이후에 써야 하고 , unique는 중복된 원소를 뒤로 보내는 것이므로 벡터의 erase와 함께 써야 한다.
	//v.erase(unique(v.begin(), v.end()), v.end());

	//길이 오름차순으로 정렬
	//ranges::sort(v, {}, &XString::size);
	//길이 오름차순으로 비교한 결과가 같다면 원소의 위치를 변경하지 말라.
	//ranges::stable_sort(v, {}, &XString::size);
	//ranges 안에 있는 함수 사용하는 것이 권장되고 있다.

	/*for (const XString& xs : v)
		cout << xs << endl;
	cout << endl;*/

	auto odd = [](int n) {
		cout << " 홀수 " << endl;
		return n % 2; };
	auto ninemultiples = [](int n) {
		cout << " 9의 배수 " << endl;
		return n % 9 == 0; };

	//views::iota(1, 1000)을 하면 1~1000의 숫자가 저장된 오브젝트가 만들어지는게 아니다! 하나씩 데이터를 만들어내서 변수에 넘겨주는 것이다.
	//그래서 views를 사용해서 변수를 생성할 때는 auto로 RValue로 받는 것이 좋다.
	for (auto&& num :
		views::iota(1, 20)
		| views::filter(odd)
		| views::filter(ninemultiples))
		{
			cout << num << " ";
		}
		
	cout << endl;
}