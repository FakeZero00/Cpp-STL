#include <iostream>
#include <fstream>
#include <string>
#include <print>
#include <array>
#include <random>
using namespace std;

//[문제] 바이너리 모드로 저장한 파일 "Dog 천마리.bin"에는 아래와 같은 맴버를 갖는 Dog 객체
//1000개가 저장되어 있다.
//각 Dog 객체는 파일의 write 함수를 사용하여 sizeof(Dog) 바이트를 기록하였다.
//파일 크기는 40'000 바이트이다.
//메모리에 Dog 객체를 모두 읽어라.
//화면에 출력하라.

random_device rd;
default_random_engine dre{ rd() };
uniform_int_distribution<int> uid{ numeric_limits<int>::min(), numeric_limits<int>::max() };
uniform_int_distribution<int> uidNum{ 1, 9999 };
uniform_int_distribution<int> uidNameLen{ 10, 30 };
uniform_int_distribution<int> uidChar{ 'a', 'z' };

class Dog
{
public:
	Dog() : num{ uidNum(dre) }
	{
		size_t len = uidNameLen(dre);
		for (int i = 0; i < len; i++) {
			name += uidChar(dre);
		}
	}
	/*
	int getNum() const
	{
		return num;
	}
	*/

private:
	string name;		//[10, 30]글자 사이의 랜덤한 이름, 소문자로만
	int num;			//[1, 9999] == [1, 10000)

	friend ostream& operator<<(ostream& os, const Dog& dog)
	{
		print(os, "[{:3}] - {}", dog.num, dog.name);
		return os;
	}
};

int main(void)
{
	ifstream in{"Dog 천마리.bin", ios::binary};
	if(not in){ 
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		return 404;
	}

	array<Dog, 1000> dogs;
	in.read((char*)dogs.data(), sizeof(Dog) * dogs.size());

	for(const Dog& dog : dogs)
		cout << dog << endl;

	system("pause");
}
