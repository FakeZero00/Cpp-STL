//File
#define NOMINMAX
#include <iostream>
#include <Windows.h>
#include <random>
#include <fstream>
#include <algorithm>
#include <array>
#include <numeric>
#include <print>
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
	
	/*
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
	
	//[문제] 가장 작은 거, 가장 큰 거 값 구하기
	//이걸 min_element, max_element 둘 다 쓰려고 하면 istream_iterator<int>{in}가 이미 끝까지 읽어버렸기 때문에 사용할 수 없다.
	//그래서 minmax_element를 사용한다. 이걸 이용하면 한번에 가장 작은 값과 가장 큰 값을 구할 수 있다.
	auto [minV, maxV] = minmax_element(istream_iterator<int>{in}, {});
	cout << "가장 작은 값 - " << *minV << endl;
	cout << "가장 큰 값 - " << *maxV << endl;
	*/

	//==============================================================
	//위의 코드처럼 txt파일로 저장하는 경우 파일 내용이 엄청 커진다.
	//따라서 바이너리 모드로 파일을 기록하고 읽는 편이 빠르고 작아진다.
	//==============================================================

	//이 메모리 bit 전체를 그대로 파일에 기록하는 방식이 binary mode이다.
	//이번엔 1억개를 저장해 본다.

	//text와 바이너리 모드의 차이점
	/*
	ofstream out{ "int억개.bin", ios::binary };
	for (int i = 0; i < 1'0000'0000; ++i)
		out.write(reinterpret_cast<char*>(&i), sizeof(int));
	*/

	//[문제] int 1000개를 바이너리로 저장하고("int천개.bin"), int천개를 메모리로 읽어와라.
	ofstream out{ "int천개.bin", ios::binary };

	array<int, 1000> a;
	iota(a.begin(), a.end(), 1);	//a배열에 1부터 1000까지의 값을 채워넣는다.

	for (int num : a)
		print("{:8}", num);
	cout << endl;

	out.write(reinterpret_cast<char*>(&a[0]), sizeof(int) * a.size());
	//[문제] int천개.bin 파일이 있을 때, 해당 파일의 int값을 메모리로 읽어올 것

	save("main.cpp");
	system("pause");
}
