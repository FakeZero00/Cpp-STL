//Container
#include <iostream>
//#include <string>
//#include <print>
#include <array>
//#include <algorithm>
#include <fstream>
#include "XString.h"
#include "Save.h"
using namespace std;

//================================================================

//container
//[String]
//string은 15글자까지는 스택에 저장되고 그 이상은 프리스토어에 저장되어 포인터로 프리스토어의 주소를 가리킨다.
//unique_ptr은 포인터에 저장된 주소를 독점해야하는데. 복사하게 되면 독점이 풀리게 되므로 복제가 금지되어 있다. 그래서 복사 생성자와 복사 대입 연산자가 삭제되어 있다. -> 복사 생성자와 복사 대입 연산자가 삭제된 클래스는 복사가 금지된 클래스라고도 불린다. -> Singleton은 생성자를 삭제하는 놈으로 사용하지 않는 편이 좋다.

//string s{"2026년"};
//->string t = move(s);
//->string t = static_cast<string&&>(s);
//->string t{static_cast<string&&>(s)};

//xvalue : 이미 사라진 value
//expired value, 즉, xvalue에서 뭔가를 가져오는 건 undefined behavior이다.

//컨테이너란?
//Containers are objects that store other objects. - 컨테이너는 다른 객체를 저장하는 객체이다. 
// 오브젝트란? 메모리에 올려진 클래스의 인스턴스
//STL의 컨테이너는 크게 3가지 종류로 나눈다.
//1. Sequence containers : vector, list, deque(덱), array, forward_list
//2. Associative containers : set, map	-> 해싱을 위해 만들어진 구조. 키값을 기준으로 자동으로 정렬함.
//3. Unordered associative containers : unordered_set, unordered_multiset, unordered_map, unordered_multimap -> 2번보다 더 빨리 해싱할 수 있는 구조.

//Homogeneous(동질적인, 균질한) -> C++은 같은 자료형을 저장한다.
//Polymorphic(다형성) -> 컨테이너는 객체의 타입을 몰라도 저장할 수 있다. (템플릿)

//array의 입력 타입으로 element type Must be MoveConstructible and MoveAssignable. 라고 써있지만 MoveConstructible가 안되면 복사 생성자와 복사 대입 연산자가 사용된다.
//모든 컨테이너는 iterator(반복자)를 제공한다. -> 컨테이너의 요소에 접근할 수 있는 방법을 제공한다.
//lexicographically(사전식으로)

//================================================================

extern bool lookup; //special()에서 관찰 여부를 결정하는 전역 변수

int main()
{
	//XString{ "나는 이름이 없지롱" };
	//array <XString, 3> a = { "12345", "안녕하세요", "Hello, World" };
	//XString s{ "2026년 4월 8일 수요일" }; // -> 21글자.
	//XString t = s;	//s 안에 복사가 금지된 변수가 있어서 복사 생성자가 금지되어 있어 복사되지 않는다. -> Singleton은 생성자를 삭제하는 놈으로 사용하지 않는 편이 좋다.
	////프리 스토어에 저장된 15글자가 넘는 문자열의 포인터를 t가 s에서 가져와서 t의 포인터에 할당한다. s는 더 이상 문자열을 가리키지 않게 된다.

	//cout << "s - " << s << endl;
	//cout << "t - " << t << endl;

	//lookup = true;	//관찰 시작
	//XString s{ "Ready OK" };
	//cout << s << endl;

	//array<XString, 5> a = { "333", "1", "55555", "4444", "22" };

	//lookup = true;
	////길이 기준 오름차순 정렬
	//sort(a.begin(), a.end(), [](const XString& a, const XString& b) {	//래퍼런스로 바꾸는 것 잊지 말기. 적어도 주소만 복사하기
	//	return a.getLen() < b.getLen();
	//	});
	//lookup = false;

	//for (const XString& s : a)
	//	cout << s << endl;

	array<XString, 5> a {"333", "1", "55555", "22", "4444"};	//array는 스택에 저장
	
	cout << "a의 원소수 - " << a.size() << endl;
	cout << "빈 컨테이너니? - " << boolalpha << a.empty() << endl;
	cout << "최대 몇 개? - " << a.max_size() << endl;

	//at operator[] front back data
	//cout << "처음 원소 - " << *a.begin() << endl;
	//cout << "처음 원소 - " << a.front() << endl;	//리턴값이 래퍼런스라서 복사본이 안생김
	//cout << "처음 원소 - " << a[0] << endl;
	//cout << "처음 원소 - " << *(a.data() + a.size() * 0) << endl;
	//cout << "마지막 원소 - " << *(a.end()-1) << endl;
	//cout << "마지막 원소 - " << a.back() << endl;
	//cout << "마지막 원소 - " << a[a.size() - 1] << endl;

	//array는 []을 encapsulation 한 것이다.
	//[]은 보안적으로 매우 위험한 연산자이다!
	//때문에 at을 사용한다. at은 범위를 벗어나면 예외를 던진다.

	//array<int, 5> b{ 0, 1, 2, 3, 4 };

	//while (true) {
	//	cout << "찾을 원소는? : ";
	//	int num;
	//	cin >> num;

	//	//cout << "찾은 값 : " << b[num] << endl;		//<- 경계 밖으로 나가도 리턴이 있다...
	//	try {
	//		cout << "찾은 값 : " << b.at(num) << endl;		//그런데 at은 속도가 느리다...
	//	}
	//	catch (std::exception& e) {
	//		cout << e.what() << endl;
	//		cout << "유효 숫자는 - [0, 4]" << endl;
	//	}
	//}

	//for (auto i = a.begin(); i != a.end(); ++i) {
	//	//post increment는 객체를 복사해서 반환하기 때문에 pre increment로 바꿔주는 것이 좋다. -> post increment는 객체가 복사되어야 하기 때문에 이동 생성자나 복사 생성자가 필요하다. -> pre increment는 객체가 복사되지 않고 주소만 이동하기 때문에 이동 생성자나 복사 생성자가 필요하지 않다.
	//	cout << *i << endl;
	//	
	//}



	//[문제] 다음 코드가 잘 실행되게 하자
	//"main.cpp" 에 있는 단어들을 XString으로 읽어오자

	/*ifstream in{ "main.cpp" };
	if (not in) {
		cout << "파일을 확인해 주세요." << endl;
		return 2022182034;
	}

	XString s;
	while (in >> s)
		cout << s << endl;*/

	save("main.cpp");
	//system("pause");
}

/* 모던 C++이전의 최대 속도 알고리즘 상태(이동 생성자 없음)
[      6] - 복사생성 객체: 0X00E7A84FFA30 글자: 0X021856D33150 - 글자 개수: 1      내용: 1
[      2] - 복사할당 객체: 0X00E7A84FFBD8 글자: 0X021856D33180 - 글자 개수: 3      내용: 333
[      1] - 복사할당 객체: 0X00E7A84FFBC0 글자: 0X021856D33280 - 글자 개수: 1      내용: 1
[      6] - 소멸     객체: 0X00E7A84FFA30 글자: 0X021856D33150 - 글자 개수: 1      내용: 1
[      7] - 복사생성 객체: 0X00E7A84FFA30 글자: 0X021856D33270 - 글자 개수: 5      내용: 55555
[      3] - 복사할당 객체: 0X00E7A84FFBF0 글자: 0X021856D33140 - 글자 개수: 5      내용: 55555
[      7] - 소멸     객체: 0X00E7A84FFA30 글자: 0X021856D33270 - 글자 개수: 5      내용: 55555
[      8] - 복사생성 객체: 0X00E7A84FFA30 글자: 0X021856D332B0 - 글자 개수: 4      내용: 4444
[      4] - 복사할당 객체: 0X00E7A84FFC08 글자: 0X021856D33110 - 글자 개수: 5      내용: 55555
[      3] - 복사할당 객체: 0X00E7A84FFBF0 글자: 0X021856D331D0 - 글자 개수: 4      내용: 4444
[      8] - 소멸     객체: 0X00E7A84FFA30 글자: 0X021856D332B0 - 글자 개수: 4      내용: 4444
[      9] - 복사생성 객체: 0X00E7A84FFA30 글자: 0X021856D33260 - 글자 개수: 2      내용: 22
[      5] - 복사할당 객체: 0X00E7A84FFC20 글자: 0X021856D33120 - 글자 개수: 5      내용: 55555
[      4] - 복사할당 객체: 0X00E7A84FFC08 글자: 0X021856D33240 - 글자 개수: 4      내용: 4444
[      3] - 복사할당 객체: 0X00E7A84FFBF0 글자: 0X021856D331D0 - 글자 개수: 3      내용: 333
[      2] - 복사할당 객체: 0X00E7A84FFBD8 글자: 0X021856D33250 - 글자 개수: 2      내용: 22
[      9] - 소멸     객체: 0X00E7A84FFA30 글자: 0X021856D33260 - 글자 개수: 2      내용: 22
1
22
333
4444
55555
*/

/* 이동생성자 추가 후 최대 속도 알고리즘 상태
[      6] - 이동생성 객체: 0X007422AFF730 글자: 0X01B1728831B0 - 글자 개수: 1      내용: 1
[      2] - 이동할당 객체: 0X007422AFF8C8 글자: 0X01B172883140 - 글자 개수: 3      내용: 333
[      1] - 이동할당 객체: 0X007422AFF8B0 글자: 0X01B1728831B0 - 글자 개수: 1      내용: 1
[      6] - 소멸     객체: 0X007422AFF730 글자: 0X000000000000 - 글자 개수: 0      내용:
[      7] - 이동생성 객체: 0X007422AFF730 글자: 0X01B172883130 - 글자 개수: 5      내용: 55555
[      3] - 이동할당 객체: 0X007422AFF8E0 글자: 0X01B172883130 - 글자 개수: 5      내용: 55555
[      7] - 소멸     객체: 0X007422AFF730 글자: 0X000000000000 - 글자 개수: 0      내용:
[      8] - 이동생성 객체: 0X007422AFF730 글자: 0X01B172883260 - 글자 개수: 4      내용: 4444
[      4] - 이동할당 객체: 0X007422AFF8F8 글자: 0X01B172883130 - 글자 개수: 5      내용: 55555
[      3] - 이동할당 객체: 0X007422AFF8E0 글자: 0X01B172883260 - 글자 개수: 4      내용: 4444
[      8] - 소멸     객체: 0X007422AFF730 글자: 0X000000000000 - 글자 개수: 0      내용:
[      9] - 이동생성 객체: 0X007422AFF730 글자: 0X01B172883290 - 글자 개수: 2      내용: 22
[      5] - 이동할당 객체: 0X007422AFF910 글자: 0X01B172883130 - 글자 개수: 5      내용: 55555
[      4] - 이동할당 객체: 0X007422AFF8F8 글자: 0X01B172883260 - 글자 개수: 4      내용: 4444
[      3] - 이동할당 객체: 0X007422AFF8E0 글자: 0X01B172883140 - 글자 개수: 3      내용: 333
[      2] - 이동할당 객체: 0X007422AFF8C8 글자: 0X01B172883290 - 글자 개수: 2      내용: 22
[      9] - 소멸     객체: 0X007422AFF730 글자: 0X000000000000 - 글자 개수: 0      내용:
1
22
333
4444
55555
"main.cpp" 파일 저장합니다.
*/