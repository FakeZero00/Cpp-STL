//Dynamic Memory Allocation
#include <iostream>
#include <string>
#include <random>
#include <print>
#include <array>
#include <algorithm>
#include <ranges>
#include <thread>
#include <chrono>
#include <fstream>
#include "Save.h"
using namespace std;

//================================================================

//연습

//================================================================

default_random_engine dre;
uniform_int_distribution uid{ 1, 999'9999 };
uniform_int_distribution uidLen{ 1, 15 };
uniform_int_distribution uidChar{ 33, 126 };

class Dog
{
public:
	//uid(dre)를 그냥 넣으려고 하면 size_t에 int를 넣으려고 해서 에러가 난다. 타입 캐스팅을 반드시 하자.
	Dog() : id{ (size_t)uid(dre) } {
		int len = uidLen(dre);
		for (int i = 0; i < len; ++i)
			name += uidChar(dre);
	}

	size_t DogId() const{
		return id;
	}

	string DogName() const {
		return name;
	}

	string& DogName() {
		return name;
	}

private:
	string name; //[1, 15] - SSO로 저장 가능한 최대크기
	size_t id; //[1, 999'9999]

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		print(os, "[{:7}] {}", dog.id, dog.name);
		return os;
	}
};

//전역 데이터를 초기화 할 때에 데이터의 크기는?
array<Dog, 1000'0000> dogs;

int main()
{
	//[문제] Dog 1000만 마리를 메모리에 저장하시오.
	//id 기준 오름차순으로 정렬하시오.
	// name 길이기준 오름차순으로 정렬하시오.
	// name자체를 abc 순으로 정렬하시오.
	//앞에서 부터 1000개를 출력하시오.

	/*sort(dogs.begin(), dogs.end(), [](const Dog& a, const Dog& b) {
		return a.DogId() < b.DogId();
		});*/

	//ranges::sort(dogs, {}, &Dog::DogId);
	/*cout << "정렬 시작" << endl;
	for (Dog& dog : dogs) {
		string& name = dog.DogName();
		sort(name.begin(), name.end());
	}
	cout << "정렬 끝" << endl;*/

	//[문제] Dog 1000만 마리를 array에 저장하라.
	//파일 "Dog 천만마리"에 binary 모드로 array 메모리 전체를 저장하라.

	ofstream out{ "Dog 천만마리", ios::binary };
	out.write((char*)dogs.data(), dogs.size() * sizeof(Dog));

	cout << "마지막 Dog 객체" << endl;
	cout << *(dogs.end() - 1) << endl;
	cout << dogs[dogs.size() - 1] << endl;	//[ 246908] ~{


	//using namespace std::chrono_literals;
	//for (const Dog& dog : dogs | views::take(100)) {
	//	cout << dog << endl;
	//	//this_thread::sleep_for(100ms);
	//}

	save("main.cpp");
	system("pause");
}
