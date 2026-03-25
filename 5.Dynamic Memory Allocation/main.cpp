//Dynamic Memory Allocation
#include <iostream>
//#include <array>
//#include <numeric>
//#include <memory>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <print>
#include <ranges>
#include "Save.h"
using namespace std;

//================================================================

//동적 할당 -> 런타임시에 결정, 프리스토어에 할당 -> 주소로만 할당
//정적 할당 -> 컴파일시에 결정, 스택에 할당 -> 이름 사용 가능
//스마트 포인터를 통해 할당과 해제를 자동으로 할 수 있다.

//Callable Type

//================================================================

/*
class Dog
{
public:
	Dog() { cout << "Dog 생성" << endl; }
	~Dog() { cout << "Dog 소멸" << endl; }
};
*/

/*
class smartPtr
{
public:
	smartPtr(Dog* p) : p{ p } {
		cout << "smartPtr 생성 - 자원 p를 관리 시작" << endl;
	}
	~smartPtr() {
		delete p;	//자원 해제
		cout << "smartPtr 소멸 - 자원 p를 관리 종료. 관리하던 p도 삭제" << endl;
	}
private :
	Dog* p;
};
*/

default_random_engine dre{};
uniform_int_distribution<int> uid{ 0, 999'9999 };
array<int, 1000'0000> a;

int compare(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	/*
	//[문제] 사용자의 원하는 수 만큼 int를 저장할 수 있는 메모리를 확보하라.
	//메모리의 내용을 1부터 시작하는 정수로 채워라.
	//합계를 계산해서 화면에 출력하라.

	while (true) {
		size_t size;
		cout << "필요한 정수의 개수를 입력하시오: ";
		cin >> size;

		//int* ptr; C++에서는 포인터를 잘 안쓴다!

		unique_ptr<int[]> ptr;	//RAII
		try {
			ptr.reset(new int[size]);	// new로 메모리를 할당받음. unique_ptr이 알아서 해제해줌.
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
			exit(404);
		}

		iota(ptr.get(), ptr.get() + size, 1);	// 1부터 시작하는 정수로 채우기

		long long sum{};
		for (int i = 0; i < size; i++)
			sum += ptr[i];

		long long sum = accumulate(ptr.get(), ptr.get() + size, 0LL);	//3번째 인자는 초기값. 초기값도 잘 자료형을 정해줘야 함. 0LL은 long long 타입의 0을 의미.

		cout << "1부터 " << size << "까지의 합계: " << sum << endl;

		delete[] ptr;	//new, 포인터를 써서 데이터를 할당 받았을 때, delte 안하면 할당 해제가 되지 않음. 램 누수가 일어나서 점점 느려짐.
					//심지어 delete가 2번 발동될 경우 프로그램이 완전히 죽어버림.
}
	*/
	//Dog* p = new Dog;
	//RAII로 자원관리의 어려움을 해결할 수 있다.
	// 자원의 생명주기와 자원을 관리하는 객체 p의 생명주기를 일치시키면 가능하다.
	// 이게 가능한 이유는 C++언어에서 지역이 끝날때 지역 객체가 반드시 소멸됨을 보장한다. -> Stack-Unwinding
	//unique_ptr<Dog[]> p{new Dog[10]};

	//[문제] "main.cpp"에 있는 소문자를 대문자로 바꾼 파일, "MAIN.cpp"를 만들어라

	/*
	ifstream in("main.cpp");
	ofstream out("MAINUPPER.cpp");

	if (not in)
	{
		cerr << "파일을 열 수 없습니다." << endl;
		system("pause");
		exit(404);
	}

	transform(istreambuf_iterator<char>{in}, {}, ostreambuf_iterator<char>{out},
		[](char c) {
			return toupper(c);
		}
	);
	*/
	
	//[문제] 랜덤 값을 갖는 int 1000만개를 메모리에 저장하라.
	//오름차순으로 정렬하고 화면에 출력하라.
	for (int& num : a)
		num = uid(dre);

	qsort(a.data(), a.size(), sizeof(array<int, 1000'0000>::value_type), compare);

	//정렬이진 화면 출력
	for (int num : a | views::take(1000))
		print("{:8}", num);

	cout << endl;

	save("main.cpp");
	system("pause");
}
