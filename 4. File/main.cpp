//File
#define NOMINMAX
#include <iostream>
#include <Windows.h>
#include <random>
#include <fstream>
#include <algorithm>
#include <array>
#include "save.h"
using namespace std;

//default_random_engine dre;
random_device rd;
default_random_engine dre{ rd() };
uniform_int_distribution<int> uid{ numeric_limits<int>::min(), numeric_limits<int>::max() };

int main()
{
	SetConsoleOutputCP(949);
	SetConsoleCP(949);

	/*
	//[문제] 임의의 값을 갖는 int 1000,0000 개 생성, int천만개.txt에 저장
	ofstream out{ "int천만개.txt" };
	for (int i = 0; i < 10000000; ++i) {
		out << uid(dre) << '\n';
	}
	*/
	
	/*
	//[문제] int천만개.txt 파일이 있을때 진짜 천만개인지 확인.-> 반드시 파일을 읽어야 함.
	ifstream in{ "int천만개.txt" };
	if (not in) {
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		exit(20260317);
	}
	int num;
	int min = numeric_limits<int>::max();
	size_t cnt{ };	//기본적으로는 비워놓으면 0으로 초기화 됨
	while (in >> num) {
		++cnt;
	}
	cout << "읽은 int 개수 - " << cnt << endl;
	*/
	
	/*
	//[문제] int천만개.txt 파일이 있을때 가장 작은값 확인
	ifstream in{ "int천만개.txt" };
	if (not in) {
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		exit(20260317);
	}
	array<int, 1000> a;
	for (int& num : a) in >> num;
	cout << "가장 작은 값 - " << *min_element(a.begin(), a.end()) << endl;
	
	//istream_iterator<int>는 istream에서 int값을 하나씩 읽어오는 반복자. 이걸 이용해 min_element의 범위를 지정해주면 된다. {}는 끝까지 읽어오라는 뜻.
	cout << "가장 작은 값 - " << *min_element(istream_iterator<int>{in}, {}) << endl;
	*/

	/*
	//[문제] int억개.txt에 랜덤 int값 1억개 저장.
	ofstream out{ "int억개.txt" };

	for (int i{}; i < 1'0000'0000; ++i)
		out << uid(dre) << ' ';
	*/
	
	//[문제] int억개.txt 파일이 있을 때, 1억개 맞는지 세보기
	//int 데이터 자체가 저장될땐 용량이 400MB정도 되지만 텍스트로 저장되면 자료형이 바뀌기 때문에 용량이 1GB정도로 저장된다.
	//[예상 문제] int 한개당 필요한 메모리 용량은 평균 몇 바이트인가?
	//이런 이유로 바이너리 파일을 사용하기도 한다.
	ifstream in{ "int억개.txt" };
	if (not in) {
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		return(20260317);
	}
	int num;
	int cnt{};
	while (in >> num) {
		++cnt;
	}
	cout << "읽은 int 개수 - " << cnt << endl;

	save("main.cpp");
	system("pause");
}
