//Template

#include <iostream>
#include <Windows.h>
#include "save.h"
using namespace std;

//같은 이름의 함수를 여러개 정의 할 수 있는 이유는 컴파일러가 name mangling을 수행하기 때문이다.
//name mangling은 함수의 이름과 매개변수의 타입 정보를 조합하여 고유한 이름을 생성하는 과정이다. 이를 통해 컴파일러는 함수 오버로딩을 지원할 수 있다.
class Dog;
void change(int&, int&);
void change(Dog&, Dog&);

class Dog
{
public:
	Dog() = default;
	explicit Dog(int n) : num{n} {}

	//operator int() { return num; }

private:
	int num{};
	friend ostream& operator<<(ostream& os, const Dog& dog) { return os << dog.num; }
};

int main()
{
	SetConsoleOutputCP(65001);

	{
		cout << addressof(main) << "\n" << addressof(save) << endl;	//main과 save의 주소값이 출력됨.
		int a{ 1 }, b{ 2 };
		cout << addressof(a) << "\n" << addressof(b) << endl;		//a와 b의 주소값이 출력됨.

		//[문제] 여기에서 change를 호출했더니 다음과 같이 출력됨.
		change(a, b);
		cout << a << ", " << b << endl;		//2, 1이라고 출력됨.
	}

	///////////////////////////////////////////////////////////////////
	//[문제] class Dog로 코딩하여 의도대로 실행되게 하자

	{
		cout << addressof(main) << "\n" << addressof(save) << endl;	//main과 save의 주소값이 출력됨.
		Dog a{ 1 }, b{ 2 };
		cout << addressof(a) << "\n" << addressof(b) << endl;		//a와 b의 주소값이 출력됨.

		//[문제] 여기에서 change를 호출했더니 다음과 같이 출력됨.
		change(a, b);
		cout << a << ", " << b << endl;		//2, 1이라고 출력됨.
	}

	save("main.cpp");
	system("pause");
}

void change(int& a, int& b)
{
	int temp{ a };
	a = b;
	b = temp;
}

void change(Dog& a, Dog& b)
{
	Dog temp{ a };
	a = b;
	b = temp;
}
