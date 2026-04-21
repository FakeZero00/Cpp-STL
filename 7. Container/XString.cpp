//------------------------------------------------------
// STL을 더 잘 알아보려고 만든 자료구조(std::string)과 유사
// 
// 생성자는 메모리와 상관이 없다. 메모리를 채우기만 한다.
// 때문에 벡터에 push_back()할때마다 임시 객체가 생성됬다가 소멸되는 것을 볼 수 있다.
//2026.4.8 시작
//------------------------------------------------------
#include <print>
#include <iostream>
#include "XString.h"

size_t XString::gid{ 0 };
bool lookup{ false };	//관찰?

XString::XString() : id{ ++gid }
{
	if (lookup)
		special("디폴트 생성");
}
XString::~XString() {
	//소멸 관찰을 위해 만든 소멸자
	if (lookup)
		special("소멸");
}
XString::XString(const char* s) : id{ ++gid } {
	len = strlen(s);
	p = std::make_unique<char[]>(len);
	memcpy(p.get(), s, len);
	/*cout << "생성(char *) - " << "글자수: " << len << ", 객체 주소: " << (void *)this
		<< ", 문자열 주소: " << (void *)p.get() << endl;*/
		//p.get() 처럼 문자열로 할당된 주소를 그냥 출력하면 문자열이 자와버리므로 (void *)으로 주소로 완전히 캐스팅 할 필요가 있다.

	if(lookup)
		special("생성(*)");
}

//복사 생성자
XString::XString(const XString& other) : id{++gid}
{
	len = other.len;
	p = std::make_unique<char[]>(len);
	memcpy(p.get(), other.p.get(), len);
	
	if (lookup)
		special("복사생성");
}

XString& XString::operator=(const XString& other)
{
	if (this == &other) return*this;	//나를 나로 할당할 필요는 없다. ex) a = a; 

	p.reset(); //기존에 가지고 있던 문자열을 해제한다. -> p가 가리키는 문자열이 해제되고 p는 nullptr이 된다.
	len = other.len;
	p = std::make_unique<char[]>(len);	//새로운 문자열을 할당한다.
	memcpy(p.get(), other.p.get(), len);

	if (lookup)
		special("복사할당");

	return *this;		//a = b = c; 처럼 연쇄적으로 할당할 때, b = c;의 결과인 b를 반환해서 a = b;가 되도록 한다.
}

//이동 생성자
XString::XString(XString&& other) noexcept: id{++gid} 
{
	len = other.len;
	p.reset(other.p.release()); //other.p가 가지고 있던 주소를 할당 해제, 반환해서 p에 할당한다. other.p는 nullptr이 된다.

	other.len = 0;
	
	if(lookup)
		special("이동생성");
}

XString& XString::operator=(XString&& other) noexcept
{
	if (this == &other) 
		return *this;

	//이 부분을 공부하자
	len = other.len;
	p.reset(other.p.release());

	other.len = 0;

	if(lookup)
		special("이동할당");
}
	
size_t XString::size() const
{
	return len;
}

char* XString::data() const
{
	return p.get();
}

void XString::special(std::string moment) {
	std::string text;
	//더 좋은 방법이 있다
	int num = 20;
	if (len < 20) num = len;
	for (int i = 0; i < num; ++i)
		text += p.get()[i];

	std::println("[{:7}] - {:8} 객체: {:#014X} 글자: {:#014X} - 글자 개수: {:<6} 내용: {}",
		id, moment, (long long)this, (long long)p.get(), len, text);
}

void XString::show()
{
	special("show");
}
	
std::ostream& operator<<(std::ostream& os, const XString& xs) {
	for (int i{}; i < xs.len; i++)
		os << xs.p.get()[i];
	return os;
}

std::istream& operator>>(std::istream& is, XString& xs) {
	std::string s;
	is >> s;
	xs.len = s.size();
	xs.p.reset();
	xs.p = std::make_unique<char[]>(xs.len);
	memcpy(xs.p.get(), s.data(), xs.len);

	return is;
}