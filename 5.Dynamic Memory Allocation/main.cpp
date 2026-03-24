//Dynamic Memory Allocation
#include <iostream>
#include <array>
#include <numeric>
#include <memory>
#include "Save.h"
using namespace std;

//================================================================

//동적 할당 -> 런타임시에 결정, 프리스토어에 할당 -> 주소로만 할당
//정적 할당 -> 컴파일시에 결정, 스택에 할당 -> 이름 사용 가능

//================================================================

int main()
{
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

		/*
		long long sum{};
		for (int i = 0; i < size; i++)
			sum += ptr[i];
		*/

		long long sum = accumulate(ptr.get(), ptr.get() + size, 0LL);	//3번째 인자는 초기값. 초기값도 잘 자료형을 정해줘야 함. 0LL은 long long 타입의 0을 의미.

		cout << "1부터 " << size << "까지의 합계: " << sum << endl;

		//delete[] ptr;	//new, 포인터를 써서 데이터를 할당 받았을 때, delte 안하면 할당 해제가 되지 않음. 램 누수가 일어나서 점점 느려짐.
						//심지어 delete가 2번 발동될 경우 프로그램이 완전히 죽어버림.
	}

	save("main.cpp");
	system("pause");
}
