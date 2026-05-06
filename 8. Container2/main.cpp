//Container2
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================

//container2
//STL을 떠받치는 3개의 기둥. 1. 컨테이너 2. 알고리즘 3. 이터레이터(반복자)
//알고리즘이 제공하는 함수에 컨테이너는 값을 제공해야 하는데 이때 컨테이너가 제공하는 값을 이터레이터로 제공한다.
//이터레이터를 이용해 알고리즘이 일을 하면 만약 새로운 자료구조가 들어와도 그 자료구조가 이터레이터를 제공한다면 알고리즘이 해당 자료구조에서도 작동할 수 있게 된다.

//vector는 데이터를 Contigous하게 저장하기 때문에 데이터 Access에 O(1) 시간이 걸린다. 또한 Contigous한 데이터는 CPU의 캐시에 저장될 때에 같이 불러와지기 때문에 Cache Hit가 많이 발생하여(캐시 적중률의 극대화) 이득이 있다.
//list는 데이터를 연결 리스트 방식으로 저장하기 때문에 임의의 장소에 데이터를 삽입하거나 삭제하는데 O(1) 시간이 걸려서 유리하지만. Page_Fault를 발생 시키기 쉬운 자료구조이기 때문에 데이터에 Access하는 속도 자체는 조금 느리다.
//deque는 vector와 list의 장점을 모두 가져오려 한 자료구조. 하지만 그만큼 단점도 같이 가지고 있다.

//================================================================

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

int main()
{
	{
		vector<int> v;
		while (true) {
			try {
				v.push_back(1);
			}
			catch (...) {	//...은 모든 예외를 잡는 catch문으로 ellipses라고 불린다.
				cout << "Vector 최대 원소 개수: " << v.size() << endl;
				break;
			}
		}
	}
	{
		deque<int> v;
		while (true) {
			try {
				v.push_back(1);
			}
			catch (...) {
				cout << "Deque 최대 원소 개수: " << v.size() << endl;
				break;
			}
		}
	}
	{
		list<int> v;
		while (true) {
			try {
				v.push_back(1);
			}
			catch (...) {
				cout << "list 최대 원소 개수: " << v.size() << endl;
				break;
			}
		}
	}

	save("main.cpp");
}