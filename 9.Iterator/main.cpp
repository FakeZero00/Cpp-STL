//Iterator
#include <iostream>
#include <algorithm>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================

//================================================================

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

int main()
{
	XString xs{ "the quick brown fox jumps over the lazy dog" };	//영문에서 모든 알파벳을 포함하는 문장.
	sort(xs.begin(), xs.end());

	for (char c : xs)
		cout << c << '-';
	cout << endl;


	save("main.cpp");
}