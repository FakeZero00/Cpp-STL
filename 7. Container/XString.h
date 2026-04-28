//------------------------------------------------------
// STL을 더 잘 알아보려고 만든 자료구조(std::string)과 유사
// STL 컨테이너처럼 동작하게
// 
//2026.4.8 시작
//2026.4.8 복사생성/할당
//2026.4.8 이동생성/할당
//------------------------------------------------------
#pragma once
#include <string>
#include <memory>

class XString {
public:
	XString();
	~XString();
	XString(const char* s);

	//복사 생성자
	XString(const XString&);
	XString& operator=(const XString&);

	//이동 생성자 C++11 move sementic
	XString(XString&&) noexcept;
	//Move에 실패할 경우, 자원이 메모리에 누수될 수 있어서 컴파일러가 우려를 표한다.
	//때문에 무결성을 보장하기 위해 이동에 문제가 없다라고 보장하는 noexcept를 붙이는 것이 좋다.
	//&&는 R-Value로 대입 연산자의 오른쪽에만 올 수 있는 연산자. 이동 생성자와 이동 대입 연산자를 구분하기 위해서 &&를 붙인다.
	XString& operator=(XString&&) noexcept;

	//컨테이너가 되려면 size라고 이름을 만드는 편이 좋다.
	size_t size() const;		//size_t getLen() const;
	char* data() const;			//Contigous 컨테이너 식으로 만들었기에 가능
	
	void special(std::string);
	void show();			//관찰용 출력 함수

	bool operator== (const XString& rhs) const;

	friend std::ostream& operator<<(std::ostream& os, const XString& xs);
	friend std::istream& operator>>(std::istream& is, XString& xs);

private:
	size_t id{};	//객체 고유 넘버
	size_t len{};	//글자 수
	std::unique_ptr<char[]> p{};	//글자가 저장된 프리스토어 주소

	static size_t gid;				//전역변수 ->id값을 부여하기 위함
};