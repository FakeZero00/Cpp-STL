//Container
#include <iostream>
#include <string>
#include "Save.h"
using namespace std;

//================================================================

//container
//[String]
//string은 15글자까지는 스택에 저장되고 그 이상은 프리스토어에 저장되어 포인터로 프리스토어의 주소를 가리킨다.

//================================================================

//string 클래스 만들어보기
class XString {
public:
	XString() = default;

	XString(const char* s) {
		len = strlen(s);
		p = make_unique<char[]>(len);
		memcpy(p.get(), s, len);
		cout << "생성(char *) - " << "글자수: " << len << ", 객체 주소: " << (void *)this
			<< ", 문자열 주소: " << (void *)p.get() << endl;
		//p.get() 처럼 문자열로 할당된 주소를 그냥 출력하면 문자열이 자와버리므로 (void *)으로 주소로 완전히 캐스틱 할 필요가 있다.
	}

	friend ostream& operator<<(ostream& os, const XString& xs) {
		for (int i{}; i < xs.len; i++)
			os << xs.p.get()[i];
		return os;
	}

private:
	size_t len{};
	unique_ptr<char[]> p{};
};

int main()
{
	XString s{ "2026년 4월 7일 화요일" };
	XString t = move(s);
	//프리 스토어에 저장된 15글자가 넘는 문자열의 포인터를 t가 s에서 가져와서 t의 포인터에 할당한다. s는 더 이상 문자열을 가리키지 않게 된다.

	cout << "s - " << s << endl;
	cout << "t - " << t << endl;


	save("main.cpp");
	system("pause");
}