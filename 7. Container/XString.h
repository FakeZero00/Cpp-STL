//------------------------------------------------------
// STL을 더 잘 알아보려고 만든 자료구조(std::string)과 유사
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
	XString(XString&&); //noexept 안붙여도 됨 &&는 R-Value로 대입 연산자의 오른쪽에만 올 수 있는 연산자. 이동 생성자와 이동 대입 연산자를 구분하기 위해서 &&를 붙인다.
	XString& operator=(XString&&);


	size_t getLen() const;
	void special(std::string);

	friend std::ostream& operator<<(std::ostream& os, const XString& xs);

private:
	size_t id{};	//객체 고유 넘버
	size_t len{};	//글자 수
	std::unique_ptr<char[]> p{};	//글자가 저장된 프리스토어 주소

	static size_t gid;				//전역변수 ->id값을 부여하기 위함
};