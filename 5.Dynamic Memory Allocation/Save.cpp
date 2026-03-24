//c++에서 사용하지 말아야할 세 가지 자료형
//char*, T*, T[N]
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "Save.h"

void save(const std::string& fname)	//string&라고 쓰는 것으로 파라미터로 받은 변수의 값을 그대로 쓸 수 있도록 한다.(주소를 받아와서 사용)
{
	std::cout << "\"" << fname << "\"" << " 파일 저장합니다." << '\n';

	std::ifstream in{ fname };	//RAII
	if (not in) {
		std::cout << fname << "파일을 열 수 없습니다" << '\n';
		exit(20260303);
	}

	/*
	in >> std::noskipws;

	char c;
	while (in >> c) std::cout << c;
	*/

	//저장할 파일을 쓰기 모드로 열기
	std::ofstream out{ "2026.03.24 STL 2022182034.txt", std::ios::app };

	//저장한 날짜, 시간 기록
	auto now = std::chrono::system_clock::now();	//auto -> 함수의 반환값이 무엇인지 컴파일러가 알아서 추론하도록 하는 키워드
	using namespace std::chrono_literals;
	out << "=====================================\n";
	out << "저장시간 - " << now + 9h << '\n';
	//int year = static_cast<int> (now.year());
	out << "=====================================\n";
	out << '\n';

	//in에 있는 모든 글자를 out에 덧붙여 쓴다.
	std::copy(std::istreambuf_iterator<char>{in}, {}, std::ostream_iterator<char>{out});

}
