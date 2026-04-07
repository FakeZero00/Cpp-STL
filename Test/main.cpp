#include <iostream>
#include <fstream>
#include <print>
#include <string>
#include <array>
#include <ranges>
using namespace std;

class Dog
{
private:
	string name; //[1, 15] - SSO로 저장 가능한 최대크기
	size_t id; //[1, 999'9999]

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		print(os, "[{:7}] {}", dog.id, dog.name);
		return os;
	}
};

//[문제] eclass에서 다운받은 바이너리 모드로 저장한 파일 "Dog 천만마리"에는
//Dog 객체 1000만개가 저장되어 있다.
//각 Dog 객체는 sizeof (Dog) 바이트를 그대로 stream의 write 함수를 사용하여 저장하였다.
//모든 객체를 읽어 메모리에 저장하라.

array <Dog, 1000'0000> dogs;

int main(void)
{
	ifstream in("Dog 천만마리", ios::binary);
	if (not in)
	{
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		return 2022182034;
	}

	in.read((char*)dogs.data(), sizeof(Dog) * dogs.size());
	cout << *(dogs.end() - 1) << endl;

	system("pause");
}
