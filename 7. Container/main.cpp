//Container
#include <iostream>
//#include <print>
#include <array>
#include <algorithm>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <numeric>
#include <list>
#include <iterator>
#include <ranges>
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
//array만 유일하게 스택에 데이터를 저장한다.

//vector는 동적 배열
//vector 24바이트에 저장하는 정보는
//첫번째 8바이트에는 현재 데이터가 실제로 저장되어 있는 데이터 개수
//두번째 8바이트에는 vector가 현재 할당한 메모리의 크기
//세번째 8바이트에는 vector가 가리키는 프리스토어 공간의 주소

//vector가 이미 할당되어 있는 메모리의 크기를 넘어서는 데이터를 저장해야할 경우,
//아예 새로운 공간을 할당받아서 그곳에 데이터를 복사, 혹은 이동해서 저장해서 포인터 주소가 가리키게 만든다.
//물론 이제 쓸모없어진 공간은 해제한다.
//이 행위의 복잡도는 O(1)인데 amortized(평균?) O(1)이라 부르며 시스템에서 메모리 할당하는 시간이 일정하지 않기때문에 그렇다.

//array만 데이터를 스택에 저장. 그 외엔 프리스토어에 저장.
//list는 .data()함수가 없다?
//data()는 Contigous하게 데이터를 저장하는 컨테이너에서만 사용할 수 있다.

//=========================기말 시작==========================
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

	//array<XString, 5> a {"333", "1", "55555", "22", "4444"};	//array는 스택에 저장
	//
	//cout << "a의 원소수 - " << a.size() << endl;
	//cout << "빈 컨테이너니? - " << boolalpha << a.empty() << endl;
	//cout << "최대 몇 개? - " << a.max_size() << endl;

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

	//==================vector 시작==================
	
	//vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };		//Release, Debug, x64, x32 마다 사용하는 용량이 달라진다. x64 기계라 8바이트 3개를 써서 24바이트가 된다.
	/*cout << "v의 크기 - " << sizeof(v) << endl;
	cout << "v의 주소 - " << addressof(v) << endl;
	cout << "v의 자료형 - " << typeid(v).name() << endl;*/

	//cout << "v의 원소 개수 - " << v.size() << endl;
	//cout << "v의 현재 할당 되어 있는 메모리 크기 - " << v.capacity() << endl;
	//cout << "v의 데이터 - " << v.data() << endl;	//프리스토어의 주소
	//cout << "v가 담을 수 있는 최대 int 개수 - " << v.max_size() << endl;

	//cout << "========원소 1개 추가========" << endl;

	//v.push_back(11);
	//cout << "v의 원소 개수 - " << v.size() << endl;
	//cout << "v의 현재 할당 되어 있는 메모리 크기 - " << v.capacity() << endl;	//VisualStudio는 1.5배씩 늘린다.
	//cout << "v의 데이터 - " << v.data() << endl;
	//cout << "v가 담을 수 있는 최대 int 개수 - " << v.max_size() << endl;	//deque 자료형이 더 많이 담을 수 있다.

	//vector<int> w;
	//w = v;
	//cout << "v의 원소 개수 - " << v.size() << endl;
	//cout << "v의 현재 할당 되어 있는 메모리 크기 - " << v.capacity() << endl;
	//cout << "v의 데이터 - " << v.data() << endl;	

	//cout << "========벡터 w========" << endl;

	//v.push_back(11);
	//cout << "v의 원소 개수 - " << w.size() << endl;
	//cout << "v의 현재 할당 되어 있는 메모리 크기 - " << w.capacity() << endl;
	//cout << "v의 데이터 - " << w.data() << endl;	//복사 후, 메모리는 새로 할당된다.

	/*v.clear();
	for(int n : v)
		cout << n << endl;

	cout << "v의 원소 개수 - " << v.size() << endl;
	cout << "v의 현재 할당 되어 있는 메모리 크기 - " << v.capacity() << endl;
	cout << "v의 데이터 - " << v.data() << endl;

	v.shrink_to_fit();

	cout << "v의 원소 개수 - " << v.size() << endl;
	cout << "v의 현재 할당 되어 있는 메모리 크기 - " << v.capacity() << endl;
	cout << "v의 데이터 - " << v.data() << endl;*/

	//[문제] 파일 "main.cpp"에 있는 모든 문자를(공백포함) 메모리에 저장하시오
	//저장한 문자를 출력하라. vector 외의 다른 컨테이너도 얼마든지 이 문제를 풀 수 있다.

	/*ifstream in{ "main.cpp" };
	if (not in)
	{
		cout << "파일을 확인해 주세요." << endl;
		return 2022182034;
	}*/

	//vector<char> v;
	//char c;
	//in >> noskipws;	//공백도 읽어오도록 설정
	//while (in >> c)
	//	v.push_back(c);

	//for (auto i = v.begin(); i != v.end(); ++i) {
	//	cout << *i;
	//	//cout << (char)7; //왜 소리나냐???
	//	this_thread::sleep_for(30ms);
	//}
	//cout << endl;

	//vector<char> v{ istreambuf_iterator<char>{in}, {} };	//벡터 생성시부터 입력 스트림 버퍼 이터레이터로 초기화. {}는 끝을 나타내는 디폴트 생성자.
	//copy(v.begin(), v.end(), ostream_iterator<char>{cout});	//벡터의 모든 요소를 출력 스트림 버퍼 이터레이터로 복사해서 출력. ostream_iterator는 출력 스트림에 데이터를 쓰는 이터레이터이다. cout은 출력 스트림 객체이다.

	//[문제] 키보드에서 단어를 그만 입력할때까지(Ctrl + Z, Enter) 메모리에 저장하라.
	//오름차순(ascending order)로 정렬하라.

	/*vector<string> v;
	string s;
	while(cin >> s)
		v.push_back(s);*/

	/*vector<string> v{ istream_iterator<string>{cin}, {} };

	sort(v.begin(), v.end());
	
	for (const string& str : v)
		cout << str << endl;*/

	//[문제] 키보드에서 입력한 모든 정수의 합계를 계산하여 출력하라.
	//cout << "합계 - " << accumulate(istream_iterator<int>{cin}, {}, 0LL) << endl;

	//lookup = true;
	/*XString x{ "2026년 4월 21일 화요일23교시입니다" };
	lookup = true;
	x.show();
	lookup = false;*/

	//벡터가 메모리를 확장하는 모습을 관찰해보자 - 컴파일러마다 다르다. 때문에 지금은  Visual Studio에서 관찰한 결과를 보여준다. -> 1.5배씩 확장
	/*vector<int> v;

	while (true) {
		v.push_back(1);

		if (v.capacity() == v.size()){
			cout << "v의 원소 개수 - " << v.size() << endl;
			cout << "v의 용량 - " << v.capacity() << endl;
			cout << "v의 데이터 - " << v.data() << endl;
		}
	}*/

	//XString의 메시지를 통해 벡터의 내부동작 알아보기
	//lookup = true;
	//vector<XString> v;
	//v.reserve(10);		//reserve는 공간만 확보하고, resize는 공간 확보와 원소도 같이 생성한다. 그래서 resize는 원소 액세스가 가능하지만 reserve는 그렇지 않다.

	//lookup = true;

	//for (int i = 0; i < 3; ++i) {
	//	cout << endl;
	//	cout << "원소를 push_back()으로 추가" << endl;
	//	//v.push_back(to_string(12340 + i).data());
	//	//v.emplace_back();	//내용물을 비워 놓으면 객체의 디폴트 생성자가 호출된다.
	//	v.emplace_back(to_string(12340 + i).data());		//emplace_back은 push_back과 달리, 객체를 생성할 때 필요한 인자를 전달해서 객체를 직접 생성한다. 이를 emplacing이라고 한다.
	//}

	//"main.cpp"의 소문자 개수를 다음과 같이 출력하라.
	//a - 10
	//b - 2
	//..z - 0

	//ifstream in{ "main.cpp" };
	//if (not in) {
	//	cout << "파일을 확인해 주세요." << endl;
	//	return 2022182034;
	//}

	//array<int, 26> a{};	// 알파벳 개수가 정해져 있으니 array를 써도 아무런 문제가 없다. map을 쓰는 건 좀 과하다.
	//char c;
	//while (in >> c) {
	//	if (islower(c))
	//		++a[c - 'a'];
	//}
	//
	//for (int i = 0; i < a.size(); ++i) {
	//	cout << static_cast<char>('a' + i) << " - " << a[i] << endl;
	//}

	/////////////////////////기말 범위 시작 //////////////////////////

	//[문제] v에서 3을 제거하라.
	/*vector<int> v{ 1, 2, 3, 4, 5 };

	for (int n : v)
		cout << n << ' ';
	cout << endl;*/

	//vector<int>::iterator new_end = remove(v.begin(), v.end(), 3);
	//v.erase(new_end, v.end());	//new_end ~ end() 범위를 쓰레기값이라고 바꾼다.
	//remove 함수가 컨테이너 내부의 값을 아예 바꿔버리는 건 vector 컨테이너의 권한을 무시하는 행동이다.
	//때문에 remove함수는 4, 5를 앞으로 옮기고 원래 5가 있던 자리를 데이터의 마지막 위치라고 알려주는 것이다.
	/*v.erase(remove(v.begin(), v.end(), 3), v.end());*/
	//C++ 20에서는
	//erase(v, 3);	//기존 C++의 문법을 파괴해서 다들 싫어하는 듯 하다...일단 전역 함수라는 명칭이 있다.
	/*cout << "현재 v의 용량 - " << v.capacity() << endl;
	cout << "현재 v의 원소 개수 - " << v.size() << endl;*/
	//remove할 때에는 반드시 erase도 같이 해야한다. erase-remove idiom(숙어)이라고 불리는 패턴이다.

	/*for(int n : v)
		cout << n << ' ';
	cout << endl;*/

	//[문제] v에서 "333"을 제거하라.
	//vector<XString> v{ "1", "22", "333", "4444", "55555" };

	//lookup = true;
	//erase(v, "333");
	//remove(v.begin(), v.end(), "333");
	//lookup = false;

	//for (const XString& s : v)
	//	cout << s << ' ';
	//cout << endl;

	//[문제] "333"을 "22" 다음에 추가해 주세요.
	/*list<XString> v{ "1", "22", "4444", "55555" };
	auto p = v.begin();

	lookup = true;*/
	//v.insert(++++v.begin(), "333");
	// 삽입은 리스트가 더 잘한다.
	//advance(v.begin(), 2); -> v.begin()은 래퍼런스가 아니라서 인자로 넣을 수 없다.
	/*advance(p, 2);
	v.emplace(p, "333");
	lookup = false;

	for (const XString& s : v)
		cout << s << ' ';
	cout << endl;*/

	//[문제] v에서 길이가 2글자인 element를 삭제하라.
	//vector<XString> v{ "1", "22", "4444", "55555", "33", "77"};

	/*auto new_end = remove_if(v.begin(), v.end(), [](const XString& x) {
		return x.size() == 2;
		});
	v.erase(new_end, v.end());*/

	/*auto Length2Comp = [](const XString& x) {
		return x.size() == 2;
		};
	erase_if(v, Length2Comp);

	for (const XString& s : v)
		cout << s << ' ';
	cout << endl;*/
	/*list<XString> cont{ "333", "1", "55555", "22", "4444" };
	vector<XString> cont2{ "333", "1", "55555", "22", "4444" };*/

	//[문제] 컨테이너를 길이 기준 오름차순으로 정렬하라
	/*sort(cont.begin(), cont.end(), [](const XString& a, const XString& b) {
		return a.size() < b.size();
		});*/
	//list는 연결리스트 방식으로 데이터를 저장하기 때문에 -연산자를 쓸 수 없어서 sort 함수를 그냥 쓸 수 없다. list 클래스의 sort 멤버 함수를 써야한다.
	/*lookup = true;
	cout << "list 컨테이너 정렬" << endl;
	cont.sort([](const XString& a, const XString& b) {
		return a.size() < b.size();
		});
	cout << "list 컨테이너 정렬 끝" << endl;
	cout << "vector 컨테이너 정렬" << endl;
	sort(cont2.begin(), cont2.end(), [](const XString& a, const XString& b) {
		return a.size() < b.size();
		});
	cout << "vector 컨테이너 정렬 끝" << endl;
	lookup = false;
	for (const XString& s : cont)
		cout << s << ' ';
	cout << endl;*/

	//[문제] 강의 저장 파일을 list<XString>에 저장하라.
	//길이 오름차순으로 정렬하라.
	//출력하라.

	//ifstream in{ "main.cpp" };
	//if (not in) return 20260429;
	//ifstream in2{ "main.cpp" };
	//if (not in) return 20260429;

	//
	//list<XString> words{ istream_iterator<XString>{in}, {} };	//벡터는 이렇게 불러오면 안된다. list만 이렇게...
	//vector<XString> cont2{};
	//cont2.reserve(2'0000);
	//cont2.assign(istream_iterator<XString>{in2}, {});	//벡터는 이렇게 불러와야 한다.
	////list<XString> cont{ cont2.begin(), cont2.end() };	//벡터에서 리스트로 옮기는 방법
	////cont2.clear();

	//auto LengthComp = [](const XString& a, const XString& b) {
	//	return a.size() < b.size();
	//	};

	//벡터 정렬 시간
	/*{
		auto b = chrono::high_resolution_clock::now();
		sort(cont2.begin(), cont2.end(), LengthComp);
		auto e = chrono::high_resolution_clock::now();
		cout << "vector 정렬 시간 - " << chrono::duration_cast<chrono::microseconds>(e - b).count() << "us" << endl;
	}
	{
		auto b = chrono::high_resolution_clock::now();
		cont.sort(LengthComp);
		auto e = chrono::high_resolution_clock::now();
		cout << "list 정렬 시간 - " << chrono::duration_cast<chrono::microseconds>(e - b).count() << "us" << endl;
	}*/
	//이동 생성은 list가 더 하지 않지만 어째선지 정렬이 Vector가 더 빠르다.
	//간단히 말하면 list는 데이터를 액세스 하기 위해 반드시 Sequantial하게 접근해야 하기 때문에 느리기 때문이다.

	//[문제] 이번엔 사전순으로 정렬하라. Lexicographical comparison
	//auto LexComp = [](const XString& a, const XString& b) {
	//	return lexicographical_compare(a.data(), a.data() + a.size(), b.data(), b.data() + b.size());	//문자열을 사전식으로 비교하는 함수
	//	};

	//words.sort(LexComp);
	//sort(cont2.begin(), cont2.end(), LexComp);

	//lookup = true;
	//for (const XString& xs : words)
	//	//xs.show();
	//	cout << xs << endl;
	//lookup = false;

	//cout << "전체 단어 개수 - " << cont2.size() << endl;
	////adjacent_find();	//인접한 원소 중에서 같은 원소가 있는지 찾아주는 함수.

	//words.unique();
	//auto newEnd = unique(cont2.begin(), cont2.end());
	//cont2.erase(newEnd, cont2.end()); //Vector에서는 이렇게 해야지 제대로 중복 삭제가 된다.
	//for (const XString& xs : cont2)
	//	cout << xs << endl;
	//cout << "서로 다른 단어의 개수는 몇 개인가? - " << cont2.size() << endl;

	//[문제] 중복을 제거하고 남은 단어 중에서 내가 찾는 단어가 알려달라. 없으면 없다, 있으면 몇 번째 단어라고 출력한다.
	/*while (true) {
		cout << "찾는 단어는? : ";
		XString xs;
		cin >> xs;

		auto target = find(cont2.begin(), cont2.end(), xs);
		if (target == cont2.end())
			cout << "단어가 없습니다." << endl;
		else
			cout << "단어가 있습니다.\n" << "위치: " << distance(cont2.begin(), target) + 1 << "번째 단어이다." << endl;
	}*/
	//distance의 인자를 반대로 바꾸면 words가 list에 저장됬을 때와 vector에 저장됬을 때의 결과가 다른 것을 알 수 있다.
	//vector는 contigous하게 데이터를 저장하기 때문에 범위를 반대로 하면 음수로 표시를 해 주지만
	//list는 연결 리스트 방식으로 데이터를 저장하기 때문에 distance 함수가 연산을 하는 것이 아닌 리스트를 앞으로(++) 순회하며 검사하며 거리를 count하기 때문에 숫자가 크게 나온다.
	//distance 함수는 컨테이너의 이터레이터 종류에 따라 다른 함수 동작을 하는데 이를 tag dispatching이라고 했었고 이제는 if constexpr로 구현한다.

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