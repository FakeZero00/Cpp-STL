//DYNAMIC MEMORY ALLOCATION
#INCLUDE <IOSTREAM>
//#INCLUDE <ARRAY>
//#INCLUDE <NUMERIC>
//#INCLUDE <MEMORY>
#INCLUDE <FSTREAM>
#INCLUDE <STRING>
#INCLUDE <ALGORITHM>
#INCLUDE "SAVE.H"
USING NAMESPACE STD;

//================================================================

//동적 할당 -> 런타임시에 결정, 프리스토어에 할당 -> 주소로만 할당
//정적 할당 -> 컴파일시에 결정, 스택에 할당 -> 이름 사용 가능
//스마트 포인터를 통해 할당과 해제를 자동으로 할 수 있다.

//CALLABLE TYPE

//================================================================

/*
CLASS DOG
{
PUBLIC:
	DOG() { COUT << "DOG 생성" << ENDL; }
	~DOG() { COUT << "DOG 소멸" << ENDL; }
};
*/

/*
CLASS SMARTPTR
{
PUBLIC:
	SMARTPTR(DOG* P) : P{ P } {
		COUT << "SMARTPTR 생성 - 자원 P를 관리 시작" << ENDL;
	}
	~SMARTPTR() {
		DELETE P;	//자원 해제
		COUT << "SMARTPTR 소멸 - 자원 P를 관리 종료. 관리하던 P도 삭제" << ENDL;
	}
PRIVATE :
	DOG* P;
};
*/

INT MAIN()
{
	/*
	//[문제] 사용자의 원하는 수 만큼 INT를 저장할 수 있는 메모리를 확보하라.
	//메모리의 내용을 1부터 시작하는 정수로 채워라.
	//합계를 계산해서 화면에 출력하라.

	WHILE (TRUE) {
		SIZE_T SIZE;
		COUT << "필요한 정수의 개수를 입력하시오: ";
		CIN >> SIZE;

		//INT* PTR; C++에서는 포인터를 잘 안쓴다!

		UNIQUE_PTR<INT[]> PTR;	//RAII
		TRY {
			PTR.RESET(NEW INT[SIZE]);	// NEW로 메모리를 할당받음. UNIQUE_PTR이 알아서 해제해줌.
		}
		CATCH (EXCEPTION& E)
		{
			COUT << E.WHAT() << ENDL;
			EXIT(404);
		}

		IOTA(PTR.GET(), PTR.GET() + SIZE, 1);	// 1부터 시작하는 정수로 채우기

		LONG LONG SUM{};
		FOR (INT I = 0; I < SIZE; I++)
			SUM += PTR[I];

		LONG LONG SUM = ACCUMULATE(PTR.GET(), PTR.GET() + SIZE, 0LL);	//3번째 인자는 초기값. 초기값도 잘 자료형을 정해줘야 함. 0LL은 LONG LONG 타입의 0을 의미.

		COUT << "1부터 " << SIZE << "까지의 합계: " << SUM << ENDL;

		DELETE[] PTR;	//NEW, 포인터를 써서 데이터를 할당 받았을 때, DELTE 안하면 할당 해제가 되지 않음. 램 누수가 일어나서 점점 느려짐.
					//심지어 DELETE가 2번 발동될 경우 프로그램이 완전히 죽어버림.
}
	*/
	//DOG* P = NEW DOG;
	//RAII로 자원관리의 어려움을 해결할 수 있다.
	// 자원의 생명주기와 자원을 관리하는 객체 P의 생명주기를 일치시키면 가능하다.
	// 이게 가능한 이유는 C++언어에서 지역이 끝날때 지역 객체가 반드시 소멸됨을 보장한다. -> STACK-UNWINDING
	//UNIQUE_PTR<DOG[]> P{NEW DOG[10]};

	//[문제] "MAIN.CPP"에 있는 소문자를 대문자로 바꾼 파일, "MAIN.CPP"를 만들어라

	IFSTREAM IN("MAIN.CPP");
	OFSTREAM OUT("MAINUPPER.CPP");

	IF (NOT IN)
	{
		CERR << "파일을 열 수 없습니다." << ENDL;
		SYSTEM("PAUSE");
		EXIT(404);
	}

	TRANSFORM(ISTREAMBUF_ITERATOR<CHAR>{IN}, {}, OSTREAMBUF_ITERATOR<CHAR>{OUT},
		[](CHAR C) {
			RETURN TOUPPER(C);
		}
	);

	/*
	AUTO TOUPPER = [](CHAR C) {
		IF (ISLOWER(C))
			RETURN STATIC_CAST<CHAR>(TOUPPER(C));
		RETURN STATIC_CAST<CHAR>(C);
	};

	STRING LINE;
	WHILE (GETLINE(IN, LINE)){
		TRANSFORM(LINE.BEGIN(), LINE.END(), LINE.BEGIN(), TOUPPER);

		OUT << LINE << ENDL;
	}
	*/
	

	SAVE("MAIN.CPP");
	SYSTEM("PAUSE");
}
