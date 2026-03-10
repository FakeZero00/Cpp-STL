//Template

#include <iostream>
#include <Windows.h>
#include "save.h"
using namespace std;

//레퍼런스를 굳이 쓰고 싶다고 하면 const를 사용하면 인자가 상수 값일때도 사용할 수 있다.
template<class T>
T add(const T& a, const T& b)
{
	return a + b;
}

int main()
{
	SetConsoleOutputCP(65001);
	
	cout << add(1, 2) << endl;
	cout << add("2026년"s, string{ "3월10일" }) << endl;

	save("main.cpp");
	system("pause");
}
