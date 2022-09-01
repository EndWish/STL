//-----------------------------------------------------------------------------
//STRING - STL 내부 동작을 관찰하려고 만든 자원을 관리하는 클래스
//		 - std::string 동작 대부분을 직접 구현하며 STL 동작방식을 이해
// 
// 2022.3.30							
//-----------------------------------------------------------------------------

#include<iostream>
#include "STRING.h"

bool 관찰{ false };						// 관찰메시지 보려면 True
int STRING::gid{};						// class static 

STRING::STRING() : num{}, p{}, id{ ++gid }
{
	if (관찰)
		print("디폴트");
}

//,로 엮은 변수를 할당할때 순서가 보장되지 않아서 p를 따로 할당한다.
STRING::STRING(const char* s) : num{ strlen(s) }
{		//축소변환 : 메모리크기가 작아지면서 데이터가 작아직수 있으므로 size_t를 사용
	p = new char[num];
	id = ++gid;
	memcpy(p, s, num);	//memcpy는 고속DMA 를 수행

	if (관찰)
		print("생성자(*)");

	// 관찰메시티 on
}

STRING::~STRING() 
{
	// 관찰메시티 on
	if (관찰) {
		print("소멸자");
	}
	if (num) {
		delete[] p;
	}
}

STRING::STRING(const STRING& other) : id{ ++gid }, num{ other.num }
{
	p = new char[num];
	memcpy(p, other.p, num);
	if (관찰)
		print("복사생성");
}

STRING& STRING::operator=(const STRING& other)
{
	if (this == &other)
		return *this;

	if (num)
		delete[] p;

	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);

	if (관찰)
		print("복사할당");

}

// 2022. 4. 7 이동생성자/이동할당연산자
STRING::STRING(STRING&& other) noexcept : id { ++gid }
{
	num = other.num;
	p = other.p;

	other.num = 0;
	other.p = nullptr;

	if (관찰) {
		print("이동생성");
	}

}

STRING& STRING::operator=(STRING&& other) noexcept {
	if (this != &other) {
		if (num) {
			delete[] p;
		}

		num = other.num;
		p = other.p;

		other.num = 0;
		other.p = nullptr;
	}

	if (관찰) {
		print("이동할당");
	}

	return *this;
}

STRING STRING::operator+(const STRING& rhs) const
{
	STRING temp;	//임시객체를 만들어 더한후 리턴
	temp.num = num + rhs.num;
	temp.p = new char[temp.num];

	memcpy(temp.p, p, num);
	memcpy(temp.p + num, rhs.p, rhs.num);
	return temp;
}

void STRING::print(const char* s) const
{
	std::cout << s << " [" << id << "] 객체:" << this;
	if (num) {
		std::cout << " - 자원 : " << num << " 주소 : " << (void*)p;	// 캐릭터 포인터는고수준 입출력이라 문자열이 입력된다.
	}
	else {
		std::cout << " - 자원없음";
	}
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& os, const STRING& s)
{
	for (int i{}; i < s.num; ++i) {
		os << s.p[i];
	}
	return os;
}

// 2022. 4. 28 추가
std::istream& operator>>(std::istream& is, STRING& s)
{
	std::string str;
	is >> str;
	s = STRING(str.c_str());
	return is;
}
