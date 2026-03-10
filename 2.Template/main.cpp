//Template

#include <iostream>
#include <Windows.h>
#include "save.h"
using namespace std;

//같은 이름의 함수를 여러개 정의 할 수 있는 이유는 컴파일러가 name mangling을 수행하기 때문이다.
//name mangling은 함수의 이름과 매개변수의 타입 정보를 조합하여 고유한 이름을 생성하는 과정이다. 이를 통해 컴파일러는 함수 오버로딩을 지원할 수 있다.
//그러나 이렇게 되면 자료형에 따라 같은 형태의 함수를 여러개 작성해야하는 문제가 발생한다. 이를 해결하기 위해 C++에서는 템플릿이라는 기능을 제공한다.
//컴파일러는 여러 단계의 Phase라는 과정을 거쳐서 코드를 컴파일하는데, 템플릿은 이 과정에서 컴파일러가 실제로 필요한 템플릿 인스턴스를 생성하는 방식으로 동작한다.
template <class DataT>
void change(DataT& a, DataT& b)
{
	DataT temp{ a };
	a = b;
	b = temp;
}

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



//template specialization(템플릿 특수화)은 템플릿이 특정 자료형에 대해서는 일반적인 형태와 다른 동작을 하도록 하는 기능이다.
//이를 통해 특정 자료형에 대한 최적화나 특별한 처리를 할 수 있다.
//아래의 코드에서는 Dog 클래스에 대한 템플릿 특수화를 정의하여, change 함수가 Dog 객체를 바꿀 때 일반적인 템플릿 버전과는 다른 방식으로 동작하도록 하고 있다.
template <>
void change(Dog& a, Dog& b)
{
	cout << "멍멍(I'm Special)" << '\n';
	Dog temp{ a };
	a = b;
	b = temp;
}

/*
//같은 이름의 탬플릿 함수가 존재하더라도 탬플릿이 아닌 전역함수가 존재한다면, 탬플릿이 아닌 전역함수가 우선적으로 호출된다.
//이는 C++의 함수 오버로딩 규칙에 따른 것이다.
void change(Dog a, Dog b)
{
	cout << "멍멍(I'm Global)" << '\n';
}
*/

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

/*
//알고리즘 절차. 어떤 자료형이든 두 개의 값을 바꾸려면 다음과 같은 과정을 반드시 밟게 된다.
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
*/
